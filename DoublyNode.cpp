#ifndef DOUBLYNODE_CPP
#define DOUBLYNODE_CPP

#include "DoublyNode.h"

/*definicion de constructores*/
template <typename T>
DoublyNode<T>::DoublyNode(T newData) : SinglyNode<T>(newData), prev(nullptr) {}

template <typename T>
DoublyNode<T>::DoublyNode(T newData, DoublyNode* newPrev) : SinglyNode<T>(newData), prev(newPrev) {}

template <typename T>
DoublyNode<T>::DoublyNode(T newData, DoublyNode* newPrev, DoublyNode* newNext)
    : SinglyNode<T>(newData, newNext), prev(newPrev) {}

/*getter*/
template <typename T>
DoublyNode<T>* DoublyNode<T>::getPrev() const {
    return this->prev;
}

/*setter*/
template <typename T>
void DoublyNode<T>::setPrev(DoublyNode* newPrev) {
    this->prev = newPrev;
}

#endif
