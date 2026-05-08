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
        cout << "1. Cargar variables\n2. Cargar probabilidades\n3. Obtener probabilidad local\n0. Salir\n";
        
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

            break;
        }
        case 3:{
            string nombreVariable;
            string valorTexto;

            cout << "Ingrese la variable: ";
            cin >> nombreVariable;
            cout << "Ingrese el valor (true/false): ";
            cin >> valorTexto;

            bool valor = (valorTexto == "true");

            int cantidadEvidencias;

            cout << "Ingrese la cantidad de evidencias: ";
            cin >> cantidadEvidencias;

            map<string,bool> evidencia;

            for (int i=0; i<cantidadEvidencias; i++){
                string variableEvidencia;
                string valorEvidencia;

                cout << "Ingresar variable de evidencia: ";
                cin >> variableEvidencia;
                cout << "Ingresar el valor (true/false): ";
                cin >> valorEvidencia;

                evidencia[variableEvidencia] = (valorEvidencia == "true");
            }

            VariableAleatoria* variable = redBayesiana.getVariablesAleatorias()[nombreVariable];

            double resultado = redBayesiana.obtenerProbabilidad(variable, valor, evidencia);

            cout << "Probabilidad: " << resultado << endl << endl;
            break;
        }

        default:
            cout << "Opcion invalida." << endl << endl;
            break;
        }


    }

    return 0;
}
