#pragma once

#include "SplayDictionary.h"
#include "DLinkedList.h"

/**
 * @brief Clase que representa un nodo de un árbol Trie.
 */

class TrieNode {
public:
	bool isFinal;
	int prefixCount;
	Dictionary<char, TrieNode*>* children;
	DLinkedList<int>* line;

	/**
	 * @brief Constructor de la clase TrieNode.
	 */

	TrieNode() {
		isFinal = false;
		prefixCount = 0;
		children = new SplayDictionary<char, TrieNode*>();
		line = new DLinkedList<int>();
	}

	/**
	 * @brief Destructor de la clase TrieNode.
	 */

	~TrieNode() {
		delete children;
		delete line;
	}

	/**
	 * @brief Verifica si este nodo tiene un hijo con el caracter especificado.
	 *
	 * @param c Caracter a buscar.
	 * @return true si el nodo tiene un hijo con el caracter especificado, false en caso contrario.
	 */

	bool containsChild(char c) {
		return children->contains(c);
	}

	/**
	 * @brief Obtiene el hijo de este nodo correspondiente al caracter especificado.
	 *
	 * @param c Caracter del hijo a obtener.
	 * @return Puntero al hijo correspondiente al caracter especificado.
	 */

	TrieNode* getChild(char c) {
		return children->getValue(c);
	}

	/**
	 * @brief Agrega un nuevo hijo a este nodo con el caracter especificado.
	 *
	 * @param c Caracter del nuevo hijo a agregar.
	 */

	void addChild(char c) {
		children->insert(c, new TrieNode());
	}

	/**
	 * @brief Elimina el hijo de este nodo correspondiente al caracter especificado.
	 *
	 * @param c Caracter del hijo a eliminar.
	 */

	void removeChild(char c) {
		children->remove(c);
	}

	/**
	 * @brief Obtiene una lista de los caracteres que son hijos de este nodo.
	 *
	 * @return Lista de caracteres que son hijos de este nodo.
	 */

	List<char>* getChildren() {
		return children->getKeys();
	}

	/**
	 * @brief Agrega un número de línea a la lista de números de línea de este nodo.
	 *
	 * @param l Número de línea a agregar.
	 */

	void insertLine(int l) {
		line->append(l);
	}

	/**
	 * @brief Obtiene la lista de números de línea asociados a este nodo.
	 *
	 * @return Lista de números de línea asociados a este nodo.
	 */

	DLinkedList<int>* getLinesList() {
		return line;
	}

	/**
	 * @brief Obtiene la cantidad de números de línea asociados a este nodo.
	 *
	 * @return Cantidad de números de línea asociados a este nodo.
	 */

	int getCountLines() {
		return line->getSize();
	}

	/**
	 * @brief Obtiene el estado final del nodo, que indica si este nodo representa el final de una palabra.
	 *
	 * @return true si este nodo representa el final de una palabra, false en caso contrario.
	 */

	bool getIsFinal() {
		return isFinal;
	}

	/**
	 * @brief Establece el estado final del nodo, que indica si este nodo representa el final de una palabra.
	 *
	 * @param isfinal true si este nodo debe representar el final de una palabra, false en caso contrario.
	 */

	void setIsFinal(bool isfinal) {
		isFinal = isfinal;
	}

	/**
	 * @brief Obtiene el contador de prefijos de este nodo, que indica cuántas palabras tienen este nodo como prefijo.
	 *
	 * @return Número de palabras que tienen este nodo como prefijo.
	 */

	int getPrefixCount() {
		return prefixCount;
	}

	/**
	 * @brief Establece el contador de prefijos de este nodo, que indica cuántas palabras tienen este nodo como prefijo.
	 *
	 * @param prefixcount Número de palabras que tienen este nodo como prefijo.
	 */

	void setPrefixCount(int prefixcount) {
		prefixCount = prefixcount;
	}
};