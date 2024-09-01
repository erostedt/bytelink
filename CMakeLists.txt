cmake_minimum_required(VERSION 3.25)

project(bytelink)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DEMOS_PATH ./demos)
set(SRC_PATH ./src)
set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB bytelink_demos ${DEMOS_PATH}/*)
foreach(bytelink_demo ${bytelink_demos})
  get_filename_component(demo_name ${bytelink_demo} NAME_WE)
  file(GLOB sources ${bytelink_demo}/*.cpp)
  add_executable(${demo_name} ${sources})
endforeach()
