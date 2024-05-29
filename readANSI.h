#pragma once
#include <iostream> // Incluye la biblioteca de entrada/salida estándar
#include <fstream>  // Incluye la biblioteca para manejo de archivos

using namespace std; // Utiliza el espacio de nombres estándar

class readANSI {


public:
    string leerArchivo(string ruta) {
        ifstream archivo(ruta); // Abre el archivo en modo lectura

        string contenido; // Variable para almacenar el contenido del archivo

        string linea; // Variable para leer cada línea del archivo


        if (archivo.is_open()) { // Verifica si el archivo se abrió correctamente
            // Lee el archivo línea por línea y concatena cada línea al contenido
            while (getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la línea y un salto de línea
            }
            archivo.close(); // Cierra el archivo después de la lectura
            return contenido; // Retorna todo el contenido del archivo
        }
        else {
            // Mensaje de error si el archivo no se pudo abrir
            cout << "Error al abrir el archivo" << endl;
            return ""; // Retorna una cadena vacía en caso de error
        }
    }

};