#pragma once
#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

// Clase plantilla MinHeap que implementa un Heap mínimo
template <typename E>
class MinHeap {
private:
    E* elements;  // Arreglo para almacenar los elementos del heap
    int max;      // Capacidad máxima del heap
    int size;     // Número de elementos actualmente en el heap

    // Constructor de copia privado para evitar la copia del heap
    MinHeap(const MinHeap<E>& other) {}
    // Operador de asignación privado para evitar la asignación del heap
    void operator =(const MinHeap<E>& other) {}

    // Función para restaurar la propiedad del heap hacia arriba
    void siftUp(int pos) {
        while (pos != 0 && elements[pos] > elements[parent(pos)]) {
            swap(pos, parent(pos));
            pos = parent(pos);
        }
    }

    // Función para restaurar la propiedad del heap hacia abajo
    void siftDown(int pos) {
        while (!isLeaf(pos) && elements[pos] < elements[minChild(pos)]) {
            int mChild = minChild(pos);
            swap(pos, mChild);
            pos = mChild;
        }
    }

    // Retorna el índice del padre de un nodo en la posición 'pos'
    int parent(int pos) {
        return (pos - 1) / 2;
    }

    // Retorna el índice del hijo izquierdo de un nodo en la posición 'pos'
    int leftChild(int pos) {
        return 2 * pos + 1;
    }

    // Retorna el índice del hijo derecho de un nodo en la posición 'pos'
    int rightChild(int pos) {
        return 2 * pos + 2;
    }

    // Retorna el índice del hijo con el valor mínimo de un nodo en la posición 'pos'
    int minChild(int pos) {
        if (rightChild(pos) >= size || elements[leftChild(pos)] < elements[rightChild(pos)]) {
            return leftChild(pos);
        }
        return rightChild(pos);
    }

    // Verifica si un nodo en la posición 'pos' es una hoja
    bool isLeaf(int pos) {
        return leftChild(pos) >= size;
    }

    // Intercambia los elementos en las posiciones 'pos1' y 'pos2'
    void swap(int pos1, int pos2) {
        E temp = elements[pos1];
        elements[pos1] = elements[pos2];
        elements[pos2] = temp;
    }

public:
    // Constructor que inicializa el heap con una capacidad máxima dada
    MinHeap(int max = DEFAULT_MAX_SIZE) {
        elements = new E[max];
        size = 0;
        this->max = max;
    }

    // Destructor que libera la memoria asignada al arreglo de elementos
    ~MinHeap() {
        delete[] elements;
    }

    // Inserta un nuevo elemento en el heap
    void insert(E element) {
        if (size == max)
            throw runtime_error("Heap is full.");
        elements[size] = element;
        size++;
        siftUp(size - 1);
    }

    // Retorna el primer elemento (mínimo) del heap sin eliminarlo
    E first() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return elements[0];
    }

    // Elimina y retorna el primer elemento (mínimo) del heap
    E removeFirst() {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        return remove(0);
    }

    // Elimina y retorna el elemento en la posición 'pos'
    E remove(int pos) {
        if (size == 0)
            throw runtime_error("Heap is empty.");
        if (pos < 0 || pos >= size)
            throw runtime_error("Index out of bounds.");
        swap(pos, size - 1);
        size--;
        siftDown(0);
        return elements[size];
    }

    // Vacía el heap
    void clear() {
        size = 0;
    }

    // Retorna el número de elementos en el heap
    int getSize() {
        return size;
    }

    // Verifica si el heap está vacío
    bool isEmpty() {
        return size == 0;
    }

    // Imprime los elementos del heap
    void print() {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << elements[i] << " ";
        }
        cout << "]" << endl;
    }
};