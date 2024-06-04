#pragma once

#include <string> 
#include <iostream>
#include <fstream> 
#include <sstream> 
#include "readANSI.h"
#include "objPalabra.h"
#include "ArrayListt.h"
#include "BSTDictionary.h"
#include "MinHeap.h"
#include "HeapPriorityQueue.h"
using namespace std;

/*
Clase Admin: Sigue el patron Singleton, esto permite que exista una unica instancia de la clase
Descripcion: Sirve como un administrador para los datos y operaciones del programa
*/

class Admin {

private:
    // Constructor privado para evitar la creaci�n de instancias fuera de la clase
    Admin() {}
    ArrayListt<string>  ignoreW;  // Lista de apariciones en líneas
    ArrayListt<string>  ignoreL;  //abecedario
    HeapPriorityQueue<string>* queue;// lista de prioridad
    // Evitar que se copie la instancia
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
  
public:
    // Metodo para obtener la instancia
    static Admin& getInstance() {
        static Admin instance; // Instancia �nica creada en el primer acceso
        return instance;

    }
 
        
       
    void selectorPalabras() {
        readANSI lector; // Crea una instancia de la clase readANSI
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        string contenidoArchivo = lector.leerArchivo(ruta, true);
        int lineNumber = 1;
        size_t inicio = 0;
        string line;

        for (size_t fin = inicio; fin < contenidoArchivo.length(); fin++) {
          
            // Avanzar hasta el primer carácter que no sea espacio o nueva línea
            while (fin < contenidoArchivo.length() && (contenidoArchivo[fin] == ' ' || contenidoArchivo[fin] == '\n')) {
                if (contenidoArchivo[fin] == '\n') {
                    lineNumber++;
                }
                fin++;
            }

            // Encontrar el final de la palabra
            size_t finPalabra = fin;
            while (finPalabra < contenidoArchivo.length() && contenidoArchivo[finPalabra] != ' ' && contenidoArchivo[finPalabra] != '\n') {
                finPalabra++;
               
            }
            
            if (fin < finPalabra) {
                string palabra = contenidoArchivo.substr(fin, finPalabra - fin);
                line.clear();
                cout << "Palabra: " << palabra << ", Línea: " << lineNumber << std::endl;
                fin = finPalabra;
            }
        }
    }

    void abc() {

        readANSI lector; // Crea una instancia de la clase readANSI

         
        string contenidoArchivo = lector.leerArchivo("g.txt", false);
        size_t inicio = 0;
        cout << contenidoArchivo;
        size_t fin = inicio;
        while (inicio < contenidoArchivo.length()) {
            
            while (fin < contenidoArchivo.length() && contenidoArchivo[fin] != ' ' && contenidoArchivo[fin] != '\n') {
                fin++;
            }

            if (inicio < fin) {
                string palabra = contenidoArchivo.substr(inicio, fin - inicio);
                cout << palabra;
                ignoreL.append(palabra);
                inicio = fin + 1;

            }
        }
    
    
    
    }
    void palabrasAIgnorar() {
        readANSI lector; // Crea una instancia de la clase readANSI
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        string contenidoArchivo = lector.leerArchivo(ruta, false);

        size_t inicio = 0;
        size_t fin = inicio;
        int lineNumber = 1;
        // Avanzar hasta el primer carácter que no sea espacio o nueva línea
        while (inicio < contenidoArchivo.length()) {
            size_t fin = inicio;
            cout << contenidoArchivo[fin];
            // Avanzar hasta el primer carácter que no sea espacio o nueva línea
            while (fin < contenidoArchivo.length() && (contenidoArchivo[fin] == ' ' || contenidoArchivo[fin] == '\n')) {
                if (contenidoArchivo[fin] == '\n') {
                    lineNumber++;

                }


                fin++;
            }

            // Encontrar el final de la palabra
            inicio = fin;
            while (fin < contenidoArchivo.length() && contenidoArchivo[fin] != ' ' && contenidoArchivo[fin] != '\n') {
                fin++;
            }

            if (inicio < fin) {
                string palabra = contenidoArchivo.substr(inicio, fin - inicio);
                ignoreW.append(palabra);
            }

            cout << "Se ingreso con exito el archivo de texto con palabras a ingresar";

        }
    }
    // falta cargar el heap 
    // falta leer archivos misma carpeta
    // falta extraer la linea completa ., hecho en read ansii

};

  



