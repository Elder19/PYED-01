#pragma once
#include <iostream> 
#include <fstream>
//INCLUIR CLASE

using namespace std;

class readANSI {


public:
 
    string leerArchivo(string ruta, bool charge) {
        //nombrECLASE NOMBREPUNTERO;
        ifstream archivo(ruta);

        string contenido; //  para almacenar el contenido del archivo

        string linea; //  para leer cada l�nea del archivo

     
        if (archivo.is_open()) {
            
            while (getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la l�nea y un salto de l�nea
                if (charge){}
                  
                   
            }
            archivo.close(); // Cierra el archivo despu�s de la lectura
            return contenido;
        }
        else {
            
            cout << "Error al abrir el archivo \n" << endl;
            return "";
        }
    }

};