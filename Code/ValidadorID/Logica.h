#ifndef LOGICA_H
#define LOGICA_H

#include <string>

// Identifica el formato (no el checksum oficial) de CURP, RFC e INE.
namespace Logica
{
    enum class TipoIdentificador
    {
        CURP,
        RFC,
        INE,
        DESCONOCIDO
    };

    bool esCurpValida(const std::string &Texto);
    bool esRfcValido(const std::string &Texto);
    bool esIneValida(const std::string &Texto);

    // Prueba los 3 patrones en cascada y devuelve el primero que coincida.
    TipoIdentificador identificar(const std::string &Texto);

    std::string nombreTipo(TipoIdentificador Tipo);
}

#endif // LOGICA_H
