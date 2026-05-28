#ifndef "emprestimo.hpp"

#include <iostream>



        Emprestimo::Emprestimo(const Usuario* u, Livro* l, int d_e)
            : usuario_(u), livro_(l),dias_empretimo(d_e)){}


        Emprestimo::~Emprestimo(){
            std::cout << "[Emprestimo] destrutor \n";
        }


        float Emprestimo::calculate_fine(){
            const int limite = 15;
            if(dias_empretimo > limite){
                return (dias_empretimo - limite) * 2.5f;
            }
            return 0.0f;
        }
        void Emprestimo::display_loan_info() const {
            std::cout << "Livro: " << livro_->titulo() << "Usuario: " << usuario_->nome() << 
            " dias " << dias_empretimo << "multa: " << calculate_fine() << "\n"  

};
