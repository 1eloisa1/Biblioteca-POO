#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <string>


class Livro {
private:
    std::string title_;
    std::string author_;
    std::string isbn_;
    int available_copies_;

public:
    Livro(std::string t_title, std::string t_author, std::string t_isbn, int t_copies);
    ~Livro();

    std::string title() const;
    std::string author() const;
    std::string isbn() const;
    int available_copies() const;

    bool loan_copy();
    void return_copy();
};

#endif