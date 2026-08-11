#include "livro.hpp"
#include <iostream>

Livro::Livro(std::string t_title, std::string t_author, std::string t_isbn, int t_copies)
    : ItemAcervo(std::move(t_title), std::move(t_isbn)),
      author_(std::move(t_author)),
      available_copies_(t_copies) {}

float Livro::calcular() const { return 2.50f; }

void Livro::exibir() const {
    ItemAcervo::exibir();
    std::cout << " (Livro por " << author_ << ") - Copias: " << available_copies_ << "\n";
}

void Livro::emprestar() { loan_copy(); }
void Livro::devolver() { return_copy(); }
bool Livro::estaEmprestado() const { return available_copies_ == 0; }

Livro::~Livro() {
    std::cout << "[Destrutor Derivada] ~Livro destruido.\n";
}

std::string Livro::title() const { return titulo; }
std::string Livro::author() const { return author_; }
std::string Livro::isbn() const { return codigo; }
int Livro::available_copies() const { return available_copies_; }

bool Livro::loan_copy() {
    if (available_copies_ > 0) {
        available_copies_--;
        return true;
    }
    return false;
}

void Livro::return_copy() { available_copies_++; }

// Q4 (A): Implementação Não-Intrusiva
void to_json(json& j, const Livro& l) {
    j = json{
        {"type", l.type_name()},
        {"codigo", l.isbn()},
        {"titulo", l.title()},
        {"author", l.author()},
        {"copies", l.available_copies()}
    };
}

void from_json(const json& j, Livro& l) {
    l = Livro(
        j.at("titulo").get<std::string>(),
        j.at("author").get<std::string>(),
        j.at("codigo").get<std::string>(),
        j.at("copies").get<int>()
    );
}