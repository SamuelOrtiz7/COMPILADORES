#ifndef AFD_H
#define AFD_H

#include <string>
#include <map>
#include <set>
#include <utility>

bool aceptaAFD(const std::string& cadena, int q0,
               const std::map<std::pair<int, char>, int>& delta,
               const std::set<int>& finales);


std::string ejecutarAFD(int q0,
                         const std::string& alfabetoTexto,
                         const std::string& finalesTexto,
                         const std::string& transicionesTexto,
                         const std::string cadenas[5],
                         int cantidadCadenas);

#endif // AFD_H
