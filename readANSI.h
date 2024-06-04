#pragma once
#include <iostream> 
#include <fstream> 

using namespace std;

class readANSI {


public:
    string leerArchivo(string ruta, bool charge) {
        ifstream archivo(ruta);

        string contenido; //  para almacenar el contenido del archivo

        string linea; //  para leer cada línea del archivo

     
        if (archivo.is_open()) {
            
            while (getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la línea y un salto de línea
                //if (charge)
                    //cargar aqui el codigo de brasly
            }
            archivo.close(); // Cierra el archivo después de la lectura
            return contenido;
        }
        else {
            
            cout << "Error al abrir el archivo \n" << endl;
            return "";
        }
    }

};