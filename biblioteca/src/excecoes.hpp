#pragma once
#include <stdexcept>
#include <string>

// Q2 (A) Exceção Base do Domínio
class ErroDominio : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Exceções Específicas
class ItemNaoEncontradoException : public ErroDominio {
public:
    explicit ItemNaoEncontradoException(const std::string& msg)
        : ErroDominio("Item nao encontrado: " + msg) {}
};

class ValidacaoInvalidaException : public ErroDominio {
public:
    explicit ValidacaoInvalidaException(const std::string& msg)
        : ErroDominio("Dados invalidos: " + msg) {}
};