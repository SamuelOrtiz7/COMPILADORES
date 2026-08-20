# AL - Analizador Lexico

Proyecto en C++ / Qt Widgets que resuelve los 3 puntos pedidos. Se compila
con **CMake**.

## Estructura

```
AL/
├── CMakeLists.txt              # build principal (CMake)
├── AL.pro                       # build alternativo con qmake (legacy, no requerido)
├── build.sh                     # compila con CMake, un solo comando (Linux/macOS)
├── build.bat                    # compila con CMake, un solo comando (Windows)
├── .vscode/tasks.json           # tarea de VS Code (Ctrl+Shift+B)
├── .vscode/c_cpp_properties.json# IntelliSense via compile_commands.json de CMake
├── interfaz/                    # Interfaz grafica (Qt)
│   ├── Main.cpp
│   ├── MainWindow.h
│   └── MainWindow.cpp
└── code/                        # Un archivo por punto
    ├── Punto1Estructuras.h / .cpp   # Punto 1: automata (estructuras de datos)
    ├── Punto2Alfabeto.h / .cpp      # Punto 2: alfabeto + expresiones regulares
    └── Punto3Regex.h / .cpp         # Punto 3: clasificacion y conteo con std::regex
```

## Que hace cada punto

- **Punto 1** (`code/Punto1Estructuras.*`): analiza la cadena caracter a caracter
  con un automata finito (enum de estados + `struct Token` + `vector<Token>`),
  SIN usar expresiones regulares. Clasifica en: numero entero, palabra
  minuscula, palabra mayuscula e identificador; ademas reconoce simbolos.

- **Punto 2** (`code/Punto2Alfabeto.*`): define el alfabeto Sigma y las
  expresiones regulares de cada categoria (entero, minuscula, mayuscula,
  identificador, simbolo). Estas mismas expresiones son las que usa el Punto 3.

- **Punto 3** (`code/Punto3Regex.*`): analiza la cadena usando `std::regex`
  (tokenizador + sub-expresiones de clasificacion) y devuelve tanto la lista
  de tokens como un conteo (`struct Conteo`) por categoria.

La interfaz (`interfaz/MainWindow.cpp`) tiene 3 pestañas, una por cada punto,
con un cuadro de texto de entrada, boton "Analizar" y tabla(s) de resultados.
En el Punto 3 ademas se muestra la tabla de conteos por categoria.

## Convencion de nombres

- **Archivos**: PascalCase (`Punto1Estructuras.h`, `MainWindow.cpp`, `Main.cpp`, etc.)
- **Funciones y metodos**: camelCase (`analizar`, `nombreTipo`, `crearTabPunto1`, etc.)
- **Variables y campos** (locales, parametros, miembros de struct/clase): PascalCase
  (`Cadena`, `Lexema`, `Tokens`, `EntradaP1`, etc.)
- Los namespaces, clases, structs y enums (`Punto1`, `AutomataLexico`, `Token`,
  `TipoToken`) ya eran PascalCase y se mantienen igual.

## Dependencias (Ubuntu)

```bash
sudo apt update
sudo apt install cmake build-essential qtbase5-dev qt5-qmake
```

(Si tienes Qt6 en vez de Qt5, instala `qt6-base-dev` en su lugar; el
`CMakeLists.txt` detecta automaticamente cual de los dos tienes.)

## Como compilar

### Opcion A: un solo comando desde la terminal de VS Code

```bash
./build.sh
```
Esto corre `cmake -S . -B build` + `cmake --build build` y deja el binario en
`build/AL`. Para compilar y ejecutar en un solo paso:
```bash
./build.sh run
```

### Opcion B: tarea integrada de VS Code

Con la carpeta `AL/` abierta en VS Code, presiona `Ctrl+Shift+B`. Corre la
tarea por defecto de `.vscode/tasks.json` (llama a `build.sh`). Tambien
puedes elegir "Compilar y ejecutar AL" desde **Terminal > Run Task...**.

### Opcion C: manual (paso a paso)

```bash
cd AL
cmake -S . -B build
cmake --build build -j$(nproc)
./build/AL
```

### IntelliSense (subrayado rojo en los `#include` de Qt)

`CMakeLists.txt` ya tiene activado `CMAKE_EXPORT_COMPILE_COMMANDS`, asi que
apenas corras `./build.sh` una vez, se genera `build/compile_commands.json`
y `.vscode/c_cpp_properties.json` lo usa automaticamente. No hace falta
editar rutas a mano — solo compila una vez y recarga la ventana de VS Code
(`Ctrl+Shift+P` -> "Reload Window") si el subrayado no desaparece solo.

## Ejemplo de entrada de prueba

```
123 abc ABC var1 Var_2 miVariable Total99 + - * / ( ) { } ;
```

Resultado esperado (resumen):
- Entero: `123`
- Minuscula: `abc`
- Mayuscula: `ABC`
- Identificador: `var1`, `Var_2`, `miVariable`, `Total99`
- Simbolo: `+ - * / ( ) { } ;` (uno por uno)
