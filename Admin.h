#pragma once

#include <list>
#include <string> 
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <algorithm> // Para std::transform
#include <cctype>    // Para std::tolower
#include "readANSI.h"
#include "objPalabra.h"
#include "ArrayListt.h"
#include "BSTDictionary.h"
#include "MaxHeap.h"
#include "HeapPriorityQueue.h"
#include "Trie.h"
#include "BSTree.h"

using namespace std;

/*
Clase Admin: Sigue el patron Singleton, esto permite que exista una unica instancia de la clase
Descripcion: Sirve como un administrador para los datos y operaciones del programa
*/

class Admin {

private:
    // Constructor privado para evitar la creaci�n de instancias fuera de la clase
    Admin() {}
    BSTree<string>* bst = new BSTree<string>(); // Lista de apariciones en líneas
    BSTree<char>* ignoreL = new BSTree<char>();  //abecedario
    DLinkedList<string>* Lineas = new DLinkedList<string>();

    // Evitar que se copie la instancia
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
    Trie trie;

    ~Admin() {
        delete bst;
        delete ignoreL;
        delete Lineas;
    }
    
  
public:
    // Metodo para obtener la instancia
    static Admin& getInstance() {
        static Admin instance; // Instancia �nica creada en el primer acceso
        return instance;

    }
    void verTop() {
        string input;
        int number;

        // Ignorar cualquier entrada previa
        cin.ignore();

        // Pedir al usuario que ingrese la cantidad de palabras
        cout << "Ingrese la cantidad de palabras que desea ver: ";
        getline(cin, input);

     
        // Intentar convertir la cadena a un entero
        number = stoi(input);

            // Verificar que el número sea positivo
        if (number <= 0) {
            cout << ("El numero no es un entero positivo.\n");
        
        trie.topNWords(number, bst);
        }
    
    }
    /**
     * @brief Lee el contenido de un archivo.
     *
     * @param ruta La ruta del archivo a leer.
     * @param charge Si es true, carga las líneas del archivo en la lista de líneas.
     * @return El contenido del archivo como una cadena de texto.
     */

    std::string leerArchivo(const std::string& ruta, bool charge) {
        std::ifstream archivo(ruta);
        std::string contenido; // Para almacenar el contenido del archivo
        std::string linea; // Para leer cada línea del archivo

        std::cout << "Ruta: " << ruta << "\n";

        if (archivo.is_open()) {
            while (std::getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la línea y un salto de línea
                if (charge) {
                    Lineas->append(linea + "\n");
                }
            }
            archivo.close(); // Cierra el archivo después de la lectura
        }
        else {
            std::cout << "Error al abrir el archivo \n" << std::endl;
        }

        return contenido;
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
            while (finPalabra < contenidoArchivo.length() && ignoreL->contains(contenidoArchivo[finPalabra]) && contenidoArchivo[finPalabra] != '\n') {

                finPalabra++;
               
            }
            
            if (fin < finPalabra) {
                string palabra = contenidoArchivo.substr(fin, finPalabra - fin);
                std::transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
                trie.insert(palabra, lineNumber);
                line.clear();
                //cout << "Palabra: " << palabra << ", Línea: " << lineNumber << std::endl;
                fin = finPalabra;
            }
        }
        trie.print();
    }

    /**
    * @brief Lee caracteres individuales de un archivo especificado y los almacena en la lista de caracteres a ignorar.
    *for (char c = 'a'; c <= 'z'; ++c) {
            ignoreL->insert(c);
            ignoreL->insert(toupper(c)); // Insertar también la versión mayúscula
        }
        ignoreL->insert('ñ');
        ignoreL->insert('Ñ'); // Insertar también la versión mayúscula de 'ñ'
        ignoreL->insert('ü');
        ignoreL->insert('Ü'); // Insertar también la versión mayúscula de 'ü'
        return true;
    * Solicita al usuario una ruta de archivo y lo lee, almacenando cada carácter en la lista de caracteres a ignorar.
    */
    void abc() {
        string contenidoArchivo = leerArchivo("abecedario.txt", false);
        for (char c : contenidoArchivo) {
            if (c != ' ' && c != '\n') {
                ignoreL->insert(c);
            }
        }
    }

    /**
    * @brief Lee palabras de un archivo y las almacena en la lista de palabras a ignorar.
    *
    * Solicita al usuario una ruta de archivo, lo lee y almacena las palabras en la lista de palabras a ignorar.
    */
    void palabrasAIgnorar() {
        std::string ruta;
        std::cin.ignore();
        std::cout << "Ingrese una dirección de archivo: ";
        std::getline(std::cin, ruta);
        std::string contenidoArchivo = leerArchivo(ruta, true);

        size_t inicio = 0;
        size_t fin = 0;
        size_t longitud = contenidoArchivo.length();

        while (inicio < longitud) {
            // Avanzar hasta el primer carácter que no sea espacio o nueva línea
            while (inicio < longitud && (contenidoArchivo[inicio] == ' ' || contenidoArchivo[inicio] == '\n')) {
                inicio++;
            }

            // Encontrar el final de la palabra
            fin = inicio;
            while (fin < longitud && contenidoArchivo[fin] != ' ' && contenidoArchivo[fin] != '\n') {
                fin++;
            }

            // Extraer y procesar la palabra si es válida
            if (inicio < fin) {
                std::string palabra = contenidoArchivo.substr(inicio, fin - inicio);
                if (!palabra.empty() && bst) {
                    bst->insert(palabra);
                }
            }

            // Continuar desde el final de la palabra
            inicio = fin;
        }
        bst->print();
    }
    // falta cargar el heap 
    // falta leer archivos misma carpeta
    // falta extraer la linea completa ., hecho en read ansii
    // C:\Users\User\Downloads\Proyecto_1_Indización_de_texto_con_Tries\Proyecto 1 Indización de texto con Tries\ignorar.txt
};