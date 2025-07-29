cmake_minimum_required(VERSION 3.22)
project(ppmini_db LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_library(internals 
    src/pager.cpp
)

add_executable(prod cli/CLI.cpp)
add_executable(test main_playground/main.cpp)

target_include_directories(internals PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(prod PRIVATE internals)
target_link_libraries(test PRIVATE internals)

set_target_properties(prod PROPERTIES OUTPUT_NAME CLI_${PROJECT_NAME})
set_target_properties(test PROPERTIES OUTPUT_NAME test_${PROJECT_NAME})