#ifndef SINGLYNODE_CPP
#define SINGLYNODE_CPP
#include "SinglyNode.h"

/*definicion de constructores*/
template <typename T>
SinglyNode<T>::SinglyNode(T newData) : data(newData), next(nullptr){} /*coloca puntero a null*/

template <typename T>
SinglyNode<T>::SinglyNode(T newData, SinglyNode<T>* newNext) : data(newData), next(newNext){}

/*definicion de getters*/
template <typename T>
T SinglyNode<T>::getData() const{
    return this->data;
}

template <typename T>
SinglyNode* SinglyNode<T>::getNext() const{
    return this->next;
}

/*definicion de setters*/
template <typename T>
void SinglyNode<T>::setData(T newData) {
    this->data = newData;
}

template <typename T>
void SinglyNode<T>::setNext(SinglyNode<T>* newNext) {
    this->next = newNext;
}

#endif