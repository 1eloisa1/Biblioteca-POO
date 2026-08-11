#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include "livro.hpp"
#include "revista.hpp"
#include "excecoes.hpp"

using json = nlohmann::json;

struct EstadoSistema {
    int version = 1;
    std::vector<std::shared_ptr<ItemAcervo>> acervo;
};

class Repository {
public:
    virtual ~Repository() = default;
    virtual void save(const EstadoSistema& estado) = 0;
    virtual EstadoSistema load() = 0;
};

class JsonRepository : public Repository {
private:
    std::string filename_;

public:
    explicit JsonRepository(std::string filename);
    void save(const EstadoSistema& estado) override;
    EstadoSistema load() override;
};

class MemoryRepository : public Repository {
private:
    EstadoSistema estado_armazenado_;

public:
    void save(const EstadoSistema& estado) override;
    EstadoSistema load() override;
};

class AppCore {
private:
    Repository& repo_;
    EstadoSistema estado_;

public:
    explicit AppCore(Repository& repo);
    void adicionar_item(std::shared_ptr<ItemAcervo> item);
    void remover_item(std::size_t index);
    void salvar();
    void carregar();
    const EstadoSistema& get_estado() const;
};