#ifndef DOUBLYNODE_H
#define DOUBLYNODE_H

#include "SinglyNode.h"

template <typename T>

class DoublyNode : public SinglyNode<T> {
    private:
    DoublyNode<T>* prev; /*apuntador al nodo anterior*/ 

    public:
    /*constructores*/
    DoublyNode(T newData);
    DoublyNode(T newData, DoublyNode* prev);
    DoublyNode(T newData, DoublyNode* prev, DoublyNode* next);

    /*getter*/
    DoublyNode* getPrev() const;

    /*setter*/
    void setPrev(DoublyNode* newPrev);
};
#endif