#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP

#include "item_acervo.hpp"
#include "livro.hpp"
#include <vector>
#include <memory> 
#include <string>

class Biblioteca {
private:
    std::string library_name_;

    std::vector<std::unique_ptr<ItemAcervo>> catalog_;

public:
    explicit Biblioteca(std::string t_name);
    ~Biblioteca();

    void add_book_to_catalog(std::string t_title, std::string t_author, std::string t_isbn, int t_copies);
    Livro* get_book(size_t index);
    void show_catalog() const;
};

#endif