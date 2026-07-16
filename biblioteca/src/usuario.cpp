#include "usuario.hpp"
#include <iostream>

using namespace std;

Usuario::Usuario(string t_name, string t_email) 
    : name_(t_name), email_(t_email) {
    cout << "[Usuario]: " << name_ << " criado.\n";
}

Usuario::~Usuario() {
    cout << "[Usuario]: " << name_ << " removido.\n";
}

string Usuario::name() const { return name_; }
string Usuario::email() const { return email_; }