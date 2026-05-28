#include "usuario.hpp"
#include <iostream>

Usuario::Usuario(std::string t_name, std::string t_email) 
    : name_(t_name), email_(t_email) {
    std::cout << "[Usuario]: " << name_ << " criado.\n";
}

Usuario::~Usuario() {
    std::cout << "[Usuario]:" << name_ << " destruido.\n";
}

std::string Usuario::name() const { return name_; }
std::string Usuario::email() const { return email_; }