#pragma once
#include "item_acervo.hpp" 

class Revista : public ItemAcervo {
private:
    int edicao;

public:
    Revista(std::string t, std::string c, int ed);
    ~Revista() override;

    float calcular() const override;
    void exibir() const override;
};