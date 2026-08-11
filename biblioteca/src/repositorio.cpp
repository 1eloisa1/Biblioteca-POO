#include "repositorio.hpp"

// Q4 (D): JsonRepository
JsonRepository::JsonRepository(std::string filename)
    : filename_(std::move(filename)) {}

void JsonRepository::save(const EstadoSistema& estado) {
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

EstadoSistema JsonRepository::load() {
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

// Q4 (D): MemoryRepository
void MemoryRepository::save(const EstadoSistema& estado) {
    estado_armazenado_ = estado;
}

EstadoSistema MemoryRepository::load() {
    return estado_armazenado_;
}

// Q4 (C): AppCore desacoplado
AppCore::AppCore(Repository& repo) : repo_(repo) {}

void AppCore::adicionar_item(std::shared_ptr<ItemAcervo> item) {
    estado_.acervo.push_back(item);
}

void AppCore::salvar() { repo_.save(estado_); }
void AppCore::carregar() { estado_ = repo_.load(); }
const EstadoSistema& AppCore::get_estado() const { return estado_; }