#pragma once

#include "Dictionary.h"
#include "KVPair.h"
#include "SplayTree.h"

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

// Clase SplayDictionary que implementa un diccionario utilizando un �rbol splay
template <typename K, typename V>
class SplayDictionary : public Dictionary<K, V> {
private:
    SplayTree<KVPair<K, V>>* pairs; // �rbol splay para almacenar los pares clave-valor

public:
    // Constructor que inicializa el diccionario
    SplayDictionary() {
        pairs = new SplayTree<KVPair<K, V>>();
    }

    // Destructor que libera la memoria asignada al �rbol
    ~SplayDictionary() {
        delete pairs;
    }

    // M�todo para insertar un nuevo par clave-valor en el diccionario
    void insert(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->insert(p);
    }

    // M�todo para eliminar un par clave-valor del diccionario y retornar su valor
    V remove(K key) {
        KVPair<K, V> p(key);
        p = pairs->remove(p);
        return p.value;
    }

    // M�todo para obtener el valor asociado a una clave
    V getValue(K key) {
        KVPair<K, V> p(key);
        p = pairs->find(p);
        return p.value;
    }

    // M�todo para establecer el valor asociado a una clave
    void setValue(K key, V value) {
        KVPair<K, V> p(key, value);
        pairs->remove(p);
        pairs->insert(p);
    }

    // M�todo para verificar si una clave est� presente en el diccionario
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs->contains(p);
    }

    // M�todo para obtener una lista con todas las claves del diccionario
    List<K>* getKeys() {
        List<K>* keys = new DLinkedList<K>();
        List<KVPair<K, V>>* elements = pairs->getElements();
        elements->goToStart();
        while (!elements->atEnd()) {
            KVPair<K, V> p = elements->getElement();
            keys->append(p.key);
            elements->next();
        }
        delete elements;
        return keys;
    }

    // M�todo para obtener una lista con todos los valores del diccionario
    List<V>* getValues() {
        List<V>* values = new DLinkedList<V>();
        List<KVPair<K, V>>* elements = pairs->getElements();
        elements->goToStart();
        while (!elements->atEnd()) {
            KVPair<K, V> p = elements->getElement();
            values->append(p.value);
            elements->next();
        }
        delete elements;
        return values;
    }

    // M�todo para obtener el tama�o del diccionario (n�mero de pares clave-valor)
    int getSize() {
        return pairs->getSize();
    }

    // M�todo para imprimir el contenido del diccionario
    void print() {
        pairs->print();
    }
};
