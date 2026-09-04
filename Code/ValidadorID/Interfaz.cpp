#include "Logica.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class VentanaPrincipal : public QWidget
{
public:
    VentanaPrincipal()
    {
        setWindowTitle("Identificador de CURP, RFC e INE");

        Campo = new QLineEdit;
        Campo->setPlaceholderText("Escribe la CURP, RFC o clave de elector INE");

        QPushButton *BotonVerificar = new QPushButton("Verificar");
        connect(BotonVerificar, &QPushButton::clicked, this, &VentanaPrincipal::verificar);

        Resultado = new QLabel("-");

        QVBoxLayout *Layout = new QVBoxLayout(this);
        Layout->addWidget(Campo);
        Layout->addWidget(BotonVerificar);
        Layout->addWidget(Resultado);
    }

private:
    void verificar()
    {
        std::string Texto = Campo->text().trimmed().toUpper().toStdString();

        Logica::TipoIdentificador Tipo = Logica::identificar(Texto);
        Resultado->setText(QString::fromStdString(Logica::nombreTipo(Tipo)));
    }

    QLineEdit *Campo = nullptr;
    QLabel *Resultado = nullptr;
};

int main(int Argc, char *Argv[])
{
    QApplication App(Argc, Argv);

    VentanaPrincipal Ventana;
    Ventana.resize(400, 150);
    Ventana.show();

    return App.exec();
}
