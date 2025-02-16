#ifndef SINGLYLIST_H
#define SINGLYLIST_H
#include "SinglyNode.h"
#include <vector>

template <typename T>

class SinglyList{
    /*atributos*/
    SinglyNode<T>* head; /*apuntador al primer elemento de la lista*/
    SinglyNode<T>* tail; /*apuntador al ultimo elemento de la lista*/
    int length; /*numero de elementos que contiene la lista*/

    /*metodos privados usados dentro de otros metodos publicos*/
    bool isNullNode(SinglyNode<T>* node) const; /*verifica que un puntero sea null o no*/
    bool isNullNode(SinglyNode<T>* firstNode,SinglyNode<T>* secondNode) const; /*sobrecarga con dos*/
    void addUpdateLastElement(SinglyNode<T>* newTail); /*actualiza el length++ y *tail */
    void removeUpdateLastElement(SinglyNode<T>* newTail); /*actualiza el length-- y *tail */
    void addUpdateFirstElement(SinglyNode<T>* newHead); /*actualiza el length++ y el *head */
    void removeUpdateFirstElement(SinglyNode<T>* newHead); /*actualiza el length-- y el *head */
    void uniqueElementUpdate(SinglyNode<T>* newHead, SinglyNode<T>* newTail); /*actualiza una vez length y el *head *tail*/
    void emptyElementsUpdate(); /*actualiza el length=0 y *head *tail a nullptr */

    /* metodos privados para el mergesort*/
    SinglyNode<T>* mergeSortRec(SinglyNode<T>* head);
    SinglyNode<T>* getMiddle(SinglyNode<T>* head);
    SinglyNode<T>* sortedMerge(SinglyNode<T>* left, SinglyNode<T>* right);

    public:
    /*constructor*/
    SinglyList(); /*inicializa en todo cero definido*/
    SinglyList(const SinglyList<T>& other); /*constructor de copia, crea una nueva lista con distintos apuntadores de memoria*/
    

    /*destructor*/
    ~SinglyList(); /*definido para evitar fugas de memoria*/

    /*getters*/
    SinglyNode<T>* getHead() const;
    SinglyNode<T>* getTail() const;
    int getLength() const; 

    /*no posee setters porque todo es definido exclusivamente en la lista no modificable por otra parte del codigo*/

    /*metodos que operan a la lista*/

    /*añadir un elemento en...*/
    void addToStart(T newElement); /*añade al principio de la lista, y actualiza a través de addUpdateFirstElement()*/
    void addToEnd(T newElement); /*añade al final de la lista, y actualiza a través de addUpdateLastElement()*/
    void addBeforeElement(int indexElement, T newElement); /*añade antes de algún elemento en específico*/
    void addAfterElement(int indexElement, T newElement); /*añade después de algún elemento en específico*/

    /*añadir varios elementos en...*/
    void addBatchToStart(const std::vector<T>& newElements); /*recibe un conjunto de elementos desde un array y los añade en conjunto al inicio, hace que vector[0] sea el primer elemento donde apunta list*/
    void addBatchToEnd(const std::vector<T>& newElements); /*recibe un conjunto de elementos donde vector[n] es el ultimo elemento que apunta a nullptr*/
    void addBatchToBeforeElement(int indexElement, const std::vector<T>& newElements); /*recibe un conjunto de elementos dónde vector[0] es apuntado por el elemento anterior del punto de inicio*/
    void addBatchToAfterElement(int indexElement, const std::vector<T>& newElements);  /*recibe un conjunto de elementos dónde vector[0] es apuntado por el elemento del punto de inicio*/

    /*eliminar un elemento en...*/
    void removeFromStart(); /*remueve el primer elemento de la lista*/
    void removeFromEnd(); /*remueve el ultimo elemento de la lista*/
    void removeElement(int indexElement); /*remueve el elemento indicado*/
    void removeBeforeElement(int indexElement); /*remueve el elemento anterior al indicado*/
    void removeAfterElement(int indexElement); /*remueve el elemento posterior al indicado*/

    /*eliminar varios elementos en...*/
    void removeBatchFromStart(int batchRemoveCount); /*O()remueve n cantidad de elementos desde el inicio hasta el fin*/
    void removeBatchFromEnd(int batchRemoveCount); /*remueve n cantidad de elementos desde el fin hasta el inicio*/
    void removeBatchBeforeElement(int indexElement); /*remueve todos los elementos anteriores a un elemento en específico*/
    void removeBatchAfterElement(int indexElement); /*remueve todos los elementos posteriores aun elemento en específico*/

    /*actualizar elementos de manera indirecta, desde un indexador...*/
    void updateElement(int indexElement, T newElement); /*actualiza un elemento desde el indice especificado*/
    void updateBatchBefore(int indexElement, const std::vector<T> &newElements); /*actualiza un conjunto de elementos, inicia en un indice y modifica este + los elementos antes de este*/
    void updateBatchAfter(int indexElement, const std::vector<T> &newElements); /*actualiza un conjunto de elementos, inicia en un indice y modifica este + los elementos despues de este*/

    /*busqueda*/
    SinglyNode<T>* findElement(int index) const; /*devuelve el elemento una vez le entregas un index*/
    int findIndex(T element) const; /*devuelve el index una vez le entregas un elemento*/
    vector<SinglyNode<T>*> findAllElementsPointers(T element) const; /*devuelve los apuntadores en formato vector a los datos requeridos*/
    vector<int> findAllElementsIndices(T element) const; /*devuelve los indexadores en formato vector a los datos requeridos*/

    /*utilidades*/
    bool isEmpty() const; /*verifica si la lista esta vacia*/
    void clear(); /*elimina los elementos de la lista*/

    /*copiado*/
    SinglyList<T>* copyToList() const; /*duplica la lista, creando una nueva instancia desde una instancia existente*/
    vector<T> copyToVector() const; /*duplica la lista, creando un vector desde la instancia existente*/
    SinglyList<T>* shallowCopy() const; /*crea una copia compartida del elemento, es decir apuntan ambos a los mismos nodos*/
    
    /*movilidad*/
    void rotateRight(int k); /*rueda los elementos a la derecha segun k de veces deseada*/
    void rotateLeft(int k); /*rueda los elementos a la izquierda segun k de veces deseada*/
    void reverseList(); /*invierte el orden de elementos de la lista*/
    void moveToFront(int indexElement); /*mueve un elemento indexado al principio, da igual si existen elementos duplicados*/
    void moveToEnd(int indexElement); /*mueve un elemento especificado al final, da igual si existen elementos duplicados*/
    void swapNodes(int indexOne, int indexTwo); /*intercambia dos nodos en la lista*/
    void moveNodeToIndex(int currentIndex, int newIndex); /*mueve un nodo indexado a una posicion requerida*/
    pair<SinglyList<T>, SinglyList<T>> splitList(int index) const; /*divide la lista actual en dos sublistas*/
    void mergeList(const SinglyList<T> otherList); /*une una lista con otra actual*/
    void mergeSort(); /*ordena la lista. O(n * log n)*/

};

#endif