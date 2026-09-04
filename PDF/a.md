| Palabra / elemento | Sintaxis | Función |
|---|---|---|
| `QApplication` | `QApplication App(Argc, Argv);` | Administrador de la aplicación gráfica y sus eventos |
| `QMainWindow` | `class MainWindow : public QMainWindow` | Estructura de la ventana principal |
| `Q_OBJECT` | `Q_OBJECT` | Macro para habilitar señales, slots y metadatos de Qt |
| `QWidget` | `QWidget *W = new QWidget;` | Contenedor gráfico genérico |
| `QTabWidget` | `QTabWidget *Tabs = new QTabWidget(this);` | Contenedor dividido en pestañas |
| `QVBoxLayout` | `QVBoxLayout *Layout = new QVBoxLayout(W);` | Distribución vertical de componentes |
| `QHBoxLayout` | `QHBoxLayout *Fila = new QHBoxLayout;` | Distribución horizontal de componentes |
| `QLabel` | `QLabel *Titulo = new QLabel("Texto");` | Etiqueta de texto |
| `QPlainTextEdit` | `QPlainTextEdit *Entrada = new QPlainTextEdit;` | Caja de texto de varias líneas |
| `QPushButton` | `QPushButton *Boton = new QPushButton("Analizar");` | Botón interactivo |
| `QTableWidget` | `QTableWidget *Tabla = new QTableWidget(0, 2);` | Tabla formada por filas y columnas |
| `QTableWidgetItem` | `new QTableWidgetItem("Contenido")` | Elemento o celda de una tabla |
| `QHeaderView` | `Tabla->horizontalHeader()` | Encabezado de una tabla |
| `QTextBrowser` | `QTextBrowser *Info = new QTextBrowser;` | Visor de texto informativo |
| `QFont` | `QFont Mono("Monospace");` | Configuración de tipografía |
| `QString` | `QString Texto = "Ejemplo";` | Cadena de texto propia de Qt |
| `private slots` | `private slots: void onAnalizarPunto1();` | Sección de métodos receptores de eventos |
| `connect()` | `connect(Boton, &QPushButton::clicked, this, &MainWindow::onAnalizarPunto1);` | Conexión entre una señal y un slot |
| `QPushButton::clicked` | `&QPushButton::clicked` | Señal de clic de un botón |
| `onAnalizarPunto1()` | `void MainWindow::onAnalizarPunto1()` | Slot para el análisis manual |
| `onAnalizarPunto3()` | `void MainWindow::onAnalizarPunto3()` | Slot para el análisis con expresiones regulares |
| `show()` | `Ventana.show();` | Presentación de una ventana en pantalla |
| `resize()` | `Ventana.resize(900, 650);` | Dimensiones iniciales de una ventana |
| `exec()` | `return App.exec();` | Ciclo principal de eventos |
| `setWindowTitle()` | `setWindowTitle("Analizador Lexico");` | Título de una ventana |
| `setCentralWidget()` | `setCentralWidget(Tabs);` | Componente central de una ventana principal |
| `addTab()` | `Tabs->addTab(W, "Nombre");` | Pestaña añadida a un contenedor |
| `addWidget()` | `Layout->addWidget(Boton);` | Componente añadido a una distribución |
| `addLayout()` | `Layout->addLayout(Fila);` | Distribución añadida dentro de otra distribución |
| `setWordWrap()` | `Titulo->setWordWrap(true);` | División automática del texto en líneas |
| `setPlaceholderText()` | `Entrada->setPlaceholderText("Escribe aquí");` | Texto de ejemplo de una entrada |
| `setFixedHeight()` | `Entrada->setFixedHeight(80);` | Altura fija de un componente |
| `toPlainText()` | `Entrada->toPlainText()` | Contenido de una caja de texto |
| `toStdString()` | `TextoQt.toStdString()` | Conversión de `QString` a `std::string` |
| `QString::fromStdString()` | `QString::fromStdString(TextoCpp)` | Conversión de `std::string` a `QString` |
| `setPlainText()` | `Info->setPlainText("Información");` | Texto sin formato de un componente |
| `setFont()` | `Info->setFont(Mono);` | Fuente asignada a un componente |
| `setStyleHint()` | `Mono.setStyleHint(QFont::TypeWriter);` | Preferencia de estilo para una fuente |
| `QFont::TypeWriter` | `QFont::TypeWriter` | Estilo de fuente monoespaciada |
| `setHorizontalHeaderLabels()` | `Tabla->setHorizontalHeaderLabels({"Lexema", "Tipo"});` | Nombres de las columnas de una tabla |
| `horizontalHeader()` | `Tabla->horizontalHeader()` | Encabezado horizontal de una tabla |
| `setStretchLastSection()` | `Tabla->horizontalHeader()->setStretchLastSection(true);` | Expansión de la última columna |
| `setEditTriggers()` | `Tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);` | Configuración de edición de una tabla |
| `QAbstractItemView::NoEditTriggers` | `QAbstractItemView::NoEditTriggers` | Modo de tabla no editable |
| `setRowCount()` | `Tabla->setRowCount(Cantidad);` | Cantidad de filas de una tabla |
| `setItem()` | `Tabla->setItem(Fila, Columna, Item);` | Contenido asignado a una celda |
| `new` | `QPushButton *Boton = new QPushButton;` | Creación dinámica de un objeto |
| `this` | `new QTabWidget(this)` | Referencia al objeto actual como elemento padre |
| `Parent` | `MainWindow(QWidget *Parent = nullptr)` | Elemento propietario de otro componente |
| `nullptr` | `QWidget *Parent = nullptr` | Ausencia de una referencia a otro objeto |
