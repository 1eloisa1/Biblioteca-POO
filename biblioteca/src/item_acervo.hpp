#pragma once
#include <string>
#include <iostream>

class ItemAcervo {
protected:
    std::string titulo;
    std::string codigo;

public:
    ItemAcervo(std::string t, std::string c) 
        : titulo(std::move(t)), codigo(std::move(c)) {}

    virtual ~ItemAcervo();

    virtual float calcular() const = 0; 
    virtual void exibir() const;
};