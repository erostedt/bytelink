#include "morphology.hpp"
#include <cassert>

using StrElem = std::vector<std::vector<bool>>;
StrElem make_grid(size_t rows, size_t cols)
{
    std::vector<std::vector<bool>> grid{};
    for (size_t r{0}; r < rows; r++)
    {
        grid.push_back(std::vector<bool>(cols, true));
    }
    return grid;
}

BinImg eroded(const BinImg &binimg, const StrElem &strelem)
{
    int s_rows = static_cast<int>(strelem.size());
    int s_cols = static_cast<int>(strelem.at(0).size());
    assert(s_rows % 2 == 1);
    assert(s_cols % 2 == 1);

    int i_rows = static_cast<int>(binimg.height());
    int i_cols = static_cast<int>(binimg.width());
    BinImg eroded_image(i_cols, i_rows);
    for (int r{s_rows / 2}; r < i_rows - s_rows / 2; r++)
    {
        for (int c{s_cols / 2}; c < i_cols - s_cols / 2; c++)
        {
            bool flag = true;
            for (int dr{-s_rows / 2}; dr <= s_rows / 2; dr++)
            {
                for (int dc{-s_cols / 2}; dc <= s_cols / 2; dc++)
                {
                    int ir = r + dr;
                    int ic = c + dc;
                    int sr = s_rows / 2 + dr;
                    int sc = s_cols / 2 + dc;
                    if (!binimg.at(ir, ic) && strelem.at(sr).at(sc))
                    {
                        flag = false;
                    }
                }
            }
            eroded_image.set(r, c, flag);
        }
    }
    return eroded_image;
}
BinImg dilated(const BinImg &binimg, const StrElem &strelem)
{
    int s_rows = static_cast<int>(strelem.size());
    int s_cols = static_cast<int>(strelem.at(0).size());
    assert(s_rows % 2 == 1);
    assert(s_cols % 2 == 1);

    int i_rows = static_cast<int>(binimg.height());
    int i_cols = static_cast<int>(binimg.width());
    BinImg dilated_image(i_cols, i_rows);
    for (int r{s_rows / 2}; r < i_rows - s_rows / 2; r++)
    {
        for (int c{s_cols / 2}; c < i_cols - s_cols / 2; c++)
        {
            bool flag = false;
            for (int dr{-s_rows / 2}; dr < s_rows / 2; dr++)
            {
                for (int dc{-s_cols / 2}; dc < s_cols / 2; dc++)
                {
                    int ir = r + dr;
                    int ic = c + dc;
                    int sr = s_rows / 2 + dr;
                    int sc = s_cols / 2 + dc;
                    if (binimg.at(ir, ic) && strelem.at(sr).at(sc))
                    {
                        flag = true;
                    }
                }
            }
            dilated_image.set(r, c, flag);
        }
    }
    return dilated_image;
}
BinImg closed(const BinImg &binimg, const StrElem &strelem)
{
    return eroded(dilated(binimg, strelem), strelem);
}

BinImg opened(const BinImg &binimg, const StrElem &strelem)
{
    return dilated(eroded(binimg, strelem), strelem);
}
