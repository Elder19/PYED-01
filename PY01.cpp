
#include <iostream>
#include "Menu.h"




using namespace std;

/*
    Proyecto 01
    Curso de Estructura de Datos

    Elder León
    Brazly Morales

*/

int main() {
    setlocale(LC_ALL, "spanish");

    Menu menu;
    int opcionMenu = 0;

    while (opcionMenu != 6) {
        opcionMenu = menu.menuPrincipal();

        switch (opcionMenu) {
        case 1:
           //menu.admin.lectorText()
            break;

        case 2:
           // menu.ticket();
            cout << "\n" << endl;
            break;

        case 3:
          //  menu.admin.menuAtenderArea();
            break;

        case 4:
         //   menu.administracion();
            cout << "\n" << endl;
            break;

        case 5:
            menu.admin.lectorText();
           
            break;

        case 6:
            break;

        default:
            break;
        }
    }

    return 0;
};