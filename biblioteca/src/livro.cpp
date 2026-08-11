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

json Livro::to_json() const {
    json j = ItemAcervo::to_json();
    j["author"] = author_;
    j["copies"] = available_copies_;
    return j;
}

Livro Livro::from_json(const json& j) {
    return Livro(
        j.at("titulo").get<std::string>(),
        j.at("author").get<std::string>(),
        j.at("codigo").get<std::string>(),
        j.at("copies").get<int>()
    );
}