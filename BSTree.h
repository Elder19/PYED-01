#pragma once

#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class BSTree {
private:
	BSTree(const BSTree<E>& other) {}
	void operator =(const BSTree<E>& other) {}

	BSTNode<E>* root;

	// Inserta un elemento en el subárbol con raíz en 'current'
	BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return new BSTNode<E>(element);
		if (element < current->element) {
			current->left = insertAux(current->left, element);
			return current;
		}
		else { // es mayor
			current->right = insertAux(current->right, element);
			return current;
		}
	}

	// Busca un elemento en el subárbol con raíz en 'current' y guarda el resultado en 'result'
	void findAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element == current->element)
			*result = current->element;
		else if (element < current->element)
			findAux(current->left, element, result);
		else
			findAux(current->right, element, result);
	}

	// Elimina un elemento del subárbol con raíz en 'current' y guarda el resultado en 'result'
	BSTNode<E>* removeAux(BSTNode<E>* current, E element, E* result) {
		if (current == nullptr)
			throw runtime_error("Element not found.");
		if (element < current->element) {
			current->left = removeAux(current->left, element, result);
			return current;
		}
		if (element > current->element) {
			current->right = removeAux(current->right, element, result);
			return current;
		}
		else { // element == current->element
			*result = current->element;
			int children = current->childrenCount();
			if (children == 0) {
				delete current;
				return nullptr;
			}
			if (children == 1) {
				BSTNode<E>* child = current->getOnlyChild();
				delete current;
				return child;
			}
			else { // children == 2
				BSTNode<E>* successor = getSuccessor(current);
				swap(current, successor);
				current->right = removeAux(current->right, element, result);
				return current;
			}
		}
	}

	// Devuelve el sucesor in-order de 'current'
	BSTNode<E>* getSuccessor(BSTNode<E>* current) {
		BSTNode<E>* successor = current->right;
		while (successor->left != nullptr)
			successor = successor->left;
		return successor;
	}

	// Intercambia los elementos de 'node1' y 'node2'
	void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
		E temp = node1->element;
		node1->element = node2->element;
		node2->element = temp;
	}

	// Comprueba si un elemento está en el subárbol con raíz en 'current'
	bool containsAux(BSTNode<E>* current, E element) {
		if (current == nullptr)
			return false;
		if (element == current->element)
			return true;
		if (element < current->element)
			return containsAux(current->left, element);
		else
			return containsAux(current->right, element);
	}

	// Elimina todos los nodos del subárbol con raíz en 'current'
	void clearAux(BSTNode<E>* current) {
		if (current == nullptr)
			return;
		clearAux(current->left);
		clearAux(current->right);
		delete current;
	}

	// Añade todos los elementos del subárbol con raíz en 'current' a la lista 'elements'
	void getElementsAux(BSTNode<E>* current, List<E>* elements) {
		if (current == nullptr)
			return;
		getElementsAux(current->left, elements);
		elements->append(current->element);
		getElementsAux(current->right, elements);
	}

	// Devuelve el tamaño del subárbol con raíz en 'current'
	int getSizeAux(BSTNode<E>* current) {
		if (current == nullptr)
			return 0;
		return 1 + getSizeAux(current->left)
			+ getSizeAux(current->right);
	}

public:
	// Constructor por defecto que inicializa un árbol vacío
	BSTree() {
		root = nullptr;
	}

	// Destructor que elimina todos los nodos del árbol
	~BSTree() {
		clear();
	}

	// Inserta un elemento en el árbol
	void insert(E element) {
		root = insertAux(root, element);
	}

	// Busca un elemento en el árbol y lo devuelve
	E find(E element) {
		E result;
		findAux(root, element, &result);
		return result;
	}

	// Elimina un elemento del árbol y lo devuelve
	E remove(E element) {
		E result;
		root = removeAux(root, element, &result);
		return result;
	}

	// Comprueba si un elemento está en el árbol
	bool contains(E element) {
		return containsAux(root, element);
	}

	// Elimina todos los nodos del árbol
	void clear() {
		clearAux(root);
		root = nullptr;
	}

	// Devuelve una lista con todos los elementos del árbol
	List<E>* getElements() {
		List<E>* elements = new DLinkedList<E>();
		getElementsAux(root, elements);
		return elements;
	}

	// Devuelve el tamaño del árbol
	int getSize() {
		return getSizeAux(root);
	}

	// Imprime todos los elementos del árbol en orden
	void print() {
		List<E>* elements = getElements();
		elements->print();
		delete elements;
	}
};
