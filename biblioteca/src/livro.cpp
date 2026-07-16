#include "livro.hpp"
#include <iostream>

Livro::Livro(std::string t_title, std::string t_author, std::string t_isbn, int t_copies)
    : ItemAcervo(std::move(t_title), std::move(t_isbn)), 
      author_(std::move(t_author)), 
      available_copies_(t_copies) {}

Livro::~Livro() {
    std::cout << "[Destrutor Derivada] ~Livro destruído.\n";
}

float Livro::calcular() const {
    return 2.50f;
}

// Questão 1 (B): 
void Livro::exibir() const {
    ItemAcervo::exibir(); // Exibe "[ISBN] Título"
    std::cout << " (Livro por " << author_ << ") - Cópias disponíveis: " 
              << available_copies_ << "\n";
}

// Questão 3 (B):
void Livro::emprestar() {
    if (loan_copy()) {
        std::cout << "O livro '" << titulo << "' foi emprestado via Interface!\n";
    } else {
        std::cout << "Nao ha copias disponiveis de '" << titulo << "' para emprestimo.\n";
    }
}

void Livro::devolver() {
    return_copy();
    std::cout << "O livro '" << titulo << "' foi devolvido via Interface.\n";
}

bool Livro::estaEmprestado() const {
    return available_copies_ == 0;
}

std::string Livro::title() const { 
    return titulo; 
}

std::string Livro::author() const { 
    return author_; 
}

std::string Livro::isbn() const { 
    return codigo;
}

int Livro::available_copies() const { 
    return available_copies_; 
}

bool Livro::loan_copy() {
    if (available_copies_ > 0) {
        available_copies_--;
        return true;
    }
    return false;
}

void Livro::return_copy() {
    available_copies_++;
}