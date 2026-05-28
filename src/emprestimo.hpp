#ifndef EMPRESTIMO_HPP
#define EMPRESTIMO_HPP

#include "usuario.hpp"
#include "livro.hpp"

class Emprestimo {
private:

    const Usuario* usuario_;
    Livro* livro_;
    int days_loaned_;

public:
    Emprestimo(const Usuario* t_user, Livro* t_book, int t_days);
    ~Emprestimo();

    float calculate_fine() const;
    void display_loan_info() const;
};

#endif