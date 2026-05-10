# Motor de Inferencia — Red Bayesiana
**Proyecto 3 · Introducción a la Inteligencia Artificial**  
Pontificia Universidad Javeriana

---

## Descripción

Este proyecto implementa un **motor de inferencia basado en Redes Bayesianas** en C++. Una Red Bayesiana es un grafo acíclico dirigido (DAG) donde cada nodo representa una variable aleatoria y las aristas representan dependencias probabilísticas entre ellas.

El programa permite:
- Cargar la estructura de la red (variables y sus relaciones padre-hijo) desde un archivo de texto.
- Cargar las tablas de probabilidad condicional (CPTs) de cada variable desde otro archivo.
- Visualizar la red cargada con sus dependencias y probabilidades.

---

## Estructura del proyecto

```
Proyecto_3_Intro_a_la_IA/
├── TADS/
│   ├── VariableAleatoria.h      # Declaracion del TAD VariableAleatoria
│   ├── VariableAleatoria.cpp    # Implementacion del TAD VariableAleatoria
│   ├── RedBayesiana.h           # Declaracion del TAD RedBayesiana
│   └── RedBayesiana.cpp         # Implementacion del TAD RedBayesiana
├── main.cpp                     # Punto de entrada y menu de usuario
├── variables.txt                # Archivo de ejemplo: estructura de la red
├── probabilidades.txt           # Archivo de ejemplo: tablas de probabilidad
└── README.md
```

---

## TADs implementados

### `VariableAleatoria`
Representa un nodo dentro de la red bayesiana.

| Atributo (privado) | Tipo | Descripción |
|---|---|---|
| `nombre` | `string` | Identificador único de la variable |
| `padres` | `vector<VariableAleatoria*>` | Variables de las que depende |
| `hijos` | `vector<VariableAleatoria*>` | Variables que dependen de ella |
| `tablaProbabilidadCondicional` | `map<string, double>` | CPT: condición → P(variable=true) |

### `RedBayesiana`
Representa la red completa y gestiona todas las variables y sus conexiones.

| Atributo (privado) | Tipo | Descripción |
|---|---|---|
| `variablesAleatorias` | `map<string, VariableAleatoria*>` | Colección de todas las variables indexadas por nombre |

---

## Formato de archivos de entrada

### Archivo de variables
Define las relaciones padre → hijo de la red. Cada línea contiene dos nombres separados por un espacio:

```
LLUVIA ROCIADOR
ROCIADOR HIERBAHUMEDA
LLUVIA HIERBAHUMEDA
```

### Archivo de probabilidades
Define las tablas de probabilidad condicional. El formato es:

```
NOMBRE_VARIABLE
true  <probabilidad>

NOMBRE_VARIABLE | PADRE1 PADRE2
PADRE1=valor,PADRE2=valor  true  <probabilidad>
```

**Ejemplo (`probabilidades.txt`):**
```
LLUVIA
true 0.2

ROCIADOR | LLUVIA
LLUVIA=true  true 0.01
LLUVIA=false true 0.4

HIERBAHUMEDA | ROCIADOR LLUVIA
ROCIADOR=false,LLUVIA=false true 0
ROCIADOR=false,LLUVIA=true  true 0.8
ROCIADOR=true,LLUVIA=false  true 0.9
ROCIADOR=true,LLUVIA=true   true 0.99
```

> **Nota:** Solo se almacena la probabilidad del valor `true`. La probabilidad de `false` se obtiene como `1 - P(true)`.

---

## Red de ejemplo

La red de ejemplo modela la siguiente situación:

```
       LLUVIA
      /      \
 ROCIADOR   HIERBAHUMEDA
      \      /
    HIERBAHUMEDA
```

| Variable | Descripción |
|---|---|
| `LLUVIA` | Si llovió (20% de probabilidad) |
| `ROCIADOR` | Si el rociador estaba encendido (depende de la lluvia) |
| `HIERBAHUMEDA` | Si el pasto está mojado (depende de la lluvia y el rociador) |

---

## Compilación y ejecución

### Compilar
```bash
g++ main.cpp TADS/VariableAleatoria.cpp TADS/RedBayesiana.cpp Utils/utils.cpp -o motor
```

### Ejecutar
```bash
./motor
```