/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#include "utils.h"
#include <sstream>

using namespace std;

/**
 * @brief Tokeniza las consultas solicitadas por el usuario.
 *
 * @param consulta Consulta enviada por el usuario
 * @param variableConsulta Almacena las variable que solicita el usuario
 * @param evidencia Almacena la evidencia que adjunta el usuario
 */
bool parsearConsulta(const string& consulta, string& variableConsulta, map<string,bool>& evidencia){
    // Extraer el contenido entre P( y )
    size_t inicio = consulta.find('(');
    size_t fin    = consulta.rfind(')');
    if (inicio == string::npos || fin == string::npos) return false;

    string contenido = consulta.substr(inicio + 1, fin - inicio - 1);

    // Si no hay '|', la consulta no tiene evidencias -> solo parsear la variable
    size_t separador = contenido.find('|');
    if (separador == string::npos) {
        string item;
        stringstream(contenido) >> item;
        size_t eq = item.find('=');
        variableConsulta = (eq != string::npos) ? item.substr(0, eq) : item;
        return true;
    }

    // Hay evidencias: dividir por '|'
    string izquierda = contenido.substr(0, separador);
    string derecha   = contenido.substr(separador + 1);

    // Extraer el nombre de la variable consulta
    string token;
    stringstream(izquierda) >> token;
    size_t eq = token.find('=');
    variableConsulta = (eq != string::npos) ? token.substr(0, eq) : token;

    // Parsear cada par "VARIABLE=valor" separado por comas
    string par;
    stringstream ssDerecha(derecha);
    while (getline(ssDerecha, par, ',')) {
        string item;
        stringstream(par) >> item;
        size_t pos = item.find('=');
        if (pos == string::npos) return false;
        evidencia[item.substr(0, pos)] = (item.substr(pos + 1) == "true");
    }

    return true;
}