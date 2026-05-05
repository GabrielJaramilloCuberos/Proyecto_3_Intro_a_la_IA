#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

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
};

int main(){

    RedBayesiana redBayesiana;
    ifstream estructura("estructura.txt");
    string linea;

    if(estructura.is_open()){
        while(getline(estructura, linea)){
            if(linea.size() == 0) continue;
            stringstream ss(linea);
            string padre, hijo;
            ss >> padre >> hijo;
            redBayesiana.agregarConexiones(padre,hijo);

        }
        estructura.close();
    } else{
        cerr<<"Error al abrir archivo."<<endl;
    }

    cout<<"Imprimir nodos:";

    for(auto& par: redBayesiana.variablesAleatorias){
        cout<<"Nodo :" << par.first << endl;
        cout<<"Padres: ";
        for(auto padres: par.second->padres){
            cout<< padres->nombre << " ";
        }

        cout<<endl<<endl;
    }

}
