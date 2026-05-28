#ifndef "usuario.hpp"

#include <iostream>



        Usuario::Usuario(std::string n, std::string e)
            : nome_(n), email_(e){
                std::cout << "[User] construtor: '" nome_ << "' registrado. \n";
            }
        Usuario::~Usuario(){
            std::cout << "[User] destrutor: '" nome_ << "' removido. \n";
        }

        std::string nome() const{
            return nome_;
        }
        std::string email() const{
            return email_;
        }

};