#pragma once
#include <iostream>
#include "Admin.h"
using namespace std;

// Clase Menu que gestiona las opciones del men� principal y las acciones asociadas

class Menu {
public:
    Admin& admin = Admin::getInstance();   // Instancia �nica de admin

    // M�todo para mostrar y manejar el men� principal
    int menuPrincipal() {
        int opcion;

        // Mostrar el men� principal
        cout << "Men� Principal" << endl;
        cout << "=============================" << endl;
        cout << "(1) Consultar por prefijo" << endl;
        cout << "(2) Buscar palabra" << endl;
        cout << "(3) Buscar por cantidad de letras" << endl;
        cout << "(4) Palabras mas utilizadas" << endl;
        cout << "(5) Cargar otro archivo" << endl;
        cout << "(6) ingresar archivo de palabras a ignorar" << endl;
        cout << "(7) Salir del programa" << endl;
        cout << "Ingrese su opci�n: ";
        cin >> opcion;

        // Validar la entrada del usuario
        while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7) {
            cout << "Error: Selecci�n Inv�lida. Escoja una de las opciones del Men�: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> opcion;
        }

        return opcion;
    }

    // M�todo para manejar la opci�n de ver las palabras m�s utilizadas
    void PalabrasMasUtilizadas() {
        int opcionWT = 0;

        // Ciclo para mostrar y manejar las opciones de la subsecci�n de palabras m�s utilizadas
        while (opcionWT != 2) {
            cout << "\n" << endl;
            cout << "	Palabras mas Utilizadas" << endl;
            cout << "==========================================" << endl;
            cout << "(1) Ver top" << endl;
            cout << "(2) Regresar" << endl;
            cout << "Ingrese su opci�n: ";
            cin >> opcionWT;

            // Validar la entrada del usuario
            while (opcionWT != 1 && opcionWT != 2) {
                cout << "Error: Selecci�n Inv�lida. Escoja una de las opciones del Men�: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> opcionWT;
            }

            // Ejecutar la acci�n correspondiente a la opci�n seleccionada
            switch (opcionWT) {
            case 1:
                admin.topNWords(); // Llamar al m�todo en Admin para ver las palabras m�s utilizadas
                break;
            case 2:
                return; // Regresar al men� principal
            default:
                break;
            }
        }
    }
};