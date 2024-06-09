#pragma once
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E>
{
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	// Constructor por defecto que inicializa una lista doblemente enlazada vacía
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}

	// Destructor que elimina todos los nodos de la lista
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}

	// Inserta un elemento en la posición actual
	void insert(E element) {
		current->next = current->next->previous
			= new DNode<E>(element, current->next, current);
		size++;
	}

	// Añade un elemento al final de la lista
	void append(E element) {
		tail->previous = tail->previous->next
			= new DNode<E>(element, tail, tail->previous);
		size++;
	}

	// Establece el elemento en la posición actual
	void set(E element) {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		current->next->element = element;
	}

	// Elimina el elemento en la posición actual y lo devuelve
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}

	// Elimina todos los elementos de la lista
	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->next->previous;
		}
		current = tail->previous = head;
		size = 0;
	}

	// Devuelve el elemento en la posición actual
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}

	// Mueve el cursor al inicio de la lista
	void goToStart() {
		current = head;
	}

	// Mueve el cursor al final de la lista
	void goToEnd() {
		current = tail->previous;
	}

	// Mueve el cursor a una posición específica en la lista
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out bounds.");
		current = head;
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}
	}

	// Mueve el cursor a la siguiente posición en la lista
	void next() {
		if (current != tail->previous)
			current = current->next;
	}

	// Mueve el cursor a la posición anterior en la lista
	void previous() {
		if (current != head)
			current = current->previous;
	}

	// Comprueba si el cursor está al inicio de la lista
	bool atStart() {
		return current == head;
	}

	// Comprueba si el cursor está al final de la lista
	bool atEnd() {
		return current == tail->previous;
	}

	// Devuelve el tamaño de la lista
	int getSize() {
		return size;
	}

	// Devuelve la posición actual del cursor en la lista
	int getPos() {
		// Elaborado por Alejandro Madrigal
		DNode<E>* temp = head;
		int i;
		for (i = 0; current != temp; i++)
			temp = temp->next;
		return i;
	}

	// Imprime todos los elementos de la lista
	void print() {
		cout << "[ ";
		DNode<E>* temp = head->next;
		while (temp != tail) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}

	// Comprueba si un elemento está en la lista
	bool contains(E element) {
		goToStart();
		while (!atEnd()) {
			if (element == getElement()) {
				return true;
			}
			next();
		}
		return false;
	}

	// Imprime el elemento en la n-ésima posición desde el final
	void printElement(int n) {
		int contador = 0;
		DNode<E>* temp = head->next;
		while (temp != tail) {
			if (contador == size - n) {
				cout << temp->element;
				break;
			}
			contador++;
			temp = temp->next;
		}
	}
};
