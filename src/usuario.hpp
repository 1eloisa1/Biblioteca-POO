#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
private:
    std::string name_;
    std::string email_;

public:
    Usuario(std::string t_name, std::string t_email);
    ~Usuario();

    std::string name() const;
    std::string email() const;
};

#endif