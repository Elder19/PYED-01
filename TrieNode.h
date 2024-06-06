#pragma once
#include "SplayDictionary.h"
#include "DLinkedList.h"

class TrieNode {
public:
	bool isFinal;
	int prefixCount;
	Dictionary<char, TrieNode*>* children;
	DLinkedList<int>* line;

	TrieNode() {
		isFinal = false;
		prefixCount = 0;
		children = new SplayDictionary<char, TrieNode*>();
		line = new DLinkedList<int>();
	}
	~TrieNode() {
		delete children;
	}
	bool containsChild(char c) {
		return children->contains(c);
	}
	TrieNode* getChild(char c) {
		return children->getValue(c);
	}
	void addChild(char c) {
		children->insert(c, new TrieNode());
	}
	void removeChild(char c) {
		children->remove(c);
	}
	List<char>* getChildren() {
		return children->getKeys();
	}

	void insertLine(int l) {
		line->append(l);
	}

	int getLine(int l) {
		line->getElement();
	}
};