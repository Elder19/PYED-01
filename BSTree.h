#pragma once

#include <stdexcept>
#include <iostream>
#include "BSTNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Árbol Binario de Búsqueda (BST).
 *
 * @tparam E Tipo de dato almacenado en el árbol.
 */
template <typename E>
class BSTree {
private:
    BSTree(const BSTree<E>& other) {}
    void operator =(const BSTree<E>& other) {}

    BSTNode<E>* root; ///< Raíz del árbol.

    /**
     * @brief Inserta un elemento en el subárbol con raíz en 'current'.
     *
     * @param current Nodo raíz del subárbol.
     * @param element Elemento a insertar.
     * @return Nodo raíz del subárbol actualizado.
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
     * @brief Busca un elemento en el subárbol con raíz en 'current' y guarda el resultado en 'result'.
     *
     * @param current Nodo raíz del subárbol.
     * @param element Elemento a buscar.
     * @param result Puntero donde se guardará el resultado.
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
     * @brief Elimina un elemento del subárbol con raíz en 'current' y guarda el resultado en 'result'.
     *
     * @param current Nodo raíz del subárbol.
     * @param element Elemento a eliminar.
     * @param result Puntero donde se guardará el resultado.
     * @return Nodo raíz del subárbol actualizado.
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
     * @param current Nodo raíz del subárbol.
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
     * @brief Comprueba si un elemento está en el subárbol con raíz en 'current'.
     *
     * @param current Nodo raíz del subárbol.
     * @param element Elemento a buscar.
     * @return true si el elemento está en el subárbol, false en caso contrario.
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
     * @brief Elimina todos los nodos del subárbol con raíz en 'current'.
     *
     * @param current Nodo raíz del subárbol.
     */
    void clearAux(BSTNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /**
     * @brief Añade todos los elementos del subárbol con raíz en 'current' a la lista 'elements'.
     *
     * @param current Nodo raíz del subárbol.
     * @param elements Lista donde se añadirán los elementos.
     */
    void getElementsAux(BSTNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /**
     * @brief Devuelve el tamaño del subárbol con raíz en 'current'.
     *
     * @param current Nodo raíz del subárbol.
     * @return Tamaño del subárbol.
     */
    int getSizeAux(BSTNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left)
            + getSizeAux(current->right);
    }

public:
    /**
     * @brief Constructor por defecto que inicializa un árbol vacío.
     */
    BSTree() {
        root = nullptr;
    }

    /**
     * @brief Destructor que elimina todos los nodos del árbol.
     */
    ~BSTree() {
        clear();
    }

    /**
     * @brief Inserta un elemento en el árbol.
     *
     * @param element Elemento a insertar.
     */
    void insert(E element) {
        root = insertAux(root, element);
    }

    /**
     * @brief Busca un elemento en el árbol y lo devuelve.
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
     * @brief Elimina un elemento del árbol y lo devuelve.
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
     * @brief Comprueba si un elemento está en el árbol.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento está en el árbol, false en caso contrario.
     */
    bool contains(E element) {
        return containsAux(root, element);
    }

    /**
     * @brief Elimina todos los nodos del árbol.
     */
    void clear() {
        clearAux(root);
        root = nullptr;
    }

    /**
     * @brief Devuelve una lista con todos los elementos del árbol.
     *
     * @return Lista con todos los elementos del árbol.
     */
    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    /**
     * @brief Devuelve el tamaño del árbol.
     *
     * @return Tamaño del árbol.
     */
    int getSize() {
        return getSizeAux(root);
    }

    /**
     * @brief Imprime todos los elementos del árbol en orden.
     */
    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};