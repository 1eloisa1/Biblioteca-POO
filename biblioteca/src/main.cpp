#include <iostream>
#include <vector>
#include <memory>
#include "livro.hpp"
#include "revista.hpp"
#include "biblioteca.hpp"
#include "usuario.hpp"
#include "emprestimo.hpp"

using namespace std;

// Questão 2 (D)
const ItemAcervo* obterMaiorTaxaAtraso(const std::vector<std::unique_ptr<ItemAcervo>>& itens) {
    if (itens.empty()) return nullptr;
    
    const ItemAcervo* maior = itens.front().get();
    for (const auto& item : itens) {
        if (item->calcular() > maior->calcular()) {
            maior = item.get();
        }
    }
    return maior;
}

// Questão 3 (D)
void realizarFluxoBiblioteca(Emprestavel& item) {
    std::cout << "\n--- Iniciando fluxo de emprestimo via Interface (Q3-D) ---\n";
    item.emprestar();
    item.devolver();
    std::cout << "--- Fluxo finalizado ---\n\n";
}

int main() {
    std::cout << "           PARTE 1: TESTES DO TP1 (BIBLIOTECA)          \n";
    
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

    std::cout << "           PARTE 2: TESTES DO TP2 (HERANCA)             \n";

    std::cout << "=== Teste 1: Cadeia de Destruicao Virtual (Q1-C) ===\n"; 
    {
        ItemAcervo* testeDestruicao = new Livro("C++ Eficaz", "Scott Meyers", "123", 2);
        delete testeDestruicao;
    }

    std::cout << "=== Teste 2 & 3: Polimorfismo Dinamico (Q2-A, B, D) ===\n"; 
    {
        // Q2 (A)
        std::vector<std::unique_ptr<ItemAcervo>> acervo;
        acervo.push_back(std::make_unique<Livro>("Design Patterns", "GoF", "001", 3));
        acervo.push_back(std::make_unique<Revista>("Mundo Computacao", "002", 42));
        acervo.push_back(std::make_unique<Livro>("Clean Code", "Robert Martin", "003", 5));

        // Q2 (B)
        std::cout << "\n--- Exibindo Acervo ---\n";
        for (const auto& item : acervo) {
            item->exibir();
            std::cout << "Taxa de Atraso Diaria:  " << item->calcular() << "\n\n";
        }

        // Q2 (D)
        const ItemAcervo* maior = obterMaiorTaxaAtraso(acervo);
        if (maior) {
            std::cout << "Item com maior taxa de atraso diaria: ";
            maior->exibir();
        }

        // Q3 (D)
        auto* livroEmprestavel = dynamic_cast<Emprestavel*>(acervo[0].get());
        if (livroEmprestavel) {
            realizarFluxoBiblioteca(*livroEmprestavel);
        }

        std::cout << "--- Saindo do escopo (Vetor sera destruido) ---\n";
        // Q2 (C)
    }

    return 0;
}