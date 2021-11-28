#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
    //Default ctr
    List() :
    first(nullptr), last(nullptr), list_size(0) {}
    
    //Copy ctr
    List(const List &copy) :
    first(nullptr), last(nullptr), list_size(0)
    {
        copy_all(copy);
    }
    
    //EFFECTS:  returns true if the list is empty
    bool empty() const {
        return (list_size == 0);
    }

    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow. Instead, keep track of the size
    //         with a private member variable. That's how std::list does it.
    int size() const {
        return static_cast<const int>(list_size);
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T & front() {
        assert(!this->empty());
        return first->datum;
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T & back() {
        assert(!this->empty());
        return last->datum;
    }

    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
        Node* temp = new Node;
        temp->datum = datum;
        // edge case: empty list
        if (first == nullptr && last == nullptr) {
            first = temp;
            first->next = nullptr;
            first->prev = nullptr;
            last = temp;
        }
        else {
            first->prev = temp;
            temp->next = first;
            temp->prev = nullptr;
            first = temp;
            temp->next->prev = temp;
        }
        list_size++;
        return;
    }

    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum) {
        Node* temp = new Node;
        temp->datum = datum;
        // edge case: empty list
        if (first == nullptr && last == nullptr) {
            first = temp;
            first->next = nullptr;
            first->prev = nullptr;
            last = temp;
        }
        else {
            temp->prev = last;
            last->next = temp;
            temp->next = nullptr;
            last = temp;
            temp->prev->next = temp;
        }
        list_size++;
        return;
    }

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        assert(!empty());
        // edge case: list with 1 node
        if (first == last) {
            Node *ptr1 = first;
            first = nullptr;
            last = nullptr;
            delete ptr1;
        }
        else {
            Node *ptr2 = first;
            first = first->next;
            first->prev = nullptr;
            delete ptr2;
        }
        decrement_list_size();
        return;
    }

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        assert(!empty());
        if (first == last) {
            Node *ptr1 = first;
            first = nullptr;
            last = nullptr;
            delete ptr1;
            
        }
        else {
            Node *ptr = last->prev;
            delete last;
            last = ptr;
            last->next = nullptr;
        }
        decrement_list_size();
        return;
    }

    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
        list_size = 0;
        return;
    }
    
    void decrement_list_size() {
        if (list_size < 0) {
            list_size = 0;
        } else {
            list_size--;
        }
    }
    
    //destructor
    ~List() {
        clear();
    }
    
//    static T get_datum() {
//        return datum;
//    }
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Lists

private:
//a private type
    struct Node {
        Node *next;
        Node *prev;
        T datum;
};

    //REQUIRES: list is empty
    //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other) {
        for (Node *ptr = other.first; ptr != nullptr; ptr = ptr->next){
            this->push_back(ptr->datum);
        }
        return;
    }

    Node *first;   // points to first Node in list, or nullptr if list is empty
    Node *last;    // points to last Node in list, or nullptr if list is empty
    int list_size;

public:
  ////////////////////////////////////////
    class Iterator {
        friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

    public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.

        Iterator() :
        node_ptr(nullptr) {}

        Iterator(const Iterator &copy) :
        node_ptr(copy.node_ptr) {}

        Iterator& operator--() {
            node_ptr = node_ptr->prev;
            return *this;
        }
        Iterator& operator++() {
            assert(node_ptr);
            node_ptr = node_ptr->next;
            return *this;
        }
        bool operator==(Iterator rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        bool operator!=(Iterator rhs) const {
            return node_ptr != rhs.node_ptr;
        }
        T & operator*() const {
            assert(node_ptr);
            return node_ptr->datum;
        }
        
    private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
        
    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

    };//List::Iterator
  ////////////////////////////////////////

    // return an Iterator pointing to the first element
    Iterator begin() const {
        return Iterator(first);
    }

    // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator();
    }

    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        Node *temp = i.node_ptr;
        if (i.node_ptr->next == nullptr) {
            pop_back();
        }
        else if (i.node_ptr->prev == nullptr) {
            pop_front();
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            decrement_list_size();
        }
        return;
    }

    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {
        if (i.node_ptr == nullptr) {
            push_back(datum);
        }
        else if (i.node_ptr->prev == nullptr) {
            push_front(datum);
        }
        else {
            Node *temp = new Node;
            temp->datum = datum;

            temp->next = i.node_ptr;
            temp->prev = i.node_ptr->prev;
            i.node_ptr->prev->next = temp;
            i.node_ptr->prev = temp;
            list_size++;
        }
        return;
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.

