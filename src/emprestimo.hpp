#ifndef EMPRESTIMO.HPP
#define EMPRESTIMO.HPP

#include <usuario.hpp>
#include <livro.pp>


class Emprestimo {
    private:
        const Usuario* usuario_;
        Livro* livro_;
        int dias_empretimo;
    
    public:
        Emprestimo(const Usuario* u, Livro* l, int d_e);
        ~Emprestimo();

        float calculate_fine() const;
        void display_loan_info() const;

};
#endif