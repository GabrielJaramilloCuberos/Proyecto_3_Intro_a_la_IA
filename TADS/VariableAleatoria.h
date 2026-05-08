/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#ifndef VARIABLEALEATORIA_H
#define VARIABLEALEATORIA_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class VariableAleatoria {

    private:
        // Nombre identificador de la variable
        string nombre;
        // Lista de punteros a las variables padre en la red bayesiana
        vector<VariableAleatoria*> padres;
        // Lista de punteros a las variables hijo en la red bayesiana
        vector<VariableAleatoria*> hijos;
        // Tabla de probabilidad condicional: clave = condicion, valor = probabilidad
        map<string, double> tablaProbabilidadCondicional;

    public:
        // Constructor
        VariableAleatoria(string nombre);

        // Destructor
        ~VariableAleatoria();

        // Getters y Setters
        string getNombre();
        void setNombre(string nombre);
        vector<VariableAleatoria*> getPadres();
        vector<VariableAleatoria*> getHijos();
        map<string, double>& getTablaProbabilidadCondicional();
        void setTablaProbabilidadCondicional(map<string, double> tabla);

        // Operaciones propias
        void agregarPadre(VariableAleatoria* padre);
        void agregarHijo(VariableAleatoria* hijo);
        void agregarEntradaTabla(string clave, double probabilidad);

};

#endif // VARIABLEALEATORIA_H
