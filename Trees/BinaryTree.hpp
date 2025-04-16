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
    BinaryTreeNode<T>* root; /* apuntador a la raiz de un arbol */
    int size; /* cantidad de nodos existentes en un arbol */

    /* metodos restringidos; su uso es permitido dentro de la misma clase por otros metodos publicos */

    /* verifica si un nodo es nuloo */
    bool isNullNode(BinaryTreeNode<T>* node) const {
        /* simplemente comprueba si el puntero es NULL */
        return node == NULL;
    } /* O(1) */

    /* verifica si alguno de dos nodos es nulo */
    bool isNullNode(BinaryTreeNode<T>* firstNode, BinaryTreeNode<T>* secondNode) const {
        /* reutiliza isNullNode para ambos nodos */
        return isNullNode(firstNode) || isNullNode(secondNode);
    } /* O(1) */

    /* metodo auxiliar para insertar un subarbol en una posicion especifica */
    BinaryTreeNode<T>* auxiliarInsertSubTree(BinaryTreeNode<T>* currentNode, BinaryTreeNode<T>* subTreeRoot, bool left) {
        /* si el subarbol a insertar es nulo, no hacemos nada */
        if(!subTreeRoot) return currentNode;
        
        /* si el nodo actual es nulo, clonamos todo el subarbol */
        if(!currentNode) {
            /* calculamos el tamaño del subarbol a insertar */
            int subTreeSize = countNodes(subTreeRoot);
            /* prevencion de desbordamiento */
            if(size > INT_MAX - subTreeSize) return currentNode; /* no insertar si excede */
            /* actualizamos el tamaño total */
            size += subTreeSize;
            /* devolvemos una copia completa del subarbol */
            return cloneTree(subTreeRoot);
        }
        
        /* decidimos en que rama insertar segun el parametro left */
        if(left) {
            /* insertamos en la rama izquierda recursivamente */
            currentNode->setLeft(auxiliarInsertSubTree(currentNode->getLeft(), subTreeRoot, left));
        } else {
            /* insertamos en la rama derecha recursivamente */
            currentNode->setRight(auxiliarInsertSubTree(currentNode->getRight(), subTreeRoot, left));
        }
        
        /* devolvemos el nodo actual modificado */
        return currentNode;
    } /* O(n) donde n es el tamaño del subarbol a insertar */

    /* metodo auxiliar para eliminar un subarbol y actualizar el tamaño */
    void auxiliarRemoveSubTree(BinaryTreeNode<T>*& subTreeRoot) {
        /* si el subarbol es nulo, no hay nada que hacer */
        if(!subTreeRoot) return;
        
        /* contamos los nodos que vamos a eliminar */
        int nodesToRemove = countNodes(subTreeRoot);
        /* eliminamos todos los nodos del subarbol */
        auxiliarClear(subTreeRoot);
        /* marcamos la raiz como nula */
        subTreeRoot = NULL;
        /* actualizamos el tamaño total con prevencion de underflow */
        size = (size > nodesToRemove) ? size - nodesToRemove : 0;
    } /* O(n) donde n es el tamaño del subarbol a eliminar */

    /* metodo auxiliar para contar nodos en un subarbol */
    int countNodes(BinaryTreeNode<T>* node) const {
        /* si el nodo es nulo, no contribuye al conteo */
        if(!node) return 0;
        /* cuenta este nodo + los de sus subarboles izquierdo y derecho */
        return 1 + countNodes(node->getLeft()) + countNodes(node->getRight());
    } /* O(n) */

    /* metodo auxiliar para eliminar un nodo especifico del arbol */
    BinaryTreeNode<T>* auxiliarRemove(BinaryTreeNode<T>* currentNode, const T& dataToDelete) {
        /* si llegamos a un nodo nulo, no hay nada que hacer */
        if(!currentNode) return NULL;
        
        /* si encontramos el nodo con el dato a eliminar */
        if(currentNode->getData() == dataToDelete) {
            /* caso 1: nodo con solo hijo derecho o sin hijos */
            if(!currentNode->getLeft()) {
                /* guardamos el hijo derecho */
                BinaryTreeNode<T>* temp = currentNode->getRight();
                /* eliminamos el nodo actual */
                delete currentNode;
                /* actualizamos el tamaño con prevencion de underflow */
                size = (size > 0) ? size - 1 : 0;
                /* devolvemos el hijo derecho para reconectar */
                return temp;
            } else if(!currentNode->getRight()) {
                /* caso 2: nodo con solo hijo izquierdo */
                BinaryTreeNode<T>* temp = currentNode->getLeft();
                /* eliminamos el nodo actual */
                delete currentNode;
                /* actualizamos el tamaño */
                size = (size > 0) ? size - 1 : 0;
                /* devolvemos el hijo izquierdo para reconectar */
                return temp;
            }
            
            /* caso 3: nodo con dos hijos */
            /* buscamos el nodo mas a la derecha del subarbol izquierdo */
            BinaryTreeNode<T>* temp = currentNode->getLeft();
            while(temp->getRight()) {
                temp = temp->getRight();
            }
            /* copiamos el dato del sucesor */
            currentNode->setData(temp->getData());
            /* eliminamos el sucesor del subarbol izquierdo */
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), temp->getData()));
        } else {
            /* si no es el nodo buscado, seguimos buscando en ambos subarboles */
            currentNode->setLeft(auxiliarRemove(currentNode->getLeft(), dataToDelete));
            currentNode->setRight(auxiliarRemove(currentNode->getRight(), dataToDelete));
        }
        /* devolvemos el nodo actual (posiblemente modificado) */
        return currentNode;
    } /* O(n) */

    /* metodo auxiliar para eliminar todos los nodos del arbol */
    void auxiliarClear(BinaryTreeNode<T>* currentNode) {
        /* si el nodo es nulo, terminamos la recursion */
        if(!currentNode) return;
        /* primero eliminamos los subarboles izquierdo y derecho */
        auxiliarClear(currentNode->getLeft());
        auxiliarClear(currentNode->getRight());
        /* luego eliminamos el nodo actual */
        delete currentNode;
        /* actualizamos el tamaño con prevencion de underflow */
        size = (size > 0) ? size - 1 : 0;
    } /* O(n) */

    /* metodo auxiliar para calcular la altura del arbol */
    int auxiliarGetHeight(BinaryTreeNode<T>* currentNode) const {
        /* la altura de un arbol nulo es 0 */
        if(!currentNode) return 0;
        /* la altura es 1 + la maxima altura de sus subarboles */
        return 1 + std::max(auxiliarGetHeight(currentNode->getLeft()),
                            auxiliarGetHeight(currentNode->getRight()));
    } /* O(n) */

    /* metodo auxiliar para contar la cantidad de hojas en el arbol */
    int auxiliarCountLeaves(BinaryTreeNode<T>* currentNode) const {
        /* un arbol nulo no tiene hojas */
        if(!currentNode) return 0;
        /* si no tiene hijos, es una hoja */
        if(!currentNode->getLeft() && !currentNode->getRight()) return 1;
        /* sumamos las hojas de ambos subarboles */
        return auxiliarCountLeaves(currentNode->getLeft()) + 
               auxiliarCountLeaves(currentNode->getRight());
    } /* O(n) */

    /* metodo auxiliar para obtener una lista con todas las hojas del arbol */
    void auxiliarGetLeaves(BinaryTreeNode<T>* currentNode, std::list<T>& leavesList) const {
        /* si el nodo es nulo, no hacemos nada */
        if(!currentNode) return;
        
        /* si es una hoja, añadimos su dato a la lista */
        if(!currentNode->getLeft() && !currentNode->getRight()) {
            leavesList.push_back(currentNode->getData());
            return;
        }
        
        /* buscamos hojas en ambos subarboles */
        auxiliarGetLeaves(currentNode->getLeft(), leavesList);
        auxiliarGetLeaves(currentNode->getRight(), leavesList);
    } /* O(n) */

    /* metodo auxiliar para clonar un arbol */
    static BinaryTreeNode<T>* cloneTree(const BinaryTreeNode<T>* currentRecNode) {
        /* si el nodo es nulo, no hay nada que clonar */
        if(!currentRecNode) return NULL;
        
        /* creamos un nuevo nodo con el mismo dato y clonamos sus subarboles */
        return new BinaryTreeNode<T>(
            currentRecNode->getData(),
            cloneTree(currentRecNode->getLeft()),
            cloneTree(currentRecNode->getRight())
        );
    } /* O(n) */

    /* metodo auxiliar para calcular el peso del arbol */
    T auxiliarGetWeight(BinaryTreeNode<T>* currentNode) const {
        /* el peso de un arbol nulo es el valor por defecto */
        if(!currentNode) return T();
        /* sumamos el dato actual + pesos de subarboles */
        return currentNode->getData() + 
               auxiliarGetWeight(currentNode->getLeft()) + 
               auxiliarGetWeight(currentNode->getRight());
    } /* O(n) */

    /* metodo auxiliar para buscar un subarbol dentro del arbol */
    bool findSubTree(BinaryTreeNode<T>* current, BinaryTreeNode<T>* subRoot) const {
        /* un subarbol vacio siempre esta contenido */
        if(!subRoot) return true;
        /* un arbol vacio no puede contener un subarbol no vacio */
        if(!current) return false;
        
        /* si encontramos una coincidencia en la raiz */
        if(current->getData() == subRoot->getData()) {
            /* verificamos que los subarboles tambien coincidan */
            return findSubTree(current->getLeft(), subRoot->getLeft()) && 
                   findSubTree(current->getRight(), subRoot->getRight());
        }
        /* si no coincide, seguimos buscando en los subarboles */
        return findSubTree(current->getLeft(), subRoot) || 
               findSubTree(current->getRight(), subRoot);
    } /* O(n*m) donde n es tamaño del arbol y m del subarbol */

    /* estructura auxiliar para removeSubTree */
    struct RemoveHelper {
        BinaryTree<T>* tree;
        /* constructor que recibe el arbol al que pertenece */
        RemoveHelper(BinaryTree<T>* t) : tree(t) {}
        
        /* operador de llamada para eliminar condicionalmente */
        void operator()(bool condition, BinaryTreeNode<T>*& branch) {
            /* si se cumple la condicion y la rama existe */
            if(condition && branch) {
                /* contamos los nodos a eliminar */
                int removed = tree->countNodes(branch);
                /* eliminamos la rama */
                tree->auxiliarClear(branch);
                /* marcamos como nula */
                branch = NULL;
                /* actualizamos el tamaño con prevencion de underflow */
                tree->size = (tree->size > removed) ? tree->size - removed : 0;
            }
        }
    };

public:
    /* constructores */
    
    /* constructor predeterminado, inicializa arbol vacio */
    BinaryTree() : root(NULL), size(0) {} /* O(1) */
    
    /* constructor con valor inicial para la raiz */
    BinaryTree(const T& rootData) : root(new BinaryTreeNode<T>(rootData)), size(1) {} /* O(1) */
    
    /* constructor copia */
    BinaryTree(const BinaryTree<T>& originalBinaryTree) : root(NULL), size(0) {
        /* solo copiamos si el arbol original no esta vacio */
        if(!originalBinaryTree.isEmpty()) {
            /* clonamos toda la estructura */
            root = cloneTree(originalBinaryTree.root);
            /* copiamos el tamaño */
            size = originalBinaryTree.size;
        }
    } /* O(n) */

    /* destructor */
    ~BinaryTree() {
        /* liberamos toda la memoria */
        clear();
    } /* O(n) */

    /* operador de asignacion */
    BinaryTree<T>& operator=(const BinaryTree<T>& originalBinaryTree) {
        /* prevencion de auto-asignacion */
        if(this != &originalBinaryTree) {
            /* limpiamos el arbol actual */
            clear();
            /* si el original no esta vacio */
            if(!originalBinaryTree.isEmpty()) {
                /* clonamos toda la estructura */
                root = cloneTree(originalBinaryTree.root);
                /* copiamos el tamaño */
                size = originalBinaryTree.size;
            }
        }
        /* devolvemos este objeto para encadenamiento */
        return *this;
    } /* O(n) */

    /* getters basicos */
    
    /* obtiene el dato almacenado en la raiz del arbol */
    T getRoot() const {
        /* si el arbol esta vacio, devuelve valor por defecto */
        if(isEmpty()) return T();
        /* devuelve el dato de la raiz */
        return root->getData();
    } /* O(1) */
    
    /* obtiene la cantidad de nodos en el arbol */
    int getSize() const {
        /* simplemente devuelve el contador */
        return size;
    } /* O(1) */

    /* metodos de insercion */
    
    /* inserta un subarbol completo como hijo izquierdo o derecho */
    void insertSubTree(const BinaryTree<T>& subTree, bool left) {
        /* delega en el metodo auxiliar */
        root = auxiliarInsertSubTree(root, subTree.root, left);
    } /* O(n) donde n es el tamaño del subarbol */

    /* metodos de eliminacion */
    
    /* elimina subarboles segun los parametros left y right */
    void removeSubTree(bool left, bool right) {
        /* si el arbol esta vacio, no hay nada que hacer */
        if(isEmpty()) return;
        
        /* creamos el ayudante de eliminacion */
        RemoveHelper remover(this);
        /* eliminamos las ramas segun los parametros */
        remover(left, root->getLeft());
        remover(right, root->getRight());
    } /* O(n) donde n es el tamaño de los subarboles a eliminar */
    
    /* elimina un nodo con el dato especificado */
    void remove(const T& data) {
        /* delega en el metodo auxiliar */
        root = auxiliarRemove(root, data);
    } /* O(n) */
    
    /* elimina todos los nodos del arbol */
    void clear() {
        /* delega en el metodo auxiliar */
        auxiliarClear(root);
        /* marca la raiz como nula */
        root = NULL;
        /* reinicia el contador */
        size = 0;
    } /* O(n) */

    /* metodos de consulta */
    
    /* obtiene la altura del arbol */
    int getHeight() const {
        /* delega en el metodo auxiliar */
        return auxiliarGetHeight(root);
    } /* O(n) */
    
    /* cuenta la cantidad de hojas en el arbol */
    int countLeaves() const {
        /* delega en el metodo auxiliar */
        return auxiliarCountLeaves(root);
    } /* O(n) */
    
    /* obtiene una lista con los valores de todas las hojas */
    std::list<T> getLeaves() const {
        /* crea una lista vacia */
        std::list<T> leavesList;
        /* la llena con los datos de las hojas */
        auxiliarGetLeaves(root, leavesList);
        /* devuelve la lista */
        return leavesList;
    } /* O(n) */
    
    /* calcula el peso del arbol (suma de todos los valores) */
    T getWeight() const {
        /* delega en el metodo auxiliar */
        return auxiliarGetWeight(root);
    } /* O(n) */
    
    /* verifica si el arbol contiene un valor especifico */
    bool contains(const T& data) const {
        /* arbol vacio no contiene nada */
        if(isEmpty()) return false;
        
        /* usamos una cola para el recorrido por niveles */
        std::queue<BinaryTreeNode<T>*> q;
        q.push(root);
        
        /* mientras haya nodos por procesar */
        while(!q.empty()) {
            /* tomamos el siguiente nodo */
            BinaryTreeNode<T>* current = q.front();
            q.pop();
            
            /* si encontramos el dato, devolvemos true */
            if(current->getData() == data) return true;
            
            /* añadimos los hijos a la cola si existen */
            if(current->getLeft()) q.push(current->getLeft());
            if(current->getRight()) q.push(current->getRight());
        }
        /* si no se encontro, devolvemos false */
        return false;
    } /* O(n) */
    
    /* verifica si el arbol contiene un subarbol especifico */
    bool containsSubTree(const BinaryTree<T>& subTree) const {
        /* un subarbol vacio siempre esta contenido */
        if(subTree.isEmpty()) return true;
        /* un arbol vacio no contiene subarboles no vacios */
        if(isEmpty()) return false;
        /* delega en el metodo auxiliar de busqueda */
        return findSubTree(root, subTree.root);
    } /* O(n*m) */

    /* metodos para obtener subarboles */
    
    /* obtiene el subarbol izquierdo */
    BinaryTree<T> getLeft() const {
        /* crea un arbol vacio */
        BinaryTree<T> leftTree;
        /* si el arbol actual no esta vacio y tiene hijo izquierdo */
        if(!isEmpty() && root->getLeft()) {
            /* clona el subarbol izquierdo */
            leftTree.root = cloneTree(root->getLeft());
            /* calcula su tamaño */
            leftTree.size = countNodes(leftTree.root);
        }
        /* devuelve el subarbol */
        return leftTree;
    } /* O(n) */
    
    /* obtiene el subarbol derecho */
    BinaryTree<T> getRight() const {
        /* crea un arbol vacio */
        BinaryTree<T> rightTree;
        /* si el arbol actual no esta vacio y tiene hijo derecho */
        if(!isEmpty() && root->getRight()) {
            /* clona el subarbol derecho */
            rightTree.root = cloneTree(root->getRight());
            /* calcula su tamaño */
            rightTree.size = countNodes(rightTree.root);
        }
        /* devuelve el subarbol */
        return rightTree;
    } /* O(n) */

    /* metodos de verificacion */
    
    /* verifica si el arbol esta vacio */
    bool isEmpty() const {
        /* simplemente comprueba si la raiz es nula */
        return root == NULL;
    } /* O(1) */

    /* metodo para aplicar una funcion a todos los nodos */
    template <typename Function>
    void forEach(Function f) const {
        /* si el arbol esta vacio, no hay nada que hacer */
        if(isEmpty()) return;
        
        /* usamos una cola auxiliar para el recorrido por niveles */
        std::queue<BinaryTreeNode<T>*> auxiliarQueue;
        auxiliarQueue.push(root);
        
        /* mientras haya nodos por procesar */
        while(!auxiliarQueue.empty()) {
            /* tomamos el siguiente nodo */
            BinaryTreeNode<T>* current = auxiliarQueue.front();
            auxiliarQueue.pop();
            
            /* aplicamos la funcion al dato del nodo */
            f(current->getData());
            
            /* añadimos los hijos a la cola si existen */
            if(current->getLeft()) auxiliarQueue.push(current->getLeft());
            if(current->getRight()) auxiliarQueue.push(current->getRight());
        }
    } /* O(n) */
};

#endif