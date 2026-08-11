#include "revista.hpp" 
#include <iostream>

Revista::Revista(std::string t, std::string c, int ed)
    : ItemAcervo(std::move(t), std::move(c)), edicao(ed) {}

float Revista::calcular() const { return 1.00f; }

void Revista::exibir() const {
    std::cout << "[Revista] Edicao " << edicao << ": " << titulo << "\n";
}

json Revista::to_json() const {
    json j = ItemAcervo::to_json();
    j["edicao"] = edicao;
    return j;
}

Revista Revista::from_json(const json& j) {
    return Revista(
        j.at("titulo").get<std::string>(),
        j.at("codigo").get<std::string>(),
        j.at("edicao").get<int>()
    );
}