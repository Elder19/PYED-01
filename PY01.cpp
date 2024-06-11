
#define NOMINMAX
#include <iostream>
#include "Windows.h"

#include "Menu.h"

using namespace std;

/*
    Proyecto 01
    Curso de Estructura de Datos

    Elder León
    Brazly Morales
    Raúl Alfaro
    Diego Araya

*/

int main() {
    // Configuración regional
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    cout << "===============================" << endl;
    cout << "      BIENVENIDO USUARIO" << endl;
    cout << "===============================" << endl;
    cout << "Sistema de Indización de Textos" << endl;
    cout << "\n" << endl;

    cout << "Este programa tiene por funcionalidad indizar cualquier contenido de archivo de texto." << endl;
    cout << "De modo en que cuando se procesa el texto el sistema es capaz de realizar operaciones sobre su contenido." << endl;
    cout << "Puede realizar busquedas de palabras, prefijos y por cantidad de letras y mostrará todas la coincidencias encontradas." << endl;
    cout << "E incluso se puede realizar una estadística de las palabras más utilizadas en el archivo de texto" << endl;
    cout << "\n" << endl;

    Menu menu;
    int opcionMenu = 0;
    menu.admin.abc();
    while (opcionMenu != 7) {
        opcionMenu = menu.menuPrincipal();

        switch (opcionMenu) {
        case 1:
            menu.admin.lookWordPrefix();
            cout << "\n" << endl;
            break;

        case 2:
            menu.admin.lookWord();
            cout << "\n" << endl;
            break;

        case 3:
            menu.admin.getLenghtWords();
            cout << "\n" << endl;
            break;

        case 4:
            menu.PalabrasMasUtilizadas();
            cout << "\n" << endl;
            break;

        case 5:
            menu.admin.selectorPalabras();
            cout << "\n" << endl;
            break;
        case 6:
            menu.admin.palabrasAIgnorar();
            cout << "\n" << endl;
            break;

        case 7:
            break;

        default:
            break;
        }
    }

    return 0;
};