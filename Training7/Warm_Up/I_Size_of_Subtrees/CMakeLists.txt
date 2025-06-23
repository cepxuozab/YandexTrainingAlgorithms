cmake_minimum_required(VERSION 3.25...4.0)
project(task LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

# cmake/LibStdCxxExp.cmake

function(EnableLibStdCxxExp target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        include(CheckCXXSymbolExists)
        unset(USES_LIBSTDCXX CACHE)
        check_cxx_symbol_exists(__GLIBCXX__ "bits/c++config.h" USES_LIBSTDCXX)
        if(USES_LIBSTDCXX)
            message(STATUS "Detected libstdc++. Linking ${target} with stdc++exp.")
            target_link_libraries(${target} PRIVATE stdc++exp)
        else()
            message(STATUS "Not using libstdc++, skipping stdc++exp linking.")
        endif()
    else()
        message(STATUS "Compiler is not GCC or Clang. Skipping stdc++exp linkage.")
    endif()
endfunction()


add_executable(${PROJECT_NAME} main.cpp)
EnableLibStdCxxExp(${PROJECT_NAME})