#include "janela.hpp"
#include <QMessageBox>

JanelaPrincipal::JanelaPrincipal(AppCore& core, QWidget* parent)
    : QMainWindow(parent), app_core_(core) 
{
    setup_ui();
    atualizar_lista();
}

void JanelaPrincipal::setup_ui() {
    auto* central = new QWidget(this);
    auto* layout_principal = new QVBoxLayout(central);

    // Lista de Itens
    lista_itens_ = new QListWidget(this);
    layout_principal->addWidget(new QLabel("Acervo da Biblioteca:", this));
    layout_principal->addWidget(lista_itens_);

    // Inputs
    auto* layout_inputs = new QHBoxLayout();
    input_titulo_ = new QLineEdit(this);
    input_titulo_->setPlaceholderText("Título");
    input_autor_ = new QLineEdit(this);
    input_autor_->setPlaceholderText("Autor");
    input_isbn_ = new QLineEdit(this);
    input_isbn_->setPlaceholderText("ISBN");

    layout_inputs->addWidget(input_titulo_);
    layout_inputs->addWidget(input_autor_);
    layout_inputs->addWidget(input_isbn_);
    layout_principal->addLayout(layout_inputs);

    // Botões
    auto* layout_botoes = new QHBoxLayout();
    btn_adicionar_ = new QPushButton("Adicionar Livro", this);
    btn_salvar_ = new QPushButton("Salvar (JSON)", this);
    btn_carregar_ = new QPushButton("Carregar (JSON)", this);

    layout_botoes->addWidget(btn_adicionar_);
    layout_botoes->addWidget(btn_salvar_);
    layout_botoes->addWidget(btn_carregar_);
    layout_principal->addLayout(layout_botoes);

    setCentralWidget(central);
    resize(600, 400);

    // Conexão dos Sinais/Slots (GUI é uma camada fina)
    connect(btn_adicionar_, &QPushButton::clicked, [this]() {
        if (input_titulo_->text().isEmpty() || input_isbn_->text().isEmpty()) {
            QMessageBox::warning(this, "Aviso", "Preencha o título e o ISBN!");
            return;
        }

        auto novo_livro = std::make_shared<Livro>(
            input_titulo_->text().toStdString(),
            input_autor_->text().toStdString(),
            input_isbn_->text().toStdString(),
            3
        );

        app_core_.adicionar_item(novo_livro);
        atualizar_lista();

        input_titulo_->clear();
        input_autor_->clear();
        input_isbn_->clear();
    });

    connect(btn_salvar_, &QPushButton::clicked, [this]() {
        app_core_.salvar();
        QMessageBox::information(this, "Sucesso", "Estado do acervo salvo com sucesso em JSON!");
    });

    connect(btn_carregar_, &QPushButton::clicked, [this]() {
        app_core_.carregar();
        atualizar_lista();
        QMessageBox::information(this, "Sucesso", "Estado carregado do JSON com sucesso!");
    });
}

void JanelaPrincipal::atualizar_lista() {
    lista_itens_->clear();
    for (const auto& item : app_core_.get_estado().acervo) {
        QString texto = QString("[%1] %2 (%3)")
                            .arg(QString::fromStdString(item->get_codigo()))
                            .arg(QString::fromStdString(item->get_titulo()))
                            .arg(QString::fromStdString(item->type_name()));
        lista_itens_->addItem(texto);
    }
}