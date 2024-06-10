#pragma once
#include <iostream>
#include "Admin.h"
using namespace std;

// Clase Menu que gestiona las opciones del menú principal y las acciones asociadas

class Menu {
public:
    Admin& admin = Admin::getInstance();   // Instancia única de admin

    // Método para mostrar y manejar el menú principal
    int menuPrincipal() {
        int opcion;

        // Mostrar el menú principal
        cout << "Menú Principal" << endl;
        cout << "=============================" << endl;
        cout << "(1) Consultar por prefijo" << endl;
        cout << "(2) Buscar palabra" << endl;
        cout << "(3) Buscar por cantidad de letras" << endl;
        cout << "(4) Palabras mas utilizadas" << endl;
        cout << "(5) Cargar otro archivo" << endl;
        cout << "(6) ingresar archivo de palabras a ignorar" << endl;
        cout << "(7) Salir del programa" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        // Validar la entrada del usuario
        while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 4 && opcion != 5 && opcion != 6 && opcion != 7) {
            cout << "Error: Selección Inválida. Escoja una de las opciones del Menú: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> opcion;
        }

        return opcion;
    }

    // Método para manejar la opción de ver las palabras más utilizadas
    void PalabrasMasUtilizadas() {
        int opcionWT = 0;

        // Ciclo para mostrar y manejar las opciones de la subsección de palabras más utilizadas
        while (opcionWT != 2) {
            cout << "\n" << endl;
            cout << "	Palabras mas Utilizadas" << endl;
            cout << "==========================================" << endl;
            cout << "(1) Ver top" << endl;
            cout << "(2) Regresar" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcionWT;

            // Validar la entrada del usuario
            while (opcionWT != 1 && opcionWT != 2) {
                cout << "Error: Selección Inválida. Escoja una de las opciones del Menú: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> opcionWT;
            }

            // Ejecutar la acción correspondiente a la opción seleccionada
            switch (opcionWT) {
            case 1:
                admin.topNWords(); // Llamar al método en Admin para ver las palabras más utilizadas
                break;
            case 2:
                return; // Regresar al menú principal
            default:
                break;
            }
        }
    }
};