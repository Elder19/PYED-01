#pragma once
#include <iostream> // Incluye la biblioteca de entrada/salida est�ndar
#include <fstream>  // Incluye la biblioteca para manejo de archivos

using namespace std; // Utiliza el espacio de nombres est�ndar

class readANSI {


public:
    string leerArchivo(string ruta) {
        ifstream archivo(ruta); // Abre el archivo en modo lectura

        string contenido; // Variable para almacenar el contenido del archivo

        string linea; // Variable para leer cada l�nea del archivo


        if (archivo.is_open()) { // Verifica si el archivo se abri� correctamente
            // Lee el archivo l�nea por l�nea y concatena cada l�nea al contenido
            while (getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la l�nea y un salto de l�nea
            }
            archivo.close(); // Cierra el archivo despu�s de la lectura
            return contenido; // Retorna todo el contenido del archivo
        }
        else {
            // Mensaje de error si el archivo no se pudo abrir
            cout << "Error al abrir el archivo" << endl;
            return ""; // Retorna una cadena vac�a en caso de error
        }
    }

};