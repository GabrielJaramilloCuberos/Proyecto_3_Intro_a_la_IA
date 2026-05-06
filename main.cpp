/*********************************************************************************
-Pontificia Universidad Javeriana
-Proyecto 3 - Introduccion a la Inteligencia Artificial
-Temas: TADs, Compilacion Modular, Redes Bayesianas
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TADS/RedBayesiana.h"

using namespace std;

int main() {

    RedBayesiana redBayesiana;
    string linea;
    string ruta;

    cout << "Ingrese el nombre del archivo donde estan las variables: ";
    cin >> ruta;
    ruta += ".txt";

    ifstream variables(ruta);

    if (variables.is_open()) {
        while (getline(variables, linea)) {
            if (linea.size() == 0) continue;
            stringstream ss(linea);
            string padre, hijo;
            ss >> padre >> hijo;
            redBayesiana.agregarConexiones(padre, hijo);
        }
        variables.close();
    } else {
        cerr << "Error al abrir archivo." << endl;
    }

    cout << "Ingrese el nombre del archivo donde estan las probabilidades: ";
    cin >> ruta;
    ruta += ".txt";

    redBayesiana.cargarTablaProbabilidadConjunta(ruta);
    redBayesiana.mostrarVariables();
    redBayesiana.mostrarTablaProbabilidadConjunta();

    return 0;
}
