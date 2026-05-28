cmake_minimum_required(VERSION 3.20)
project(biblioteca CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    add_compile_options(-Wall -Wextra -fsanitize=address,undefined -g)
    add_link_options(-fsanitize=address,undefined)
endif()

add_executable(biblioteca
    src/main.cpp
    src/livro.cpp
    src/usuario.cpp
    src/emprestimo.cpp
    src/biblioteca.cpp
)

target_include_directories(biblioteca PRIVATE src)