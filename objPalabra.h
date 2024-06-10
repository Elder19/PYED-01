#pragma once
#include <string>
#include <iostream>
#include "ArrayListt.h"

using namespace std;

/**
 * @brief Clase para representar una palabra junto con su informaci�n adicional.
 */
class objPalabra {
public:
    int cantidadLetras; ///< Cantidad de letras de la palabra.
    string palabra; ///< La palabra.
    int apariciones; ///< N�mero de apariciones de la palabra.
    ArrayListt<int>  CP;  ///< Lista de apariciones en l�neas.

    /**
     * @brief Constructor parametrizado.
     *
     * @param cantidadLetras Cantidad de letras de la palabra.
     * @param palabra La palabra.
     * @param apariciones N�mero de apariciones de la palabra.
     * @param linea N�mero de la l�nea donde aparece la palabra.
     */
    objPalabra(int cantidadLetras, string& palabra, int apariciones, int linea) {
        this->cantidadLetras = cantidadLetras;
        this->palabra = palabra;
        this->apariciones = apariciones;
        CP.append(linea);
    }

    // Destructor
    ~objPalabra() {}

    // Getters
    int getCantidadLetras() { return cantidadLetras; }
    string getPalabra() { return palabra; }
    int getApariciones() { return apariciones; }

    // Setters
    void setCantidadLetras(int cantidadLetras) { this->cantidadLetras = cantidadLetras; }
    void setPalabra(string& palabra) { this->palabra = palabra; }
    void setApariciones(int apariciones) { this->apariciones += apariciones; }

    /**
     * @brief A�ade una l�nea de aparici�n de la palabra.
     *
     * @param linea N�mero de la l�nea de aparici�n.
     */
    void addLine(int linea) { CP.append(linea); }

    /**
     * @brief M�todo para imprimir la informaci�n de la palabra.
     */
    void print() {
        cout << "Palabra: " << palabra << endl;
        cout << "Cantidad de Letras: " << cantidadLetras << endl;
        cout << "Apariciones: " << apariciones << endl;
        cout << "Lista de apariciones en l�neas: ";
        for (int i = 0; i < CP.getSize(); ++i) {
            CP.goToPos(i);
            cout << CP.getElement() << " ";
        }
        cout << endl;
    }
};