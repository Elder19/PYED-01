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

    // Destructor de la clase para devolver la memoria solicitada
    ~Admin() {
        clear();
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
        int lineNumber = 0;

        if (archivo.is_open()) {
            while (std::getline(archivo, linea)) {
                contenido += linea + "\n"; // Concatena la línea y un salto de línea
                string contain = linea + "\n";
                if (charge) {
                    lineNumber++;
                    Lineas->insert(linea + "\n");
                    selectorPalabras2(contain, lineNumber);

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
        Lineas->clear();
        trie.clear();
        string ruta;
        cin.ignore();
        cout << "ingrese una direccion de archivo: ";
        getline(cin, ruta);
        leerArchivo(ruta, true);
    }
    /**
   * @brief Procesa el contenido del archivo y extrae palabras, insertándolas en el trie.
   *
   * @param contenidoArchivo El contenido del archivo a procesar.
   * @param lineNumber El número de línea actual.
   */
    void selectorPalabras2(string contenidoArchivo, int lineNumber) {
        size_t inicio = 0;
        string line;

        for (size_t fin = inicio; fin < contenidoArchivo.length(); fin++) {

            // Avanzar hasta el primer carácter que no sea espacio o nueva línea
            while (fin < contenidoArchivo.length() && (contenidoArchivo[fin] == ' ' || contenidoArchivo[fin] == '\n')) {
                if (contenidoArchivo[fin] == '\n')  {
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
                fin = finPalabra;
            }
        }
    }
    /**
    * @brief Carga el abecedario desde un archivo y lo inserta en el árbol de caracteres a ignorar.
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
        bst->clear();
        std::string ruta;
        std::cin.ignore();
        std::cout << "Ingrese una dirección de archivo: ";
        std::getline(std::cin, ruta);
        std::string contenidoArchivo = leerArchivo(ruta, false);

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
        cout << "\n" << endl;
        cout << "Lista de Palabras a Ignorar" << endl;
        cout << "\n" << endl;
        bst->print();
    }

    /**
     * @brief Busca palabras con un prefijo dado en el trie y muestra sus apariciones.
     */
    void lookWordPrefix() {
        string prefix;
        cout << "ingrese un prefijo a buscar: ";
        cin.ignore();
        getline(cin, prefix);

        for (char c : prefix) {
            if (std::isdigit(c)) {
                cout << "Error: No pueden haber números en la opción" << endl;
                lookWordPrefix();
            }
        }

        std::transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);

        List<string>* matches = trie.getMatches(prefix);
        if (matches == nullptr) {
            cout << "Error: No hay coincidencia para el prefijo ingresado." << endl;
            return;
        }
        
        for (matches->goToStart(); !matches->atEnd(); matches->next()) {
            DLinkedList<int>* lines = trie.getLine(matches->getElement());

            cout << "\n" << endl;
            cout << matches->getElement() << ": ";
            cout << "Cantidad de Aparciciones: " << lines->getSize();
            cout << "\n" << endl;
            
            for (lines->goToStart(); !lines->atEnd(); lines->next()) {
                cout << "Linea " << lines->getElement() << ": ";
                Lineas->printElement(lines->getElement());
            }
        }
    }
    /**
  * @brief Busca una palabra específica en el trie y muestra sus apariciones.
  */
    void lookWord() {
        string word;
        cout << "ingrese una palabra a buscar: ";
        cin.ignore();
        getline(cin, word);

        for (char c : word) {
            if (std::isdigit(c)) {
                cout << "Error: No pueden haber números en la opción" << endl;
                lookWord();
            }
        }
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        DLinkedList<int>* lines = trie.buscarPalabra(word);

        if (lines == nullptr) {
            cout << "Error: Palabra no encontrada." << endl;
            return;
        }

        cout << "\n" << endl;
        cout << word << ": ";
        cout << "Cantidad de Aparciciones: " << lines->getSize();
        cout << "\n" << endl;

        for (lines->goToStart(); !lines->atEnd(); lines->next()) {
            cout << "Linea " << lines->getElement() << ": ";
            Lineas->printElement(lines->getElement());
        }
    }
     /**
     * @brief busca y retorna la palabras con n cantidad de letras
     *
     
     */
    void getLenghtWords() {
        string lenght;
        cout << "ingrese un valor numérico: ";
        cin.ignore();
        getline(cin, lenght);

        for (char c : lenght) {
            if (std::isalpha(c)) {
                cout << "Error: No pueden haber letras en la opción";
                return;
            }
        }

        int numero = std::stoi(lenght);
        DLinkedList<string>* words = trie.getWords_lenght(numero);

        for (words->goToStart(); !words->atEnd(); words->next()) {
            DLinkedList<int>* lines = trie.getLine(words->getElement());

            cout << "\n" << endl;
            cout << words->getElement() << ": ";
            cout << "Cantidad de Aparciciones: " << lines->getSize();
            cout << "\n" << endl;

            for (lines->goToStart(); !lines->atEnd(); lines->next()) {
                cout << "Linea " << lines->getElement() << ": ";
                Lineas->printElement(lines->getElement());
            }
        }
    }
    /**
     * @brief pide al usuario la cantidad de palabras mas utilizadas que deseen usar .
     *

     */
    void topNWords() {
        string lenght;
        cout << "ingrese un valor numérico: ";
        cin.ignore();
        getline(cin, lenght);

        for (char c : lenght) {
            if (std::isalpha(c)) {
                cout << "Error: No pueden haber letras en la opción";
                return;
            }
        }

        int numero = std::stoi(lenght);
        DLinkedList<KVPair<int, string>>* topWords = trie.topNWords(numero, bst);
        topWords->print();
    }

    /**
 * @brief Limpia toda la memoria de las estructuras
 *

 */
    void clear() {
        Lineas->clear();
        ignoreL->clear();
        bst->clear();
        trie.clear();
    }
};