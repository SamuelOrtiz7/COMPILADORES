/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupIdentificacion;
    QFormLayout *formIdentificacion;
    QLabel *labelN;
    QSpinBox *spinN;
    QLabel *labelS;
    QSpinBox *spinS;
    QLabel *labelD;
    QSpinBox *spinD;
    QLabel *labelQ0;
    QSpinBox *spinQ0;
    QLabel *labelT;
    QSpinBox *spinT;
    QLabel *labelC;
    QSpinBox *spinC;
    QGroupBox *groupAlfabetoFinales;
    QFormLayout *formAlfabetoFinales;
    QLabel *labelAlfabeto;
    QLineEdit *lineAlfabeto;
    QLabel *labelFinales;
    QLineEdit *lineFinales;
    QGroupBox *groupTransiciones;
    QVBoxLayout *verticalLayoutTransiciones;
    QPlainTextEdit *transicionesEdit;
    QGroupBox *groupCadenas;
    QFormLayout *formCadenas;
    QLabel *labelCadena1;
    QLineEdit *cadena1;
    QLabel *labelCadena2;
    QLineEdit *cadena2;
    QLabel *labelCadena3;
    QLineEdit *cadena3;
    QLabel *labelCadena4;
    QLineEdit *cadena4;
    QLabel *labelCadena5;
    QLineEdit *cadena5;
    QHBoxLayout *horizontalLayoutBotones;
    QPushButton *ejecutarBtn;
    QPushButton *limpiarBtn;
    QLabel *labelResultado;
    QPlainTextEdit *salidaEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(560, 760);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupIdentificacion = new QGroupBox(centralwidget);
        groupIdentificacion->setObjectName("groupIdentificacion");
        formIdentificacion = new QFormLayout(groupIdentificacion);
        formIdentificacion->setObjectName("formIdentificacion");
        labelN = new QLabel(groupIdentificacion);
        labelN->setObjectName("labelN");

        formIdentificacion->setWidget(0, QFormLayout::ItemRole::LabelRole, labelN);

        spinN = new QSpinBox(groupIdentificacion);
        spinN->setObjectName("spinN");
        spinN->setMinimum(1);
        spinN->setMaximum(100);
        spinN->setValue(3);

        formIdentificacion->setWidget(0, QFormLayout::ItemRole::FieldRole, spinN);

        labelS = new QLabel(groupIdentificacion);
        labelS->setObjectName("labelS");

        formIdentificacion->setWidget(1, QFormLayout::ItemRole::LabelRole, labelS);

        spinS = new QSpinBox(groupIdentificacion);
        spinS->setObjectName("spinS");
        spinS->setMinimum(1);
        spinS->setMaximum(100);
        spinS->setValue(2);

        formIdentificacion->setWidget(1, QFormLayout::ItemRole::FieldRole, spinS);

        labelD = new QLabel(groupIdentificacion);
        labelD->setObjectName("labelD");

        formIdentificacion->setWidget(2, QFormLayout::ItemRole::LabelRole, labelD);

        spinD = new QSpinBox(groupIdentificacion);
        spinD->setObjectName("spinD");
        spinD->setMinimum(1);
        spinD->setMaximum(10000);
        spinD->setValue(6);

        formIdentificacion->setWidget(2, QFormLayout::ItemRole::FieldRole, spinD);

        labelQ0 = new QLabel(groupIdentificacion);
        labelQ0->setObjectName("labelQ0");

        formIdentificacion->setWidget(3, QFormLayout::ItemRole::LabelRole, labelQ0);

        spinQ0 = new QSpinBox(groupIdentificacion);
        spinQ0->setObjectName("spinQ0");
        spinQ0->setMinimum(1);
        spinQ0->setMaximum(100);
        spinQ0->setValue(1);

        formIdentificacion->setWidget(3, QFormLayout::ItemRole::FieldRole, spinQ0);

        labelT = new QLabel(groupIdentificacion);
        labelT->setObjectName("labelT");

        formIdentificacion->setWidget(4, QFormLayout::ItemRole::LabelRole, labelT);

        spinT = new QSpinBox(groupIdentificacion);
        spinT->setObjectName("spinT");
        spinT->setMinimum(0);
        spinT->setMaximum(100);
        spinT->setValue(1);

        formIdentificacion->setWidget(4, QFormLayout::ItemRole::FieldRole, spinT);

        labelC = new QLabel(groupIdentificacion);
        labelC->setObjectName("labelC");

        formIdentificacion->setWidget(5, QFormLayout::ItemRole::LabelRole, labelC);

        spinC = new QSpinBox(groupIdentificacion);
        spinC->setObjectName("spinC");
        spinC->setMinimum(0);
        spinC->setMaximum(5);
        spinC->setValue(4);

        formIdentificacion->setWidget(5, QFormLayout::ItemRole::FieldRole, spinC);


        verticalLayout->addWidget(groupIdentificacion);

        groupAlfabetoFinales = new QGroupBox(centralwidget);
        groupAlfabetoFinales->setObjectName("groupAlfabetoFinales");
        formAlfabetoFinales = new QFormLayout(groupAlfabetoFinales);
        formAlfabetoFinales->setObjectName("formAlfabetoFinales");
        labelAlfabeto = new QLabel(groupAlfabetoFinales);
        labelAlfabeto->setObjectName("labelAlfabeto");

        formAlfabetoFinales->setWidget(0, QFormLayout::ItemRole::LabelRole, labelAlfabeto);

        lineAlfabeto = new QLineEdit(groupAlfabetoFinales);
        lineAlfabeto->setObjectName("lineAlfabeto");

        formAlfabetoFinales->setWidget(0, QFormLayout::ItemRole::FieldRole, lineAlfabeto);

        labelFinales = new QLabel(groupAlfabetoFinales);
        labelFinales->setObjectName("labelFinales");

        formAlfabetoFinales->setWidget(1, QFormLayout::ItemRole::LabelRole, labelFinales);

        lineFinales = new QLineEdit(groupAlfabetoFinales);
        lineFinales->setObjectName("lineFinales");

        formAlfabetoFinales->setWidget(1, QFormLayout::ItemRole::FieldRole, lineFinales);


        verticalLayout->addWidget(groupAlfabetoFinales);

        groupTransiciones = new QGroupBox(centralwidget);
        groupTransiciones->setObjectName("groupTransiciones");
        verticalLayoutTransiciones = new QVBoxLayout(groupTransiciones);
        verticalLayoutTransiciones->setObjectName("verticalLayoutTransiciones");
        transicionesEdit = new QPlainTextEdit(groupTransiciones);
        transicionesEdit->setObjectName("transicionesEdit");
        QFont font;
        font.setFamilies({QString::fromUtf8("monospace")});
        transicionesEdit->setFont(font);

        verticalLayoutTransiciones->addWidget(transicionesEdit);


        verticalLayout->addWidget(groupTransiciones);

        groupCadenas = new QGroupBox(centralwidget);
        groupCadenas->setObjectName("groupCadenas");
        formCadenas = new QFormLayout(groupCadenas);
        formCadenas->setObjectName("formCadenas");
        labelCadena1 = new QLabel(groupCadenas);
        labelCadena1->setObjectName("labelCadena1");

        formCadenas->setWidget(0, QFormLayout::ItemRole::LabelRole, labelCadena1);

        cadena1 = new QLineEdit(groupCadenas);
        cadena1->setObjectName("cadena1");

        formCadenas->setWidget(0, QFormLayout::ItemRole::FieldRole, cadena1);

        labelCadena2 = new QLabel(groupCadenas);
        labelCadena2->setObjectName("labelCadena2");

        formCadenas->setWidget(1, QFormLayout::ItemRole::LabelRole, labelCadena2);

        cadena2 = new QLineEdit(groupCadenas);
        cadena2->setObjectName("cadena2");

        formCadenas->setWidget(1, QFormLayout::ItemRole::FieldRole, cadena2);

        labelCadena3 = new QLabel(groupCadenas);
        labelCadena3->setObjectName("labelCadena3");

        formCadenas->setWidget(2, QFormLayout::ItemRole::LabelRole, labelCadena3);

        cadena3 = new QLineEdit(groupCadenas);
        cadena3->setObjectName("cadena3");

        formCadenas->setWidget(2, QFormLayout::ItemRole::FieldRole, cadena3);

        labelCadena4 = new QLabel(groupCadenas);
        labelCadena4->setObjectName("labelCadena4");

        formCadenas->setWidget(3, QFormLayout::ItemRole::LabelRole, labelCadena4);

        cadena4 = new QLineEdit(groupCadenas);
        cadena4->setObjectName("cadena4");

        formCadenas->setWidget(3, QFormLayout::ItemRole::FieldRole, cadena4);

        labelCadena5 = new QLabel(groupCadenas);
        labelCadena5->setObjectName("labelCadena5");

        formCadenas->setWidget(4, QFormLayout::ItemRole::LabelRole, labelCadena5);

        cadena5 = new QLineEdit(groupCadenas);
        cadena5->setObjectName("cadena5");

        formCadenas->setWidget(4, QFormLayout::ItemRole::FieldRole, cadena5);


        verticalLayout->addWidget(groupCadenas);

        horizontalLayoutBotones = new QHBoxLayout();
        horizontalLayoutBotones->setObjectName("horizontalLayoutBotones");
        ejecutarBtn = new QPushButton(centralwidget);
        ejecutarBtn->setObjectName("ejecutarBtn");

        horizontalLayoutBotones->addWidget(ejecutarBtn);

        limpiarBtn = new QPushButton(centralwidget);
        limpiarBtn->setObjectName("limpiarBtn");

        horizontalLayoutBotones->addWidget(limpiarBtn);


        verticalLayout->addLayout(horizontalLayoutBotones);

        labelResultado = new QLabel(centralwidget);
        labelResultado->setObjectName("labelResultado");

        verticalLayout->addWidget(labelResultado);

        salidaEdit = new QPlainTextEdit(centralwidget);
        salidaEdit->setObjectName("salidaEdit");
        salidaEdit->setFont(font);
        salidaEdit->setReadOnly(true);

        verticalLayout->addWidget(salidaEdit);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AFD - Automata Finito Determinista", nullptr));
        groupIdentificacion->setTitle(QCoreApplication::translate("MainWindow", "Identificacion del AFD", nullptr));
        labelN->setText(QCoreApplication::translate("MainWindow", "N (numero de estados):", nullptr));
        labelS->setText(QCoreApplication::translate("MainWindow", "S (tamano del alfabeto):", nullptr));
        labelD->setText(QCoreApplication::translate("MainWindow", "D (numero de transiciones):", nullptr));
        labelQ0->setText(QCoreApplication::translate("MainWindow", "q0 (estado inicial):", nullptr));
        labelT->setText(QCoreApplication::translate("MainWindow", "T (numero de estados finales):", nullptr));
        labelC->setText(QCoreApplication::translate("MainWindow", "C (cantidad de cadenas, maximo 5):", nullptr));
        groupAlfabetoFinales->setTitle(QCoreApplication::translate("MainWindow", "Alfabeto y estados finales", nullptr));
        labelAlfabeto->setText(QCoreApplication::translate("MainWindow", "Simbolos de Sigma (separados por espacio):", nullptr));
        lineAlfabeto->setText(QCoreApplication::translate("MainWindow", "0 1", nullptr));
        labelFinales->setText(QCoreApplication::translate("MainWindow", "Estados finales F (separados por espacio):", nullptr));
        lineFinales->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        groupTransiciones->setTitle(QCoreApplication::translate("MainWindow", "Transiciones (una por linea: origen simbolo destino)", nullptr));
        transicionesEdit->setPlainText(QCoreApplication::translate("MainWindow", "1 1 2\n"
"1 0 3\n"
"2 0 3\n"
"2 1 2\n"
"3 0 2\n"
"3 1 2", nullptr));
        groupCadenas->setTitle(QCoreApplication::translate("MainWindow", "Cadenas a evaluar (maximo 5, se usan las primeras C)", nullptr));
        labelCadena1->setText(QCoreApplication::translate("MainWindow", "Cadena 1:", nullptr));
        cadena1->setText(QCoreApplication::translate("MainWindow", "101", nullptr));
        labelCadena2->setText(QCoreApplication::translate("MainWindow", "Cadena 2:", nullptr));
        cadena2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelCadena3->setText(QCoreApplication::translate("MainWindow", "Cadena 3:", nullptr));
        cadena3->setText(QCoreApplication::translate("MainWindow", "11", nullptr));
        labelCadena4->setText(QCoreApplication::translate("MainWindow", "Cadena 4:", nullptr));
        cadena4->setText(QCoreApplication::translate("MainWindow", "1000100001", nullptr));
        labelCadena5->setText(QCoreApplication::translate("MainWindow", "Cadena 5:", nullptr));
        ejecutarBtn->setText(QCoreApplication::translate("MainWindow", "Ejecutar", nullptr));
        limpiarBtn->setText(QCoreApplication::translate("MainWindow", "Limpiar", nullptr));
        labelResultado->setText(QCoreApplication::translate("MainWindow", "Resultado:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
