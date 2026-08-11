#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include "livro.hpp"
#include "revista.hpp"

using json = nlohmann::json;

// Q4 (A) & (B): Estrutura serializável com controle de versão
struct EstadoSistema {
    int version = 1;
    std::vector<std::shared_ptr<ItemAcervo>> acervo;
};

// Q4 (C) DIP: Abstração de infraestrutura para persistência (Interface)
class Repository {
public:
    virtual ~Repository() = default;
    virtual void save(const EstadoSistema& estado) = 0;
    virtual EstadoSistema load() = 0;
};

// Q4 (D): Implementação 1 - Produção (Persistência em Arquivo JSON)
class JsonRepository : public Repository {
private:
    std::string filename_;

public:
    explicit JsonRepository(std::string filename);
    void save(const EstadoSistema& estado) override;
    EstadoSistema load() override;
};

// Q4 (D): Implementação 2 - Testes (MemoryRepository sem toque no disco)
class MemoryRepository : public Repository {
private:
    EstadoSistema estado_armazenado_;

public:
    void save(const EstadoSistema& estado) override;
    EstadoSistema load() override;
};

// Q4 (C): Classe de alto nível que usa DIP (Injeção de Dependência)
class AppCore {
private:
    Repository& repo_;
    EstadoSistema estado_;

public:
    explicit AppCore(Repository& repo);
    void adicionar_item(std::shared_ptr<ItemAcervo> item);
    void salvar();
    void carregar();
    const EstadoSistema& get_estado() const;
};