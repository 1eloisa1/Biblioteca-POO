#include "excecoes.hpp"

// Q2 (A): Implementação dos construtores das exceções específicas
ItemNaoEncontradoException::ItemNaoEncontradoException(const std::string& msg)
    : ErroDominio("Item nao encontrado: " + msg) {}

ValidacaoInvalidaException::ValidacaoInvalidaException(const std::string& msg)
    : ErroDominio("Dados invalidos: " + msg) {}