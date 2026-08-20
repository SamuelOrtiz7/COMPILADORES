#include "MainWindow.h"

#include <QTabWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QTextBrowser>
#include <QFont>

#include "Punto1Estructuras.h"
#include "Punto2Alfabeto.h"
#include "Punto3Regex.h"
using namespace std;

MainWindow::MainWindow(QWidget *Parent)
    : QMainWindow(Parent)
{
    setWindowTitle("Analizador Lexico");

    QTabWidget *Tabs = new QTabWidget(this);
    Tabs->addTab(crearTabPunto1(), "1-Estructuras de datos");
    Tabs->addTab(crearTabPunto2(), "2-Alfabeto y expresiones regulares");
    Tabs->addTab(crearTabPunto3(), "3-Regex y conteo");

    setCentralWidget(Tabs);
}

//Estructuras de datos
QWidget *MainWindow::crearTabPunto1()
{
    QWidget *W = new QWidget;
    QVBoxLayout *Layout = new QVBoxLayout(W);

    QLabel *Titulo = new QLabel(
        "Analizador basado en un automata finito (estructuras de datos), "
        "sin usar expresiones regulares.\nEscribe una cadena y presiona "
        "\"Analizar\".");
    Titulo->setWordWrap(true);
    Layout->addWidget(Titulo);

    EntradaP1 = new QPlainTextEdit;
    EntradaP1->setPlaceholderText("Ej: 123 abc ABC var1 Var_2 + - ;");
    EntradaP1->setFixedHeight(80);
    Layout->addWidget(EntradaP1);

    QPushButton *BtnAnalizar = new QPushButton("Analizar");
    Layout->addWidget(BtnAnalizar);
    connect(BtnAnalizar, &QPushButton::clicked, this, &MainWindow::onAnalizarPunto1);

    TablaP1 = new QTableWidget(0, 2);
    TablaP1->setHorizontalHeaderLabels({"Lexema", "Tipo de token"});
    TablaP1->horizontalHeader()->setStretchLastSection(true);
    TablaP1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Layout->addWidget(TablaP1);

    return W;
}

void MainWindow::onAnalizarPunto1()
{
    string Entrada = EntradaP1->toPlainText().toStdString();

    Punto1::AutomataLexico Automata;
    Punto1::ListaTokens Tokens = Automata.analizar(Entrada);

    TablaP1->setRowCount(Tokens.Cantidad);
    for (int I = 0; I < Tokens.Cantidad; ++I)
    {
        TablaP1->setItem(I, 0, new QTableWidgetItem(QString::fromStdString(Tokens.Datos[I].Lexema)));
        TablaP1->setItem(I, 1, new QTableWidgetItem(QString::fromStdString(Punto1::nombreTipo(Tokens.Datos[I].Tipo))));
    }
}

//Diccionario/Alfabeto y expresiones regulares
QWidget *MainWindow::crearTabPunto2()
{
    QWidget *W = new QWidget;
    QVBoxLayout *Layout = new QVBoxLayout(W);

    QLabel *Titulo = new QLabel(
        "Definicion formal del alfabeto (Sigma) y de las expresiones "
        "regulares para cada tipo de palabra del lenguaje regular.");
    Titulo->setWordWrap(true);
    Layout->addWidget(Titulo);

    InfoP2 = new QTextBrowser;
    QFont Mono("Monospace");
    Mono.setStyleHint(QFont::TypeWriter);
    InfoP2->setFont(Mono);
    InfoP2->setPlainText(QString::fromStdString(Punto2::descripcionCompleta()));
    Layout->addWidget(InfoP2);

    return W;
}

//Expresiones regulares y conteo
QWidget *MainWindow::crearTabPunto3()
{
    QWidget *W = new QWidget;
    QVBoxLayout *Layout = new QVBoxLayout(W);

    QLabel *Titulo = new QLabel(
        "Analizador basado en expresiones regulares (regex) que "
        "clasifica y cuenta cada categoria.\nEscribe una cadena y presiona "
        "\"Analizar\".");
    Titulo->setWordWrap(true);
    Layout->addWidget(Titulo);

    EntradaP3 = new QPlainTextEdit;
    EntradaP3->setPlaceholderText("Ej: 123 abc ABC var1 Var_2 + - ;");
    EntradaP3->setFixedHeight(80);
    Layout->addWidget(EntradaP3);

    QPushButton *BtnAnalizar = new QPushButton("Analizar");
    Layout->addWidget(BtnAnalizar);
    connect(BtnAnalizar, &QPushButton::clicked, this, &MainWindow::onAnalizarPunto3);

    QHBoxLayout *Fila = new QHBoxLayout;

    TablaP3 = new QTableWidget(0, 2);
    TablaP3->setHorizontalHeaderLabels({"Lexema", "Tipo de token"});
    TablaP3->horizontalHeader()->setStretchLastSection(true);
    TablaP3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Fila->addWidget(TablaP3, 2);

    ConteoP3 = new QTableWidget(6, 2);
    ConteoP3->setHorizontalHeaderLabels({"Categoria", "Cantidad"});
    ConteoP3->horizontalHeader()->setStretchLastSection(true);
    ConteoP3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    Fila->addWidget(ConteoP3, 1);

    Layout->addLayout(Fila);

    return W;
}

void MainWindow::onAnalizarPunto3()
{
    string Entrada = EntradaP3->toPlainText().toStdString();

    Punto3::AnalizadorRegex Analizador;
    Punto3::ListaTokens Tokens = Analizador.analizar(Entrada);
    Punto3::Conteo ConteoResultado = Analizador.contar(Tokens);

    // Tabla de tokens
    TablaP3->setRowCount(Tokens.Cantidad);
    for (int I = 0; I < Tokens.Cantidad; ++I)
    {
        TablaP3->setItem(I, 0, new QTableWidgetItem(QString::fromStdString(Tokens.Datos[I].Lexema)));
        TablaP3->setItem(I, 1, new QTableWidgetItem(QString::fromStdString(Punto3::nombreTipo(Tokens.Datos[I].Tipo))));
    }

    // Tabla de conteo por categoria
    struct Fila
    {
        QString Nombre;
        int Valor;
    };
    Fila Filas[6] = {
        {"Numero entero", ConteoResultado.Enteros},
        {"Palabra minuscula", ConteoResultado.Minusculas},
        {"Palabra mayuscula", ConteoResultado.Mayusculas},
        {"Identificador", ConteoResultado.Identificadores},
        {"Simbolo", ConteoResultado.Simbolos},
        {"TOTAL", ConteoResultado.total()},
    };

    ConteoP3->setRowCount(6);
    for (int I = 0; I < 6; ++I)
    {
        ConteoP3->setItem(I, 0, new QTableWidgetItem(Filas[I].Nombre));
        ConteoP3->setItem(I, 1, new QTableWidgetItem(QString::number(Filas[I].Valor)));
    }
}