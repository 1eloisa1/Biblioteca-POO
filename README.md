# Sistema de Gerenciamento de Biblioteca

**Aluna:** Maria Eloísa Silva de Sousa  
**Disciplina:** Programação Orientada a Objetos
**Professor:** Carlos Eduardo C. F. Batista  

## Descrição do Domínio
O projeto consiste em uma plataforma digital projetada para automatizar processos de gestão de acervos físicos. O sistema modela entidades fundamentais de uma biblioteca, permitindo o cadastro de acervos de livros, o controle de estoque de cópias físicas, o gerenciamento de usuários locatários e a automatização do cálculo de multas geradas por devoluções atrasadas.

No **TP2**, a arquitetura foi estendida para suportar herança polimórfica por meio de uma classe base abstrata (`ItemAcervo`), uma interface pura de capacidades (`Emprestavel`) e as derivadas concretas (`Livro` e `Revista`), unificando a robustez dos Smart Pointers com o polimorfismo dinâmico.

## Relações e Ciclo de Vida 
Composição (Biblioteca -- Livro): A relação é de composição porque a classe Biblioteca é a dona absoluta das instâncias de Livro em seu catálogo. Em termos de ciclo de vida, os livros são criados dinamicamente por ela e deixam de existir no momento exato em que o objeto da Biblioteca é destruído, impossibilitando a existência de um livro do catálogo se o seu contêiner gerenciador for desalocado.  
Agregação (Emprestimo -- Usuario e Livro): A relação é de agregação porque a classe Emprestimo apenas associa e referencia objetos de Usuario e Livro que já possuem existência independente externa. Quando o ciclo de vida do objeto Emprestimo chega ao fim no escopo do main() e ele é destruído, o registro some, mas as instâncias agregadas originais continuam intactas e ativas na memória. 

## Smart Pointers 
std::unique_ptr<Livro> em Biblioteca: Substituiu com sucesso o uso de ponteiros brutos (raw pointers) no vetor do catálogo. A escolha foi por um ponteiro inteligente de posse exclusiva (unique_ptr) porque a relação de herança/ciclo de vida é uma Composição estrita. Com isso, os destrutores manuais que continham laços de deleção foram totalmente eliminados, deixando a cargo do próprio ponteiro a limpeza automática da memória ao sair de escopo, evitando vazamentos (memory leaks).  
Ponteiros Brutos Observadores (Livro* e const Usuario*) em Emprestimo: Mantidos como ponteiros brutos por recomendação direta da semântica de posse do C++ moderno para relações de Agregação. Como a classe Emprestimo funciona estritamente como uma observadora sem posse, ela não tem o direito de gerenciar ou destruir o Usuario ou o Livro associado. No método get_book(), usamos a função .get() do unique_ptr para expor o endereço bruto interno de forma segura apenas para essa observação.  



### Relações de Ciclo de Vida e Semântica de Posse

**Composição (`Biblioteca` ➔ `ItemAcervo`):** A classe `Biblioteca` é a dona absoluta das instâncias do acervo. A relação é implementada usando `std::vector<std::unique_ptr<ItemAcervo>>`. Isso garante que, quando a biblioteca é destruída, todos os itens do acervo gerenciado são automaticamente desalocados na ordem inversa correta.

* **Agregação (`Emprestimo` ➔ `Usuario` e `Livro`):** A classe `Emprestimo` apenas associa e referencia entidades que têm existências independentes na memória. É implementada utilizando ponteiros observadores brutos (`const Usuario*` e `Livro*`), garantindo que o ciclo de vida do empréstimo não interfira na persistência das instâncias agregadas.

## Programação Genérica (TP3 - Questão 1)
* **O que o template abstrai:** A classe `Registry<T>` abstrai o armazenamento e acesso genérico e seguro para coleções de qualquer tipo de item do domínio que satisfaça as regras de negócio.
* **Por que CRTP em vez de Herança Virtual:** O CRTP (`Counted<Derived>`) permite injetar contagem estática de instâncias vivas diretamente em tempo de compilação, eliminando totalmente o custo de chamadas virtuais (vtable lookup) para essa funcionalidade.
* **Ranges vs. Laço Tradicional:** O pipeline de `std::ranges` torna a filtragem e transformação declarativas e concisas. O código antes/depois eliminou a necessidade de criar vetores intermediários manuais e laços `for` repetitivos.

## SOLID (TP3 - Questão 4)
* **SRP (Single Responsibility Principle):** A classe `ItemAcervo` gerencia os dados do item, enquanto a persistência é delegada à hierarquia `Repository`.
* **OCP (Open/Closed Principle):** Novos tipos de itens (ex: `CD`, `Tese`) podem ser criados herdando de `ItemAcervo` sem modificar a classe `Biblioteca` ou o `Registry`.
* **LSP (Liskov Substitution Principle):** Instâncias de `Livro` ou `Revista` podem substituir `ItemAcervo` transparentemente.
* **ISP (Interface Segregation Principle):** A interface `Emprestavel` expõe apenas os métodos necessários para emprestar/devolver, sem poluir a interface base `ItemAcervo`.
* **DIP (Dependency Inversion Principle):** A classe de alto nível `AppCore` depende apenas da abstração `Repository`, recebida via injeção no construtor.

## Interface Gráfica com Qt (TP3 - Questão 6)
Para compilar e executar a interface gráfica:

```bash
mkdir build && cd build
cmake ..
cmake --build . --target gui
./gui
---

## Diagrama de Classes UML (Unificado)

```mermaid
classDiagram
    class ItemAcervo {
        <<abstract>>
        # string titulo
        # string codigo
        + virtual float calcular() = 0
        + virtual void exibir()
        + virtual ~ItemAcervo()
    }

    class Emprestavel {
        <<interface>>
        + virtual void emprestar() = 0
        + virtual void devolver() = 0
        + virtual bool estaEmprestado() = 0
        + virtual ~Emprestavel()
    }

    class Livro {
        - string author_
        - int available_copies_
        + float calcular() override
        + void exibir() override
        + void emprestar() override
        + void devolver() override
        + bool estaEmprestado() const override
        + string title() const
        + string author() const
        + string isbn() const
        + int available_copies() const
        + bool loan_copy()
        + void return_copy()
    }

    class Revista {
        - int edicao
        + float calcular() override
        + void exibir() override
    }

    class Usuario {
        - string name_
        - string email_
        + name() const string
        + email() const string
    }

    class Emprestimo {
        - const Usuario* usuario_
        - Livro* livro_
        - int days_loaned_
        + calculate_fine() const float
        + display_loan_info() const void
    }

    class Biblioteca {
        - string library_name_
        - vector~unique_ptr~ItemAcervo~~ catalog_
        + add_book_to_catalog(string, string, string, int) void
        + get_book(size_t) Livro*
        + show_catalog() const void
    }

    ItemAcervo <|-- Livro : Herança
    Emprestavel <|.. Livro : Implementa
    ItemAcervo <|-- Revista : Herança
    Biblioteca "1" *-- "0..*" ItemAcervo : Composição (via unique_ptr)
    Emprestimo "0..*" --> "1" Usuario : Agregação (Ponteiro Observador)
    Emprestimo "0..*" --> "1" Livro : Agregação (Ponteiro Observador)