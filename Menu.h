#pragma once
#include <iostream>
#include "Admin.h"
using namespace std;

class Menu {
public:
    Admin& admin = Admin::getInstance();   // Instancia única de admin

    int menuPrincipal() {
        int opcion;

        cout << "Menú Principal" << endl;
        cout << "=============================" << endl;
        cout << "(1) Consultar por prefijo" << endl;
        cout << "(2) Buscar palabra" << endl;
        cout << "(3) Buscar por cantidad de letras" << endl;
        cout << "(4) Palabras mas utilizadas" << endl;
        cout << "(5) Cargar otro archivo" << endl;
        cout << "(6) Salir del programa" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6) {
            cout << "Error: Selección Inválida. Escoja una de las opciones del Menú: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> opcion;
        }

        return opcion;
    }

    void PalabrasMasUtilizadas() {
        int opcionWT = 0;

        while (opcionWT != 2) {
            cout << "\n" << endl;
            cout << "	palabras mas uttilizadas" << endl;
            cout << "==========================================" << endl;
            cout << "(1) Ver top" << endl;
            cout << "(2) Regresar" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcionWT;

            while (opcionWT != 1 && opcionWT != 2) {
                cout << "Error: Selección Inválida. Escoja una de las opciones del Menú: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> opcionWT;
            }

            switch (opcionWT) {
            case 1:
                // admin.VerTop();
                break;
            case 2:
                return;
            default:
                break;
            }
        }
    }
};
