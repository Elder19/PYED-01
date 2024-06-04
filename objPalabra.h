#pragma once
#include <string>
#include <iostream>
#include "ArrayListt.h"

using namespace std;



class objPalabra {
public:
    int cantidadLetras;
    string palabra;
    int apariciones;
    ArrayListt<int>  CP;  // Lista de apariciones en líneas



    // Constructor parametrizado
    objPalabra(int cantidadLetras,  string& palabra,  int apariciones, int linea) {
        this->cantidadLetras = cantidadLetras;
        this->palabra = palabra;
        this->apariciones=apariciones;
        CP.append(linea);
      
    }
        

    // Destructor
    ~objPalabra() {}

    // Getters
    int getCantidadLetras()  { return cantidadLetras; }
    string getPalabra()  { return palabra; }
    int getApariciones()  { return apariciones; }
    //void takeline() { this->CP.getElement() }




    // Setters
    void setCantidadLetras(int cantidadLetras) { this->cantidadLetras = cantidadLetras; }
    void setPalabra( string& palabra) { this->palabra = palabra; }
    void setApariciones( int apariciones) { this->apariciones += apariciones; }

    void addLine(int linea) { CP.append(linea); }
    // Método print
    void print()  {
        cout << "Palabra: " << palabra << endl;
        cout << "Cantidad de Letras: " << cantidadLetras << endl;
        cout << "Apariciones: " << apariciones << endl;
        cout << "Lista de apariciones en líneas: ";
        for (int i = 0; i < CP.getSize(); ++i) {
            CP.goToPos(i);
            cout << CP.getElement() << " ";
        }
        cout << endl;
    }

    
};
