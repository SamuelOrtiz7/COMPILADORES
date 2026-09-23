#ifndef AFD_H
#define AFD_H

#include <string>
#include <map>
#include <set>
#include <utility>

// Logica original de la practica: recorre la cadena aplicando delta desde q0
// y verifica si el estado final pertenece al conjunto de aceptacion.
bool aceptaAFD(const std::string& cadena, int q0,
               const std::map<std::pair<int, char>, int>& delta,
               const std::set<int>& finales);

// Recibe cada parte del AFD ya separada (una por cada grupo de campos de la
// interfaz) y evalua un arreglo de hasta 5 cadenas (mismo limite que la
// interfaz), devolviendo ya armado el texto con un resultado por linea.
//   alfabetoTexto:     simbolos de Sigma separados por espacio (ej. "0 1")
//   finalesTexto:      estados finales separados por espacio (ej. "2")
//   transicionesTexto: una transicion por linea, "origen simbolo destino"
//   cadenas:           arreglo de hasta 5 cadenas W a evaluar
//   cantidadCadenas:   cuantas posiciones de "cadenas" son validas (0 a 5)
// Lanza std::runtime_error si una linea de transicion no se puede interpretar.
std::string ejecutarAFD(int q0,
                         const std::string& alfabetoTexto,
                         const std::string& finalesTexto,
                         const std::string& transicionesTexto,
                         const std::string cadenas[5],
                         int cantidadCadenas);

#endif // AFD_H
