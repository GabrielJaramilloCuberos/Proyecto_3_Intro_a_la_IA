/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#ifndef REDBAYESIANA_H
#define REDBAYESIANA_H

#include <map>
#include <string>
#include <algorithm>
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
        double obtenerProbabilidad(VariableAleatoria* variable, bool valor, map<string,bool>& evidencia);
        double enumerarTodas(vector<VariableAleatoria*> variables, map<string,bool>& evidencia);
        map<bool,double> consultaPorEnumeracion(string variableConsulta, map<string,bool>& evidencia);
        vector<VariableAleatoria*> obtenerOrdenTopologico();
        void dfsTopologico(VariableAleatoria* variable, map<string,bool>& variablesVisitadas, vector<VariableAleatoria*>& orden);
};

#endif // REDBAYESIANA_H
