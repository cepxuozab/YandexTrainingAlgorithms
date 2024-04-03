cmake_minimum_required(VERSION 3.27)
project(Template)

set(CMAKE_CXX_STANDARD 23)

add_executable(Template  main.cpp)

if(MSVC)
    target_compile_options(Template PRIVATE /W4 /WX)
else()
    target_compile_options(Template PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
