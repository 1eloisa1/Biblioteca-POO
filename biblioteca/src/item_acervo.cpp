#include "item_acervo.hpp"
#include <iostream>

void ItemAcervo::exibir() const {
    std::cout << "[" << codigo << "] " << titulo;
}

json ItemAcervo::to_json() const {
    return json{
        {"type", type_name()},
        {"codigo", codigo},
        {"titulo", titulo}
    };
}
