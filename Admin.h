#pragma once
#pragma once
#include <string> 
#include <iostream>
#include <sstream> 
#include "readANSI.h"
#include "objPalabra.h"

using namespace std;

/*
Clase Admin: Sigue el patron Singleton, esto permite que exista una unica instancia de la clase
Descripcion: Sirve como un administrador para los datos y operaciones del programa
*/

class Admin {

private:
	// Constructor privado para evitar la creaci�n de instancias fuera de la clase
	Admin() {}

	// Evitar que se copie la instancia
	Admin(const Admin&) = delete;
	Admin& operator=(const Admin&) = delete;

public:
	// Metodo para obtener la instancia
	static Admin& getInstance() {
		static Admin instance; // Instancia �nica creada en el primer acceso
		return instance;
		
	}
	void lectorText( ) {
		string ruta;
		cin.ignore();
		cout << "ingrese una direccion de archivo: ";
		getline(cin, ruta);


		readANSI lector; // Crea una instancia de la clase readANSI
		string rutaArchivo = ruta; // Define la ruta del archivo que deseas leer

		// Llama al método leerArchivo() de la instancia lector, pasando la ruta del archivo
		
		string contenidoArchivo = lector.leerArchivo(rutaArchivo);
		if (contenidoArchivo == "") {
			cout << "Asegurese de haber ingresado una direccion valida.\n Vuelva a intentarlo.\n";
			return; 

		}
	
		selectorPalabras(contenidoArchivo);
		cout << "Contenido del archivo:\n" << contenidoArchivo << endl;
	
	}
	void selectorPalabras(string contenidoArchivo) 





	}

};

