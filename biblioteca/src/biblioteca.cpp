#include "biblioteca.hpp"
#include <iostream>

Biblioteca::Biblioteca(std::string name) : library_name_(std::move(name)) {}

void Biblioteca::add_book_to_catalog(std::string title, std::string author, std::string isbn, int copies) {
    catalog_.push_back(std::make_unique<Livro>(std::move(title), std::move(author), std::move(isbn), copies));
}

Livro* Biblioteca::get_book(std::size_t index) {
    if (index < catalog_.size()) {
        return dynamic_cast<Livro*>(catalog_[index].get());
    }
    return nullptr;
}

void Biblioteca::show_catalog() const {
    std::cout << "Catalog de " << library_name_ << ":\n";
    for (const auto& item : catalog_) {
        item->exibir();
    }
}