#pragma once

#include <stdexcept>
#include <iostream>
#include "SNode.h"
#include "DLinkedList.h"

using std::runtime_error;
using namespace std;

/**
 * @brief Clase que implementa un árbol Splay.
 *
 * @tparam E Tipo de dato de los elementos del árbol.
 */

template <typename E>
class SplayTree {

private:
    SNode<E>* root; /**< Puntero al nodo raíz del árbol. */
    SNode<E>* last; /**< Puntero al último nodo accedido. */

    /**
     * @brief Función auxiliar para insertar un elemento en el árbol.
     *
     * @param current Puntero al nodo actual.
     * @param element Elemento a insertar.
     * @return Puntero al nodo insertado.
     */

    SNode<E>* insertAux(SNode<E>* current, E element) {
        if (current == nullptr) {
            SNode<E>* result = new SNode<E>(element);
            last = result;
            return result;
        }

        if (element == current->element) {
            last = current;
            throw runtime_error("Duplicated element.");
        }

        if (element < current->element) {
            current->left = insertAux(current->left, element);
            current->left->parent = current;
            return current;

        }
        else {
            current->right = insertAux(current->right, element);
            current->right->parent = current;
            return current;
        }
    }
       
    /**
    * @brief Función auxiliar para buscar un elemento en el árbol.
    *
    * @param current Puntero al nodo actual.
    * @param element Elemento a buscar.
    * @return Elemento encontrado.
    */

    E findAux(SNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        last = current;
        if (element == current->element) {
            return current->element;
        }

        if (element < current->element)
            return findAux(current->left, element);

        else
            return findAux(current->right, element);
    }

    /**
    * @brief Función auxiliar para buscar un elemento en el árbol y devolver un puntero a él.
    *
    * @param current Puntero al nodo actual.
    * @param element Elemento a buscar.
    * @return Puntero al elemento encontrado.
    */

    E* findPointerAux(SNode<E>* current, E element) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        last = current;
        if (element == current->element)
            return &(current->element);

        if (element < current->element)
            return findPointerAux(current->left, element);

        else
            return findPointerAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para verificar si un elemento está presente en el árbol.
     *
     * @param current Puntero al nodo actual.
     * @param element Elemento a buscar.
     * @return true si el elemento está presente, false en caso contrario.
     */

    bool containsAux(SNode<E>* current, E element) {
        if (current == nullptr)
            return false;

        last = current;
        if (element == current->element)
            return true;

        if (element < current->element)
            return containsAux(current->left, element);

        else
            return containsAux(current->right, element);
    }

    /**
     * @brief Función auxiliar para eliminar un elemento del árbol.
     *
     * @param current Puntero al nodo actual.
     * @param element Elemento a eliminar.
     * @param result Puntero al resultado de la operación.
     * @return Puntero al nodo resultante después de la eliminación.
     */

    SNode<E>* removeAux(SNode<E>* current, E element, E* result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        if (element < current->element) {
            last = current;
            current->left = removeAux(current->left, element, result);

            if (current->left != nullptr)
                current->left->parent = current;

            return current;
        }

        if (element > current->element) {
            last = current;
            current->right = removeAux(current->right, element, result);

            if (current->right != nullptr)
                current->right->parent = current;

            return current;

        }
        else {
            // element == current->element;
            last = current->parent;
            *result = current->element;

            if (current->childrenCount() == 0) {
                delete current;
                return nullptr;
            }

            if (current->childrenCount() == 1) {
                SNode<E>* child = current->getUniqueChild();
                child->parent = current->parent;
                delete current;
                return child;

            }
            else {
                // current->childrenCount() == 2
                SNode<E>* successor = getSuccessor(current);
                swap(current, successor);
                current->right = removeAux(current->right, element, result);

                if (current->right != nullptr)
                    current->right->parent = current;

                return current;
            }
        }
    }

    /**
     * @brief Función auxiliar para obtener el sucesor de un nodo en el árbol.
     *
     * @param current Puntero al nodo actual.
     * @return Puntero al sucesor del nodo.
     */

    SNode<E>* getSuccessor(SNode<E>* current) {
        SNode<E>* successor = current->right;

        while (successor->left != nullptr)
            successor = successor->left;

        return successor;
    }

    /**
     * @brief Función auxiliar para intercambiar los elementos de dos nodos.
     *
     * @param n1 Puntero al primer nodo.
     * @param n2 Puntero al segundo nodo.
     */

    void swap(SNode<E>* n1, SNode<E>* n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }

    /**
    * @brief Función auxiliar para limpiar todos los nodos del árbol.
    *
    * @param current Puntero al nodo actual.
    */

    void clearAux(SNode<E>* current) {
        if (current == nullptr)
            return;

        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    /**
     * @brief Función auxiliar para obtener todos los elementos del árbol en una lista.
     *
     * @param current Puntero al nodo actual.
     * @param elements Lista donde se almacenarán los elementos.
     */

    void getElementsAux(SNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;

        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    /**
     * @brief Función auxiliar para obtener el tamaño del árbol.
     *
     * @param current Puntero al nodo actual.
     * @return Tamaño del árbol.
     */

    int getSizeAux(SNode<E>* current) {
        if (current == nullptr)
            return 0;

        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }

    /**
     * @brief Función auxiliar para obtener la altura del árbol.
     *
     * @param current Puntero al nodo actual.
     * @return Altura del árbol.
     */

    int height(SNode<E>* current) {
        if (current == nullptr)
            return 0;

        int lh = height(current->left);
        int rh = height(current->right);
        return 1 + (lh > rh ? lh : rh);
    }

    /**
     * @brief Función para realizar una rotación a la derecha en el árbol.
     *
     * @param current Puntero al nodo actual.
     */

    void rotateRight(SNode<E>* current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate right a null tree.");

        if (current->left == nullptr)
            throw runtime_error("Can't rotate right with a null left child.");

        SNode<E>* temp = current->left;
        temp->parent = current->parent;
        current->left = temp->right;

        if (current->left != nullptr)
            current->left->parent = current;

        temp->right = current;
        current->parent = temp;

        if (current == root)
            root = temp;

        else if (temp->parent->right == current)
            temp->parent->right = temp;

        else
            temp->parent->left = temp;
    }

    /**
     * @brief Función para realizar una rotación a la izquierda en el árbol.
     *
     * @param current Puntero al nodo actual.
     */

    void rotateLeft(SNode<E>* current) {
        if (current == nullptr)
            throw runtime_error("Can't rotate left a null tree.");

        if (current->right == nullptr)
            throw runtime_error("Can't rotate left with a null right child.");

        SNode<E>* temp = current->right;
        temp->parent = current->parent;
        current->right = temp->left;

        if (current->right != nullptr)
            current->right->parent = current;

        temp->left = current;
        current->parent = temp;

        if (current == root)
            root = temp;

        else if (temp->parent->right == current)
            temp->parent->right = temp;

        else
            temp->parent->left = temp;
    }

    /**
     * @brief Función para realizar la operación de splay en el árbol.
     */

    void splay() {
        if (last == nullptr)
            return;

        SNode<E>* current = last;

        while (last != root) {
            if (current == root->left) {
                rotateRight(root);
                root->parent = nullptr;
            }

            else if (current == root->right) {
                rotateLeft(root);
                root->parent = nullptr;

            }
            else {
                SNode<E>* grand = current->parent->parent;

                if (grand->left != nullptr &&
                    grand->left->left == current) {
                    rotateRight(grand);
                    rotateRight(current->parent);
                }

                else if (grand->right != nullptr &&
                    grand->right->right == current) {
                    rotateLeft(grand);
                    rotateLeft(current->parent);
                }

                else if (grand->left != nullptr &&
                    grand->left->right == current) {
                    rotateLeft(current->parent);
                    rotateRight(grand);

                }
                else {
                    rotateRight(current->parent);
                    rotateLeft(grand);
                }
            }

        }
    }

public:

    /**
     * @brief Constructor de la clase SplayTree.
     */

    SplayTree() {
        root = nullptr;
        last = nullptr;
    }

    /**
     * @brief Destructor de la clase SplayTree.
     */

    ~SplayTree() {
        clear();
    }

    /**
     * @brief Inserta un elemento en el árbol y realiza la operación de splay.
     *
     * @param element Elemento a insertar.
     */

    void insert(E element) {
        try {
            root = insertAux(root, element);
            root->parent = nullptr;
            splay();

        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Busca un elemento en el árbol y realiza la operación de splay.
     *
     * @param element Elemento a buscar.
     * @return Elemento encontrado.
     */

    E find(E element) {
        try {
            E result = findAux(root, element);
            splay();
            return result;

        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Busca un elemento en el árbol y devuelve un puntero a él, realizando la operación de splay.
     *
     * @param element Elemento a buscar.
     * @return Puntero al elemento encontrado.
     */

    E* findPointer(E element) {
        try {
            E* result = findPointerAux(root, element);
            splay();
            return result;

        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Verifica si un elemento está presente en el árbol y realiza la operación de splay.
     *
     * @param element Elemento a buscar.
     * @return true si el elemento está presente, false en caso contrario.
     */

    bool contains(E element) {
        bool result = containsAux(root, element);
        splay();
        return result;
    }

    /**
     * @brief Elimina un elemento del árbol y realiza la operación de splay.
     *
     * @param element Elemento a eliminar.
     * @return Elemento eliminado.
     */

    E remove(E element) {
        try {
            E result;
            root = removeAux(root, element, &result);
            if (root != nullptr) root->parent = nullptr;
            splay();
            return result;

        }
        catch (runtime_error& e) {
            splay();
            throw e;
        }
    }

    /**
     * @brief Limpia todos los nodos del árbol.
     */

    void clear() {
        clearAux(root);
        root = nullptr;
    }

    /**
     * @brief Obtiene todos los elementos del árbol en una lista.
     *
     * @return Lista con los elementos del árbol.
     */

    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    /**
     * @brief Obtiene el tamaño del árbol.
     *
     * @return Tamaño del árbol.
     */

    int getSize() {
        return getSizeAux(root);
    }

    /**
     * @brief Obtiene la altura del árbol.
     *
     * @return Altura del árbol.
     */

    int getHeight() {
        return height(root);
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