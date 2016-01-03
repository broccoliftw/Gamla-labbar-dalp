/*
 * This program is a client that uses our ArrayList class.
 */

#include <iostream>
#include <stdexcept>
#include "ArrayList.h"

using namespace std;

void testAdd(ArrayList<int>& list);
void testRemove(ArrayList<int>& list);
void testMisc(ArrayList<int>& list);
void testResize(ArrayList<int>& list);
void testConversion();
void testCopy(ArrayList<int>& list);
void testAssign(ArrayList<int>& list);
void testMove(ArrayList<int>& list);
void testException(ArrayList<int>& list);

int main() {

    ArrayList<int> list;
    testAdd(list);
    testRemove(list);
    testMisc(list);
    testResize(list);
    testConversion();
    testCopy(list);
    testAssign(list);
    testMove(list);
    testException(list);

    return 0;
}

void testAdd(ArrayList<int> &list) {
    cout << "add:" << endl;
    list.add(42);
    list.add(-5);
    list.add(17);
    list.add(28);
    cout << list.toString() << ", size " << list.size() << endl;
    cout << endl;

    cout << "insert:" << endl;
    list.insert(1, 111);
    cout << list.toString() << ", size " << list.size() << endl;
    list.insert(4, 444);
    cout << list.toString() << ", size " << list.size() << endl;
    list.insert(0, 0);
    cout << list.toString() << ", size " << list.size() << endl;
    list.insert(7, 7777);
    cout << list.toString() << ", size " << list.size() << endl;
    cout << endl;
}

void testRemove(ArrayList<int> &list) {
    cout << "remove:" << endl;
    list.remove(2);
    cout << list.toString() << ", size " << list.size() << endl;
    list.remove(list.size() - 1);
    cout << list.toString() << ", size " << list.size() << endl;
    list.remove(0);
    cout << list.toString() << ", size " << list.size() << endl;
    cout << endl;
}

void testMisc(ArrayList<int> &list) {
    cout << "get:" << endl;
    for (int i = 0; i < list.size(); i++) {
        cout << "index " << i << ": " << list.get(i) << endl;
    }
    cout << endl;

    cout << "set:" << endl;
    list.set(2, 222);
    cout << list.toString() << ", size " << list.size() << endl;
    list.set(0, 12345);
    cout << list.toString() << ", size " << list.size() << endl;
    cout << endl;

    cout << "clear:" << endl;
    list.clear();
    cout << list.toString() << ", size " << list.size() << endl;
    cout << endl;
}

void testResize(ArrayList<int> &list) {
    cout << "resize:" << endl;
    for (int i = 1; i <= 25; i++) {
        list.add(i);
        cout << list.toString() << ", size " << list.size() << endl;
    }
    cout << endl;
}
void testConversion() {
    vector<int> v = {12, 22, 32, 42, 52};
    ArrayList<int> list1 = v;
    cout << list1.toString() << endl;
    ArrayList<int> list2 = ArrayList<int>(vector<int> {23, 24, 25, 26});
    cout << list2.toString() << endl;
}

void testCopy(ArrayList<int> &list) {
    cout << "copy:" << endl;
    list.clear();
    for (int i = 1; i <= 5; i++) {
        list.add(i * 10);
    }
    ArrayList<int> list2 = list;
    cout << "list    : " << list.toString() << ", size " << list.size() << endl;
    cout << "list2   : " << list2.toString() << ", size " << list2.size() << endl;
    cout << endl;

    list2.add(60);
    list2.set(1, 99);
    list.remove(3);
    cout << "list    : " << list.toString() << ", size " << list.size() << endl;
    cout << "list2   : " << list2.toString() << ", size " << list2.size() << endl;
    cout << endl;
}

void testAssign(ArrayList<int> &list) {
    cout << "assign:" << endl;
    list.clear();
    for (int i = 1; i <= 5; i++) {
        list.add(i * 10);
    }
    ArrayList<int> list2;
    list2 = list;
    cout << "list    : " << list.toString() << ", size " << list.size() << endl;
    cout << "list2   : " << list2.toString() << ", size " << list2.size() << endl;
    cout << endl;

    list2.add(60);
    list2.set(1, 99);
    list.remove(3);
    cout << "list    : " << list.toString() << ", size " << list.size() << endl;
    cout << "list2   : " << list2.toString() << ", size " << list2.size() << endl;
    cout << endl;
}

void testMove(ArrayList<int> &list) {
    cout << "move constructor:" << endl;
    list.clear();
    for (int i = 1; i <= 5; i++) {
        list.add(i * 10);
    }
    ArrayList<int> list2{std::move(list)};
    cout << "list2    : " << list2.toString() << ", size " << list2.size() << endl;
    cout << "list   : " << list.toString() << ", size " << list.size() << endl;
    cout << endl;

    cout << "move assignment:" << endl;
    list = std::move(list2);
    cout << "list    : " << list.toString() << ", size " << list.size() << endl;
    cout << "list2   : " << list2.toString() << ", size " << list2.size() << endl;
    cout << endl;
}


void testException(ArrayList<int> &list) {
    cout << "index checking:" << endl;
    try {
        list.insert(-3, 99999);
    }
    catch (const std::out_of_range& oor) {
        cerr << "Out of range error: " << oor.what() << '\n';
    }
}
