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

    cout << "<-----> Bienvenido al motor de inferencia <-----> " << endl << endl;

    int opcion = -1;

    while (opcion != 0){

        cout << "Menu:" << endl;
        cout << "1. Cargar variables\n2. Cargar probabilidades\n0. Salir\n";
        
        cout << "Ingrese la opcion: "; 
        cin >> opcion;
        switch (opcion) {

        case 0: {
            cout << "Hasta luego." << endl;
            exit(0);
        }
        case 1: {
            cout << endl << "Ingrese el nombre del archivo donde estan las variables: ";
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
                cout << endl << "Variables cargadas." << endl << endl;
            } else {
                cerr << "Error al abrir archivo." << endl;
                break;
            }
            break;
        }
        case 2: {

            map<string,VariableAleatoria*> contenedor = redBayesiana.getVariablesAleatorias();
            
            if(contenedor.empty()){
                cout << "Error: no hay variables registradas." << endl << endl;
                break;
            }

            cout << "Ingrese el nombre del archivo donde estan las probabilidades: ";
            cin >> ruta;
            ruta += ".txt";

            cout << endl << "Red creada." << endl << endl;

            redBayesiana.cargarTablaProbabilidadConjunta(ruta);
            redBayesiana.mostrarVariables();
            redBayesiana.mostrarTablaProbabilidadConjunta();

        }
        break;
        default:
            cout << "Opcion invalida." << endl << endl;
            break;
        }


    }

    return 0;
}
