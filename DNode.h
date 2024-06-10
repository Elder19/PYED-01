#pragma once

/**
 * @brief Clase para representar un nodo en una lista doblemente enlazada.
 *
 * @tparam E Tipo de dato almacenado en el nodo.
 */

template <typename E>
class DNode
{
public:
	E element;
	DNode<E>* next;
	DNode<E>* previous;
	
	DNode(E element, DNode<E> *next, DNode<E>* previous) {
		this->element = element;
		this->next = next;
		this->previous = previous;
	}
	DNode(DNode<E>* next, DNode<E>* previous) {
		this->next = next;
		this->previous = previous;
	}
};