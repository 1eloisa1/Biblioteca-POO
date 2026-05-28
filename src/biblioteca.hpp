#ifndef BIBLIOTECA.HPP
#define BIBLIOTECA.HPP

#include livro.hpp
#include <vector>

class Biblioteca {
    private:
        std::string nome_biblioteca_;
        std::vector<Livro*> catalogo_;

    
    public:
        explicit Biblioteca(std::string t_nome);
        ~Biblioteca();


        void novo_livro(std::string t, std::strig a, std::string isbn, int c);
        Livro* get_livro(size_t index);
        void mostra_catalogo() const;

};
#endif