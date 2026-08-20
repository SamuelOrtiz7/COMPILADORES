#include "Punto2Alfabeto.h"

using namespace std;

namespace Punto2
{

    const string SigmaDescripcion =
        "Σ = { 0..9 } U { a..z } U { A..Z } U { _ } U { simbolos especiales: "
        "+ - * / = ( ) { } [ ] ; , . : < > ! ? \" ' % & | ^ ~ @ # $ etc. } U "
        "{ simbolos compuestos: == != <= >= ++ -- += -= *= /= && || << >> }";

    const string RegexEntero = "[+-]?[0-9]+";
    const string RegexMinuscula = "[a-z]+";
    const string RegexMayuscula = "[A-Z]+";
    const string RegexIdentificador = "[A-Za-z_][A-Za-z0-9_]*";
    const string RegexSimboloCompuesto =
        "==|!=|<=|>=|\\+\\+|--|\\+=|-=|\\*=|/=|&&|\\|\\||<<|>>";
    const string RegexSimbolo = "[^A-Za-z0-9_\\s]";

    const string RegexTokenizador =
        RegexSimboloCompuesto + "|" + RegexEntero + "|" + RegexIdentificador + "|" + RegexSimbolo;

    string descripcionCompleta()
    {
        return R"(ALFABETO (Σ)

)" + SigmaDescripcion +
               R"(


    EXPRESIONES REGULARES POR CATEGORIA

    1) Numero entero
    ER: )" + RegexEntero +
                R"(
    Descripcion: representa una o mas cifras numericas consecutivas,
    con signo + o - opcional al inicio (ej: 123, -5, +5).


    2) Palabra en minusculas
    ER: )" + RegexMinuscula +
                R"(
    Descripcion: cadena formada unicamente por letras minusculas
    del rango a-z.


    3) Palabra en mayusculas
    ER: )" + RegexMayuscula +
                R"(
    Descripcion: cadena formada unicamente por letras mayusculas
    del rango A-Z.


    4) Identificador (nombre de variable)
    ER: )" + RegexIdentificador +
                R"(
    Descripcion: inicia con una letra o guion bajo y puede continuar
    con letras, digitos o guion bajo.

    Ejemplos validos:
    variable
    contador1
    _valor
    MiVariable

    Las palabras que contienen solamente letras minusculas o solamente
    letras mayusculas se clasifican primero como PALABRA_MINUSCULA o
    PALABRA_MAYUSCULA.


    5) Simbolo compuesto
    ER: )" + RegexSimboloCompuesto +
                R"(
    Descripcion: pares de caracteres que forman un unico operador.

    Ejemplos:
    == != <= >= ++ -- += -= *= /= && || << >>


    6) Simbolo
    ER: )" + RegexSimbolo +
                R"(
    Descripcion: representa cualquier caracter que no sea letra,
    numero, guion bajo o espacio.

    Ejemplos:
    + - * / = ( ) { } [ ] ; , .


    EXPRESION TOKENIZADORA

    La siguiente expresion permite recorrer una cadena de entrada y
    separar sus elementos para clasificarlos:

    )" + RegexTokenizador +
                R"(

    )";
        }

    }