# Biblioteca - Sistema de Gerenciamento de Biblioteca

**Aluna:** Maria Eloísa Silva  
**Disciplina:** Programação Orientada a Objetos (2026.1)  
**Professor:** Carlos Eduardo C. F. Batista  

## Descrição do Domínio
O projeto consiste em uma plataforma digital, projetado para automatizar processos de gestão de acervos físicos. O sistema modela entidades fundamentais de uma biblioteca, permitindo o cadastro de acervos de livros, o controle de estoque de cópias físicas, o gerenciamento de usuários locatários e a automatização do cálculo de multas geradas por devoluções atrasadas.

## Diagrama UML de Classes
## Diagrama UML de Classes

```mermaid

classDiagram
    class Biblioteca {
        -string library_name_
        -vector~unique_ptr~Livro~~ catalog_
        +add_book_to_catalog(string, string, string, int) void
        +get_book(size_t) Livro*
        +show_catalog() const void
    }

    class Livro {
        -string title_
        -string author_
        -string isbn_
        -int available_copies_
        +title() const string
        +author() const string
        +isbn() const string
        +available_copies() const int
        +loan_copy() bool
        +return_copy() void
    }

    class Usuario {
        -string name_
        -string email_
        +name() const string
        +email() const string
    }

    class Emprestimo {
        -Usuario* usuario_
        -Livro* livro_
        -int days_loaned_
        +calculate_fine() const float
        +display_loan_info() const void
    }

    Biblioteca "1" *-- "0..*" Livro : Composição
    Emprestimo "0..*" --> "1" Usuario : Agregação
    Emprestimo "0..*" --> "1" Livro : Agregação

## Smart Pointers (Questão 4 - Extra)

* **`std::unique_ptr<Livro>` em `Biblioteca`**: Aplicado no vetor do catálogo de livros porque a relação é de composição (posse exclusiva). A `Biblioteca` gerencia completamente o ciclo de vida dos livros e, ao usar ponteiros únicos, eliminamos a necessidade de desalocação manual no destrutor, evitando vazamentos de memória (*memory leaks*).
* **Ponteiros Brutos Observadores (`Livro*` e `Usuario*`) em `Emprestimo`**: Mantidos como ponteiros brutos para representar a semântica de agregação (observadores sem posse). Como o `Emprestimo` não é dono das instâncias de `Usuario` nem de `Livro`, ele apenas aponta para objetos controlados externamente, não interferindo no ciclo de vida deles ao ser destruído.