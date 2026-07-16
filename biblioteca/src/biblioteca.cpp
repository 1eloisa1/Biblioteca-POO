#include "biblioteca.hpp"
#include <iostream>

using namespace std;

Biblioteca::Biblioteca(string t_name) : library_name_(t_name) {
    cout << "[Biblioteca] '" << library_name_ << "' aberta.\n";
}

Biblioteca::~Biblioteca() {
    cout << "Fechando a biblioteca.\n";
}

void Biblioteca::add_book_to_catalog(string t_title, string t_author, string t_isbn, int t_copies) {
    catalog_.push_back(make_unique<Livro>(t_title, t_author, t_isbn, t_copies));
}

Livro* Biblioteca::get_book(size_t index) {
    if (index < catalog_.size()) {
        return dynamic_cast<Livro*>(catalog_[index].get());
    }
    return nullptr;
}

void Biblioteca::show_catalog() const {
    cout << "\n--- Catalogo da " << library_name_ << " ---\n";
    for (const auto& item : catalog_) {
        cout << "- ";
        item->exibir(); 
    }
}