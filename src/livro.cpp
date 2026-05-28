#include "livro.hpp"
#include <iostream>

using namespace std; // Adicionado aqui

Livro::Livro(string t_title, string t_author, string t_isbn, int t_copies)
    : title_(t_title), author_(t_author), isbn_(t_isbn), available_copies_(t_copies) {
    cout << "[Livro] '" << title_ << "' registrado.\n";
}

Livro::~Livro() {
    cout << "[Livro] '" << title_ << "' removido.\n";
}

string Livro::title() const { return title_; }
string Livro::author() const { return author_; }
string Livro::isbn() const { return isbn_; }
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