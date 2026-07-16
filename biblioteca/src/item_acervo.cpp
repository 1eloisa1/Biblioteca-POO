#include "item_acervo.hpp"
#include <iostream>

ItemAcervo::~ItemAcervo() {
    std::cout << "[Destrutor Base] ~ItemAcervo limpo para: " << titulo << "\n";
}

void ItemAcervo::exibir() const {
    std::cout << "[" << codigo << "] " << titulo;
}