#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "afd.h"

#include <QLineEdit>
#include <QMessageBox>
#include <QString>

#include <exception>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->ejecutarBtn, &QPushButton::clicked, this, &MainWindow::onEjecutar);
    connect(ui->limpiarBtn, &QPushButton::clicked, this, &MainWindow::onLimpiar);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onEjecutar() {
    ui->salidaEdit->clear();

    try {
        int q0 = ui->spinQ0->value();
        int cantidadCadenas = ui->spinC->value();

        QLineEdit *camposCadena[5] = {
            ui->cadena1, ui->cadena2, ui->cadena3, ui->cadena4, ui->cadena5};

        std::string cadenas[5];
        for (int i = 0; i < 5; i++)
            cadenas[i] = camposCadena[i]->text().toStdString();

        std::string salida = ejecutarAFD(q0,
                                          ui->lineAlfabeto->text().toStdString(),
                                          ui->lineFinales->text().toStdString(),
                                          ui->transicionesEdit->toPlainText().toStdString(),
                                          cadenas,
                                          cantidadCadenas);

        ui->salidaEdit->setPlainText(QString::fromStdString(salida));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error",
            QString("Ocurrio un error al procesar la entrada:\n%1").arg(e.what()));
    }
}

void MainWindow::onLimpiar() {
    ui->spinN->setValue(ui->spinN->minimum());
    ui->spinS->setValue(ui->spinS->minimum());
    ui->spinD->setValue(ui->spinD->minimum());
    ui->spinQ0->setValue(ui->spinQ0->minimum());
    ui->spinT->setValue(ui->spinT->minimum());
    ui->spinC->setValue(ui->spinC->minimum());

    ui->lineAlfabeto->clear();
    ui->lineFinales->clear();
    ui->transicionesEdit->clear();

    ui->cadena1->clear();
    ui->cadena2->clear();
    ui->cadena3->clear();
    ui->cadena4->clear();
    ui->cadena5->clear();

    ui->salidaEdit->clear();
}
