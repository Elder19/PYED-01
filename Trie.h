#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "TrieNode.h"
#include "MaxHeap.h"
#include "DLinkedList.h"
#include "BSTree.h"

using std::string;
using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @brief Clase que representa un Trie.
 */

class Trie {

private:
	TrieNode* root; /**< Puntero al nodo raíz del Trie. */

	/**
	 * @brief Encuentra el nodo correspondiente a una palabra en el Trie.
	 *
	 * @param word Palabra a buscar.
	 * @return Puntero al nodo correspondiente a la palabra, o nullptr si la palabra no está en el Trie.
	 */

	TrieNode* findNode(string word) {
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			if (!current->containsChild(word[i]))
				return nullptr;
			current = current->getChild(word[i]);
		}
		return current;
	}

	/**
	 * @brief Función auxiliar para limpiar los nodos del Trie.
	 *
	 * @param current Puntero al nodo actual.
	 */

	void clearAux(TrieNode* current) {
		List<char>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			char c = children->getElement();
			TrieNode* child = current->getChild(c);
			clearAux(child);
			children->next();
		}
		delete children;
		delete current;
	}

	/**
	 * @brief Función auxiliar para obtener todas las palabras que coinciden con un prefijo dado.
	 *
	 * @param current Puntero al nodo actual.
	 * @param prefix Prefijo a buscar.
	 * @param words Lista donde se almacenarán las palabras coincidentes.
	 */

	void getMatchesAux(TrieNode* current, string prefix, List<string>* words) {
		if (current->isFinal)
			words->append(prefix);
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			getMatchesAux(current->getChild(c), prefix + c, words);
		}
		delete children;
	}

	/**
	 * @brief Función auxiliar para obtener todas las palabras de cierta longitud en el Trie.
	 *
	 * @param current Puntero al nodo actual.
	 * @param word Palabra actual construida durante la recursión.
	 * @param length Longitud deseada de las palabras.
	 * @param words Lista donde se almacenarán las palabras de longitud `length`.
	 */

	void getWords_lenghtAux(TrieNode* current, string word, int lenght, List<string>* words) {
		if (lenght == -1 && current->isFinal)
			words->append(word);
		List<char>* children = current->getChildren();
		for (children->goToStart(); !children->atEnd(); children->next()) {
			char c = children->getElement();
			getWords_lenghtAux(current->getChild(c), word + c, lenght - 1, words);
		}
		delete children;
	}

public:

	/**
	 * @brief Constructor de la clase Trie.
	 */

	Trie() {
		root = new TrieNode();
	}

	/**
	 * @brief Destructor de la clase Trie.
	 */

	~Trie() {
		clear();
		delete root;
	}

	/**
	 * @brief Inserta una palabra en el Trie.
	 *
	 * @param word Palabra a insertar.
	 * @param line Número de línea donde aparece la palabra.
	 */

	void insert(string word, int line) {
		TrieNode* current = root;
		if (containsWord(word)) {
			for (unsigned int i = 0; i < word.size(); i++)
				current = current->getChild(word[i]);
			current->insertLine(line);
			return;
		}
		for (unsigned int i = 0; i < word.size(); i++) {
			current->prefixCount++;
			if (!current->containsChild(word[i]))
				current->addChild(word[i]);
			current = current->getChild(word[i]);
		}
		current->insertLine(line);
		current->prefixCount++;
		current->isFinal = true;

	}

	/**
	 * @brief Verifica si una palabra está presente en el Trie.
	 *
	 * @param word Palabra a buscar.
	 * @return true si la palabra está en el Trie, false en caso contrario.
	 */

	bool containsWord(string word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) 
			return false;
		return current->isFinal;
	}

	/**
	 * @brief Verifica si un prefijo está presente en el Trie.
	 *
	 * @param prefix Prefijo a buscar.
	 * @return true si el prefijo está en el Trie, false en caso contrario.
	 */

	bool containsPrefix(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return false;
		return true;
	}

	/**
	 * @brief Obtiene el número de palabras que tienen un cierto prefijo.
	 *
	 * @param prefix Prefijo a buscar.
	 * @return Número de palabras que tienen el prefijo especificado.
	 */

	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return 0;
		return current->prefixCount;
	}

	/**
	 * @brief Elimina una palabra del Trie.
	 *
	 * @param word Palabra a eliminar.
	 */

	void remove(string word) {
		if (!containsWord(word))
			throw runtime_error("Word not found.");
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			current->prefixCount--;
			TrieNode* child = current->getChild(word[i]);
			if (child->prefixCount == 1)
				current->removeChild(word[i]);
			if (current->prefixCount == 0)
				delete current;
			current = child;
		}
		current->prefixCount--;
		current->isFinal = false;
		if (current->prefixCount == 0)
			delete current;
	}

	/**
	 * @brief Limpia el Trie, eliminando todas las palabras.
	 */

	void clear() {
		clearAux(root);
		root = new TrieNode();
	}

	/**
	 * @brief Obtiene todas las palabras que coinciden con un cierto prefijo.
	 *
	 * @param prefix Prefijo a buscar.
	 * @return Lista de palabras que coinciden con el prefijo especificado.
	 */

	List<string>* getMatches(string prefix) {
		List<string>* words = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);

		if (current != nullptr) {
			getMatchesAux(current, prefix, words);

		} else {
			cout << "Error: No se encontraron coincidencias con el prefijo ingresado." << endl;
			return nullptr;
		}

		return words;
	}

	/**
	 * @brief Obtiene todas las palabras de cierta longitud en el Trie.
	 *
	 * @param length Longitud deseada de las palabras.
	 * @return Lista de palabras de longitud `length`.
	 */

	int getSize() {
		return root->prefixCount;
	}

	/**
	 * @brief Imprime todas las palabras almacenadas en el Trie
	 */

	void print() {
		List<string>* words = new DLinkedList<string>();
		words = getMatches("");
		words->print();
		delete words;
	}

	/**
	 * @brief Obtiene todas las palabras de cierta longitud en el Trie.
	 *
	 * @param length Longitud deseada de las palabras.
	 * @return Lista de palabras de longitud `length`.
	 */

	DLinkedList<string>* getWords_lenght(int lenght) {
		DLinkedList<string>* lista = new DLinkedList<string>();
		getWords_lenghtAux(root, "", lenght - 1, lista);
		return lista;
	}

	/**
	 * @brief Obtiene las `n` palabras más frecuentes que no están en un árbol binario de búsqueda.
	 *
	 * @param n Número de palabras a obtener.
	 * @param bst Árbol binario de búsqueda que contiene las palabras excluidas.
	 * @return Lista de las `n` palabras más frecuentes que no están en el árbol binario de búsqueda.
	 */

	DLinkedList<KVPair<int, string>>* topNWords(int n, BSTree<string>* bst) {
		MinHeap<KVPair<int, string>> heap(getSize());
		List<string>* words = getMatches("");

		words->goToStart();
		while (!words->atEnd()) {
			string word = words->getElement();
			if (!bst->contains(word)) {
				TrieNode* node = findNode(word);
				int contador = node->getCountLines();
				KVPair<int, string> pares(contador, word);
				heap.insert(pares);
			}
			words->next();
		}

		DLinkedList<KVPair<int, string>>* topWords = new DLinkedList<KVPair<int, string>>();
		for (int i = 0; i < n && !heap.isEmpty(); i++) {
			topWords->append(heap.removeFirst());
		}

		delete words;
		return topWords;
	}

	/**
	 * @brief Obtiene las palabras que coinciden con un cierto prefijo, junto con la cantidad de veces que aparecen.
	 *
	 * @param prefix Prefijo a buscar.
	 * @return Lista de pares (cantidad de apariciones, palabra) que coinciden con el prefijo especificado.
	 */

	DLinkedList<KVPair<int, string>>* getPrefixWords(string prefix) {
		string word;
		int apariciones;
		List<string>* words = getMatches(prefix);
		DLinkedList<KVPair<int, string>>* prefixWords = new DLinkedList<KVPair<int, string>>();
		words->goToStart();

		while (!words->atEnd()) {
			word = words->getElement();
			TrieNode* node = findNode(word);
			apariciones = node->getCountLines();
			KVPair<int, string> par(apariciones, word);
			prefixWords->append(par);
			words->next();
		}
		delete words;
		return prefixWords;
	}

	/**
	 * @brief Busca una palabra en el Trie y devuelve la lista de números de línea donde aparece.
	 *
	 * @param word Palabra a buscar.
	 * @return Lista de números de línea donde aparece la palabra especificada.
	 */

	DLinkedList<int>* buscarPalabra(string word) {
		TrieNode* node = findNode(word);

		if (node == nullptr) {
			cout << "Error: Palabra no encontrada." << endl;
			return nullptr;
		}

		return node->getLinesList();
	}

	/**
	 * @brief Obtiene la lista de números de línea donde aparece una palabra en el Trie.
	 *
	 * @param word Palabra a buscar.
	 * @return Lista de números de línea donde aparece la palabra especificada.
	 */

	DLinkedList<int>* getLine(string word) {
		TrieNode* current = findNode(word);
		return current->getLinesList();
	}
};