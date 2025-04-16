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
    /* atributos de la clase */
    BinaryTreeNode<T>* root; /* apuntador a la raiz del arbol */
    int size; /* cantidad de nodos en el arbol */

    /* metodos restringidos; su uso es permitido dentro de la misma clase por otros metodos publicos */

    /*  verifica si un nodo es nulo, recibe un puntero al nodo a verificar y retorna 
    true si es nulo, false si no */
    bool isNullNode(BinaryTreeNode<T>* node) const {
        return node == NULL;
    }

    /* verifica si alguno de dos nodos es nulo, firstNode es el primer nodo a verificar y secondNode
     el segundo nodo a verificar, retorna true si alguno es nulo, false si ambos son validos */
    bool isNullNode(BinaryTreeNode<T>* firstNode, BinaryTreeNode<T>* secondNode) const {
        return isNullNode(firstNode) || isNullNode(secondNode);
    }

    /* inserta un subarbol en la posicion especificada, currentNode es el nodo actual en la recursion el parametro subTreeRoot
     es la raiz del subarbol a insertar, left indica si se inserta a la izquierda (true) o derecha (false), 
     retorna el puntero al nodo modificado */
    BinaryTreeNode<T>* auxiliarInsertSubTree(BinaryTreeNode<T>* currentNode, BinaryTreeNode<T>* subTreeRoot, bool left) {
        if(!subTreeRoot) return currentNode;
        
        if(!currentNode) {
            int subTreeSize = countNodes(subTreeRoot);
            if(size > INT_MAX - subTreeSize) return currentNode;
            size += subTreeSize;
            return cloneTree(subTreeRoot);
        }
        
        if(left) {
            currentNode->setLeft(auxiliarInsertSubTree(currentNode->getLeft(), subTreeRoot, left));
        } else {
            currentNode->setRight(auxiliarInsertSubTree(currentNode->getRight(), subTreeRoot, left));
        }
        
        return currentNode;
    }

    /* elimina el subarbol izquierdo y actualiza el tamaño */
    void removeLeftSubTree() {
        if(isEmpty()) return;
        BinaryTreeNode<T>* leftBranch = root->getLeft();
        if(leftBranch) {
            int removed = countNodes(leftBranch);
            auxiliarClear(leftBranch);
            root->setLeft(NULL);
            size = (size > removed) ? size - removed : 0;
        }
    }

    /* 
     * elimina el subarbol derecho y actualiza el tamaño
     */
    void removeRightSubTree() {
        if(isEmpty()) return;
        BinaryTreeNode<T>* rightBranch = root->getRight();
        if(rightBranch) {
            int removed = countNodes(rightBranch);
            auxiliarClear(rightBranch);
            root->setRight(NULL);
            size = (size > removed) ? size - removed : 0;
        }
    }

    /* 
     * cuenta los nodos en un subarbol
     * @param node: raiz del subarbol a contar
     * @return: cantidad de nodos en el subarbol
     */
    int countNodes(BinaryTreeNode<T>* node) const {
        if(!node) return 0;
        return 1 + countNodes(node->getLeft()) + countNodes(node->getRight());
    }

    /* 
     * elimina un nodo con el dato especificado
     * @param currentNode: nodo actual en la recursion
     * @param dataToDelete: dato a buscar y eliminar
     * @return: puntero al nodo modificado
     */
    BinaryTreeNode<T>* auxiliarRemove(BinaryTreeNode<T>* currentNode, const T& dataToDelete) {
        if(!currentNode) return NULL;
        
        if(currentNode->getData() == dataToDelete) {
            if(!currentNode->getLeft()) {
                BinaryTreeNode<T>* temp = currentNode->getRight();
                delete currentNode;
                size = (size > 0) ? size - 1 : 0;
                return temp;
            } else if(!currentNode->getRight()) {
                BinaryTreeNode<T>* temp = currentNode->getLeft();
                delete currentNode;
                size = (size > 0) ? size - 1 : 0;
                return temp;
            }
            
            BinaryTreeNode<T>* temp = currentNode->getLeft();
            while(temp->getRight()) {
                temp = temp->getRight();
            }
            currentNode->setData(temp->getData());
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), temp->getData()));
        } else {
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), dataToDelete));
            currentNode->setRight(auxiliarRemove(currentNode->getRight(), dataToDelete));
        }
        return currentNode;
    }

    /* 
     * elimina todos los nodos del arbol
     * @param currentNode: nodo actual en la recursion
     */
    void auxiliarClear(BinaryTreeNode<T>* currentNode) {
        if(!currentNode) return;
        auxiliarClear(currentNode->getLeft());
        auxiliarClear(currentNode->getRight());
        delete currentNode;
        size = (size > 0) ? size - 1 : 0;
    }

    /* 
     * calcula la altura del arbol
     * @param currentNode: nodo actual en la recursion
     * @return: altura del subarbol
     */
    int auxiliarGetHeight(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return 0;
        return 1 + std::max(auxiliarGetHeight(currentNode->getLeft()),
                           auxiliarGetHeight(currentNode->getRight()));
    }

    /* 
     * cuenta la cantidad de hojas en el arbol
     * @param currentNode: nodo actual en la recursion
     * @return: cantidad de hojas en el subarbol
     */
    int auxiliarCountLeaves(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return 0;
        if(!currentNode->getLeft() && !currentNode->getRight()) return 1;
        return auxiliarCountLeaves(currentNode->getLeft()) + 
               auxiliarCountLeaves(currentNode->getRight());
    }

    /* 
     * obtiene los valores de las hojas del arbol
     * @param currentNode: nodo actual en la recursion
     * @param leavesList: lista donde se almacenan los valores
     */
    void auxiliarGetLeaves(BinaryTreeNode<T>* currentNode, std::list<T>& leavesList) const {
        if(!currentNode) return;
        
        if(!currentNode->getLeft() && !currentNode->getRight()) {
            leavesList.push_back(currentNode->getData());
            return;
        }
        
        auxiliarGetLeaves(currentNode->getLeft(), leavesList);
        auxiliarGetLeaves(currentNode->getRight(), leavesList);
    }

    /* 
     * clona un arbol recursivamente
     * @param currentRecNode: nodo actual en la recursion
     * @return: puntero al nuevo nodo clonado
     */
    static BinaryTreeNode<T>* cloneTree(const BinaryTreeNode<T>* currentRecNode) {
        if(!currentRecNode) return NULL;
        
        return new BinaryTreeNode<T>(
            currentRecNode->getData(),
            cloneTree(currentRecNode->getLeft()),
            cloneTree(currentRecNode->getRight())
        );
    }

    /* 
     * calcula la suma de todos los valores del arbol
     * @param currentNode: nodo actual en la recursion
     * @return: suma acumulada de los valores
     */
    T auxiliarGetWeight(BinaryTreeNode<T>* currentNode) const {
        if(!currentNode) return T();
        return currentNode->getData() + 
               auxiliarGetWeight(currentNode->getLeft()) + 
               auxiliarGetWeight(currentNode->getRight());
    }

    /* 
     * busca un subarbol dentro del arbol
     * @param current: nodo actual en el arbol principal
     * @param subRoot: nodo actual en el subarbol buscado
     * @return: true si el subarbol esta contenido, false si no
     */
    bool findSubTree(BinaryTreeNode<T>* current, BinaryTreeNode<T>* subRoot) const {
        if(!subRoot) return true;
        if(!current) return false;
        
        if(current->getData() == subRoot->getData()) {
            return findSubTree(current->getLeft(), subRoot->getLeft()) && 
                   findSubTree(current->getRight(), subRoot->getRight());
        }
        return findSubTree(current->getLeft(), subRoot) || 
               findSubTree(current->getRight(), subRoot);
    }

public:
    /* constructores */
    
    /* constructor predeterminado */
    BinaryTree() : root(NULL), size(0) {}
    
    /* constructor con valor inicial */
    BinaryTree(const T& rootData) : root(new BinaryTreeNode<T>(rootData)), size(1) {}
    
    /* constructor copia */
    BinaryTree(const BinaryTree<T>& originalBinaryTree) : root(NULL), size(0) {
        if(!originalBinaryTree.isEmpty()) {
            root = cloneTree(originalBinaryTree.root);
            size = originalBinaryTree.size;
        }
    }

    /* destructor */
    ~BinaryTree() {
        clear();
    }

    /* operador de asignacion */
    BinaryTree<T>& operator=(const BinaryTree<T>& originalBinaryTree) {
        if(this != &originalBinaryTree) {
            clear();
            if(!originalBinaryTree.isEmpty()) {
                root = cloneTree(originalBinaryTree.root);
                size = originalBinaryTree.size;
            }
        }
        return *this;
    }

    /* getters basicos */
    
    /* obtiene el dato de la raiz */
    T getRoot() const {
        if(isEmpty()) return T();
        return root->getData();
    }
    
    /* obtiene la cantidad de nodos */
    int getSize() const {
        return size;
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