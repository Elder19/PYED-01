#pragma once
#include <string>
#include <iostream>
#include "ArrayListt.h"

using namespace std;



class objPalabra {
public:
    int cantidadLetras;
    string palabra;
    string apariciones;
    ArrayListt<objPalabra*> lines;  // Lista de apariciones en líneas



    // Constructor parametrizado
    objPalabra(int cantidadLetras, const string& palabra, const string& apariciones, const ArrayList<Linea*>& lines)
        : cantidadLetras(cantidadLetras), palabra(palabra), apariciones(apariciones), lines(lines) {}

    // Destructor
    ~objPalabra() {}

    // Getters
    int getCantidadLetras() const { return cantidadLetras; }
    string getPalabra() const { return palabra; }
    string getApariciones() const { return apariciones; }
   



    // Setters
    void setCantidadLetras(int cantidadLetras) { this->cantidadLetras = cantidadLetras; }
    void setPalabra(const string& palabra) { this->palabra = palabra; }
    void setApariciones(const string& apariciones) { this->apariciones = apariciones; }
    void addLine(objPalabra* line) { lines.append(line); }


    
};
