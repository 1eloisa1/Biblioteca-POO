cmake_minimum_required(VERSION 3.20)
project(biblioteca CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opções de compilação para Debug (com Address Sanitizer)
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
    add_compile_options(-Wall -Wextra -fsanitize=address,undefined -g)
    add_link_options(-fsanitize=address,undefined)
endif()

# Executável principal do sistema
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

# ==========================================
# Bloco de Configuração do Catch2 (Questão 4) 
# ==========================================
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(testes 
    tests/test_tp2.cpp 
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/usuario.cpp
    src/emprestimo.cpp
    src/biblioteca.cpp
)
target_include_directories(testes PRIVATE src)
target_link_libraries(testes PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(testes)