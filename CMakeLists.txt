cmake_minimum_required(VERSION 3.22)

project(plus_mini_db LANGUAGES CXX)

include_directories(include/plusmini_db)

add_executable(${PROJECT_NAME} src/plusmini_db.cpp)

