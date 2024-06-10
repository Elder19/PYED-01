#pragma once

/**
 * @brief Nodo de un �rbol Binario de B�squeda (BST).
 *
 * @tparam E Tipo de dato almacenado en el nodo.
 */

template <typename E>
class BSTNode {
public:
	E element;
	BSTNode<E>* left;
	BSTNode<E>* right;

	BSTNode(E element, BSTNode<E>* left = nullptr, BSTNode<E>* right = nullptr) {
		this->element = element;
		this->left = left;
		this->right = right;
	}
	int childrenCount() {
		return (left == nullptr? 0 : 1) + (right == nullptr? 0 : 1);
	}
	BSTNode<E>* getOnlyChild() {
		return left == nullptr ? right : left;
	}
};