
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
            break;

        case 2:
           // menu.ticket();
            cout << "\n" << endl;
            break;

        case 3:
          //  menu.admin.menuAtenderArea();
            break;

        case 4:
            menu.PalabrasMasUtilizadas();
            cout << "\n" << endl;
            break;

        case 5:
            menu.admin.selectorPalabras();
           
            break;
        case 6:
            menu.admin.palabrasAIgnorar();
            break;

        case 7:
            break;

        default:
            break;
        }
    }

    return 0;
};