#include "repositorio.hpp"

JsonRepository::JsonRepository(std::string filename)
    : filename_(std::move(filename)) {}

void JsonRepository::save(const EstadoSistema& estado) {
    json j;
    j["version"] = estado.version;
    
    json items_array = json::array();
    for (const auto& item : estado.acervo) {
        if (auto livro = std::dynamic_pointer_cast<Livro>(item)) {
            json j_item;
            to_json(j_item, *livro);
            items_array.push_back(j_item);
        } else if (auto revista = std::dynamic_pointer_cast<Revista>(item)) {
            json j_item;
            to_json(j_item, *revista);
            items_array.push_back(j_item);
        }
    }
    j["itens"] = items_array;

    std::ofstream file(filename_);
    file << j.dump(4);
}

EstadoSistema JsonRepository::load() {
    std::ifstream file(filename_);
    if (!file.is_open()) return EstadoSistema{};

    json j;
    file >> j;

    EstadoSistema estado;
    estado.version = j.value("version", 1);

    // Q4 (B): Tratamento explícito baseado na versão do schema
    if (estado.version == 1) {
        for (const auto& item_json : j.at("itens")) {
            std::string type = item_json.at("type").get<std::string>();
            if (type == "Livro") {
                Livro l("", "", "", 0);
                from_json(item_json, l);
                estado.acervo.push_back(std::make_shared<Livro>(l));
            } else if (type == "Revista") {
                Revista r("", "", 0);
                from_json(item_json, r);
                estado.acervo.push_back(std::make_shared<Revista>(r));
            }
        }
    } else {
        throw ValidacaoInvalidaException("Versao de esquema JSON nao suportada!");
    }
    return estado;
}

void MemoryRepository::save(const EstadoSistema& estado) {
    estado_armazenado_ = estado;
}

EstadoSistema MemoryRepository::load() {
    return estado_armazenado_;
}

AppCore::AppCore(Repository& repo) : repo_(repo) {}

void AppCore::adicionar_item(std::shared_ptr<ItemAcervo> item) {
    estado_.acervo.push_back(item);
}

void AppCore::remover_item(std::size_t index) {
    if (index < estado_.acervo.size()) {
        estado_.acervo.erase(estado_.acervo.begin() + index);
    }
}

void AppCore::salvar() { repo_.save(estado_); }
void AppCore::carregar() { estado_ = repo_.load(); }
const EstadoSistema& AppCore::get_estado() const { return estado_; }