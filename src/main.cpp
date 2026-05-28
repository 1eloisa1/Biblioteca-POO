#include "biblioteca.hpp"
#include "usuario.hpp"
#include "emprestimo.hpp"
#include <iostream>

int main() {

    Usuario usuario_estudante("Amanda", "amanda@gmail.br");

    std::cout << "\n--- Entrando no Bloco de Escopo da Biblioteca ---\n";
    {
        Biblioteca minha_biblioteca("Biblioteca");

        minha_biblioteca.add_book_to_catalog("Alice no Pais das Maravilhas", "Lewis Carroll", "6558700654", 4);
        minha_biblioteca.show_catalog();

        Livro* livro_alvo = minha_biblioteca.get_book(0);

        if (livro_alvo && livro_alvo->loan_copy()) {
            std::cout << "\n[Sucesso] Copia do livro '" << livro_alvo->title() << "' reservada para emprestimo.\n";
            
            Emprestimo novo_emprestimo(&usuario_estudante, livro_alvo, 10);
            novo_emprestimo.display_loan_info();
            
            std::cout << "\n--- Finalizando o Emprestimo (Destruicao do objeto agregador) ---\n";
        }
        
        std::cout << "\n--- Saindo do Bloco (A Biblioteca e tudo que ela compõe serão destruídos) ---\n";
    }
    
    std::cout << "Verificação de independência da agregação:\n";
    std::cout << "O usuário '" << usuario_estudante.name() << "' continua ativo no sistema.\n\n";

    return 0;
}