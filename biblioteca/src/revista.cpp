#include "revista.hpp" 
#include <iostream>

Revista::Revista(std::string t, std::string c, int ed)
    : ItemAcervo(std::move(t), std::move(c)), edicao(ed) {}

Revista::~Revista() {
    std::cout << "[Destrutor Derivada] ~Revista destruida.\n";
}

float Revista::calcular() const {
    return 1.00f;
}

void Revista::exibir() const {
    std::cout << "[Revista] Edicao " << edicao << ": " << titulo << "\n";
}