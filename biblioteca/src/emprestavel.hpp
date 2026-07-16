#pragma once

class Emprestavel {
public:
    virtual ~Emprestavel() = default;

    virtual void emprestar() = 0;
    virtual void devolver() = 0;
    virtual bool estaEmprestado() const = 0;
};