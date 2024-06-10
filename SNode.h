#pragma once

/**
 * @brief Clase de nodo para un �rbol binario de b�squeda (BST).
 *
 * @tparam E Tipo de elemento que se almacenar� en el nodo.
 */

template <typename E>
class SNode {
public:
    SNode<E>* left;
    SNode<E>* right;
    SNode<E>* parent;
    E element;

    SNode(E element) {
        this->element = element;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    int childrenCount() {
        return (left == nullptr ? 0 : 1) + (right == nullptr ? 0 : 1);
    }
    SNode<E>* getUniqueChild() {
        return (left == nullptr ? right : left);
    }
};