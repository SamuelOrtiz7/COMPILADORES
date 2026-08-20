#ifndef PUNTO1ESTRUCTURAS_H
#define PUNTO1ESTRUCTURAS_H

#include <string>

using namespace std;

namespace Punto1
{

    constexpr int MaxTokens = 512;

    enum class TipoToken
    {
        ENTERO,
        PALABRA_MINUSCULA,
        PALABRA_MAYUSCULA,
        IDENTIFICADOR,
        SIMBOLO
    };

    struct Token
    {
        string Lexema;
        TipoToken Tipo;
    };

    struct ListaTokens
    {
        Token Datos[MaxTokens];
        int Cantidad = 0;
    };

    string nombreTipo(TipoToken Tipo);

    class AutomataLexico
    {
    public:
        ListaTokens analizar(const string &Cadena);

    private:
        static TipoToken clasificar(const string &Lexema);
    };

}

#endif