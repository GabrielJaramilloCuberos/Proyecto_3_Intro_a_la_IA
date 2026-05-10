/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#include "VariableAleatoria.h"

using namespace std;

/**
 * @brief Inicializa la variable con su nombre identificador.
 *        Los vectores de padres e hijos quedan vacios y la CPT sin entradas.
 */
VariableAleatoria::VariableAleatoria(string nombre) {
    this->nombre = nombre;
}

/**
 * @brief Destructor por defecto. Los punteros a padres e hijos
 *        son administrados por RedBayesiana, no se liberan aqui.
 */
VariableAleatoria::~VariableAleatoria() {}

// ──────────────────────────── Getters y Setters ────────────────────────────

/** @brief Retorna el nombre identificador de la variable. */
string VariableAleatoria::getNombre() {
    return nombre;
}

/** @brief Asigna un nuevo nombre a la variable. */
void VariableAleatoria::setNombre(string nombre) {
    this->nombre = nombre;
}

/** @brief Retorna la lista de punteros a las variables padre. */
vector<VariableAleatoria*> VariableAleatoria::getPadres() {
    return padres;
}

/** @brief Retorna la lista de punteros a las variables hijo. */
vector<VariableAleatoria*> VariableAleatoria::getHijos() {
    return hijos;
}

/**
 * @brief Retorna una referencia a la tabla de probabilidad condicional.
 *        Se retorna por referencia para permitir modificaciones directas
 *        (necesario en obtenerProbabilidad de RedBayesiana).
 */
map<string, double>& VariableAleatoria::getTablaProbabilidadCondicional() {
    return tablaProbabilidadCondicional;
}

/** @brief Reemplaza toda la tabla de probabilidad condicional por una nueva. */
void VariableAleatoria::setTablaProbabilidadCondicional(map<string, double> tabla) {
    tablaProbabilidadCondicional = tabla;
}

// ──────────────────────────── Operaciones propias ──────────────────────────

/** @brief Agrega un puntero a la lista de padres de esta variable. */
void VariableAleatoria::agregarPadre(VariableAleatoria* padre) {
    padres.push_back(padre);
}

/** @brief Agrega un puntero a la lista de hijos de esta variable. */
void VariableAleatoria::agregarHijo(VariableAleatoria* hijo) {
    hijos.push_back(hijo);
}

/**
 * @brief Inserta una entrada en la tabla de probabilidad condicional.
 *        Si la clave ya existe, sobreescribe su valor.
 *
 * @param clave        Combinacion de valores de los padres, ej. "LLUVIA=true,ROCIADOR=false".
 *                     Para variables sin padres se usa "" (string vacio).
 * @param probabilidad P(esta variable = true | clave)
 */
void VariableAleatoria::agregarEntradaTabla(string clave, double probabilidad) {
    tablaProbabilidadCondicional[clave] = probabilidad;
}
