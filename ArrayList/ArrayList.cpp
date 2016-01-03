/*
 * ArrayList.cpp implements the ArrayList class behavior declared in ArrayList.h.
 *
 * Today's version is able to resize the array to grow it as needed if it
 * becomes full. It throws exceptions when you pass invalid index parameters.
 * The list is also templatized.
 */

#include <string>
#include <stdexcept>
//#include "ArrayList.h"

using namespace std;

// helper that sets all elements of an array to 0
template<typename T>
static void zeroOut(T* a, int length);

template<typename T>
ArrayList<T>::ArrayList() {}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &other) {
    copyOther(other);
}

template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &&other) {
    m_elements = other.m_elements;
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    other.m_size = 0;
    other.m_capacity = 10;
    other.m_elements = new int[other.m_capacity];
}

template<typename T>
ArrayList<T>::ArrayList(const vector<int>& v) {
    for (auto vi : v) {
        add(vi);
    }
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] m_elements;
}

template<typename T>
ArrayList<T>& ArrayList<T>::ArrayList::operator=(const ArrayList<T>& other) {
    if (this != &other) {
        delete[] m_elements;
        copyOther(other);
    }
    return *this;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator= (ArrayList<T>&& other) {
    if (this != &other) {
        delete[] m_elements;
        m_elements = other.m_elements;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_size = 0;
        other.m_capacity = 10;
        other.m_elements = new int[other.m_capacity];
    }
    return *this;
}

template<typename T>
void ArrayList<T>::add(T value) {
    checkResize();
    m_elements[m_size] = value;
    m_size++;
}

template<typename T>
void ArrayList<T>::clear() {
    zeroOut(m_elements, m_capacity);
    m_size = 0;
}

template<typename T>
T ArrayList<T>::get(int index) const {
    checkIndex(index, 0, m_size - 1);
    return m_elements[index];
}

template<typename T>
void ArrayList<T>::insert(int index, T value) {
    checkIndex(index, 0, m_size); // index of m_size is allowed (appends at end)
    checkResize();

    // shift right to make room
    for (int i = m_size; i > index; i--) {
        m_elements[i] = m_elements[i - 1];
    }
    m_elements[index] = value;
    m_size++;
}

template<typename T>
bool ArrayList<T>::isEmpty() const {
    return m_size == 0;
}

template<typename T>
void ArrayList<T>::remove(int index) {
    checkIndex(index, 0, m_size - 1);
    for (int i = index; i < m_size; i++) {
        m_elements[i] = m_elements[i + 1];
    }
    m_size--;
}

template<typename T>
void ArrayList<T>::set(int index, T value) {
    checkIndex(index, 0, m_size - 1);
    m_elements[index] = value;
}

template<typename T>
int ArrayList<T>::size() const {
    return m_size;
}

template<typename T>
string ArrayList<T>::toString() const {
    string s = "[";
    if (!isEmpty()) {
        s += to_string(m_elements[0]);
        for (int i = 1; i < m_size; i++) {
            s += ", ";
            s += to_string(m_elements[i]);
        }
    }
    s += "]";
    return s;
}

template<typename T>
void ArrayList<T>::checkResize() {
    if (m_size == m_capacity) {
        // out of space; resize
        int* bigDaddy = new int[m_capacity * 2];
        for (int i = 0; i < m_size; i++) {
            bigDaddy[i] = m_elements[i];
        }
        delete[] m_elements;   // free old array's memory
        m_elements = bigDaddy;
        m_capacity *= 2;
    }
}

template<typename T>
void ArrayList<T>::checkIndex(int i, int min, int max) const {
    if (i < min || i > max) {
        throw std::out_of_range("Index " + std::to_string(i)
                              + " out of range; (must be between "
                              + std::to_string(min) + " and "
                              + std::to_string(max) + ")");
    }
}

// private helper
template<typename T>
void ArrayList<T>::copyOther(const ArrayList<T> &other) {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_elements = new int[m_capacity]; // deep copy
    for (int i = 0; i < m_size; i++) {
            m_elements[i] = other.m_elements[i];
    }
}


// helper to set all m_elements of an int array to 0.
template<typename T>
static void zeroOut(T *a, int length) {
    for (int i = 0; i < length; i++) {
        a[i] = 0;
    }
}
