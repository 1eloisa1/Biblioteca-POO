#pragma once
#include "item_acervo.hpp"
#include "emprestavel.hpp"

class Livro final : public ItemAcervo, public Emprestavel {
private:
    std::string author_;
    int available_copies_;

public:
    Livro(std::string t_title, std::string t_author, std::string t_isbn, int t_copies);
    ~Livro() override = default;

    float calcular() const override;
    void exibir() const override;

    void emprestar() override;
    void devolver() override;
    bool estaEmprestado() const override;

    std::string title() const;
    std::string author() const;
    std::string isbn() const;
    int available_copies() const;
    bool loan_copy();
    void return_copy();

    std::string type_name() const override { return "Livro"; }
};

// Q4 (A): Funções Não-Intrusivas no padrão nlohmann/json (ADL)
void to_json(json& j, const Livro& l);
void from_json(const json& j, Livro& l);