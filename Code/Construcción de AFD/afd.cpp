#include "afd.h"

#include <sstream>
#include <stdexcept>

bool aceptaAFD(const std::string& cadena, int q0,
               const std::map<std::pair<int, char>, int>& delta,
               const std::set<int>& finales) {
    int estado = q0;

    for (char simbolo : cadena) {
        auto transicion = delta.find({estado, simbolo});

        if (transicion == delta.end())
            return false;

        estado = transicion->second;
    }
    return finales.count(estado) > 0;
}

std::string ejecutarAFD(int q0,
                         const std::string& alfabetoTexto,
                         const std::string& finalesTexto,
                         const std::string& transicionesTexto,
                         const std::string cadenas[5],
                         int cantidadCadenas) {

    std::istringstream alfabetoIn(alfabetoTexto);
    char simboloAlfabeto;
    while (alfabetoIn >> simboloAlfabeto) {
    }

    std::set<int> finales;
    std::istringstream finalesIn(finalesTexto);
    int estadoFinal;
    while (finalesIn >> estadoFinal)
        finales.insert(estadoFinal);

    std::map<std::pair<int, char>, int> delta;
    std::istringstream transicionesIn(transicionesTexto);
    std::string linea;
    while (std::getline(transicionesIn, linea)) {
        if (linea.find_first_not_of(" \t\r") == std::string::npos)
            continue; // ignora lineas en blanco

        std::istringstream lineaIn(linea);
        int origen, destino;
        char simboloTransicion;
        if (!(lineaIn >> origen >> simboloTransicion >> destino))
            throw std::runtime_error("Transicion invalida: '" + linea + "'");

        delta[{origen, simboloTransicion}] = destino;
    }

    std::string salida;
    for (int i = 0; i < cantidadCadenas && i < 5; i++) {
        const std::string& cadena = cadenas[i];

        salida += cadena;
        salida += aceptaAFD(cadena, q0, delta, finales) ? " -> ACEPTADA\n" : " -> RECHAZADA\n";
    }

    return salida;
}
