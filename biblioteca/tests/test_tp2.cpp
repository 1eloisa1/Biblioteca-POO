#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <sstream>
#include <memory>
#include <vector>
#include "item_acervo.hpp"
#include "livro.hpp"
#include "revista.hpp"

TEST_CASE("Cadeia de destruicao da hierarquia", "[Q1]") {
    std::streambuf* oldCout = std::cout.rdbuf();
    std::stringstream ss;
    std::cout.rdbuf(ss.rdbuf());

    {
        ItemAcervo* item = new Livro("C++ Eficaz", "Scott Meyers", "123", 2);
        delete item;
    }

    std::cout.rdbuf(oldCout);

    std::string output = ss.str();

    REQUIRE(output.find("[Destrutor Derivada] ~Livro destruido.") != std::string::npos);
    REQUIRE(output.find("[Destrutor Base] ~ItemAcervo limpo para: C++ Eficaz") != std::string::npos);
    REQUIRE(output.find("[Destrutor Derivada] ~Livro destruido.") < output.find("[Destrutor Base] ~ItemAcervo limpo para: C++ Eficaz"));
}


TEST_CASE("Polimorfismo e calculo de taxas", "[Q2]") {
    std::vector<std::unique_ptr<ItemAcervo>> acervo;
    acervo.push_back(std::make_unique<Livro>("Design Patterns", "GoF", "001", 3));
    acervo.push_back(std::make_unique<Revista>("Mundo Computacao", "002", 42));

    REQUIRE_THAT(acervo[0]->calcular(), Catch::Matchers::WithinRel(2.50f, 0.001f));
    REQUIRE_THAT(acervo[1]->calcular(), Catch::Matchers::WithinRel(1.00f, 0.001f));
}

TEST_CASE("Interface pura Emprestavel", "[Q3]") {
    Livro livro("Clean Code", "Robert Martin", "003", 2);

    Emprestavel& emp = livro;

    REQUIRE_FALSE(emp.estaEmprestado());
    
    emp.emprestar();
    REQUIRE(livro.available_copies() == 1);
    
    emp.devolver();
    REQUIRE(livro.available_copies() == 2); 
}