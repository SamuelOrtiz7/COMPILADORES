#ifndef PUNTO2ALFABETO_H
#define PUNTO2ALFABETO_H

#include <string>

using namespace std;


namespace Punto2
{
    extern const string SigmaDescripcion;

    extern const string RegexEntero;          
    extern const string RegexMinuscula;       
    extern const string RegexMayuscula;       
    extern const string RegexIdentificador;    
    extern const string RegexSimboloCompuesto; 
    extern const string RegexSimbolo;          

    extern const string RegexTokenizador;


    string descripcionCompleta();

}

#endif 
