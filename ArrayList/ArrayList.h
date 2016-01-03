/*
 * ArrayList is our example of implementing a basic data structure.
 */

#ifndef _arraylist_h
#define _arraylist_h

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * An ArrayList is an ordered collection of elements stored and accessed
 * with 0-based integer indexes, using an array as the internal representation.
 */
template<typename T> class ArrayList {
public:
    /*
     * Constructs a new empty list.
     */
    ArrayList();

    /*
     * Copy constructor
     */
    ArrayList(const ArrayList<T> &other);

    /*
     * Move constructor
     */
    ArrayList(ArrayList<T> &&other);

    /*
     * Converting constructor
     */
    ArrayList(const vector<int> &v);

    /*
     * This destructor frees the memory that was allocated internally by the list.
     */
    ~ArrayList();

    /*
     * Copy assignment
     */
    ArrayList<T>& operator=(const ArrayList<T>& other);

    /*
     * Move assignment
     */
    ArrayList<T>& operator=(ArrayList<T>&& other);

    /*
     * Appends the given value to the end of the list.
     */
    void add(T value);

    /*
     * Removes all values from the list.
     */
    void clear();

    /*
     * Returns the value at the given 0-based index of the list.
     */
    T get(int index) const;

    /*
     * Adds the given value just before the given 0-based index in the list,
     * shifting subsequent elements right as necessary to make room.
     */
    void insert(int index, T value);

    /*
     * Returns true if there are no elements in the list.
     */
    bool isEmpty() const;

    /*
     * Removes the element at the given 0-based index from the list,
     * shifting subsequent elements left as necessary to cover its slot.
     */
    void remove(int index);

    /*
     * Stores the given value at the given 0-based index in the list.
     */
    void set(int index, T value);

    /*
     * Returns the number of elements in the list.
     */
    int size() const;

    /*
     * Returns a string representation of the list such as "[42, 3, 17]".
     */
    string toString() const;

private:
    // member variables inside each list object;
    // we precede them with "m_" just as a stylistic convention
    // to make them easier to identify in the .cpp code

    int m_size = 0;                          // number of elements added
    int m_capacity = 10;                     // length of array
    T* m_elements = new T[m_capacity];       // array of elements

    /*
     * This private helper resizes the list's internal array buffer if necessary
     * to accommodate additional elements.
     */
    void checkResize();

    /*
     * This helper throws an out_of_range exception if the given index is not between
     * the given min/max indexes, inclusive.
     */
    void checkIndex(int i, int min, int max) const;

    /*
     * This helper copies the contents of other into this list.
     */
    void copyOther(const ArrayList<T> &other);
};

#include "ArrayList.cpp"
#endif // _arraylist_h
