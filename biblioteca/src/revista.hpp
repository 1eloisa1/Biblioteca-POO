#pragma once
#include "item_acervo.hpp" 

class Revista : public ItemAcervo {
private:
    int edicao;

public:
    Revista(std::string t, std::string c, int ed);
    ~Revista() override = default;

    float calcular() const override;
    void exibir() const override;

    std::string type_name() const override { return "Revista"; }
    json to_json() const override;
    static Revista from_json(const json& j);
};