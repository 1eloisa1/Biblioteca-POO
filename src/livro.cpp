#include "livro.hpp"
#include <iostream>

Livro::Livro(std::string t_title, std::string t_author, std::string t_isbn, int t_copies)
    : title_(t_title), author_(t_author), isbn_(t_isbn), available_copies_(t_copies) {
    std::cout << "[Livro]: '" << title_ << "' registrado.\n";
}

Livro::~Livro() {
    std::cout << "[Livro]: '" << title_ << "' removido.\n";
}

std::string Livro::title() const { return title_; }
std::string Livro::author() const { return author_; }
std::string Livro::isbn() const { return isbn_; }
int Livro::available_copies() const { return available_copies_; }

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