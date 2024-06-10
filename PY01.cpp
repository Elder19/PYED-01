
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
    Raúl Alfaro Rodríguez
    Diego Araya Ureña

*/

int main() {
    // Configuración regional
    setlocale(LC_ALL, "spanish");
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

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