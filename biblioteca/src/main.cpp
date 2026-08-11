#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <mutex>

#include "registry.hpp"
#include "excecoes.hpp"
#include "livro.hpp"
#include "revista.hpp"
#include "repositorio.hpp"

std::optional<std::shared_ptr<ItemAcervo>> buscar_por_codigo(
    const std::vector<std::shared_ptr<ItemAcervo>>& acervo,
    const std::string& codigo)
{
    for (const auto& item : acervo) {
        if (item->get_codigo() == codigo) return item;
    }
    return std::nullopt;
}

using ResultadoOperacao = std::variant<std::shared_ptr<ItemAcervo>, std::string>;

ResultadoOperacao processar_requisicao(bool sucesso, std::shared_ptr<ItemAcervo> item) {
    if (sucesso) return item;
    return std::string("Falha ao processar a requisicao do item.");
}

int main() {

    // Q1 (A): Instanciando Template Reutilizável com dois tipos diferentes
    Registry<Livro> registro_livros;
    registro_livros.add(Livro("C++20 Advanced", "Stroustrup", "ISBN-101", 5));
    registro_livros.add(Livro("Clean Code", "Robert Martin", "ISBN-102", 2));

    Registry<Revista> registro_revistas;
    registro_revistas.add(Revista("Tech Monthly", "REV-001", 12));

    // Q1 (D): DEMONSTRAÇÃO DE VIOLAÇÃO DO CONCEPT (Descomentar para testar o erro de compilação)
    // Registry<int> registro_invalido;
    // ERRO DE COMPILAÇÃO: 'int' nao satisfaz o concept 'Calculavel'

    std::cout << "Livros no registro generico: " << registro_livros.size() << "\n";
    std::cout << "Revistas no registro generico: " << registro_revistas.size() << "\n";
    std::cout << "Instancias vivas de ItemAcervo (via CRTP): " << Counted<ItemAcervo>::alive() << "\n";

    std::vector<Livro> catalogo_livros = {
        Livro("Design Patterns", "GoF", "001", 3),
        Livro("Refactoring", "Fowler", "002", 0),
        Livro("Effective Modern C++", "Meyers", "003", 4)
    };

    namespace rv = std::ranges::views;
    auto titulos_disponiveis = catalogo_livros
        | rv::filter([](const Livro& l) { return l.available_copies() > 0; })
        | rv::transform([](const Livro& l) { return l.title(); });

    std::cout << "\nLivros disponiveis (via Pipeline Ranges C++20):\n";
    for (const auto& titulo : titulos_disponiveis) {
        std::cout << " - " << titulo << "\n";
    }

    // Q2: Tratamento de Erros
    try {
        std::cout << "Tentando operacao invalida...\n";
        throw ValidacaoInvalidaException("O ISBN do livro nao pode conter simbolos especiais!");
    } catch (const ErroDominio& e) {
        std::cout << "[CAPTURADO PELA BASE] " << e.what() << "\n";
    }

    std::vector<std::shared_ptr<ItemAcervo>> acervo_misto = {
        std::make_shared<Livro>("Domain-Driven Design", "Evans", "DDD-01", 2),
        std::make_shared<Revista>("Scientific American", "SA-99", 500)
    };

    auto busca_sucesso = buscar_por_codigo(acervo_misto, "DDD-01");
    if (busca_sucesso.has_value()) {
        std::cout << "Busca por 'DDD-01': Encontrado -> " << busca_sucesso.value()->get_titulo() << "\n";
    }

    auto busca_falha = buscar_por_codigo(acervo_misto, "CODIGO_INEXISTENTE");
    if (!busca_falha.has_value()) {
        std::cout << "Busca por 'CODIGO_INEXISTENTE': Retornou std::nullopt (Correto!)\n";
    }

    ResultadoOperacao res1 = processar_requisicao(true, acervo_misto[0]);
    ResultadoOperacao res2 = processar_requisicao(false, nullptr);

    auto visitante = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::shared_ptr<ItemAcervo>>) {
            std::cout << "Variant Sucesso: " << arg->get_titulo() << "\n";
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Variant Erro: " << arg << "\n";
        }
    };

    std::visit(visitante, res1);
    std::visit(visitante, res2);

    // Q3: STL & Concorrência
    std::map<std::string, std::shared_ptr<ItemAcervo>> indice_ordenado;
    indice_ordenado["B001"] = acervo_misto[0];
    indice_ordenado["A002"] = acervo_misto[1];

    // Q3 (B): Algoritmo 1 - std::count_if com lambda capturando taxa_limite
    float taxa_limite = 1.50f;
    auto qtd_acima_limite = std::count_if(acervo_misto.begin(), acervo_misto.end(),
        [taxa_limite](const std::shared_ptr<ItemAcervo>& item) {
            return item->calcular() > taxa_limite;
        });
    std::cout << "Qtd de itens com taxa diaria > " << taxa_limite << ": " << qtd_acima_limite << "\n";

    // Q3 (B): Algoritmo 2 - std::accumulate
    float soma_taxas = std::accumulate(acervo_misto.begin(), acervo_misto.end(), 0.0f,
        [](float acc, const std::shared_ptr<ItemAcervo>& item) {
            return acc + item->calcular();
        });
    std::cout << "Soma acumulada das taxas: R$ " << soma_taxas << "\n";

    // Q3 (B): Algoritmo 3 - std::sort ordenando catalogo por titulo
    std::sort(catalogo_livros.begin(), catalogo_livros.end(), [](const Livro& a, const Livro& b) {
        return a.title() < b.title();
    });
    std::cout << "Livro ordenado alfabeticamente (std::sort): " << catalogo_livros[0].title() << "\n";

    // Q3 (C) & (D): Concorrência com std::async, std::mutex e std::lock_guard
    std::mutex mtx;
    double total_taxas_paralelo = 0.0;
    std::vector<std::future<double>> futuros;

    for (const auto& item : acervo_misto) {
        futuros.push_back( 
            std::async(
                std::launch::async,
                    [item, &mtx, &total_taxas_paralelo]() {

                        double taxa = item->calcular();

                            {
                                std::lock_guard<std::mutex> lock(mtx);
                                total_taxas_paralelo += taxa;
                            }

                        return taxa;
                 }
            )
);
    }

    for (auto& f : futuros) {
        f.get();
    }
    std::cout << "Calculo paralelo com threads/mutex finalizado! Total: R$ " << total_taxas_paralelo << "\n";

    // Q4: Serialização JSON e SOLID (DIP)
    MemoryRepository repo_memoria;
    AppCore app_teste(repo_memoria);
    app_teste.adicionar_item(acervo_misto[0]);
    app_teste.adicionar_item(acervo_misto[1]);
    app_teste.salvar();
    std::cout << "Dados salvos no MemoryRepository! Itens salvos: "
              << app_teste.get_estado().acervo.size() << "\n";

    JsonRepository repo_json("estado_biblioteca.json");
    AppCore app_producao(repo_json);
    app_producao.adicionar_item(acervo_misto[0]);
    app_producao.adicionar_item(acervo_misto[1]);
    app_producao.salvar();
    std::cout << "Estado serializado com sucesso no arquivo 'estado_biblioteca.json'!\n";

    return 0;
}