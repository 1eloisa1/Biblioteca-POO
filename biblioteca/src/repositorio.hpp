#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include "livro.hpp"
#include "revista.hpp"

using json = nlohmann::json;

// Q4 (A) & (B) Estrutura serializável com versão
struct EstadoSistema {
    int version = 1;
    std::vector<std::shared_ptr<ItemAcervo>> acervo;
};

// Q4 (C) DIP: Abstração de infraestrutura
class Repository {
public:
    virtual ~Repository() = default;
    virtual void save(const EstadoSistema& estado) = 0;
    virtual EstadoSistema load() = 0;
};

// Q4 (D) Implementação 1: Produção (JSON File)
class JsonRepository : public Repository {
private:
    std::string filename_;

public:
    explicit JsonRepository(std::string filename) : filename_(std::move(filename)) {}

    void save(const EstadoSistema& estado) override {
        json j;
        j["version"] = estado.version;
        
        json items_array = json::array();
        for (const auto& item : estado.acervo) {
            items_array.push_back(item->to_json());
        }
        j["itens"] = items_array;

        std::ofstream file(filename_);
        file << j.dump(4);
    }

    EstadoSistema load() override {
        std::ifstream file(filename_);
        if (!file.is_open()) return EstadoSistema{};

        json j;
        file >> j;

        EstadoSistema estado;
        estado.version = j.value("version", 1);

        for (const auto& item_json : j.at("itens")) {
            std::string type = item_json.at("type").get<std::string>();
            if (type == "Livro") {
                estado.acervo.push_back(std::make_shared<Livro>(Livro::from_json(item_json)));
            } else if (type == "Revista") {
                estado.acervo.push_back(std::make_shared<Revista>(Revista::from_json(item_json)));
            }
        }
        return estado;
    }
};

// Q4 (D) Implementação 2: Testes (Memory Repository - sem efeitos colaterais no disco)
class MemoryRepository : public Repository {
private:
    EstadoSistema estado_armazenado_;

public:
    void save(const EstadoSistema& estado) override {
        estado_armazenado_ = estado;
    }

    EstadoSistema load() override {
        return estado_armazenado_;
    }
};

// Classe de alto nível que usa DIP
class AppCore {
private:
    Repository& repo_;
    EstadoSistema estado_;

public:
    explicit AppCore(Repository& repo) : repo_(repo) {}

    void adicionar_item(std::shared_ptr<ItemAcervo> item) {
        estado_.acervo.push_back(item);
    }

    void salvar() { repo_.save(estado_); }
    void carregar() { estado_ = repo_.load(); }
    const EstadoSistema& get_estado() const { return estado_; }
};