#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <memory>
#include "repositorio.hpp"

class JanelaPrincipal : public QMainWindow {
    Q_OBJECT

private:
    AppCore& app_core_;
    
    QListWidget* lista_itens_;
    QLineEdit* input_titulo_;
    QLineEdit* input_autor_;
    QLineEdit* input_isbn_;
    
    QPushButton* btn_adicionar_;
    QPushButton* btn_salvar_;
    QPushButton* btn_carregar_;

    void setup_ui();
    void atualizar_lista();

public:
    explicit JanelaPrincipal(AppCore& core, QWidget* parent = nullptr);
};