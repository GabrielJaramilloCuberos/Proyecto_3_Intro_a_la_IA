/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#include "VariableAleatoria.h"

using namespace std;

VariableAleatoria::VariableAleatoria(string nombre) {
    this->nombre = nombre;
}

VariableAleatoria::~VariableAleatoria() {}

// Getters y Setters

string VariableAleatoria::getNombre() {
    return nombre;
}

void VariableAleatoria::setNombre(string nombre) {
    this->nombre = nombre;
}

vector<VariableAleatoria*> VariableAleatoria::getPadres() {
    return padres;
}

vector<VariableAleatoria*> VariableAleatoria::getHijos() {
    return hijos;
}

map<string, double> VariableAleatoria::getTablaProbabilidadCondicional() {
    return tablaProbabilidadCondicional;
}

void VariableAleatoria::setTablaProbabilidadCondicional(map<string, double> tabla) {
    tablaProbabilidadCondicional = tabla;
}

// Operaciones propias

void VariableAleatoria::agregarPadre(VariableAleatoria* padre) {
    padres.push_back(padre);
}

void VariableAleatoria::agregarHijo(VariableAleatoria* hijo) {
    hijos.push_back(hijo);
}

void VariableAleatoria::agregarEntradaTabla(string clave, double probabilidad) {
    tablaProbabilidadCondicional[clave] = probabilidad;
}
