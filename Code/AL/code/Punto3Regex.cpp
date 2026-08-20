#include "Punto3Regex.h"
#include "Punto2Alfabeto.h"
#include <regex>
using namespace std;

namespace Punto3
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

    ListaTokens AnalizadorRegex::analizar(const string &Cadena) const
    {
        ListaTokens Resultado;
        Resultado.Cantidad = 0;

        static const regex Tokenizador(Punto2::RegexTokenizador);

        // 2) Sub-expresiones para clasificar cada token ya extraido.
        static const regex ReEntero("^" + Punto2::RegexEntero + "$");
        static const regex ReMinuscula("^" + Punto2::RegexMinuscula + "$");
        static const regex ReMayuscula("^" + Punto2::RegexMayuscula + "$");
        static const regex ReIdentificador("^" + Punto2::RegexIdentificador + "$");

        auto Inicio = sregex_iterator(Cadena.begin(), Cadena.end(), Tokenizador);
        auto Fin = sregex_iterator();

        for (auto It = Inicio; It != Fin; ++It)
        {
            // Si ya se lleno el array de tamaño fijo, se ignoran tokens extra.
            if (Resultado.Cantidad >= MaxTokens)
            {
                break;
            }

            string Lexema = It->str();

            TipoToken Tipo;
            if (regex_match(Lexema, ReEntero))
            {
                Tipo = TipoToken::ENTERO;
            }
            else if (regex_match(Lexema, ReMinuscula))
            {
                Tipo = TipoToken::PALABRA_MINUSCULA;
            }
            else if (regex_match(Lexema, ReMayuscula))
            {
                Tipo = TipoToken::PALABRA_MAYUSCULA;
            }
            else if (regex_match(Lexema, ReIdentificador))
            {
                Tipo = TipoToken::IDENTIFICADOR;
            }
            else
            {
                // Cualquier cosa que no encaje en las anteriores es un simbolo
                Tipo = TipoToken::SIMBOLO;
            }

            Resultado.Datos[Resultado.Cantidad].Lexema = Lexema;
            Resultado.Datos[Resultado.Cantidad].Tipo = Tipo;
            Resultado.Cantidad++;
        }

        return Resultado;
    }

    Conteo AnalizadorRegex::contar(const ListaTokens &Tokens) const
    {
        Conteo C;
        for (int I = 0; I < Tokens.Cantidad; ++I)
        {
            switch (Tokens.Datos[I].Tipo)
            {
            case TipoToken::ENTERO:
                ++C.Enteros;
                break;
            case TipoToken::PALABRA_MINUSCULA:
                ++C.Minusculas;
                break;
            case TipoToken::PALABRA_MAYUSCULA:
                ++C.Mayusculas;
                break;
            case TipoToken::IDENTIFICADOR:
                ++C.Identificadores;
                break;
            case TipoToken::SIMBOLO:
                ++C.Simbolos;
                break;
            }
        }
        return C;
    }

}