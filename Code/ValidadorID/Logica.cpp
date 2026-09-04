#include "Logica.h"
#include <regex>

namespace Logica
{

    bool esCurpValida(const std::string &Texto)
    {
        static const std::regex Patron(
            "^[A-Z]{4}[0-9]{6}[HM][A-Z]{2}[B-DF-HJ-NP-TV-Z]{3}[A-Z0-9][0-9]$");
        return std::regex_match(Texto, Patron);
    }

    bool esRfcValido(const std::string &Texto)
    {
        static const std::regex Patron(
            "^[A-ZÑ&]{3,4}[0-9]{6}[A-Z0-9]{3}$");
        return std::regex_match(Texto, Patron);
    }

    bool esIneValida(const std::string &Texto)
    {
        static const std::regex Patron(
            "^[A-Z]{6}[0-9]{8}[HM][0-9]{3}$");
        return std::regex_match(Texto, Patron);
    }

    TipoIdentificador identificar(const std::string &Texto)
    {
        if (esCurpValida(Texto))
        {
            return TipoIdentificador::CURP;
        }
        else if (esIneValida(Texto))
        {
            return TipoIdentificador::INE;
        }
        else if (esRfcValido(Texto))
        {
            return TipoIdentificador::RFC;
        }
        else
        {
            return TipoIdentificador::DESCONOCIDO;
        }
    }

    std::string nombreTipo(TipoIdentificador Tipo)
    {
        switch (Tipo)
        {
        case TipoIdentificador::CURP:
            return "CURP";
        case TipoIdentificador::RFC:
            return "RFC";
        case TipoIdentificador::INE:
            return "Clave de elector (INE)";
        default:
            return "No se reconoce el formato";
        }
    }
}
