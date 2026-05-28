#include "emprestimo.hpp"
#include <iostream>

Emprestimo::Emprestimo(const Usuario* t_user, Livro* t_book, int t_days)
    : usuario_(t_user), livro_(t_book), days_loaned_(t_days) {
    std::cout << "[Emprestimo] Construtor: Emprestimo gerado para o usuario.\n";
}

Emprestimo::~Emprestimo() {
    std::cout << "[Emprestimo] Destrutor: Registro de emprestimo finalizado.\n";
}

float Emprestimo::calculate_fine() const {
    const int limit_days = 7;
    if (days_loaned_ > limit_days) {
        // R$ 2.50 por dia de atraso
        return (days_loaned_ - limit_days) * 2.50f;
    }
    return 0.0f;
}

void Emprestimo::display_loan_info() const {
    std::cout << "Livro: " << livro_->title() << " | Usuario: " << usuario_->name() 
              << " | Dias: " << days_loaned_ << " | Multa: " << calculate_fine() << " reais \n";
}