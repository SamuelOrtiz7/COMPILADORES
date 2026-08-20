#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;
class QTableWidget;
class QTextBrowser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *Parent = nullptr);

private slots:
    void onAnalizarPunto1();
    void onAnalizarPunto3();

private:
    QWidget *crearTabPunto1();
    QWidget *crearTabPunto2();
    QWidget *crearTabPunto3();

    // ---- Punto 1: automata / estructuras de datos ----
    QPlainTextEdit *EntradaP1 = nullptr;
    QTableWidget *TablaP1 = nullptr;

    // ---- Punto 2: alfabeto y expresiones regulares ----
    QTextBrowser *InfoP2 = nullptr;

    // ---- Punto 3: expresiones regulares + conteo ----
    QPlainTextEdit *EntradaP3 = nullptr;
    QTableWidget *TablaP3 = nullptr;
    QTableWidget *ConteoP3 = nullptr;
};

#endif // MAINWINDOW_H
