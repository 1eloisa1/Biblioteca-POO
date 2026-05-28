# Sistema de Gerenciamento de Biblioteca

**Aluna:** Maria Eloísa Silva de Sousa  
**Disciplina:** Programação Orientada a Objetos
**Professor:** Carlos Eduardo C. F. Batista  

## Descrição do Domínio
O projeto consiste em uma plataforma digital projetada para automatizar processos de gestão de acervos físicos. O sistema modela entidades fundamentais de uma biblioteca, permitindo o cadastro de acervos de livros, o controle de estoque de cópias físicas, o gerenciamento de usuários locatários e a automatização do cálculo de multas geradas por devoluções atrasadas.

## Relações e Ciclo de Vida 
Composição (Biblioteca -- Livro): A relação é de composição porque a classe Biblioteca é a dona absoluta das instâncias de Livro em seu catálogo. Em termos de ciclo de vida, os livros são criados dinamicamente por ela e deixam de existir no momento exato em que o objeto da Biblioteca é destruído, impossibilitando a existência de um livro do catálogo se o seu contêiner gerenciador for desalocado.  
Agregação (Emprestimo -- Usuario e Livro): A relação é de agregação porque a classe Emprestimo apenas associa e referencia objetos de Usuario e Livro que já possuem existência independente externa. Quando o ciclo de vida do objeto Emprestimo chega ao fim no escopo do main() e ele é destruído, o registro some, mas as instâncias agregadas originais continuam intactas e ativas na memória. 

## Smart Pointers 
std::unique_ptr<Livro> em Biblioteca: Substituiu com sucesso o uso de ponteiros brutos (raw pointers) no vetor do catálogo. A escolha foi por um ponteiro inteligente de posse exclusiva (unique_ptr) porque a relação de herança/ciclo de vida é uma Composição estrita. Com isso, os destrutores manuais que continham laços de deleção foram totalmente eliminados, deixando a cargo do próprio ponteiro a limpeza automática da memória ao sair de escopo, evitando vazamentos (memory leaks).  
Ponteiros Brutos Observadores (Livro* e const Usuario*) em Emprestimo: Mantidos como ponteiros brutos por recomendação direta da semântica de posse do C++ moderno para relações de Agregação. Como a classe Emprestimo funciona estritamente como uma observadora sem posse, ela não tem o direito de gerenciar ou destruir o Usuario ou o Livro associado. No método get_book(), usamos a função .get() do unique_ptr para expor o endereço bruto interno de forma segura apenas para essa observação.  

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


