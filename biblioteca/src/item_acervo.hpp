#pragma once
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include "registry.hpp"

using json = nlohmann::json;

// Q1 (B) Integrando CRTP na base do acervo
class ItemAcervo : public Counted<ItemAcervo> {
protected:
    std::string titulo;
    std::string codigo;

public:
    ItemAcervo(std::string t, std::string c) 
        : titulo(std::move(t)), codigo(std::move(c)) {}

    virtual ~ItemAcervo() override = default;

    virtual float calcular() const = 0; 
    virtual void exibir() const;

    std::string get_titulo() const { return titulo; }
    std::string get_codigo() const { return codigo; }

    virtual std::string type_name() const = 0;
    virtual json to_json() const;
};