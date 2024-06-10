#pragma once

#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief �rbol Binario de B�squeda (BST).
 *
 * @tparam E Tipo de dato almacenado en el �rbol.
 */
template <typename E>
class BSTree {
private:
    BSTree(const BSTree<E>& other) {}
    void operator =(const BSTree<E>& other) {}

    BSTNode<E>* root; ///< Ra�z del �rbol.

    /**
     * @brief Inserta un elemento en el sub�rbol con ra�z en 'current'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @param element Elemento a insertar.
     * @return Nodo ra�z del sub�rbol actualizado.
     */
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

    /**
     * @brief Busca un elemento en el sub�rbol con ra�z en 'current' y guarda el resultado en 'result'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @param element Elemento a buscar.
     * @param result Puntero donde se guardar� el resultado.
     */
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

    /**
     * @brief Elimina un elemento del sub�rbol con ra�z en 'current' y guarda el resultado en 'result'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @param element Elemento a eliminar.
     * @param result Puntero donde se guardar� el resultado.
     * @return Nodo ra�z del sub�rbol actualizado.
     */
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

    /**
     * @brief Devuelve el sucesor in-order de 'current'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @return Sucesor in-order.
     */
    BSTNode<E>* getSuccessor(BSTNode<E>* current) {
        BSTNode<E>* successor = current->right;
        while (successor->left != nullptr)
            successor = successor->left;
        return successor;
    }

    /**
     * @brief Intercambia los elementos de 'node1' y 'node2'.
     *
     * @param node1 Primer nodo.
     * @param node2 Segundo nodo.
     */
    void swap(BSTNode<E>* node1, BSTNode<E>* node2) {
        E temp = node1->element;
        node1->element = node2->element;
        node2->element = temp;
    }

    /**
     * @brief Comprueba si un elemento est� en el sub�rbol con ra�z en 'current'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @param element Elemento a buscar.
     * @return true si el elemento est� en el sub�rbol, false en caso contrario.
     */
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

    /**
     * @brief Elimina todos los nodos del sub�rbol con ra�z en 'current'.
     *
     * @param current Nodo ra�z del sub�rbol.
     */
    void clearAux(BSTNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /**
     * @brief A�ade todos los elementos del sub�rbol con ra�z en 'current' a la lista 'elements'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @param elements Lista donde se a�adir�n los elementos.
     */
    void getElementsAux(BSTNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /**
     * @brief Devuelve el tama�o del sub�rbol con ra�z en 'current'.
     *
     * @param current Nodo ra�z del sub�rbol.
     * @return Tama�o del sub�rbol.
     */
    int getSizeAux(BSTNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left)
            + getSizeAux(current->right);
    }

public:
    /**
     * @brief Constructor por defecto que inicializa un �rbol vac�o.
     */
    BSTree() {
        root = nullptr;
    }

    /**
     * @brief Destructor que elimina todos los nodos del �rbol.
     */
    ~BSTree() {
        clear();
    }

    /**
     * @brief Inserta un elemento en el �rbol.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        root = insertAux(root, element);
    }

    /**
     * @brief Busca un elemento en el �rbol y lo devuelve.
     *
     * @param element Elemento a buscar.
     * @return Elemento encontrado.
     * @throws std::runtime_error si el elemento no se encuentra.
     */
    E find(E element) {
        E result;
        findAux(root, element, &result);
        return result;
    }

    /**
     * @brief Elimina un elemento del �rbol y lo devuelve.
     *
     * @param element Elemento a eliminar.
     * @return Elemento eliminado.
     * @throws std::runtime_error si el elemento no se encuentra.
     */
    E remove(E element) {
        E result;
        root = removeAux(root, element, &result);
        return result;
    }

    /**
     * @brief Comprueba si un elemento est� en el �rbol.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento est� en el �rbol, false en caso contrario.
     */
    bool contains(E element) {
        return containsAux(root, element);
    }

    /**
     * @brief Elimina todos los nodos del �rbol.
     */
    void clear() {
        clearAux(root);
        root = nullptr;
    }

    /**
     * @brief Devuelve una lista con todos los elementos del �rbol.
     *
     * @return Lista con todos los elementos del �rbol.
     */
    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    /**
     * @brief Devuelve el tama�o del �rbol.
     *
     * @return Tama�o del �rbol.
     */
    int getSize() {
        return getSizeAux(root);
    }

    /**
     * @brief Imprime todos los elementos del �rbol en orden.
     */
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};