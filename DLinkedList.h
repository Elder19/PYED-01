#pragma once
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Clase para representar una lista doblemente enlazada.
 *
 * @tparam E Tipo de dato almacenado en la lista.
 */
template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E>* head; ///< Nodo cabecera.
    DNode<E>* tail; ///< Nodo final.
    DNode<E>* current; ///< Nodo actual.
    int size; ///< Tama�o de la lista.

public:
    /**
     * @brief Constructor por defecto que inicializa una lista doblemente enlazada vac�a.
     */
    DLinkedList() {
        current = head = new DNode<E>(nullptr, nullptr);
        head->next = tail = new DNode<E>(nullptr, head);
        size = 0;
    }

    /**
     * @brief Destructor que elimina todos los nodos de la lista.
     */
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }

    /**
     * @brief Inserta un elemento en la posici�n actual.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        current->next = current->next->previous
            = new DNode<E>(element, current->next, current);
        size++;
    }

    /**
     * @brief A�ade un elemento al final de la lista.
     *
     * @param element Elemento a a�adir.
     */
    void append(E element) {
        tail->previous = tail->previous->next
            = new DNode<E>(element, tail, tail->previous);
        size++;
    }

    /**
     * @brief Establece el elemento en la posici�n actual.
     *
     * @param element Elemento a establecer.
     * @throws runtime_error si la lista est� vac�a o no hay elemento actual.
     */
    void set(E element) {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        current->next->element = element;
    }

    /**
     * @brief Elimina el elemento en la posici�n actual y lo devuelve.
     *
     * @return Elemento eliminado.
     * @throws runtime_error si la lista est� vac�a o no hay elemento actual.
     */
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

    /**
     * @brief Elimina todos los elementos de la lista.
     */
    void clear() {
        while (head->next != tail) {
            head->next = head->next->next;
            delete head->next->previous;
        }
        current = tail->previous = head;
        size = 0;
    }

    /**
     * @brief Devuelve el elemento en la posici�n actual.
     *
     * @return Elemento en la posici�n actual.
     * @throws runtime_error si la lista est� vac�a o no hay elemento actual.
     */
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }

    /**
     * @brief Mueve el cursor al inicio de la lista.
     */
    void goToStart() {
        current = head;
    }

    /**
     * @brief Mueve el cursor al final de la lista.
     */
    void goToEnd() {
        current = tail->previous;
    }

    /**
     * @brief Mueve el cursor a una posici�n espec�fica en la lista.
     *
     * @param pos Posici�n a la que se desea mover el cursor.
     * @throws runtime_error si la posici�n est� fuera de los l�mites.
     */
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of bounds.");
        current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
    }

    /**
     * @brief Mueve el cursor a la siguiente posici�n en la lista.
     */
    void next() {
        if (current != tail->previous)
            current = current->next;
    }

    /**
     * @brief Mueve el cursor a la posici�n anterior en la lista.
     */
    void previous() {
        if (current != head)
            current = current->previous;
    }

    /**
     * @brief Comprueba si el cursor est� al inicio de la lista.
     *
     * @return true si el cursor est� al inicio, false en caso contrario.
     */
    bool atStart() {
        return current == head;
    }

    /**
     * @brief Comprueba si el cursor est� al final de la lista.
     *
     * @return true si el cursor est� al final, false en caso contrario.
     */
    bool atEnd() {
        return current == tail->previous;
    }

    /**
     * @brief Devuelve el tama�o de la lista.
     *
     * @return Tama�o de la lista.
     */
    int getSize() {
        return size;
    }

    /**
     * @brief Devuelve la posici�n actual del cursor en la lista.
     *
     * @return Posici�n actual del cursor.
     */
    int getPos() {
        DNode<E>* temp = head;
        int i;
        for (i = 0; current != temp; i++)
            temp = temp->next;
        return i;
    }

    /**
     * @brief Imprime todos los elementos de la lista.
     */
    void print() {
        cout << "[ ";
        DNode<E>* temp = head->next;
        while (temp != tail) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }

    /**
     * @brief Comprueba si un elemento est� en la lista.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento est� en la lista, false en caso contrario.
     */
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

    /**
     * @brief Imprime el elemento en la n-�sima posici�n desde el inicio.
     *
     * @param n Posici�n desde el inicio.
     */
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