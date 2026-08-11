#include "revista.hpp"
#include <iostream>

Revista::Revista(std::string t, std::string c, int ed)
    : ItemAcervo(std::move(t), std::move(c)), edicao(ed) {}

float Revista::calcular() const { return 1.00f; }

void Revista::exibir() const {
    std::cout << "[Revista] Edicao " << edicao << ": " << titulo << "\n";
}

// Q4 (A): Implementação Não-Intrusiva
void to_json(json& j, const Revista& r) {
    j = json{
        {"type", r.type_name()},
        {"codigo", r.get_codigo()},
        {"titulo", r.get_titulo()},
        {"edicao", r.get_edicao()}
    };
}

void from_json(const json& j, Revista& r) {
    r = Revista(
        j.at("titulo").get<std::string>(),
        j.at("codigo").get<std::string>(),
        j.at("edicao").get<int>()
    );
}