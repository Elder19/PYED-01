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

class Trie {

private:
	TrieNode* root;

	TrieNode* findNode(string word) {
		TrieNode* current = root;
		for (unsigned int i = 0; i < word.size(); i++) {
			if (!current->containsChild(word[i]))
				return nullptr;
			current = current->getChild(word[i]);
		}
		return current;
	}

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

	Trie() {
		root = new TrieNode();
	}

	~Trie() {
		clear();
		delete root;
	}

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

	bool containsWord(string word) {
		TrieNode* current = findNode(word);
		if (current == nullptr) return false;
		return current->isFinal;
	}

	bool containsPrefix(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return false;
		return true;
	}

	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		if (current == nullptr) return 0;
		return current->prefixCount;
	}

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

	void clear() {
		clearAux(root);
		root = new TrieNode();
	}

	List<string>* getMatches(string prefix) {
		List<string>* words = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getMatchesAux(current, prefix, words);
		return words;
	}

	int getSize() {
		return root->prefixCount;
	}

	void print() {
		List<string>* words = new DLinkedList<string>();
		words = getMatches("");
		words->print();
		delete words;
	}

	DLinkedList<string>* getWords_lenght(int lenght) {
		DLinkedList<string>* lista = new DLinkedList<string>();
		getWords_lenghtAux(root, "", lenght - 1, lista);
		return lista;
	}

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

	DLinkedList<int>* buscarPalabra(string word) {
		TrieNode* node = findNode(word);
		DLinkedList<int>* appearancesWord = node->line;
		DLinkedList<int>* appearances = new DLinkedList<int>();
		appearancesWord->goToStart();

		for (int i = 0; i < appearancesWord->getSize(); i++) {
			int appearance = appearancesWord->getElement();
			if (!appearances->contains(appearance)) {
				appearances->append(appearance);
			}
			appearancesWord->next();
		}
		return appearances;
	}

};