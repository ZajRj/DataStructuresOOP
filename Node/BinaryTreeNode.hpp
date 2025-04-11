#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#include <cstddef>

/* esta clase esta reservada para ser utilizada en arboles binarios (y cualquier herencia proveniente de estos)
estan definidos de forma literal, mas no conceptual; por lo tanto, definiciones como: isLeaf() u otras referencias
a la estructura se reservan netamente a la clase BinaryTree y subyacentes. Si lees esto, no toques nada de la
definicion de estos a menos que sea extremedamente necesario. */

template <typename T>
class BinaryTreeNode {
    
    T data; /* dato almacenado en el nodo */
    BinaryTreeNode<T> *left, *right; /* punteros que referencian a sus hijos conceptuales */

    public:
    /* constructores */
    BinaryTreeNode() : data(T()), left(NULL), right(NULL) {} /* constructor por defecto, inicializa el dato con su valor por defecto y el puntero a sus hijos como NULL */
 
    BinaryTreeNode(T newData) : data(newData), left(NULL), right(NULL) {} /* inicializa con un dato indicado por parametro y coloca sus hijos con valor NULL */
 
    BinaryTreeNode(T newData, BinaryTreeNode<T>* newNode, bool isLeft) /* inicializa con un dato indicado por parametro y pregunta sobre el booleano isLeft */
        : data(newData), 
          left(isLeft ? newNode : NULL), /* si isLeft es verdadero, asignara el pointer entregado por parametro a left */    
          right(isLeft ? NULL : newNode) /* si isLeft es falso, asignara el pointer entregado por parametro a right */ {}
 
    BinaryTreeNode(T newData, BinaryTreeNode<T>* newLeft, BinaryTreeNode<T>* newRight) : data(newData), left(newLeft), right(newRight){} /* inicializa con un dato indicado por parametro y asigna ambos punteros
    segun como fueron enviados por parametro, el primer dato por parametro es el dato, el segundo es el pointer al hijo izquierdo y el tercero es el pointer al hijo derecho */
    
    /* getters */
    T getData() const { return this->data; } /* devuelve contenido */
    
    BinaryTreeNode<T>* getLeft() const { return this->left; } /* devuelve el puntero al nodo izquierdo */
    
    BinaryTreeNode<T>* getRight() const { return this->right; } /* devuelve el puntero al nodo derecho */
    
    /* setters */
    void setData(T newData ) { this->data = newData; } /* modifica el dato actual */

    void setLeft(BinaryTreeNode<T>* newLeft) { /* modifica el puntero izquierdo actual */
        if (newLeft != this) { /* evitamos la auto-referencia */
            left = newLeft; 
        }
    }
    
    void setRight(BinaryTreeNode<T>* newRight) { /* modifica el puntero derecho actual */
        if (newRight != this) { /* evitamos la auto-referencia */
            right = newRight; 
        }
    }

};

#endif