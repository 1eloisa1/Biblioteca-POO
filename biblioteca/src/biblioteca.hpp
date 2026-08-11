#pragma once
#include <string>
#include <vector>
#include <memory>
#include "livro.hpp"
#include "item_acervo.hpp"

class Biblioteca {
private:
    std::string library_name_;
    std::vector<std::unique_ptr<ItemAcervo>> catalog_;

public:
    explicit Biblioteca(std::string name);
    void add_book_to_catalog(std::string title, std::string author, std::string isbn, int copies);
    Livro* get_book(std::size_t index);
    void show_catalog() const;
};