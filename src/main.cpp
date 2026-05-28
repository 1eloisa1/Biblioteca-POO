#include "biblioteca.hpp"
#include "usuario.hpp"
#include "emprestimo.hpp"
#include <iostream>

using namespace std;

int main() {

    Usuario usuario_estudante("Amanda", "amanda@gmail.br");

    {
        Biblioteca minha_biblioteca("Biblioteca");

        minha_biblioteca.add_book_to_catalog("Alice no Pais das Maravilhas", "Lewis Carroll", "6558700654", 4);
        minha_biblioteca.show_catalog();

        Livro* livro_alvo = minha_biblioteca.get_book(0);

        if (livro_alvo && livro_alvo->loan_copy()) {
            cout << "\nCopia do livro '" << livro_alvo->title() << "' reservada para emprestimo.\n";
            
            Emprestimo novo_emprestimo(&usuario_estudante, livro_alvo, 20);
            novo_emprestimo.display_loan_info();
            
            cout << "\n--- Finalizando o Emprestimo ---\n";
        }
        
        cout << "\n--- Saindo do Bloco (A Biblioteca e tudo que ela compoe serao destruidos) ---\n";
    }
    
    cout << "Verificacao de independencia da agregacao:\n";
    cout << "O usuario '" << usuario_estudante.name() << "' continua ativo no sistema.\n\n";

    return 0;
}