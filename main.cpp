#include <bits/stdc++.h>

using namespace std;

class VariableAleatoria{
public:
    string nombre;
    vector<VariableAleatoria*> padres;
    vector<VariableAleatoria*> hijos;

    map<string,double> tablaProbabilidadCondicional;

    VariableAleatoria(string nombre){
        this->nombre = nombre;
    }

    void agregarPadre(VariableAleatoria* padre){
        padres.push_back(padre);
    }

    void agregarHijo(VariableAleatoria* hijo){
        hijos.push_back(hijo);
    }
};

class RedBayesiana{
public:
    map<string, VariableAleatoria*> variablesAleatorias;

    void agregarVariableAleatoria(string nombre){
        if(variablesAleatorias.find(nombre) == variablesAleatorias.end()){
            variablesAleatorias[nombre] = new VariableAleatoria(nombre);
        }
    }

    void agregarConexiones(string padre, string hijo){
        agregarVariableAleatoria(padre);
        agregarVariableAleatoria(hijo);

        VariableAleatoria* variablePadre = variablesAleatorias[padre];
        VariableAleatoria* variableHijo = variablesAleatorias[hijo];

        variablePadre->agregarHijo(variableHijo);
        variableHijo->agregarPadre(variablePadre);

    }

    void cargarTablaProbabilidadConjunta(string ruta){
        cout << "Cargando probabilidades... " << endl << endl;
        ifstream archivo(ruta);
        string linea;

        VariableAleatoria* variableActual = nullptr;

        cout<<"Vamor bien"<<endl;

        if(archivo.is_open()){
            while (getline(archivo,linea)){
                cout<<"Vamor bien en el bucle"<<endl;

                if(linea.empty()) continue;

                stringstream ss(linea);
                string a,b;
                ss >> a >> b;
                
                if(b.empty()){
                    string nombreVariable = a;

                    if(variablesAleatorias.find(nombreVariable) == variablesAleatorias.end()){
                        cout << "ERROR: Variable no encontrada: " << nombreVariable << endl;
                        continue;
                    }

                    variableActual = variablesAleatorias[nombreVariable];
                    cout<<"Bien"<<endl;
                    continue;
                }

                if(linea.find('|') != string::npos){
                    string nombreVariable = a;

                    if(variablesAleatorias.find(nombreVariable) == variablesAleatorias.end()){
                        cout << "ERROR: Variable no encontrada: " << nombreVariable << endl;
                        continue;
                    }

                    variableActual = variablesAleatorias[nombreVariable];
                    cout<<"Bien"<<endl;
                    continue;
                }
                
                stringstream lectura(linea);
                vector<string> tokens;
                string temporal;

                while(lectura >> temporal){
                    tokens.push_back(temporal);
                }

                if(variableActual == nullptr){
                    cout << "variableActual es null" << endl;
                    continue;
                }

                if(tokens.size() == 2){
                    string valor = tokens[0];
                    double probabilidad = stod(tokens[1]);

                    if(valor == "true"){
                        variableActual -> tablaProbabilidadCondicional[""] = probabilidad;
                    }
                }
                else if (tokens.size() == 3){
                        string condicion = tokens[0];
                        string valor = tokens[1];
                        double probabilidad = stod(tokens[2]);

                    if(valor == "true"){
                        variableActual -> tablaProbabilidadCondicional[condicion] = probabilidad;
                    }

                }
                
            }
            cout<<"Datos cargados"<<endl;
            archivo.close();
        }
        else{
            cerr<<"Error al abrir archivo."<<endl;
        }   
    }

    void mostrarVariables(){
        for(auto& par: variablesAleatorias){
            cout<< "Variable: " << par.first << endl;
            cout<< "Padres: ";

            for(auto& padre: par.second -> padres){
                cout << padre -> nombre << " ";
            }

            cout<<endl<<endl;
        }
    }

    void mostrarTablaProbabilidadConjunta(){
        for(auto& par: variablesAleatorias){
            cout << "Variable: " << par.first << endl;

            for(auto& entrada: par.second -> tablaProbabilidadCondicional){
                cout << entrada.first << " -> " << entrada.second << endl;
            }
        }
        cout << endl;
    }
};

int main(){

    RedBayesiana redBayesiana;
    string linea;

    string ruta;
    cout << "Ingrese el nombre del archivo donde estan las variables: ";
    cin >> ruta;
    ruta += ".txt";

    ifstream variables(ruta);

    if(variables.is_open()){
        while(getline(variables, linea)){
            if(linea.size() == 0) continue;
            stringstream ss(linea);
            string padre, hijo;
            ss >> padre >> hijo;
            redBayesiana.agregarConexiones(padre,hijo);

        }
        variables.close();
    } else{
        cerr<<"Error al abrir archivo."<<endl;
    }

    cout << "Ingrese el nombre del archivo donde estan las probabilidades: ";
    cin >> ruta;
    ruta += ".txt";

    redBayesiana.cargarTablaProbabilidadConjunta(ruta);
    redBayesiana.mostrarVariables();
    redBayesiana.mostrarTablaProbabilidadConjunta();


    return 0;

}
