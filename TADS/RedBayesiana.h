/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#ifndef REDBAYESIANA_H
#define REDBAYESIANA_H

#include <map>
#include <string>
#include "VariableAleatoria.h"

using namespace std;

class RedBayesiana {

    private:
        // Mapa de variables aleatorias indexadas por nombre
        map<string, VariableAleatoria*> variablesAleatorias;

    public:
        // Constructor
        RedBayesiana();

        // Destructor
        ~RedBayesiana();

        // Getters y Setters
        map<string, VariableAleatoria*> getVariablesAleatorias();

        // Operaciones propias
        void agregarVariableAleatoria(string nombre);
        void agregarConexiones(string padre, string hijo);
        void cargarTablaProbabilidadConjunta(string ruta);
        void mostrarVariables();
        void mostrarTablaProbabilidadConjunta();

};

#endif // REDBAYESIANA_H
