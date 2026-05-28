#ifndef LIVRO.HPP
#define LIVRO.HPP

#include <string>


class Livro {
    private:
        std::string titulo_;
        std::string autor_;
        std::string isbn_;
        int copiasdisponiveis_;
    
    public:
        Livro(std::string t, std::string a, std::string isbn, int copiasd);
        ~Livro();

        std::string titulo() const;
        std::string autor() const;
        std::string isbn() const;
        int copiasdisponiveis() const;


        bool loan_copy();
        void return_copy();

};
#endif