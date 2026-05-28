#ifndef "livro.hpp"

#include <iostream>



        Livro::Livro(std::string t, std::string a, std::string isbn, int copiasd)
            : titulo_(t), autor_(a), isbn_(isbn), copiasdisponiveis_(copiasd){
                std::cout << "[Livro] construtor: '" titulo_ << "' registrado. \n";
            }
        Livro::~Livro(){
            std::cout << "[Livro] destrutor: '" titulo_ << "' removido. \n";
        }

        std::string titulo() const{
            return titulo_;
        }
        std::string autor() const{
            return autor_;
        }
        std::string isbn() const{
            return isbn_;
        }
        int copiasdisponiveis() const{
            return copiasdisponiveis_;
        }

        bool Livro::loan_copy(){
            if(copiasdisponiveis_ > 0){
                copiasdisponiveis_--;
                return true;
            }
            return false;
        }
        void Livro::return_copy(){
            copiasdisponiveis_++;
        }

};
