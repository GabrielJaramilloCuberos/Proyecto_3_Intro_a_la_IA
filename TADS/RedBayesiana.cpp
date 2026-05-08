/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#include "RedBayesiana.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

RedBayesiana::RedBayesiana() {}

RedBayesiana::~RedBayesiana() {
    for (auto& par : variablesAleatorias) {
        delete par.second;
    }
}

// Getters y Setters

map<string, VariableAleatoria*> RedBayesiana::getVariablesAleatorias() {
    return variablesAleatorias;
}

// Operaciones propias

/**
 * @brief Agrega una variable aleatoria a la red si no existe aun
 *
 * @param nombre Nombre de la variable a agregar
 */
void RedBayesiana::agregarVariableAleatoria(string nombre) {
    if (variablesAleatorias.find(nombre) == variablesAleatorias.end()) {
        variablesAleatorias[nombre] = new VariableAleatoria(nombre);
    }
}

/**
 * @brief Crea la conexion padre-hijo entre dos variables,
 * agregandolas a la red si aun no existen
 *
 * @param padre Nombre de la variable padre
 * @param hijo  Nombre de la variable hijo
 */
void RedBayesiana::agregarConexiones(string padre, string hijo) {
    agregarVariableAleatoria(padre);
    agregarVariableAleatoria(hijo);

    VariableAleatoria* variablePadre = variablesAleatorias[padre];
    VariableAleatoria* variableHijo  = variablesAleatorias[hijo];

    variablePadre->agregarHijo(variableHijo);
    variableHijo->agregarPadre(variablePadre);
}

/**
 * @brief Carga la tabla de probabilidad condicional desde un archivo de texto.
 * Cada variable puede tener probabilidades incondicionales o condicionales
 * segun el formato del archivo.
 *
 * @param ruta Ruta del archivo de probabilidades
 */
void RedBayesiana::cargarTablaProbabilidadConjunta(string ruta) {
    cout << "Cargando probabilidades..." << endl << endl;
    ifstream archivo(ruta);
    string linea;

    VariableAleatoria* variableActual = nullptr;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            stringstream ss(linea);
            string a, b;
            ss >> a >> b;

            // Linea con un solo token: nombre de variable (probabilidad incondicional)
            if (b.empty()) {
                if (variablesAleatorias.find(a) == variablesAleatorias.end()) {
                    continue;
                }
                variableActual = variablesAleatorias[a];
                continue;
            }

            // Linea con '|': encabezado de probabilidad condicional
            if (linea.find('|') != string::npos) {
                if (variablesAleatorias.find(a) == variablesAleatorias.end()) {
                    cout << "ERROR: Variable no encontrada: " << a << endl;
                    continue;
                }
                variableActual = variablesAleatorias[a];
                continue;
            }

            // Linea de datos: extraer tokens
            stringstream lectura(linea);
            vector<string> tokens;
            string temporal;
            while (lectura >> temporal) {
                tokens.push_back(temporal);
            }

            if (variableActual == nullptr) {
                cout << "variableActual es null" << endl;
                continue;
            }

            // Probabilidad incondicional: "valor probabilidad"
            if (tokens.size() == 2) {
                string valor = tokens[0];
                double probabilidad = stod(tokens[1]);
                if (valor == "true") {
                    variableActual->agregarEntradaTabla("", probabilidad);
                }
            }
            // Probabilidad condicional: "condicion valor probabilidad"
            else if (tokens.size() == 3) {
                string condicion    = tokens[0];
                string valor        = tokens[1];
                double probabilidad = stod(tokens[2]);
                if (valor == "true") {
                    variableActual->agregarEntradaTabla(condicion, probabilidad);
                }
            }
        }
        cout << "Datos cargados" << endl;
        archivo.close();
    } else {
        cerr << "Error al abrir archivo." << endl;
    }
}

/**
 * @brief Muestra en consola cada variable y sus padres
 *
 */
void RedBayesiana::mostrarVariables() {
    for (auto& par : variablesAleatorias) {
        cout << "Variable: " << par.first << endl;
        cout << "Padres: ";
        for (auto& padre : par.second->getPadres()) {
            cout << padre->getNombre() << " ";
        }
        cout << endl << endl;
    }
}

/**
 * @brief Muestra en consola la tabla de probabilidad condicional de cada variable
 *
 */
void RedBayesiana::mostrarTablaProbabilidadConjunta() {
    for (auto& par : variablesAleatorias) {
        cout << "Variable: " << par.first << endl;
        for (auto& entrada : par.second->getTablaProbabilidadCondicional()) {
            cout << entrada.first << " -> " << entrada.second << endl;
        }
    }
    cout << endl;
}

double RedBayesiana::obtenerProbabilidad(VariableAleatoria* variable, bool valor, map<string,bool>& evidencia){

    string clave ="";

    for(auto padre: variable -> getPadres()){

        clave += padre -> getNombre() + "=";

        if(evidencia[padre -> getNombre()]){
            clave += "true";
        }
        else{
            clave += "false";
        }

        clave += ",";
    }

    if(!clave.empty()){
        clave.pop_back();
    }

    auto& tabla = variable -> getTablaProbabilidadCondicional();
    if(tabla.find(clave) == tabla.end()){
        cout << "Error: clave no encontrada: " << clave << endl;
        return 0;
    }

    double probabilidad = tabla[clave];

    if(valor){
        return probabilidad;
    }
    
    return 1-probabilidad;
}