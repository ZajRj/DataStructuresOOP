#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "../Node/BinaryTreeNode.hpp"
#include <iostream>
#include <list>

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

    BinaryTreeNode<T>* getRoot(){ return this->root; }

    int getSize(){ return this->size; }

    /* metodos que operan al arbol */

    void buildTreePE(std::list<T>){

    }

    void buildTreePO()

};
#endif