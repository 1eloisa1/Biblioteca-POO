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

    int get_edicao() const { return edicao; }
    std::string type_name() const override { return "Revista"; }
};

// Q4 (A): Funções Não-Intrusivas no padrão nlohmann/json
void to_json(json& j, const Revista& r);
void from_json(const json& j, Revista& r);