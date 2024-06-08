#pragma once

#include <string> 
#include <iostream>
#include <fstream> 
#include <sstream> 
#include "readANSI.h"
#include "objPalabra.h"
#include "ArrayListt.h"
#include "BSTDictionary.h"
#include "MaxHeap.h"
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
    ArrayListt<char>  ignoreL;  //abecedario
    HeapPriorityQueue<string>* queue;// lista de prioridad
    DLinkedList<string>* Lineas = new DLinkedList<string>();
    // Evitar que se copie la instancia
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
  
public:
    // Metodo para obtener la instancia
    static Admin& getInstance() {
        static Admin instance; // Instancia �nica creada en el primer acceso
        return instance;

    }
    /**
     * @brief Lee el contenido de un archivo.
     *
     * @param ruta La ruta del archivo a leer.
     * @param charge Si es true, carga las líneas del archivo en la lista de líneas.
     * @return El contenido del archivo como una cadena de texto.
     */
    string leerArchivo(string ruta, bool charge) {
        
        ifstream archivo(ruta);

        string contenido; //  para almacenar el contenido del archivo

        string linea; //  para leer cada línea del archivo

        cout << "Ruta: " << ruta << "\n";
        if (archivo.is_open()) {

            while (getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la línea y un salto de línea
                if (charge)
                    Lineas->insert(linea + "\n");

            }
            archivo.close(); // Cierra el archivo después de la lectura
            return contenido;
        }
        else {

            cout << "Error al abrir el archivo \n" << endl;
            return "";
        }
    }

    /**
    * @brief Selecciona y muestra palabras del archivo especificado.
    *
    * Solicita al usuario una ruta de archivo, lo lee y muestra cada palabra junto con su número de línea.
    */
    void selectorPalabras() {
      
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        string contenidoArchivo = leerArchivo(ruta, true);
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
    /**
    * @brief Lee caracteres individuales de un archivo especificado y los almacena en la lista de caracteres a ignorar.
    *
    * Solicita al usuario una ruta de archivo y lo lee, almacenando cada carácter en la lista de caracteres a ignorar.
    */
    void abc() {
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        string contenidoArchivo = leerArchivo(ruta, false);
        cout << contenidoArchivo;
        for (char c : contenidoArchivo) {
            if (c != ' ' && c != '\n') {
                cout << c;
                ignoreL.append(c);
            }
        }
    }
    /**
    * @brief Lee palabras de un archivo y las almacena en la lista de palabras a ignorar.
    *
    * Solicita al usuario una ruta de archivo, lo lee y almacena las palabras en la lista de palabras a ignorar.
    */
    void palabrasAIgnorar() {
       
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        string contenidoArchivo = leerArchivo(ruta, false);

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
            while (fin < contenidoArchivo.length() && ignoreL.contains(contenidoArchivo[fin]) && contenidoArchivo[fin] != '\n') {

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