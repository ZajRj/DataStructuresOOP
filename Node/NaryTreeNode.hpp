#ifndef NARYTREENODE_H
#define NARYTREENODE_H

#include <cstddef>

/* esta clase esta reservada para ser utilizada en arboles N-arios (y cualquier herencia proveniente de estos)
estan definidos de forma literal, mas no conceptual; por lo tanto, definiciones como: isLeaf() u otras referencias
a la estructura se reservan netamente a la clase NaryTree y subyacentes. Si lees esto, no toques nada de la
definicion de estos a menos que sea extremedamente necesario */

template <typename T>
class NaryTreeNode {
    
    T data; /* dato almacenado en el nodo */
    NaryTreeNode<T> *left, *right; /* punteros que referencian a su hijoIzquierdo y a su hermanoDerecho */

    public:
    /* constructores */
    NaryTreeNode() : data(T()), left(NULL), right(NULL) {} /* constructor por defecto, inicializa el dato con su valor por defecto y el puntero a sus hijoIzquierdo y hermanoDerecho como NULL */
 
    NaryTreeNode(T newData) : data(newData), left(NULL), right(NULL) {} /* inicializa con un dato indicado por parametro y coloca su hijoIzquierdo y hermanoDerecho con valor NULL */
 
    NaryTreeNode(T newData,NaryTreeNode<T>* newLeft) : data(newData), left(newLeft), right(NULL) /* inicializa con un dato indicado por parametro e inicializa el nodo pasado por parametro como hijo */ {}
    
    /* MEJORA ADICIONAL: constructor completo que usa setters */
    NaryTreeNode(T newData, NaryTreeNode<T>* newLeft, NaryTreeNode<T>* newRight) 
        : data(newData), left(NULL), right(NULL) {
        setLeft(newLeft); /* usa setter para validacion */
        setRight(newRight); /* usa setter para validacion */
    }

    /* getters */
    T getData() const { return data; } /* devuelve contenido */
    
    NaryTreeNode<T>* getLeft() const { return left; } /* devuelve el puntero al nodo hijoIzquierdo */
    
    NaryTreeNode<T>* getRight() const { return right; } /* devuelve el puntero al nodo hermanoDerecho */
    
    /* setters */
    void setData(T newData ) { this->data = newData; } /* modifica el dato actual */

    void setLeft(NaryTreeNode<T>* newLeft) { /* modifica el puntero izquierdo actual */
        if (newLeft != this && newLeft != right) { /* evitamos auto-referencia y ciclos */
            left = newLeft; 
        }
    }
    
    void setRight(NaryTreeNode<T>* newRight) { /* modifica el puntero derecho actual */
        if (newRight != this && newRight != left) { /* evitamos auto-referencia y ciclos */
            right = newRight; 
        }
    }

    ~NaryTreeNode() {
        /* no eliminar left/right aqui, debe manejarse desde la clase NaryTree */
    }

    private:

    NaryTreeNode(const NaryTreeNode&); /* no implementado */
    NaryTreeNode& operator=(const NaryTreeNode&); /* no implementado */
};

#endif