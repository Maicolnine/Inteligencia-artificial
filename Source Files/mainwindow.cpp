#include "ia.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ia.h"
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
    ui->textEditRespuesta->setText("¡Esto es una prueba!");
}

