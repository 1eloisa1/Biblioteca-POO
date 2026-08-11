#include <QApplication>
#include "janela.hpp"
#include "repositorio.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Injeção de dependência do DIP (Q4/Q6)
    JsonRepository repo("estado_biblioteca.json");
    AppCore core(repo);

    JanelaPrincipal janela(core);
    janela.setWindowTitle("Sistema de Biblioteca POO - TP3");
    janela.show();

    return app.exec();
}