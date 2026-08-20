#ifndef PUNTO3REGEX_H
#define PUNTO3REGEX_H

#include <string>
using namespace std;

namespace Punto3
{

    // Capacidad maxima de tokens que se pueden guardar por analisis.
    constexpr int MaxTokens = 512;

    enum class TipoToken
    {
        ENTERO,
        PALABRA_MINUSCULA,
        PALABRA_MAYUSCULA,
        IDENTIFICADOR,
        SIMBOLO
    };

    string nombreTipo(TipoToken Tipo);

    struct ResultadoToken
    {
        string Lexema;
        TipoToken Tipo;
    };

    struct ListaTokens
    {
        ResultadoToken Datos[MaxTokens];
        int Cantidad = 0;
    };

    struct Conteo
    {
        int Enteros = 0;
        int Minusculas = 0;
        int Mayusculas = 0;
        int Identificadores = 0;
        int Simbolos = 0;

        int total() const { return Enteros + Minusculas + Mayusculas + Identificadores + Simbolos; }
    };

    class AnalizadorRegex
    {
    public:
        // Recorre la cadena y devuelve cada token clasificado
        ListaTokens analizar(const string &Cadena) const;

        // Contabiliza los resultados de analizar()
        Conteo contar(const ListaTokens &Tokens) const;
    };

} // namespace Punto3

#endif // PUNTO3REGEX_H