#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include "registry.hpp"
#include "excecoes.hpp"
#include "livro.hpp"
#include "revista.hpp"
#include "repositorio.hpp"

using json = nlohmann::json;

// Q1 - Template e Concept

TEST_CASE("Template Registry e Concept Calculavel", "[Q1][Q5]") {

    Registry<Livro> reg;

    reg.add(
        Livro(
            "Design Patterns",
            "GoF",
            "001",
            3
        )
    );

    REQUIRE(reg.size() == 1);
    REQUIRE(reg.at(0).title() == "Design Patterns");
}
// Q2 - Excecoes e Optional

TEST_CASE("Hierarquia de Excecoes e std::optional", "[Q2][Q5]") {

    SECTION("Excecao capturada pela base") {

        REQUIRE_THROWS_AS(
            []() {
                throw ValidacaoInvalidaException("Erro de teste");
            }(),
            ErroDominio
        );
    }

    SECTION("Busca com optional") {

        std::vector<std::shared_ptr<ItemAcervo>> acervo;

        acervo.push_back(
            std::make_shared<Livro>(
                "Clean Code",
                "Martin",
                "002",
                2
            )
        );

        auto achar =
            [](const auto& vec, const std::string& cod)
            -> std::optional<std::shared_ptr<ItemAcervo>> {

                for (const auto& item : vec) {

                    if (item->get_codigo() == cod) {
                        return item;
                    }
                }

                return std::nullopt;
            };

        REQUIRE(achar(acervo, "002").has_value());

        REQUIRE_FALSE(
            achar(acervo, "999").has_value()
        );
    }
}

// Q4 - Serializacao

TEST_CASE("Serializacao Round-Trip com JSON", "[Q4][Q5]") {

    Livro original(
        "Refactoring",
        "Fowler",
        "003",
        5
    );

    json j;

    to_json(j, original);

    Livro reconstruido(
        "",
        "",
        "",
        0
    );

    from_json(j, reconstruido);

    REQUIRE(
        reconstruido.title() ==
        original.title()
    );

    REQUIRE(
        reconstruido.isbn() ==
        original.isbn()
    );

    REQUIRE(
        reconstruido.author() ==
        original.author()
    );

    REQUIRE(
        reconstruido.available_copies() ==
        original.available_copies()
    );
}

// Q4 - DIP

TEST_CASE(
    "DIP com MemoryRepository sem efeito colateral",
    "[Q4][Q5]"
) {

    MemoryRepository repo_memoria;

    AppCore app(repo_memoria);

    auto livro =
        std::make_shared<Livro>(
            "Domain-Driven Design",
            "Evans",
            "004",
            1
        );

    app.adicionar_item(livro);

    app.salvar();

    REQUIRE(
        app.get_estado().acervo.size() == 1
    );

    REQUIRE(
        app.get_estado()
            .acervo[0]
            ->get_titulo()
        == "Domain-Driven Design"
    );
}