#include "biblioteca.hpp"
#include <iostream>

Biblioteca::Biblioteca(std::string t_name) : library_name_(t_name) {
    std::cout << "[Biblioteca] Construtor: '" << library_name_ << "' aberta.\n";
}

Biblioteca::~Biblioteca() {
    std::cout << "[Biblioteca] Destrutor: Fechando a biblioteca e limpando o catálogo físico (Composição).\n";

    for (Livro* book : catalog_) {
        delete book;
    }
    catalog_.clear();
}

void Biblioteca::add_book_to_catalog(std::string t_title, std::string t_author, std::string t_isbn, int t_copies) {

    catalog_.push_back(new Livro(t_title, t_author, t_isbn, t_copies));
}

Livro* Biblioteca::get_book(size_t index) {
    if (index < catalog_.size()) {
        return catalog_[index];
    }
    return nullptr;
}

void Biblioteca::show_catalog() const {
    std::cout << "\n--- Catalogo da " << library_name_ << " ---\n";
    for (const auto& book : catalog_) {
        std::cout << "- " << book->title() << " (" << book->author() << ") - Cópias: " << book->available_copies() << "\n";
    }
    std::cout << "\n";
}