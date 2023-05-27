#include <iostream> // Proporciona funciones básicas de entrada y salida a través de la consola, como cout y cin, para imprimir y leer datos.
#include <string> // Proporciona funcionalidad para trabajar con cadenas de caracteres, como la clase string y varias funciones relacionadas con manipulación de cadenas.
#include <fstream> // Permite leer y escribir archivos en disco, proporcionando clases como ifstream para leer archivos y ofstream para escribir en ellos.
#include <iomanip> // Proporciona herramientas para manipular el formato de salida, como establecer la precisión decimal, el ancho de campo y la alineación.
#include <vector> // Implementa una estructura de datos de arreglo dinámico que puede crecer o reducir su tamaño según sea necesario.
#include <set> // Implementa un contenedor de conjunto que almacena elementos únicos en un orden específico.
#include <unistd.h> // Es una librería de C que proporciona funciones para interactuar con el sistema operativo, como la función sleep para pausar la ejecución durante un tiempo determinado.
#include <cmath> // Proporciona funciones matemáticas comunes, como funciones trigonométricas, logarítmicas y exponenciales.


using namespace std;

const double IGSS_PORCENTAJE = 4.83 / 100;

// Arreglos de cadenas para convertir números a palabras
string unidades[] = {"", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
string especiales[] = {"diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete", "dieciocho", "diecinueve"};
string decenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};

// Definición de la estructura Trabajador
struct Trabajador {
    int id;
    string nombre;
    string apellido;
    double sueldo;
    double igss;
    double descuentos;
    double liquido;
};

// Función para mostrar el menú y obtener la opción seleccionada
int mostrarMenu() {
    int opcion;
    cout << endl;
    cout << "Menu:" << endl;
    cout << "1. Ingreso de trabajadores" << endl;
    cout << "2. Visualizacion de la planilla" << endl;
    cout << "3. Actualizar datos de un trabajador" << endl;
    cout << "4. Eliminar un trabajador" << endl;
    cout << "5. Guardar archivo de planilla" << endl;
    cout << "6. Cargar archivo de planilla" << endl;
    cout << "7. Imprimir cheque" << endl;
    cout << "8. Salir" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;
    system("clear");
    return opcion;
}

// Función para ingresar los datos de los trabajadores
void ingresoTrabajadores(vector<Trabajador>& trabajadores) { // recibe una referencia al vector de trabajadores para poder modificarlo 
    int cantidad;
    cout << "Ingrese la cantidad de trabajadores: ";
    cin >> cantidad;
    set<int> ids; // Conjunto para almacenar los IDs de los trabajadores ingresados para garantizar que no haya IDs duplicados.
    for(int i=0; i<cantidad; i++) {
        Trabajador t;
        cout << "Ingrese los datos del trabajador " << i+1 << ":" << endl;
        bool idValido = false;
        while(!idValido) {
            cout << "ID: ";
            cin >> t.id;
            // Verificar si el ID ya existe en el conjunto de IDs
            auto it = ids.find(t.id);
            if(it == ids.end()) {
                idValido = true;
                ids.insert(t.id); // Agregar el ID al conjunto
            } else {
                cout << "El ID ingresado ya existe. Ingrese un ID diferente." << endl;
            }
        }
        //Los datos se ingresan y asignan al objeto Trabajador t.
        cout << "Nombre: ";
        cin >> t.nombre;
        cout << "Apellido: ";
        cin >> t.apellido;
        cout << "Sueldo: ";
        cin >> t.sueldo;
        t.igss = t.sueldo * IGSS_PORCENTAJE;  // Calcular el IGSS basado en el sueldo
        cout << "Descuentos: ";
        cin >> t.descuentos;
        t.liquido = t.sueldo - t.descuentos - t.igss; // Calcular el sueldo líquido
        trabajadores.push_back(t); // Agregar el trabajador al vector de trabajadores
    }
}

// Muestra la información de los trabajadores en forma de planilla
void visualizacionPlanilla(const vector<Trabajador>& trabajadores) { // Recibe el vector de trabajadores como parámetro, pero se declara como una referencia constante para evitar modificaciones accidentales en los datos.
    // Encabezado de la planilla
    // Se utiliza setw para establecer el ancho de cada columna en la planilla, lo que permite alinear correctamente los datos.
    cout << left << setw(5) << "ID" << setw(20) << "Nombre"  << setw(20) << "Apellido" << setw(10) << "Sueldo" << setw(20) << "Igss - 4.83%" << setw(15) << "Descuentos" << setw(15) << "Liquido" << endl;
    // Iterar sobre cada trabajador en el vector
    for(auto t : trabajadores) { // En cada iteración, se imprime la información del trabajador en la planilla
        cout << fixed << setprecision(2); // Configurar la precisión decimal para imprimir los valores con dos decimales
        // Imprimir los datos del trabajador en la planilla
        cout << left << setw(5) << t.id << setw(20) << t.nombre << setw(20) << t.apellido << setw(10) << t.sueldo << setw(20) << t.igss << setw(15) << t.descuentos << setw(15) << t.liquido << endl;
    }
}

// Actualiza los datos de un trabajador existente en el vector
void actualizarTrabajador(vector<Trabajador>& trabajadores) {
    int id;
    cout << "Ingrese el ID del trabajador que desea actualizar: ";
    cin >> id;

    bool encontrado = false;
    for(auto& t : trabajadores) { // Itera sobre cada trabajador en el vector.
        if(t.id == id) { // Se verifica si el ID del trabajador actual coincide con el ID ingresado por el usuario
            cout << "Ingrese los nuevos datos para el trabajador:" << endl;
            cout << "Nombre: ";
            cin >> t.nombre;
            cout << "Apellido: ";
            cin >> t.apellido;
            cout << "Sueldo: ";
            cin >> t.sueldo;
            t.igss = t.sueldo * IGSS_PORCENTAJE; // Se recalcula
            cout << "Descuentos: ";
            cin >> t.descuentos;

            t.liquido = t.sueldo - t.descuentos - t.igss; //Se calcula el valor de liquido

            cout << "Datos del trabajador actualizados correctamente." << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se encontro un trabajador con el ID especificado." << endl;
    }
}

// Elimina un trabajador del vector trabajadores en base a su ID
void eliminarTrabajador(vector<Trabajador>& trabajadores) { //Recibe el vector de trabajadores como referencia para poder modificar al eliminar un trabajador.
    int id;
    cout << "Ingrese el ID del trabajador que desea eliminar: ";
    cin >> id;
    bool encontrado = false;
    // Iterar sobre el vector
    for(auto it = trabajadores.begin(); it != trabajadores.end(); ++it) {
        if(it->id == id) {
            trabajadores.erase(it); // Eliminar el trabajador del vector
            cout << "Trabajador eliminado correctamente." << endl;
            encontrado = true;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se encontro un trabajador con el ID especificado." << endl;
    }
}

// Guardar los datos de los trabajadores en un archivo en formato CSV
void guardarArchivo(const vector<Trabajador>& trabajadores) {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    cin >> nombreArchivo;
     // Verificar si la extensión es ".csv" y agregarla si no está presente
    if(nombreArchivo.substr(nombreArchivo.length()-4) != ".csv") {
        nombreArchivo += ".csv";
    }

 // Crear un objeto de tipo ofstream para abrir el archivo en modo escritura
ofstream archivo(nombreArchivo);
    // Escribir los encabezados en la primera línea del archivo
    archivo << "ID\tNombre\tApellido\tSueldo\tDescuentos\tLiquido" << endl;
    // Recorrer el vector de trabajadores y escribir sus datos en el archivo
    for(auto t : trabajadores) {
        archivo << fixed << setprecision(2); // Configurar la precisión decimal en 2
        archivo << t.id << "\t" << t.nombre << "\t" << t.apellido << "\t" << t.sueldo << "\t" << t.igss << "\t" << t.descuentos << "\t\t" << t.liquido << endl;
    }
    archivo.close(); // Cerrar el archivo
    cout << "Archivo guardado correctamente." << endl;
    sleep(2);
}

// Carga los datos de los trabajadores desde un archivo CSV y almacenarlos en el vector de trabajadores.
void cargarArchivo(vector<Trabajador>& trabajadores) {
string nombreArchivo;
cout << "Ingrese el nombre del archivo: ";
cin >> nombreArchivo;

// Agregar extension .csv si no este presente
if (nombreArchivo.substr(nombreArchivo.length() - 4) != ".csv") {
    nombreArchivo += ".csv";
}

// Crear un objeto de tipo ifstream para abrir el archivo en modo lectura
ifstream archivo(nombreArchivo);
if (!archivo) {
    cout << "No se pudo abrir el archivo." << endl;
    return;
}

// Limpiar el vector de trabajadores
trabajadores.clear();

string linea;
getline(archivo, linea); // Leer y descartar la primera línea (encabezados)

// Leer cada línea del archivo y procesar los datos
while (getline(archivo, linea)) {
    Trabajador t;
    int pos = 0;
    string token;

    // Obtener el ID del trabajador
    pos = linea.find("\t");
    token = linea.substr(0, pos);
    t.id = stoi(token);

    // Obtener el nombre del trabajador
    int posNombre = pos + 1;
    pos = linea.find("\t", posNombre);
    token = linea.substr( posNombre, pos - posNombre);
    t.nombre = token;

    // Obtener el apellido del trabajador
    int posApellido = pos + 1;
    pos = linea.find("\t", posApellido);
    token = linea.substr(posApellido, pos - posApellido);
    t.apellido = token;

    // Obtener el sueldo del trabajador
    int posSueldo = pos + 1;
    pos = linea.find("\t", posSueldo);
    token = linea.substr(posSueldo, pos - posSueldo);
    t.sueldo = stod(token);

    // Obtener el IGSS del trabajador
    int posIgss = pos + 1;
    pos = linea.find("\t", posIgss);
    token = linea.substr(posIgss, pos - posIgss);
    t.igss = stod(token);

    // Obtener los descuentos del trabajador
    int posDescuentos = pos + 1;
    pos = linea.find("\t", posDescuentos);
    token = linea.substr( posDescuentos, pos - posDescuentos );
    t.descuentos = stod(token);

    // Obtener el sueldo líquido del trabajador
    int posLiquido = pos + 1;
    token = linea.substr(posLiquido );
    t.liquido = stod(token);

    // Agregar el trabajador al vector
    trabajadores.push_back(t);
}

// Cerrar el archivo
archivo.close();

cout << "Archivo cargado correctamente." << endl;
}

// Toma un número entero y lo convierte en su representación en palabras. "Acepta números de hasta billones"
string convertirNumero(long long numero, bool esMil = false, bool esMillon = false) {
    string resultado;

    // Convertir millones
    if (numero >= 1000000) {
        if (numero / 1000000 == 1) {
            resultado += "un millon ";
        } else {
            resultado += convertirNumero(numero / 1000000, false, true) + " millones ";
        }
        numero %= 1000000;
    }
    
    // Convertir miles
    if (numero >= 1000) {
        if (numero == 100000) {
            resultado += "cien mil ";
        } else {
            resultado += convertirNumero(numero / 1000, true) + " mil ";
        }
        numero %= 1000;
    }

    // Convertir centenas
    if (numero >= 100) {
        resultado += centenas[numero / 100] + " ";
        numero %= 100;
    }

    // Convertir números del 10 al 19
    if (numero >= 10 && numero <= 19) {
        resultado += especiales[numero - 10] + " ";
    }

    // Convertir decenas
    else if (numero >= 20) {
        resultado += decenas[numero / 10] + " ";
        numero %= 10;
    }

    // Convertir unidades
    if (numero >= 1 && numero <= 9) {
        resultado += unidades[numero] + " ";
    }

    // Eliminar espacio adicional despues de "mil" o "millon" si no es seguido por otro numero
    if ((esMil || esMillon) && numero == 0)
        resultado.pop_back();

    return resultado;
}

// Funcion para convertir un numero en letras (solo admite numeros hasta billones)
string convertirNumeroALetras(double numero) {


    long long parteEntera = static_cast<long long>(numero);
    long long parteDecimal = static_cast<long long>(round((numero - parteEntera) * 100)); // Convertir a entero sin aproximar


    string cantidadEnLetras;

    // Convertir la parte entera
    if (parteEntera == 0) {
        cantidadEnLetras = "cero";
    } else {
        cantidadEnLetras += convertirNumero(parteEntera);
        if (parteEntera == 1 && parteEntera < 1000000)
            cantidadEnLetras += " quetzal ";
    else if (parteEntera > 1 && parteEntera < 1000000)
    cantidadEnLetras += " quetzales ";
    }

    // Convertir la parte decimal
    if (parteDecimal > 0) {
    if (parteDecimal == 1)
        cantidadEnLetras += "con un centavo";
    else
        cantidadEnLetras += "con " + convertirNumero(parteDecimal) + " centavos";
    }
    else {
        cantidadEnLetras += "exactos";
    }
    return cantidadEnLetras;
}

// Genera un cheque para un trabajador específico
void generarCheque(const vector<Trabajador>& trabajadores) {
    int id;
    cout << "Ingrese el ID del trabajador: ";
    cin >> id;

    bool encontrado = false;
    for(auto t : trabajadores) {
        if(t.id == id) {
            encontrado = true;
            cout << "Pago a la orden de: " << t.nombre << " " << t.apellido << endl;
            cout << fixed << setprecision(2);
            cout << "GTQ = " << t.liquido << endl;
            cout << "La suma de = " << convertirNumeroALetras(t.liquido) << endl;
            break;
        }
    }
    if(!encontrado) {
        cout << "No se encontro un trabajador con el ID especificado." << endl;
    }
}

int main(){
    vector<Trabajador> trabajadores;

    int opcion;
    do {
        opcion = mostrarMenu();

        switch(opcion) {
            case 1:
                ingresoTrabajadores(trabajadores);
                system("clear");
                break;
            case 2:
                visualizacionPlanilla(trabajadores);
                break;
            case 3:
                actualizarTrabajador(trabajadores);
                break;
            case 4:
                eliminarTrabajador(trabajadores);
                break;
            case 5:
                guardarArchivo(trabajadores);
                system("clear");
                 break;
            case 6:
                cargarArchivo(trabajadores);
                break;
            case 7:
                generarCheque(trabajadores);
                break;
            case 8:
                cout << "Saliendo del programa..." << endl;
                sleep(1);
                return 0;
            default:
                cout << "Opcion invalida. Ingrese una opcion valida." << endl;
                break;
    }
} while(opcion != 8);
return 0;
}
