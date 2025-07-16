#include "ia.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cargar_conocimiento("conocimiento.txt");
}

MainWindow::~MainWindow()
{
    guardar_conocimiento("conocimiento.txt");
    delete ui;
}

void MainWindow::on_pushButtonEnviar_clicked()
{
    // Obtener la pregunta del usuario desde el QLineEdit
    QString pregunta = ui->lineEditPreguntaNueva->text();
    std::string pregunta_std = pregunta.toStdString();

    // Obtener la respuesta de la IA
    std::string respuesta_std = responder(pregunta_std);

    // Mostrar la respuesta en el QTextEdit
    ui->textEditRespuestaNueva->setText(QString::fromStdString(respuesta_std));
}

void MainWindow::on_pushButtonAgregar_clicked()
{
    std::string pregunta = ui->lineEditPreguntaNueva->text().toStdString();
    std::string respuesta = ui->textEditRespuestaNueva->toPlainText().toStdString();
    if (!pregunta.empty() && !respuesta.empty()) {
        conocimiento[pregunta] = respuesta;
        guardar_conocimiento("conocimiento.txt");
        ui->lineEditPreguntaNueva->clear();
        ui->textEditRespuestaNueva->clear();
        ui->textEditRespuestaNueva->setText("¡Nuevo conocimiento agregado!");
    } else {
        ui->textEditRespuestaNueva->setText("Por favor, completa ambos campos.");
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Obtener la pregunta y respuesta de los campos nuevos
    std::string pregunta = ui->lineEdit->text().toStdString();
    std::string respuesta = ui->lineEdit_2->text().toStdString();

    if (!pregunta.empty() && !respuesta.empty()) {
        conocimiento[pregunta] = respuesta;
        guardar_conocimiento("conocimiento.txt");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->textEditRespuestaNueva->setText("¡He aprendido la respuesta!");
    } else {
        ui->textEditRespuestaNueva->setText("Por favor, escribe la pregunta y la respuesta.");
    }
}
