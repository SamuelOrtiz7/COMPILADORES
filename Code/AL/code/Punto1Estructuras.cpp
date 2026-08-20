#include "Punto1Estructuras.h"
#include <cctype>

using namespace std;

namespace Punto1
{

    string nombreTipo(TipoToken Tipo)
    {
        switch (Tipo)
        {
        case TipoToken::ENTERO:
            return "Numero entero";

        case TipoToken::PALABRA_MINUSCULA:
            return "Palabra minuscula";

        case TipoToken::PALABRA_MAYUSCULA:
            return "Palabra mayuscula";

        case TipoToken::IDENTIFICADOR:
            return "Identificador";

        case TipoToken::SIMBOLO:
            return "Simbolo";
        }

        return "Desconocido";
    }

    // Verifica si dos caracteres forman un símbolo compuesto válido
    bool esSimboloCompuesto(char Actual, char Siguiente)
    {
        string Operador;

        Operador += Actual;
        Operador += Siguiente;

        return (
            Operador == "==" ||
            Operador == "!=" ||
            Operador == "<=" ||
            Operador == ">=" ||
            Operador == "++" ||
            Operador == "--" ||
            Operador == "+=" ||
            Operador == "-=" ||
            Operador == "*=" ||
            Operador == "/=" ||
            Operador == "&&" ||
            Operador == "||" ||
            Operador == "<<" ||
            Operador == ">>");
    }

    TipoToken AutomataLexico::clasificar(const string &Lexema)
    {

        // Números con signo 
        if (Lexema.size() > 1 &&
            (Lexema[0] == '+' || Lexema[0] == '-'))
        {
            bool SoloDigitos = true;

            for (size_t I = 1; I < Lexema.size(); ++I)
            {
                if (!isdigit(static_cast<unsigned char>(Lexema[I])))
                {
                    SoloDigitos = false;
                    break;
                }
            }

            if (SoloDigitos)
                return TipoToken::ENTERO;
        }

        bool TieneDigito = false;
        bool TieneMinuscula = false;
        bool TieneMayuscula = false;
        bool TieneGuion = false;
        bool EsValido = true;

        for (char C : Lexema)
        {

            if (isdigit(static_cast<unsigned char>(C)))
                TieneDigito = true;

            else if (islower(static_cast<unsigned char>(C)))
                TieneMinuscula = true;

            else if (isupper(static_cast<unsigned char>(C)))
                TieneMayuscula = true;

            else if (C == '_')
                TieneGuion = true;

            else
                EsValido = false;
        }

        //Se considera símbolo cualquier lexema que contenga caracteres no alfanuméricos y que no sea un identificador válido.
        if (!EsValido)
            return TipoToken::SIMBOLO;

        //Identificadores válidos: deben comenzar con una letra (mayúscula o minúscula) o un guion bajo, y pueden contener letras, dígitos y guiones bajos. No pueden contener otros caracteres especiales ni espacios.
        if (TieneGuion ||
            (TieneDigito && (TieneMinuscula || TieneMayuscula)) ||
            (TieneMinuscula && TieneMayuscula))
        {
            return TipoToken::IDENTIFICADOR;
        }

        if (TieneDigito)
            return TipoToken::ENTERO;

        if (TieneMinuscula)
            return TipoToken::PALABRA_MINUSCULA;

        if (TieneMayuscula)
            return TipoToken::PALABRA_MAYUSCULA;

        return TipoToken::SIMBOLO;
    }

    ListaTokens AutomataLexico::analizar(const string &Cadena)
    {

        ListaTokens Resultado;
        Resultado.Cantidad = 0;

        size_t N = Cadena.size();


        char *Buffer = new char[N + 1];

        Cadena.copy(Buffer, N);

        Buffer[N] = '\0';

        // Arreglo para construir lexemas
        char *Lex = new char[N + 1];

        size_t I = 0;

        while (I < N)
        {

            char C = Buffer[I];

            //Separadores: espacios en blanco, tabulaciones y saltos de línea. Se ignoran y no se consideran tokens.
            if (isspace(static_cast<unsigned char>(C)))
            {
                ++I;
                continue;
            }

            int LexLen = 0;

            Lex[LexLen++] = C;

            ++I;

            //Símbolos compuestos
            if (I < N && esSimboloCompuesto(C, Buffer[I]))
            {
                Lex[LexLen++] = Buffer[I];

                ++I;
            }


            //números con signo
            else if ((C == '+' || C == '-') &&
                     I < N &&
                     isdigit(static_cast<unsigned char>(Buffer[I])))
            {

                while (I < N &&
                       isdigit(static_cast<unsigned char>(Buffer[I])))
                {
                    Lex[LexLen++] = Buffer[I];

                    ++I;
                }
            }


            //Palabras e identificadores: secuencias de caracteres alfanume
            else if (isalnum(static_cast<unsigned char>(C)) || C == '_')
            {

                while (I < N &&
                       (isalnum(static_cast<unsigned char>(Buffer[I])) || Buffer[I] == '_'))
                {
                    Lex[LexLen++] = Buffer[I];

                    ++I;
                }
            }


            //Guardamos el lexema y su tipo en la lista de tokens
            if (Resultado.Cantidad < MaxTokens)
            {

                string Lexema(Lex, static_cast<size_t>(LexLen));

                Resultado.Datos[Resultado.Cantidad].Lexema = Lexema;

                Resultado.Datos[Resultado.Cantidad].Tipo =
                    clasificar(Lexema);

                ++Resultado.Cantidad;
            }
        }

        delete[] Lex;
        delete[] Buffer;

        return Resultado;
    }

} 