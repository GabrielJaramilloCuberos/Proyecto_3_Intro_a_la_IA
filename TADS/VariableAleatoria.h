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

/**
 * @brief Representa un nodo dentro de una Red Bayesiana.
 *
 * Cada variable aleatoria tiene un nombre unico, conoce a sus padres
 * (variables de las que depende) y a sus hijos (variables que dependen de ella).
 * Tambien almacena su tabla de probabilidad condicional (CPT), que mapea
 * una combinacion de valores de los padres a P(variable = true).
 */
class VariableAleatoria {

    private:
        // Nombre unico que identifica la variable en la red
        string nombre;
        // Punteros a las variables de las que esta variable depende directamente
        vector<VariableAleatoria*> padres;
        // Punteros a las variables que dependen directamente de esta variable
        vector<VariableAleatoria*> hijos;
        // Tabla de probabilidad condicional (CPT).
        // Clave: string con los valores de los padres, ej. "LLUVIA=true,ROCIADOR=false"
        // Valor: P(esta variable = true | condicion de los padres)
        // Si la variable no tiene padres, la clave es "" (string vacio)
        map<string, double> tablaProbabilidadCondicional;

    public:
        // Constructor: inicializa la variable con su nombre
        VariableAleatoria(string nombre);

        // Destructor por defecto
        ~VariableAleatoria();

        // Getters y Setters
        string getNombre();
        void setNombre(string nombre);
        vector<VariableAleatoria*> getPadres();
        vector<VariableAleatoria*> getHijos();
        map<string, double>& getTablaProbabilidadCondicional();
        void setTablaProbabilidadCondicional(map<string, double> tabla);

        // Operaciones propias

        // Registra una variable como padre de esta
        void agregarPadre(VariableAleatoria* padre);
        // Registra una variable como hijo de esta
        void agregarHijo(VariableAleatoria* hijo);
        // Inserta o actualiza una entrada en la tabla de probabilidad condicional
        void agregarEntradaTabla(string clave, double probabilidad);

};

#endif // VARIABLEALEATORIA_H
