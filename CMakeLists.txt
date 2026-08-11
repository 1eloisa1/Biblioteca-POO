cmake_minimum_required(VERSION 3.20)
project(biblioteca CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opção de Sanitizer (Address por padrão, ThreadSanitizer opcional via -DENABLE_TSAN=ON)
option(ENABLE_TSAN "Habilitar ThreadSanitizer" OFF)

if(ENABLE_TSAN)
    add_compile_options(-Wall -Wextra -fsanitize=thread -g)
    add_link_options(-fsanitize=thread)
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
        add_compile_options(-Wall -Wextra -fsanitize=address,undefined -g)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_executable(biblioteca
    src/main.cpp
    src/biblioteca.cpp
    src/usuario.cpp
    src/emprestimo.cpp
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/registry.cpp
    src/repositorio.cpp
    src/excecoes.cpp
    src/emprestavel.cpp
)
target_include_directories(biblioteca PRIVATE src)
target_link_libraries(biblioteca PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(testes_tp3
    tests/test_tp3.cpp
    src/biblioteca.cpp
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/usuario.cpp
    src/emprestimo.cpp
    src/registry.cpp
    src/repositorio.cpp
    src/excecoes.cpp
    src/emprestavel.cpp
)
target_include_directories(testes_tp3 PRIVATE src)
target_link_libraries(testes_tp3 PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

include(CTest)
include(Catch)
catch_discover_tests(testes_tp3)

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
    src/registry.cpp
    src/repositorio.cpp
    src/excecoes.cpp
    src/emprestavel.cpp
)

target_include_directories(gui PRIVATE src)
target_link_libraries(gui PRIVATE Qt6::Widgets nlohmann_json::nlohmann_json)