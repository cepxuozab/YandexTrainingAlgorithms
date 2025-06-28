cmake_minimum_required(VERSION 3.20)
project(Template)

add_executable(main main.cpp)

# Устанавливаем стандарт C++
target_compile_features(main PUBLIC cxx_std_23)

# Добавляем -lstdc++exp, если используем GCC или Clang с libstdc++
target_link_libraries(main PRIVATE stdc++exp)

# DEBUG/RELEASE флаги
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(main PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(main PUBLIC DEBUG=0)
endif()

# Флаги компилятора
if (MSVC)
    target_compile_options(main PRIVATE /W4 /WX)
else ()
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
