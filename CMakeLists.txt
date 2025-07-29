cmake_minimum_required(VERSION 3.22)

project(ppmini_db LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_TEST_FOLDER "${CMAKE_SOURCE_DIR}/playground")

option(TEST "Build tests without GoogleTest" OFF)


if(TEST)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/373af2e3df71599b87a40ce0e37164523849166b.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()

add_library(internals 
    src/pager.cpp
)

target_include_directories(internals PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(prod cli/CLI.cpp)
target_link_libraries(prod PRIVATE internals)
set_target_properties(prod PROPERTIES OUTPUT_NAME CLI_${PROJECT_NAME})


if(EXISTS "${MY_TEST_FOLDER}/main.cpp" AND CMAKE_BINARY_DIR STREQUAL MY_TEST_FOLDER)

add_executable(test playground/main.cpp)
target_link_libraries(test PRIVATE internals)
set_target_properties(test PROPERTIES OUTPUT_NAME test_${PROJECT_NAME})

endif()

