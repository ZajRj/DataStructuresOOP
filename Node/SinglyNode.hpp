#ifndef SINGLYNODE_H
#define SINGLYNODE_H

template <typename T>

class SinglyNode{
    protected:

    T data; /*dato almacenado en el nodo*/
    SinglyNode<T>* next; /*apuntador al nodo siguiente*/

    public:
    
    /*constructores*/
    SinglyNode(T newData); /*constructor si solo se tiene la data (util si es el primer elemento o el ultimo)*/
    SinglyNode(T newData, SinglyNode<T>* newNext); /*constructor si se tiene un puntero (util para introducciones en medio)*/

    /*getters*/
    T getData() const; /*devuelve el contenido*/
    SinglyNode* getNext() const; /*devuelve el puntero*/

    /*setters*/
    void setData(T newData); /*modifica contenido*/
    void setNext(SinglyNode<T>* newNext); /*modifica el puntero*/

};
#endif