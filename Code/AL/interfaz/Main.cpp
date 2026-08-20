#include <QApplication>
#include "MainWindow.h"

int main(int Argc, char *Argv[])
{
    QApplication App(Argc, Argv);

    MainWindow Ventana;
    Ventana.resize(900, 650);
    Ventana.show();

    return App.exec();
}
