#ifndef USUARIO.HPP
#define USUARIO.HPP

#include <string>


class Usuario {
    private:
        std::string nome_;
        std::string email_;
    
    public:
        Usuario(std::string n, std::string e);
        ~Usuario();

        std::string nome_() const;
        std::string email_() const;

};
#endif