#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "../Node/BinaryTreeNode.hpp"
#include <iostream>
#include <list>
#include <algorithm>

template <typename T>
class BinaryTree {
    protected:
    /* atributos de la clase */
    BinaryTreeNode<T>* root; /* apuntador a la raiz de un arbol */
    int size; /* cantidad de nodos existentes en un arbol */

    /* metodos restringidos; su uso es permitido dentro de la misma clase por otros metodos publicos */

    bool isNullNode(BinaryTreeNode<T>* node) const{
        return node == NULL
    } /* O(1) */

    bool isNullNode(BinaryTreeNode<T>* firstNode,BinaryTreeNode<T>* secondNode){
        return this->isNullNode(firstNode) || this->isNullNode(secondNode);
    }

    BinaryTreeNode<T>* auxiliarInsert(BinaryTreeNode<T>* currentNode, const T& data){

    }

    BinaryTreeNode<T>* auxiliarRemove(BinaryTreeNode<T>* currentNode, const T& data){

    }

    void auxiliarClear(BinaryTreeNode<T>* currentNode){

    }

    int auxiliarGetHeight(BinaryTreeNode<T>* currentNode) const{

    }

    /* metodo auxiliar para clonar un arbol desde la entrada por parametro del mismo */
    static BinaryTreeNode<T>* cloneTree(const BinaryTreeNode<T>* currentRecNode){
        /* decidimos implementar un metodo estatico porque la funcion cloneTree() llega a ser llamada en metodos constructores
        como el caso del constructor copia o el operator assign; esto hace que, cuando el metodo cloneTree() es llamado se den
        ocasiones donde el objeto del mismo tipo aun no este completamente inicializado (su root y size tienen valores inexactos
        previo a la finalizacion total de su metodo constructor copia); y, en este caso, el metodo static no depende del estado 
        del objeto, por lo que puede ejecutarse sin errores inesperados durante la construccion del mismo */

        if(!currentRecNode) return NULL /* caso base */
        
        return new BinaryTreeNode<T>( /* reeeeecursion en preorden */
            currentRecNode->getData(), /* proceso raiz */
            cloneTree(currentRecNode->getLeft()), /* recursamos hijo izquierdo */
            cloneTree(currentRecNode->getRight()) /* recursamos hijo derecho */
        );
    } /* O(n) */

    /* metodo auxiliar para llenar un arbol de forma recursiva desde una inOrderList y una preOrderList */
    BinaryTreeNode<T>* buildFromPreIn(
        typename std::list<T>::iterator inOrderBegin,
        typename std::list<T>::iterator inOrderEnd,
        typename std::list<T>::iterator& preOrderIterator){
            if( inOrderBegin == inOrderEnd ) return NULL; /* si los iteradores son iguales (condicion de parada), retornar caso base */
            T currentElement = *preOrderIterator++; /* obtiene el elemento donde apunta el iterador de la lista preorden y aumenta su posicion al siguiente elemento */
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(currentElement); /* genera un nuevo nodo con este dato obtenido (duplicacion) */
            /* ocupamos una busqueda lineal desde el inOrderList */
            typename std::list<T>::iterator iteratorOnPosition = inOrderBegin;
            while (iteratorOnPosition != inOrderEnd && *iteratorOnPosition != currentElement) ++iteratorOnPosition;

            node
        }

    public:

    /* constructores */
    BinaryTree(): root(NULL), size(0) {} /* constructor predeterminado, inicializa en NULL la raiz. O(1) */
    
    BinaryTree(BinaryTreeNode<T>* newRoot): root(newRoot), size(newRoot->getSize()) {} /* constructor con solamente el parametro 
    raiz, calculara el size por si mismo con un metodo auxiliar e inicializara root con el valor enviado por parametro. O(n) */
    
    BinaryTree(int actualTreeSize, BinaryTreeNode<T>* newRoot): size(actualTreeSize), root(newRoot) {} /* constructor ideal. O(1)*/

    BinaryTree(const BinaryTree<T>& originalBinaryTree): root(NULL), size(0) { /* constructor de tipo copia */
        if(originalBinaryTree.isNullNode(originalBinaryTree.getRoot())){ /* si es nula la direccion de memoria enviada por parametro, construye de forma predeterminada*/
            root = NULL;
            size = 0;
        }else { /* reeeeercursion y clonando */
            root = cloneTree(originalBinaryTree.getRoot());
            size = originalBinaryTree.getSize();
        }
    } /* O(1) + O(n) = O(n) */

    /* destructor */
    ~BinaryTree() { this->clear(); } /* O(n) */

    /* asignadores directos */
    BinaryTree<T>& operator=(const BinaryTree<T>& originalBinaryTree){
        if(this != &originalBinaryTree){ /* si la instancia actual es distinta a la direccion de memoria, evita la auto-referencia */
            clear(this->root); /* elimina el arbol existente en la instancia actual para asignar uno nuevo */
            root = cloneTree(originalBinaryTree.getRoot()); /* crea un nuevo nodo raiz que a su vez contiene todos 
            los nodos formados recursivamente con fin a formar un arbol */
            size = originalBinaryTree.getSize(); /* le copia el tamaño de forma muy literal xd */
        }
        return *this;
    } /* O(n) */

    /* getters */

    BinaryTreeNode<T>* getRoot(){ return this->root; } /* O(1) */

    int getSize(){ return this->size; } /* O(1) */

    /* metodos que operan al arbol */

    /* metodo publico para construir un Arbol Binario a partir de dos listas InOrder and PostOrder */
    void buildTreePE(std::list<T> inOrderList, std::list<t> preOrderList){
        if(inOrderList.size() != preOrderList.size() ) return; /* si las listas tienen cantidades de elementos distintos, retornar */

        std::list<T> auxiliarInOrderList = inOrderList;
        std::list<T> auxiliarPreOrderList = preOrderList;

        typename std::list<T>::iterator preOrderIterator = auxiliarPreOrderList.begin();
        root = buildFromPreIn(auxiliarInOrderList.begin(), auxiliarInOrderList.end(), preOrderIterator); /* ocupa el metodo privado, el que hace todo el trabajo recursivo*/
    }

    void buildTreePO((std::list<T> inOrderList, std::list<t> postOrderList){

    }

};
#endif