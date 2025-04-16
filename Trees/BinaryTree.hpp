#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "../Node/BinaryTreeNode.hpp"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>

template <typename T>
class BinaryTree {
protected:
    BinaryTreeNode<T>* root; /* puntero al nodo raiz del arbol */
    int size;               /* cantidad total de nodos en el arbol */

    /* verifica si un nodo es nulo */
    bool isNullNode(BinaryTreeNode<T>* node) const {
        return node == NULL; /* compara el puntero con NULL y retorna true si son iguales */
    }

    /* verifica si alguno de dos nodos es nulo */
    bool isNullNode(BinaryTreeNode<T>* firstNode, BinaryTreeNode<T>* secondNode) const {
        return isNullNode(firstNode) /* verifica si el primer nodo es nulo */ 
               || isNullNode(secondNode); /* o si el segundo nodo es nulo */
    }

    /* inserta un subarbol en la posicion especificada */
    BinaryTreeNode<T>* auxiliarInsertSubTree(BinaryTreeNode<T>* currentNode, BinaryTreeNode<T>* subTreeRoot, bool left) {
        if(!subTreeRoot) return currentNode; /* si el subarbol a insertar es nulo, retorna el nodo actual sin cambios */
        
        if(!currentNode) { /* si el nodo actual es nulo */
            int subTreeSize = countNodes(subTreeRoot); /* cuenta los nodos del subarbol a insertar */
            if(size > INT_MAX - subTreeSize) return currentNode; /* evita desbordamiento de enteros */
            size += subTreeSize; /* actualiza el tamaño total del arbol */
            return cloneTree(subTreeRoot); /* retorna una copia del subarbol */
        }
        
        if(left) { /* si se debe insertar a la izquierda */
            currentNode->setLeft(auxiliarInsertSubTree(currentNode->getLeft(), subTreeRoot, left)); /* inserta recursivamente en el subarbol izquierdo */
        } else { /* si se debe insertar a la derecha */
            currentNode->setRight(auxiliarInsertSubTree(currentNode->getRight(), subTreeRoot, left)); /* inserta recursivamente en el subarbol derecho */
        }
        
        return currentNode; /* retorna el nodo actual con los cambios realizados */
    }

    /* elimina el subarbol izquierdo y actualiza el tamaño */
    void removeLeftSubTree() {
        if(isEmpty()) return; /* si el arbol esta vacio, no hay nada que eliminar */
        BinaryTreeNode<T>* leftBranch = root->getLeft(); /* obtiene el subarbol izquierdo */
        if(leftBranch) { /* si existe el subarbol izquierdo */
            int removed = countNodes(leftBranch); /* cuenta cuantos nodos se van a eliminar */
            auxiliarClear(leftBranch); /* elimina todos los nodos del subarbol izquierdo */
            root->setLeft(NULL); /* desvincula el subarbol izquierdo de la raiz */
            size = (size > removed) ? size - removed : 0; /* actualiza el tamaño total */
        }
    }

    /* elimina el subarbol derecho y actualiza el tamaño */
    void removeRightSubTree() {
        if(isEmpty()) return; /* si el arbol esta vacio, no hay nada que eliminar */
        BinaryTreeNode<T>* rightBranch = root->getRight(); /* obtiene el subarbol derecho */
        if(rightBranch) { /* si existe el subarbol derecho */
            int removed = countNodes(rightBranch); /* cuenta cuantos nodos se van a eliminar */
            auxiliarClear(rightBranch); /* elimina todos los nodos del subarbol derecho */
            root->setRight(NULL); /* desvincula el subarbol derecho de la raiz */
            size = (size > removed) ? size - removed : 0; /* actualiza el tamaño total */
        }
    }

    /* cuenta los nodos en un subarbol */
    int countNodes(BinaryTreeNode<T>* node) const {
        if(!node) return 0; /* si el nodo es nulo, retorna 0 */
        return 1 /* cuenta el nodo actual */ 
               + countNodes(node->getLeft()) /* suma los nodos del subarbol izquierdo */
               + countNodes(node->getRight()); /* suma los nodos del subarbol derecho */
    }

    /* elimina un nodo con el dato especificado */
    BinaryTreeNode<T>* auxiliarRemove(BinaryTreeNode<T>* currentNode, const T& dataToDelete) {
        if(!currentNode) return NULL; /* si el nodo actual es nulo, retorna nulo */
        
        if(currentNode->getData() == dataToDelete) { /* si encontramos el nodo a eliminar */
            if(!currentNode->getLeft()) { /* si no tiene hijo izquierdo */
                BinaryTreeNode<T>* temp = currentNode->getRight(); /* guardamos el hijo derecho */
                delete currentNode; /* liberamos la memoria del nodo actual */
                size = (size > 0) ? size - 1 : 0; /* actualizamos el tamaño */
                return temp; /* retornamos el hijo derecho para reemplazar al nodo eliminado */
            } else if(!currentNode->getRight()) { /* si no tiene hijo derecho */
                BinaryTreeNode<T>* temp = currentNode->getLeft(); /* guardamos el hijo izquierdo */
                delete currentNode; /* liberamos la memoria del nodo actual */
                size = (size > 0) ? size - 1 : 0; /* actualizamos el tamaño */
                return temp; /* retornamos el hijo izquierdo para reemplazar al nodo eliminado */
            }
            
            /* si el nodo tiene ambos hijos */
            BinaryTreeNode<T>* temp = currentNode->getLeft(); /* empezamos por el hijo izquierdo */
            while(temp->getRight()) { /* buscamos el nodo mas a la derecha en el subarbol izquierdo */
                temp = temp->getRight(); /* avanzamos al siguiente hijo derecho */
            }
            currentNode->setData(temp->getData()); /* copiamos el dato del nodo encontrado */
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), temp->getData())); /* eliminamos el nodo duplicado */
        } else { /* si no es el nodo que buscamos */
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), dataToDelete)); /* buscamos en el subarbol izquierdo */
            currentNode->setRight(auxiliarRemove(currentNode->getRight(), dataToDelete)); /* buscamos en el subarbol derecho */
        }
        return currentNode; /* retornamos el nodo actual */
    }

    /* elimina todos los nodos del arbol */
    void auxiliarClear(BinaryTreeNode<T>* currentNode) {
        if(!currentNode) return; /* si el nodo es nulo, terminamos la recursion */
        auxiliarClear(currentNode->getLeft()); /* eliminamos el subarbol izquierdo */
        auxiliarClear(currentNode->getRight()); /* eliminamos el subarbol derecho */
        delete currentNode; /* liberamos la memoria del nodo actual */
        size = (size > 0) ? size - 1 : 0; /* actualizamos el tamaño */
    }

    /* calcula la altura del arbol */
    int auxiliarGetHeight(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return 0; /* si el nodo es nulo, su altura es 0 */
        return 1 /* contamos el nodo actual */ 
               + std::max(auxiliarGetHeight(currentNode->getLeft()), /* altura del subarbol izquierdo */
                         auxiliarGetHeight(currentNode->getRight())); /* altura del subarbol derecho */
    }

    /* cuenta la cantidad de hojas en el arbol */
    int auxiliarCountLeaves(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return 0; /* si el nodo es nulo, no es una hoja */
        if(!currentNode->getLeft() && !currentNode->getRight()) return 1; /* si no tiene hijos, es una hoja */
        return auxiliarCountLeaves(currentNode->getLeft()) /* contamos hojas en subarbol izquierdo */
               + auxiliarCountLeaves(currentNode->getRight()); /* contamos hojas en subarbol derecho */
    }

    /* obtiene los valores de las hojas del arbol */
    void auxiliarGetLeaves(BinaryTreeNode<T>* currentNode, std::list<T>& leavesList) const {
        if(!currentNode) return; /* si el nodo es nulo, terminamos la recursion */
        
        if(!currentNode->getLeft() && !currentNode->getRight()) { /* si es una hoja */
            leavesList.push_back(currentNode->getData()); /* agregamos su dato a la lista */
            return; /* terminamos esta rama de recursion */
        }
        
        auxiliarGetLeaves(currentNode->getLeft(), leavesList); /* buscamos hojas en subarbol izquierdo */
        auxiliarGetLeaves(currentNode->getRight(), leavesList); /* buscamos hojas en subarbol derecho */
    }

    /* clona un arbol recursivamente */
    static BinaryTreeNode<T>* cloneTree(const BinaryTreeNode<T>* currentRecNode) {
        if(!currentRecNode) return NULL; /* si el nodo es nulo, retornamos nulo */
        
        return new BinaryTreeNode<T>( /* creamos un nuevo nodo con */
            currentRecNode->getData(), /* el mismo dato */
            cloneTree(currentRecNode->getLeft()), /* clon del subarbol izquierdo */
            cloneTree(currentRecNode->getRight()) /* clon del subarbol derecho */
        );
    }

    /* calcula la suma de todos los valores del arbol */
    T auxiliarGetWeight(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return T(); /* si el nodo es nulo, retorna valor por defecto */
        return currentNode->getData() /* valor del nodo actual */
               + auxiliarGetWeight(currentNode->getLeft()) /* suma de subarbol izquierdo */
               + auxiliarGetWeight(currentNode->getRight()); /* suma de subarbol derecho */
    }

    /* busca un subarbol dentro del arbol */
    bool findSubTree(BinaryTreeNode<T>* current, BinaryTreeNode<T>* subRoot) const {
        if(!subRoot) return true; /* un arbol vacio siempre esta contenido */
        if(!current) return false; /* si el arbol actual es vacio y el buscado no, no esta contenido */
        
        if(current->getData() == subRoot->getData()) { /* si coinciden los nodos raices */
            return findSubTree(current->getLeft(), subRoot->getLeft()) /* comparar subarbol izquierdo */
                   && findSubTree(current->getRight(), subRoot->getRight()); /* y subarbol derecho */
        }
        return findSubTree(current->getLeft(), subRoot) /* buscar en subarbol izquierdo */
               || findSubTree(current->getRight(), subRoot); /* o en subarbol derecho */
    }

public:
    /* constructores */
    
    /* constructor predeterminado */
    BinaryTree() : root(NULL), size(0) {} /* inicializacion normal, promedio */
    
    /* constructor con valor inicial */
    BinaryTree(const T& rootData) : root(new BinaryTreeNode<T>(rootData)), size(1) {} /* inicializa con un dato */
    
    /* constructor copia */
    BinaryTree(const BinaryTree<T>& originalBinaryTree) : root(NULL), size(0) { /* inicializa predeterminado */
        if(!originalBinaryTree.isEmpty()) { /* si el arbol del parametro tiene contenido */
            root = cloneTree(originalBinaryTree.root); /* clona el arbol hasta la raiz */
            size = originalBinaryTree.size; /* obtiene el elemento actual, directo */
        }
    }

    /* destructor */
    ~BinaryTree() {
        clear(); /* limpia todos y cada uno de los nodos */
    }

    /* operador de asignacion, esto es utilizado para que puedan permitirse asignaciones directas
    entre mismos tipos de datos, de forma que miArbol = otroArbol sea directo y genere una copie real
    y efectiva */
    BinaryTree<T>& operator=(const BinaryTree<T>& originalBinaryTree) { 
        if(this != &originalBinaryTree) { /* evita la auto-asignacion */
            clear(); /* limpia el arbol actual */
            if(!originalBinaryTree.isEmpty()) { /* si el arbol pasado por parametro tiene contenido, procede a copiar */
                root = cloneTree(originalBinaryTree.root); /* clona */
                size = originalBinaryTree.size; /* clona */
            }
        }
        return *this;
    }

    /* getters basicos */
    
    /* obtiene el dato de la raiz */
    T getRoot() const {
        if(isEmpty()) return T(); /* si esta vacio, retorna el dato predeterminado */
        return root->getData(); /* retorna el real */
    }
    
    /* obtiene la cantidad de nodos */
    int getSize() const {
        return size; /* retorna el tama;o */
    }

    /* metodos de insercion */
    
    /* inserta un subarbol completo */
    void insertSubTree(const BinaryTree<T>& subTree, bool left) {
        root = auxiliarInsertSubTree(root, subTree.root, left); 
    }

    /* metodos de eliminacion */
    
    /* elimina subarboles condicionalmente */
    void removeSubTree(bool left, bool right) {
        if(left) removeLeftSubTree();
        if(right) removeRightSubTree();
    }
    
    /* elimina un nodo con el dato especificado */
    void remove(const T& data) {
        root = auxiliarRemove(root, data);
    }
    
    /* elimina todos los nodos del arbol */
    void clear() {
        auxiliarClear(root);
        root = NULL;
        size = 0;
    }

    /* metodos de consulta */
    
    /* obtiene la altura del arbol */
    int getHeight() const {
        return auxiliarGetHeight(root);
    }
    
    /* cuenta la cantidad de hojas */
    int countLeaves() const {
        return auxiliarCountLeaves(root);
    }
    
    /* obtiene una lista con los valores de las hojas */
    std::list<T> getLeaves() const {
        std::list<T> leavesList;
        auxiliarGetLeaves(root, leavesList);
        return leavesList;
    }
    
    /* calcula la suma de todos los valores */
    T getWeight() const {
        return auxiliarGetWeight(root);
    }
    
    /* verifica si contiene un valor */
    bool contains(const T& data) const {
        if(isEmpty()) return false;
        
        std::queue<BinaryTreeNode<T>*> auxiliarQueue;
        auxiliarQueue.push(root);
        
        while(!auxiliarQueue.empty()) {
            BinaryTreeNode<T>* current = auxiliarQueue.front();
            auxiliarQueue.pop();
            
            if(current->getData() == data) return true;
            
            if(current->getLeft()) auxiliarQueue.push(current->getLeft());
            if(current->getRight()) auxiliarQueue.push(current->getRight());
        }
        return false;
    }
    
    /* verifica si contiene un subarbol */
    bool containsSubTree(const BinaryTree<T>& subTree) const {
        if(subTree.isEmpty()) return true;
        if(isEmpty()) return false;
        return findSubTree(root, subTree.root);
    }

    /* metodos para obtener subarboles */
    
    /* obtiene el subarbol izquierdo */
    BinaryTree<T> getLeft() const {
        BinaryTree<T> leftTree;
        if(!isEmpty() && root->getLeft()) {
            leftTree.root = cloneTree(root->getLeft());
            leftTree.size = countNodes(leftTree.root);
        }
        return leftTree;
    }
    
    /* obtiene el subarbol derecho */
    BinaryTree<T> getRight() const {
        BinaryTree<T> rightTree;
        if(!isEmpty() && root->getRight()) {
            rightTree.root = cloneTree(root->getRight());
            rightTree.size = countNodes(rightTree.root);
        }
        return rightTree;
    }

    /* metodos de verificacion */
    
    /* verifica si el arbol esta vacio */
    bool isEmpty() const {
        return root == NULL;
    }

    /* aplica una funcion a todos los nodos */
    template <typename Function>
    void forEach(Function f) const {
        if(isEmpty()) return;
        
        std::queue<BinaryTreeNode<T>*> auxiliarQueue;
        auxiliarQueue.push(root);
        
        while(!auxiliarQueue.empty()) {
            BinaryTreeNode<T>* current = auxiliarQueue.front();
            auxiliarQueue.pop();
            
            f(current->getData());
            
            if(current->getLeft()) auxiliarQueue.push(current->getLeft());
            if(current->getRight()) auxiliarQueue.push(current->getRight());
        }
    }
};

#endif