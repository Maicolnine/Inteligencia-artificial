#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonEnviar_clicked();
    void on_pushButtonAgregar_clicked(); // <-- NUEVO
    void on_pushButton_clicked(); // Para el botón "Enseñar"

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
