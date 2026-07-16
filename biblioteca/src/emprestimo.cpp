#include "emprestimo.hpp"
#include <iostream>

using namespace std;

Emprestimo::Emprestimo(const Usuario* t_user, Livro* t_book, int t_days)
    : usuario_(t_user), livro_(t_book), days_loaned_(t_days) {
    cout << "Emprestimo gerado para o usuario.\n";
}

Emprestimo::~Emprestimo() {
    cout << "Registro de emprestimo finalizado.\n";
}

float Emprestimo::calculate_fine() const {
    const int limit_days = 15;
    if (days_loaned_ > limit_days) {
        return (days_loaned_ - limit_days) * 2.50f;
    }
    return 0.0f;
}

void Emprestimo::display_loan_info() const {
    cout << "Livro: " << livro_->title() << " | Usuario: " << usuario_->name() 
         << " | Dias emprestado: " << days_loaned_ <<  " Dias limite: 15 | Multa: " << calculate_fine() << " reais \n";
}