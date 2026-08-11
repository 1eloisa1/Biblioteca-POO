#pragma once
#include <stdexcept>
#include <string>

// Q2 (A): Exceção Base do Domínio derivada de std::runtime_error
class ErroDominio : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Q2 (A): Exceções Específicas derivadas da Base
class ItemNaoEncontradoException : public ErroDominio {
public:
    explicit ItemNaoEncontradoException(const std::string& msg);
};

class ValidacaoInvalidaException : public ErroDominio {
public:
    explicit ValidacaoInvalidaException(const std::string& msg);
};