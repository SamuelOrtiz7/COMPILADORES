# Guion de exposición — Herramientas del proyecto Analizador Léxico

> Proyecto: `SamuelOrtiz7/COMPILADORES` · Analizador léxico en **C++17 + Qt Widgets**
> Enfoque de la exposición: **las herramientas** (Qt, CMake, GitHub Actions), no la lógica de regex ni la clasificación de lexemas.
> Idea que debe quedar clara: *desarrollé en Ubuntu, pero entrego un ejecutable de Windows portable generado automáticamente por CI.*

---

## 0. Presentación del proyecto (30 s)

- Analizador léxico con **interfaz gráfica de escritorio**.
- Tres puntos, cada uno en una pestaña:
  1. Autómata finito con estructuras de datos (sin regex).
  2. Definición del alfabeto y las expresiones regulares.
  3. Clasificación y conteo con `std::regex`.
- El proyecto real vive en `Code/AL/`.

```
Code/AL/
├── CMakeLists.txt          → build principal
├── AL.pro                  → build alternativo con qmake (legacy, no se usa)
├── build.sh / build.bat    → compilar con un comando (Linux / Windows)
├── deploy-windows.bat      → empaquetar portable en Windows
├── .vscode/                → tasks.json + IntelliSense
├── interfaz/               → GUI: Main.cpp, MainWindow.h / .cpp
└── code/                   → lógica: Punto1 / Punto2 / Punto3
.github/workflows/build-windows.yml   → CI que compila el .exe de Windows
Releases/Ejecutable Windows.zip       → salida final distribuible
```

---

# BLOQUE 1 — Qt: cómo funcionan ventanas, paneles y botones

## 1.1 La idea central: programación dirigida por eventos

**Frase:** *"Un programa de consola es secuencial: empieza en `main`, ejecuta línea a línea y termina. Un programa Qt monta la interfaz y entra en un bucle de eventos que no termina hasta cerrar la ventana."*

- En consola, `cin` **detiene** el programa esperando al usuario.
- En Qt, el control lo tiene Qt: está escuchando clics, teclas, redibujados… y cuando ocurre algo que me interesa (clic en mi botón), **Qt llama a mi función**.

`Main.cpp` es exactamente ese esquema:

```cpp
int main(int Argc, char *Argv[])
{
    QApplication App(Argc, Argv);   // 1. infraestructura de Qt
    MainWindow Ventana;             // 2. construye la interfaz
    Ventana.resize(900, 650);
    Ventana.show();                 // 3. la hace visible
    return App.exec();             // 4. ENTRA en el bucle de eventos (no vuelve hasta cerrar)
}
```

## 1.2 Todo es un `QWidget`

**Frase:** *"En Qt casi todo lo que se ve es un widget: la ventana, un botón, una etiqueta, una tabla, un cuadro de texto. Todos heredan de `QWidget`."*

Cada widget:
- ocupa un rectángulo en pantalla,
- tiene un **widget padre** y puede tener **hijos**,
- se dibuja a sí mismo y recibe eventos.

La relación **padre → hijo** sirve para dos cosas:
1. **Visual:** los hijos se dibujan dentro del padre.
2. **Memoria:** al destruir el padre, Qt destruye a los hijos automáticamente → por eso hay muchos `new` sin `delete`; los gestiona el árbol de objetos de Qt.

Árbol de mi `MainWindow`:

```
MainWindow (QMainWindow)          ← ventana principal
 └── QTabWidget                   ← widget central, con 3 pestañas
      ├── QWidget (pestaña 1)
      │    └── QVBoxLayout
      │         ├── QLabel            (título explicativo)
      │         ├── QPlainTextEdit    (entrada de texto)
      │         ├── QPushButton       (botón "Analizar")
      │         └── QTableWidget      (tabla de resultados)
      ├── QWidget (pestaña 2) ...
      └── QWidget (pestaña 3) ...
```

## 1.3 Widgets usados y su papel

| Widget | Rol en el proyecto | Equivalente mental de consola |
|---|---|---|
| `QMainWindow` | Ventana con marco, título | La "pantalla" completa |
| `QTabWidget` | Contenedor con 3 pestañas (un punto cada una) | Un menú de 3 opciones |
| `QWidget` | Panel que agrupa los controles de una pestaña | Una "sección" |
| `QLabel` | Texto fijo de instrucciones | `cout` de una instrucción |
| `QPlainTextEdit` | Caja donde el usuario escribe la cadena | `cin` |
| `QPushButton` | Botón "Analizar" que dispara el análisis | El Enter que confirma el `cin` |
| `QTableWidget` | Tabla de resultados (Lexema / Tipo) | `cout` de una tabla con `printf` |
| `QTextBrowser` | Texto largo de solo lectura (Punto 2) | `cout` de un bloque de texto |

## 1.4 Los *layouts*: colocar sin coordenadas

**Frase:** *"No pongo coordenadas x/y. Le digo a Qt 'estos van en columna' o 'estos van en fila', y Qt calcula posiciones y tamaños, y los recalcula al redimensionar la ventana."*

- `QVBoxLayout` → apila en **vertical**.
- `QHBoxLayout` → coloca en **horizontal**.
- Se anidan entre sí.

Pestaña 3 (mostrar en pantalla):

```cpp
QVBoxLayout *Layout = new QVBoxLayout(W);   // columna principal
Layout->addWidget(Titulo);                  // fila 1: etiqueta
Layout->addWidget(EntradaP3);               // fila 2: cuadro de texto
Layout->addWidget(BtnAnalizar);             // fila 3: botón

QHBoxLayout *Fila = new QHBoxLayout;        // fila 4: dos columnas
Fila->addWidget(TablaP3, 2);               //   tabla de tokens  (peso 2)
Fila->addWidget(ConteoP3, 1);             //   tabla de conteo   (peso 1)
Layout->addLayout(Fila);
```

El `2` y el `1` son **factores de estiramiento**: la tabla de tokens ocupa el doble de ancho.

## 1.5 Signals y slots: cómo el botón llama a mi función

**Frase:** *"En vez de preguntar en un bucle '¿han pulsado el botón?', declaro una conexión: cuando el botón emita la señal `clicked`, ejecuta mi función `onAnalizarPunto3`."*

```cpp
connect(BtnAnalizar, &QPushButton::clicked,          // emisor + señal
        this,         &MainWindow::onAnalizarPunto3); // receptor + slot
```

- **Signal**: evento que un objeto anuncia (`clicked`, `textChanged`…). No tiene cuerpo; lo genera Qt.
- **Slot**: una función normal mía que reacciona.

```cpp
private slots:
    void onAnalizarPunto1();
    void onAnalizarPunto3();
```

Flujo: clic → el bucle de eventos lo detecta → ve la conexión → llama a `onAnalizarPunto3()` → ahí está mi lógica.

## 1.6 La macro `Q_OBJECT` (enlaza con el bloque de CMake)

```cpp
class MainWindow : public QMainWindow
{
    Q_OBJECT          // ← obligatorio para tener signals/slots propios
    ...
};
```

**Frase clave:** *"C++ por sí solo no sabe qué es un slot ni cómo funciona `connect`. Hace falta un paso de generación de código previo a la compilación llamado **moc**. Y ese paso es justo lo que CMake orquesta."*

---

# BLOQUE 2 — CMake: por qué esto no compila como un `.cpp` de consola

## 2.1 Qué tiene de especial el código Qt

Un programa de consola se compila con `g++ main.cpp -o programa`. Con Qt **eso falla**, por tres motivos:

1. **Faltan las cabeceras de Qt.** `#include <QApplication>` está en rutas como `/usr/include/.../qt5/QtWidgets/`. Hay que pasarlas al compilador (`-I`).
2. **Faltan las librerías de Qt al enlazar.** El código de `QApplication`, `QPushButton`… está en `libQt6Widgets.so` / `Qt6Widgets.dll`. Hay que enlazar contra ellas (`-l`).
3. **Falta el paso de moc.** La macro `Q_OBJECT` exige generar `moc_MainWindow.cpp`, con la implementación real de las signals/slots y del sistema de meta-objetos (introspección). Lo produce la herramienta **moc** (Meta-Object Compiler) leyendo el `.h`. Sin ese archivo: errores tipo *"undefined reference to vtable for MainWindow"*.

(Análogos en Qt: **uic** para archivos `.ui`, **rcc** para recursos `.qrc`. Aquí no se usan, pero CMake los deja activados.)

## 2.2 Qué hace mi `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.16)
project(AL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # genera compile_commands.json (IntelliSense de VS Code)

set(CMAKE_AUTOMOC ON)                   # ← ejecuta moc automáticamente en los .h con Q_OBJECT
set(CMAKE_AUTORCC ON)                   # ← ejecuta rcc en los .qrc
set(CMAKE_AUTOUIC ON)                   # ← ejecuta uic en los .ui

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)        # ¿hay Qt6? si no, ¿Qt5?
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)   # carga ese Qt concreto

add_executable(AL
    interfaz/Main.cpp
    interfaz/MainWindow.cpp
    interfaz/MainWindow.h               # se lista para que AUTOMOC lo procese
    code/Punto1Estructuras.cpp  code/Punto1Estructuras.h
    code/Punto2Alfabeto.cpp     code/Punto2Alfabeto.h
    code/Punto3Regex.cpp        code/Punto3Regex.h
)

target_include_directories(AL PRIVATE code interfaz)
target_link_libraries(AL PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
```

| Problema del 2.1 | Lo resuelve |
|---|---|
| Rutas de cabeceras de Qt | `find_package(... Widgets)` + `target_link_libraries(... Qt::Widgets)` — el "target" `Qt6::Widgets` ya lleva dentro las rutas de include y los flags |
| Enlazar con las librerías de Qt | `target_link_libraries(AL PRIVATE Qt6::Widgets)` |
| Generar y compilar `moc_MainWindow.cpp` | `set(CMAKE_AUTOMOC ON)` + listar `MainWindow.h` en `add_executable` |
| Compilar con Qt5 en Ubuntu y Qt6 en Windows sin tocar nada | `find_package(QT NAMES Qt6 Qt5 ...)` + usar `${QT_VERSION_MAJOR}` en todos lados |

## 2.3 El flujo de dos fases de CMake

**Frase:** *"CMake no compila. Es un generador: lee `CMakeLists.txt` y produce los archivos de build nativos de la plataforma — Makefiles en Linux, un proyecto de Visual Studio en Windows. Luego otra herramienta compila de verdad."*

```bash
# Fase 1: configurar / generar
cmake -S . -B build
#   -S .      → el fuente está aquí (donde está CMakeLists.txt)
#   -B build  → todo lo generado va a build/
#   CMake busca Qt, comprueba el compilador, escribe los Makefiles / proyecto VS.

# Fase 2: construir
cmake --build build
#   1. corre moc sobre MainWindow.h  → build/AL_autogen/moc_MainWindow.cpp
#   2. compila cada .cpp (los míos + el de moc) → .o / .obj
#   3. enlaza todo + Qt6Widgets → ejecutable AL (o AL.exe)
```

**Ventaja para mi caso:** el mismo `CMakeLists.txt` y los mismos dos comandos funcionan en mi Ubuntu y en la máquina Windows del CI. Solo cambia lo que CMake genera por debajo.

## 2.4 `AL.pro` (qmake) — por qué está y no se usa

- `qmake` es el sistema de build *antiguo* de Qt; el `.pro` hace lo mismo (`SOURCES`, `HEADERS`, `QT += widgets`).
- Es específico de Qt y lo entiende solo Qt; Qt lo está retirando en favor de CMake desde Qt6.
- Está en el repo como alternativa histórica. El build oficial es **CMake**.

---

# BLOQUE 3 — Sustituir `cin` / `cout` por elementos de Qt

**Frase:** *"En consola, entrada y salida son un flujo de texto secuencial. En Qt son el estado de unos widgets que leo o escribo cuando hace falta, normalmente dentro de un slot."*

## 3.1 Entrada: `cin` → leer de un widget

Consola:
```cpp
string entrada;
getline(cin, entrada);      // el programa se bloquea hasta que el usuario escribe
```

Qt — leo el contenido del cuadro de texto **en el momento en que se pulsa "Analizar"**:
```cpp
void MainWindow::onAnalizarPunto3()
{
    string Entrada = EntradaP3->toPlainText().toStdString();
    ...
}
```
- `toPlainText()` devuelve un `QString` (texto de Qt, Unicode).
- `.toStdString()` lo pasa a `std::string`, que es lo que espera mi `AnalizadorRegex::analizar(const string&)`.
- No hay bloqueo ni espera: el "cuándo" lo marca el evento del botón.

## 3.2 Salida: `cout` → escribir en un widget

Consola:
```cpp
for (auto& t : tokens)
    cout << t.lexema << "\t" << nombreTipo(t.tipo) << "\n";
```

Qt — relleno una tabla; cada fila impresa se convierte en insertar celdas:
```cpp
TablaP3->setRowCount(Tokens.Cantidad);              // tantas filas como tokens
for (int I = 0; I < Tokens.Cantidad; ++I)
{
    TablaP3->setItem(I, 0,                          // fila I, columna 0
        new QTableWidgetItem(QString::fromStdString(Tokens.Datos[I].Lexema)));
    TablaP3->setItem(I, 1,                          // fila I, columna 1
        new QTableWidgetItem(QString::fromStdString(Punto3::nombreTipo(Tokens.Datos[I].Tipo))));
}
```
- `QString::fromStdString(...)` → conversión inversa `std::string` → `QString` (los widgets solo hablan `QString`).
- `QString::number(entero)` sustituye a imprimir un número (tabla de conteo):
  ```cpp
  ConteoP3->setItem(I, 1, new QTableWidgetItem(QString::number(Filas[I].Valor)));
  ```

## 3.3 Tabla de equivalencias

| Consola | Qt (en el proyecto) |
|---|---|
| `cin >> x` / `getline(cin, x)` | `widget->toPlainText()` (o `->text()` en `QLineEdit`) |
| Confirmar entrada con Enter | Pulsar un `QPushButton` → se dispara un slot |
| `cout << "texto fijo"` | `QLabel("texto fijo")` o `QTextBrowser::setPlainText(...)` |
| `cout << variable` (número) | `QString::number(variable)` en un `QTableWidgetItem` / `QLabel` |
| `cout` de una tabla con columnas | `QTableWidget` + `setRowCount` + `setItem(fila, col, ...)` |
| `std::string` ↔ texto de UI | `QString::fromStdString()` / `qstr.toStdString()` |
| Bucle `while` que pide datos repetidamente | No hay bucle propio: el bucle de eventos de Qt vuelve a llamar a mi slot cada vez que se pulsa el botón |

## 3.4 Consecuencia de diseño (frase de cierre del bloque)

*"Mi lógica de análisis no cambió: `Punto1`, `Punto2`, `Punto3` siguen trabajando con `std::string`, `std::regex`, `struct`, `enum`… C++ puro. Qt solo envuelve esa lógica."*

```
[QPlainTextEdit] --toStdString()--> [AnalizadorRegex] --struct ListaTokens--> [QTableWidget]
     entrada                           lógica pura                                salida
```

**La GUI es una capa fina de entrada/salida; el núcleo del compilador es independiente de Qt.**

---

# BLOQUE 4 — El workflow de GitHub Actions: VM + compilar a Windows portable

Archivo: `.github/workflows/build-windows.yml`.

## 4.1 Qué es GitHub Actions

**Frase:** *"Es el sistema de integración continua de GitHub. Describo en un archivo YAML unos pasos; cuando ocurre un disparador, GitHub arranca una máquina virtual limpia en sus servidores, clona mi repo dentro y ejecuta esos pasos. Al terminar, la VM se destruye."*

Problema que resuelve: **desarrollo en Ubuntu pero necesito un `.exe` de Windows**. En vez de instalar Windows, pido a GitHub una VM Windows temporal que compile por mí.

## 4.2 Anatomía del YAML

```yaml
name: Build Windows Portable        # nombre en la pestaña "Actions"

on:                                 # DISPARADORES
  workflow_dispatch:                #   - botón "Run workflow" manual en la web
  push:
    branches: [ main, master ]      #   - automático en cada push a main o master

jobs:
  build-windows:                    # un "job" = pasos que corren en una VM
    runs-on: windows-latest         # ← PIDE UNA VM WINDOWS (imagen con MSVC preinstalado)
    defaults:
      run:
        working-directory: Code/AL  # los comandos se ejecutan dentro de Code/AL/
    steps:
      - ...                         # lista ordenada de pasos
```

Conceptos para explicar:
- **`on`**: eventos que lanzan el workflow (`push` automático + `workflow_dispatch` manual).
- **`job`**: unidad aislada; corre en su propia VM.
- **`runs-on: windows-latest`**: la línea que hace que GitHub aprovisione una **VM Windows Server** ya preparada (Visual Studio / compilador MSVC, CMake, PowerShell, git…). Alternativas: `ubuntu-latest`, `macos-latest`.
- **`steps`**: se ejecutan **en orden** en la misma VM. Si uno falla, el workflow para y se marca en rojo.
- Cada step es `uses:` (una *action* reutilizable de terceros/GitHub) o `run:` (un comando de shell).

## 4.3 Los pasos, uno a uno

### Paso 1 — traer el proyecto a la VM
```yaml
- name: Checkout
  uses: actions/checkout@v4
```
La VM nace **vacía**. Esta action oficial clona mi repositorio (el que ya subí a GitHub) dentro de la VM.
**Aclara la duda de "el proyecto ya subido al repositorio":** el workflow no compila "en GitHub" mágicamente; **descarga el repo en una VM y compila ahí**.

### Paso 2 — instalar Qt en la VM
```yaml
- name: Instalar Qt (MSVC 64 bits)
  uses: jurplel/install-qt-action@v4
  with:
    version: '6.7.*'
    host: 'windows'
    target: 'desktop'
    arch: 'win64_msvc2019_64'
```
La VM trae compilador pero **no trae Qt**. Esta action de terceros descarga e instala **Qt 6.7** para Windows en la variante **MSVC 2019, 64 bits**, y deja las variables de entorno listas para que CMake lo encuentre con `find_package`.
Aquí encaja la decisión del `CMakeLists.txt`: como usa `find_package(QT NAMES Qt6 Qt5 ...)`, en Ubuntu coge Qt5 y en esta VM coge Qt6 **sin cambiar una línea**.

### Paso 3 — configurar con CMake
```yaml
- name: Configurar CMake
  run: cmake -S . -B build -A x64 -DCMAKE_BUILD_TYPE=Release
```
Fase 1 de CMake en la VM:
- `-S .` = fuente en `Code/AL` (por el `working-directory`),
- `-B build` = genera en `Code/AL/build`,
- `-A x64` = arquitectura 64 bits,
- `-DCMAKE_BUILD_TYPE=Release` = build optimizada, sin símbolos de depuración (la que se entrega).
CMake genera un proyecto de Visual Studio.

### Paso 4 — compilar
```yaml
- name: Compilar
  run: cmake --build build --config Release
```
Fase 2: CMake invoca a MSBuild (compilador de Visual Studio), que corre **moc** sobre `MainWindow.h`, compila todos los `.cpp` y enlaza con `Qt6Widgets`.
Resultado: `Code/AL/build/Release/AL.exe`.

### Paso 5 — hacer el ejecutable portable con `windeployqt`
```yaml
- name: Crear carpeta portable con windeployqt
  shell: pwsh
  run: |
    New-Item -ItemType Directory -Force -Path dist
    Copy-Item build\Release\AL.exe dist\
    windeployqt --release --compiler-runtime dist\AL.exe
```
Problema: `AL.exe` solo **no arranca** en un PC sin Qt, porque depende de DLLs (`Qt6Core.dll`, `Qt6Gui.dll`, `Qt6Widgets.dll`, el plugin de plataforma `platforms/qwindows.dll`, y el runtime de Visual C++).
`windeployqt` es una herramienta oficial de Qt que:
1. analiza `AL.exe` para ver qué partes de Qt usa,
2. copia **todas** esas DLLs y plugins junto al `.exe` en `dist/`,
3. con `--compiler-runtime`, añade también el runtime de MSVC.

`shell: pwsh` = ese bloque son comandos **PowerShell**.
Resultado: `dist/` es **autocontenida** → se copia a cualquier Windows y funciona con doble clic, sin instalar nada. Eso es "portable".

### Paso 6 — publicar el resultado
```yaml
- name: Subir carpeta portable como artefacto
  uses: actions/upload-artifact@v4
  with:
    name: AL-Windows-Portable
    path: Code/AL/dist
```
La VM se va a destruir → hay que **sacar** `dist/` antes. Esta action la sube a GitHub como **artefacto**: un `.zip` descargable desde la página del run (Actions → run → "Artifacts"). Ese archivo acabó también en `Releases/Ejecutable Windows.zip`.

## 4.4 El ciclo completo (dibujar en pantalla)

```
git push a main (desde Ubuntu)
        │
        ▼
GitHub detecta el push → dispara el workflow (on: push)
        │
        ▼
GitHub arranca una VM Windows Server limpia (runs-on: windows-latest)
        │
        ├─ 1. checkout       → clona el repo dentro de la VM
        ├─ 2. install-qt     → instala Qt 6.7 (MSVC 64)
        ├─ 3. cmake -B build  → genera proyecto Visual Studio (Release, x64)
        ├─ 4. cmake --build   → moc + compila + enlaza → AL.exe
        ├─ 5. windeployqt     → dist/ = AL.exe + todas las DLLs (portable)
        └─ 6. upload-artifact → sube dist/ como .zip descargable
        │
        ▼
GitHub destruye la VM. Queda el artefacto "AL-Windows-Portable".
```

## 4.5 Matiz importante (no equivocarse al exponer)

**Frase:** *"Esto NO es compilación cruzada — no compilo Windows desde Linux con un toolchain tipo MinGW-w64. Es compilación nativa en una máquina Windows remota: GitHub me presta una VM Windows unos minutos."*
Ventaja frente a la compilación cruzada: uso el compilador oficial de la plataforma (MSVC) y el `windeployqt` de Windows, con cero configuración especial — **el mismo `CMakeLists.txt` que uso en mi Ubuntu**.

---

# BLOQUE 5 — Herramientas de apoyo (mencionar rápido)

## 5.1 VS Code como entorno (en Ubuntu)
- **`.vscode/tasks.json`**: tarea de build por defecto (`Ctrl+Shift+B`) que llama a `build.sh` / `build.bat` según el SO, con `problemMatcher: $gcc` para ver los errores clicables.
- **`.vscode/c_cpp_properties.json`**: configura la extensión **C/C++ de Microsoft** para leer `build/compile_commands.json` (generado por CMake). Así los `#include <QApplication>` no salen en rojo sin listar carpetas de Qt a mano.
- Puente clave: **CMake genera `compile_commands.json` → VS Code lo consume** para el autocompletado.

## 5.2 Scripts de un comando
| Script | SO | Qué hace |
|---|---|---|
| `build.sh` | Linux/macOS | `cmake -S . -B build` + `cmake --build build -j$(nproc)`; con `run` ejecuta. `set -e` aborta al primer error. Comprueba que `cmake` esté en el PATH. |
| `build.bat` | Windows | Igual, con generador `MinGW Makefiles`. |
| `deploy-windows.bat` | Windows | Compila en Release + genera `dist/` portable con `windeployqt` (equivalente local del paso 5 del CI). |

## 5.3 Git + GitHub
- Repo público, workflow en `.github/workflows/`.
- Los mensajes de commit muestran que ajustar el CI llevó iteración: *"Muevo workflow de GitHub Actions a la ubicacion correcta"*, *"Update working directory and artifact path in workflow"*.
- Carpeta `PDF/` con el enunciado (`Practica1.pdf`) y el informe (`main.pdf`).

---

# GUION RÁPIDO (checklist para exponer en orden)

1. **Lenguaje + GUI:** C++17 y Qt Widgets — bucle de eventos, todo es `QWidget`, layouts sin coordenadas, signals/slots, `Q_OBJECT`.
2. **CMake:** por qué Qt no compila con un `g++` simple (cabeceras, librerías, **moc**); qué resuelve el `CMakeLists.txt` (`find_package`, `AUTOMOC`, `Qt::Widgets`, detección Qt5/Qt6); flujo de dos fases (configurar / construir).
3. **`cin`/`cout` → Qt:** leer de `QPlainTextEdit`, escribir en `QTableWidget`; conversiones `QString` ↔ `std::string`; la lógica del analizador no cambia.
4. **Entorno:** VS Code en Ubuntu (tasks.json, IntelliSense vía `compile_commands.json`); scripts `build.sh` / `build.bat`.
5. **Problema:** desarrollo en Ubuntu, entrega en Windows.
6. **Solución CI:** workflow de GitHub Actions → `runs-on: windows-latest` levanta una VM → `checkout` (repo) → `install-qt-action` (Qt 6.7 MSVC) → `cmake` configurar + construir → `windeployqt` (portable) → `upload-artifact`.
7. **Aclaración:** no es compilación cruzada, es una VM Windows nativa; mismo `CMakeLists.txt` en ambas plataformas.
8. **Entrega final:** `Releases/Ejecutable Windows.zip`.
