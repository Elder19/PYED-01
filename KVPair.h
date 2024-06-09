#pragma once

#include <iostream>

using std::ostream;

template <typename K, typename V>
class KVPair
{
public:
	K key;
	V value;

	// Constructor por defecto
	KVPair() {}

	// Constructor que inicializa solo la clave
	KVPair(K key) {
		this->key = key;
	}

	// Constructor que inicializa la clave y el valor
	KVPair(K key, V value) {
		this->key = key;
		this->value = value;
	}

	// Constructor de copia
	KVPair(const KVPair<K, V>& other) {
		key = other.key;
		value = other.value;
	}

	// Operador de asignación
	void operator =(const KVPair<K, V>& other) {
		key = other.key;
		value = other.value;
	}

	// Operador de igualdad
	bool operator ==(const KVPair<K, V>& other) {
		return key == other.key;
	}

	// Operador de menor que
	bool operator <(const KVPair<K, V>& other) {
		return key < other.key;
	}

	// Operador de menor o igual que
	bool operator <=(const KVPair<K, V>& other) {
		return key <= other.key;
	}

	// Operador de mayor que
	bool operator >(const KVPair<K, V>& other) {
		return key > other.key;
	}

	// Operador de mayor o igual que
	bool operator >=(const KVPair<K, V>& other) {
		return key >= other.key;
	}

	// Operador de desigualdad
	bool operator !=(const KVPair<K, V>& other) {
		return key != other.key;
	}
};

// Operador de inserción en flujo para imprimir un par clave-valor
template <typename K, typename V>
ostream& operator <<(ostream& os, const KVPair<K, V>& pair) {
	os << "(" << pair.key << ", " << pair.value << ")";
	return os;
}
