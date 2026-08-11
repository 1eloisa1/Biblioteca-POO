cmake_minimum_required(VERSION 3.20)
project(biblioteca CXX)

# Exigido pelo TP3: Suporte ao C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opções de compilação Debug + Address Sanitizer
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    add_compile_options(-Wall -Wextra -fsanitize=address,undefined -g)
    add_link_options(-fsanitize=address,undefined)
endif()

# Q4 (A): nlohmann/json via FetchContent
include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Executável principal (Q1 a Q4)
add_executable(biblioteca
    src/main.cpp 
    src/biblioteca.cpp
    src/usuario.cpp
    src/emprestimo.cpp
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
)
target_include_directories(biblioteca PRIVATE src)
target_link_libraries(biblioteca PRIVATE nlohmann_json::nlohmann_json)

# Q5 (A): Configuração do Catch2 v3
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Executável dos testes do TP3 (Q5)
add_executable(testes_tp3
    tests/test_tp3.cpp
    src/biblioteca.cpp
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/usuario.cpp
    src/emprestimo.cpp
)
target_include_directories(testes_tp3 PRIVATE src)
target_link_libraries(testes_tp3 PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

include(CTest)
include(Catch)
catch_discover_tests(testes_tp3)

# Q6: Suporte ao Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(gui
    src/gui_main.cpp
    src/janela.cpp
    src/janela.hpp
    src/biblioteca.cpp
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/usuario.cpp
    src/emprestimo.cpp
)

target_include_directories(gui PRIVATE src)
target_link_libraries(gui PRIVATE Qt6::Widgets nlohmann_json::nlohmann_json)