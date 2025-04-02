#ifndef SINGLYLIST_H
#define SINGLYLIST_H
#include "SinglyNode.h"
#include <stdexcept>

/*METODOS PRIVADOS USADOS EN OTROS METODOS PUBLICOS*/

template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* node) const{

    return node == nullptr;
} /*O(1)*/

template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* firstNode,SinglyNode<T>* secondNode) const{
    return this->isNullNode(firstNode) || this->isNullNode(secondNode);
} /*O(1)*/

/*seccion para actualizar los atributos de la lista (head, tail, length) despues de operaciones de eliminacion o de insercion en cualquier
punto.
    *estos metodos son utilizados por los metodos publicos para mantener consistencia y evitar repeticion de codigo
    *addUpdateLastElement actualiza la tail despues de agregar un nodo al final
    *removeUpdateLastElement actualiza la tail despues de eliminar un nodo al final
    *addUpdateFirstElement actualiza la head despues de agregar un nodo al principio
    *removeUpdateFirstElement actualiza la head despues de eliminar un nodo al principio
    *uniqueElementUpdate actualiza la head y tail, usado en caso que sea el primer elemento
*/

/* precondición: debe verificarse que el puntero pasado por parametro NO sea null */
template <typename T>
void SinglyList<T>::addUpdateLastElement(SinglyNode<T>* newTail){
    this->tail= newTail;
    this->length++;
} /*O(1)*/

/* precondición: debe verificarse que el puntero pasado por parametro NO sea null */
template <typename T>
void SinglyList<T>::removeUpdateLastElement(SinglyNode<T>* newTail){
    this->tail= newTail;
    this->length--;
} /*O(1)*/

/* precondición: debe verificarse que el puntero pasado por parametro NO sea null */
template <typename T>
void SinglyList<T>::addUpdateFirstElement(SinglyNode<T>* newHead){
    this->head= newHead;
    this->length++;
} /*O(1)*/

/* precondición: debe verificarse que el puntero pasado por parametro NO sea null */
template <typename T>
void SinglyList<T>::removeUpdateFirstElement(SinglyNode<T>* newHead){
    this->head= newHead;
    this->length--;
}/*O(1)*/

/* precondición: debe verificarse que el puntero pasado por parametro NO sea null */
template <typename T>
void SinglyList<T>::uniqueElementUpdate(SinglyNode<T>* newHead, SinglyNode<T>* newTail){
            this->head = newHead;
            this->tail = newTail;
            this->length = 1;
} /*O(1)*/

template <typename T>
void SinglyList<T>::emptyElementsUpdate(){
    this->length=0; 
    this->head= nullptr;
    this->tail= nullptr;
} /*O(1)*/

/* seccion de metodos privados del mergesort */

/* precondición: head no debe ser nullptr (a menos que la lista este vacia) */
template <typename T>
SinglyNode<T>* SinglyList<T>::mergeSortRec(SinglyNode<T>* head){
    /* si la lista esta vacia o tiene un solo elemento, ya esta ordenada. */
    if (isNullNode(head) || isNullNode(head->getNext())){
        return head;
    }

    /* divide la lista en dos mitades */
    SinglyNode<T>* middle = getMiddle(head);
    SinglyNode<T>* nextOfMiddle = middle->getNext();
    middle->setNext(nullptr); /* separa la lista en dos mitades: head -> middle y nextOfMiddle -> tail */

    /* ordena recursivamente ambas mitades */
    SinglyNode<T>* left = mergeSortRec(head);
    SinglyNode<T>* right = mergeSortRec(nextOfMiddle);

    /* une las mitades ordenadas*/
    return sortedMerge(left, right);
} /*O(n log n)*/

/* precondición: head no debe ser nullptr (a menos que la lista este vacia) */
template <typename T>
SinglyNode<T>* SinglyList<T>::getMiddle(SinglyNode<T>* head){
    /* si la lista esta vacia devolvera nullptr */
    if (isNullNode(head)){
        return nullptr;
    }

    /* usamos dos punteros: slow avanza un nodo a la vez, fast avanza dos nodos a la vez */
    SinglyNode<T>* slow = head;       
    SinglyNode<T>* fast = head;       

    /* avanzamos hasta que fast llegue al final de la lista */
    while (!isNullNode(fast->getNext()) && !isNullNode(fast->getNext()->getNext())){
        // fast->getNext() no es nullptr, por lo que fast->getNext()->getNext() es seguro
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    /*si fast llego al final, slow esta en el medio*/
    return slow;
} /*O(n)*/

/* precondición: left y right deben ser listas ordenadas */
template <typename T>
SinglyNode<T>* SinglyList<T>::sortedMerge(SinglyNode<T>* left, SinglyNode<T>* right) {
    /* si una de las listas es nullptr, devuelve la otra */
    if (isNullNode(left)) {
        return right;
    }
    if (isNullNode(right)) {
        return left;
    }

    /* nodo ficticio para simplificar la fusión */
    SinglyNode<T> dummy;
    SinglyNode<T>* tail = &dummy;

    /* fusiona ambas listas mientras haya elementos en ambas */
    while (!isNullNode(left) && !isNullNode(right)) {
        if (left->getData() <= right->getData()) {
            tail->setNext(left);
            left = left->getNext();
        } else {
            tail->setNext(right);
            right = right->getNext();
        }
        tail = tail->getNext();
    }

    /* conecta con la lista no vacía */
    if (!isNullNode(left)) {
        tail->setNext(left);
    } else {
        tail->setNext(right);
    }

    /* devuelve la lista fusionada, excluyendo el nodo ficticio */
    return dummy.getNext();
} /* O(n + m) */

/* METODOS PUBLICOS */

/* constructores */

/* constructor base: inicializa una lista vacia con longitud 0 y punteros head y tail nulos al no existir elementos */
template <typename T>
SinglyList<T>::SinglyList(): length(0), head(nullptr), tail(nullptr){} /* O(1) */

/* constructor de tipo copia: */
template <typename T>
SinglyList<T>::SinglyList(const SinglyList<T>& other) : length{0}, head{nullptr}, tail{nullptr} {
    SinglyNode<T>* current = other.head;
    while (current != nullptr) {
        this->addToEnd(current->getData());
        current = current->getNext();
    }
} /* O(n) */

/* destructor: libera la memoria de todos los nodos de la lista */
template <typename T>
SinglyList<T>::~SinglyList(){
    this->clear();
} /* O(n) */

/* getters */
template <typename T>
SinglyNode<T>* SinglyList<T>::getHead() const{ return (this->head); } /* O(1) */

template <typename T>
SinglyNode<T>* SinglyList<T>::getTail() const{ return (this->tail); } /* O(1) */

template <typename T>
int SinglyList<T>::getLength() const{ return (this->length); } /* O(1) */

/* metodos que operan la lista */

/* añadir un elemento en... */

/* agrega un nuevo elemento al principio de la lista 
precondición: newElement debe ser un valor valido de tipo T. */
template <typename T>
void SinglyList<T>::addToStart(T newElement){
    /* construye el nodo con el elemento nuevo a insertar */
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);
    /* verifica si la lista esta vacia */
    if(this->isEmpty()){ 
        /* si esta vacia, el nuevo nodo sera tanto el head como el tail */
        this->uniqueElementUpdate(newNode,newNode);
    }else {
        /* conecta al nuevo nodo en el principio de la lista */
        newNode->setNext(this->head);
        /* actualiza el head para que apunte al nuevo nodo */
        this->addUpdateFirstElement(newNode);
    }
} /* O(1) */

/* agrega un nuevo elemento al principio de la lista 
precondición: newElement debe ser un valor valido de tipo T. */
template <typename T>
void SinglyList<T>::addToEnd(T newElement){
    /* construye el nodo con el elemento nuevo a insertar */
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);
    /* verifica si la lista esta vacia */
    if(this->isEmpty()){
        /* si esta vacia, el nuevo nodo sera tanto el head como el tail */
        this->uniqueElementUpdate(newNode,newNode);
    }else {
        /* conecta el nuevo nodo al final de la lista */
        this->tail->setNext(newNode);
        /* actualiza el tail para que apunte al nuevo nodo */
        this->addUpdateLastElement(newNode);
    }
} /* O(1) */

/* agrega un nuevo elemento después del elemento en la posición indexElement
precondición: newElement debe ser un valor valido de tipo T. */
template <typename T>
void SinglyList<T>::addAtPosition(int indexElement, T newElement) {
    /* verifica si la lista esta vacia */
    if (this->isEmpty()) {
        /* si esta vacia, crea el nodo y actualiza head y tail */
        SinglyNode<T>* newNode = new SinglyNode<T>(newElement);
        this->uniqueElementUpdate(newNode, newNode);
    } else {
        /* si el indice es menor o igual a 0, inserta al principio */
        if (indexElement <= 0) {
            this->addToStart(newElement);
        }
        /* si el indice es mayor o igual a la longitud, inserta al final */
        else if (indexElement >= this->length) {
            this->addToEnd(newElement);
        }
        /* caso general: inserta en la posicion deseada */
        else {
            /* construye el nodo con el nuevo elemento */
            SinglyNode<T>* newNode = new SinglyNode<T>(newElement);

            /* busca el nodo previo a la posicion deseada */
            SinglyNode<T>* prevNode = this->findElement(indexElement - 1);

            /* conecta el nuevo nodo a la lista */
            newNode->setNext(prevNode->getNext());
            prevNode->setNext(newNode);

            /* incrementa la longitud de la lista */
            this->length++;
        }
    }
} /* O(n) */

/*eliminar un elemento en...*/

/*remueve el primer elemento de la lista*/
template <typename T>
void SinglyList<T>::removeFromStart() {
    /* verifica si la lista esta vacia */
    if (!this->isEmpty()) {
        /* guarda el nodo que se va a eliminar (el primer nodo) */
        SinglyNode<T>* nodeToRemove = this->head;

        /* actualiza el head para que apunte al siguiente nodo */
        this->head = this->head->getNext();

        /* si la lista queda vacia despues de la eliminacion, actualiza tail a nullptr */
        if (this->head == nullptr) {
            this->tail = nullptr;
        }

        /* libera la memoria del nodo eliminado */
        delete nodeToRemove;

        /* reduce la longitud de la lista - 1 */
        this->length--;
    }
} /* O(1) */

/*remueve el ultimo elemento de la lista*/
template <typename T>
void SinglyList<T>::removeFromEnd() {
    /* verifica si la lista esta vacia */
    if (!this->isEmpty()) {
        /* si la lista tiene un solo nodo */
        if (this->head == this->tail) {
            /* libera la memoria del unico nodo */
            delete this->head;
            /* actualiza head y tail a nullptr */
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            /* si la lista tiene mas de un nodo, busca el nodo anterior al tail */
            SinglyNode<T>* current = this->head;
            while (current->getNext() != this->tail) {
                current = current->getNext();
            }

            /* guarda el nodo que se va a eliminar (el tail actual) */
            SinglyNode<T>* nodeToRemove = this->tail;

            /* actualiza tail para que apunte al nodo anterior */
            this->tail = current;

            /* actualiza el next del nuevo tail a nullptr */
            this->tail->setNext(nullptr);

            /* libera la memoria del nodo eliminado */
            delete nodeToRemove;
        }

        /* reduce la longitud de la lista en 1 */
        this->length--;
    }
} /* O(n) */

/*remueve el elemento indicado*/
template <typename T>
void SinglyList<T>::removeElement(int indexElement) {
    /* verifica si la lista esta vacia */
    if (!this->isEmpty()) {
        /* si el indice es menor o igual a 1, elimina el primer elemento */
        if (indexElement <= 1) {
            this->removeFromStart();
        }
        /* si el indice es mayor o igual a la longitud, elimina el ultimo elemento */
        else if (indexElement >= this->length) {
            this->removeFromEnd();
        }
        /* caso general: elimina el elemento en la posicion indexElement */
        else {
            /* busca el nodo en la posicion (indexElement - 1), que es el nodo anterior al que se desea eliminar */
            SinglyNode<T>* prevNode = this->findElement(indexElement - 1);

            /* guarda el nodo que se va a eliminar (el siguiente al prevNode) */
            SinglyNode<T>* nodeToRemove = prevNode->getNext();

            /* actualiza el next del prevNode para que apunte al nodo siguiente al que se va a eliminar */
            prevNode->setNext(nodeToRemove->getNext());

            /* si el nodo eliminado era el tail, actualiza tail para que apunte al prevNode */
            if (nodeToRemove == this->tail) {
                this->tail = prevNode;
            }

            /* libera la memoria del nodo eliminado */
            delete nodeToRemove;

            /* reduce la longitud de la lista en 1 */
            this->length--;
        }
    }
} /*O(n) */

/*eliminar varios elementos en...*/

template <typename T>
void SinglyList<T>::removeBatchFromStart(int batchRemoveCount) {
    /* verifica si la lista esta vacia */
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /* valida si el numero de elementos a eliminar es valido */
    if (batchRemoveCount < 1 || batchRemoveCount > this->length) {
        throw std::out_of_range("el numero de elementos a eliminar es invalido.");
    }

    /* eliminacion masiva optimizada */
    SinglyNode<T>* current = this->head;
    SinglyNode<T>* newHead = current;

    /* avanza newHead hasta el nodo que sera el nuevo head */
    for (int i = 0; i < batchRemoveCount; ++i) {
        newHead = newHead->next;
    }

    /* libera la memoria de los nodos eliminados */
    while (current != newHead) {
        SinglyNode<T>* temp = current;
        current = current->next;
        delete temp;
        this->length--;  /* actualiza la longitud */
    }

    /* actualiza el head de la lista */
    this->head = newHead;

    /* si la lista queda vacia, actualiza tail a nullptr */
    if (this->head == nullptr) {
        this->tail = nullptr;
    }
}

template <typename T>
void SinglyList<T>::removeBatchFromEnd(int batchRemoveCount) {
    /* verifica si la lista esta vacia */
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /* valida si el numero de elementos a eliminar es valido */
    if (batchRemoveCount < 1 || batchRemoveCount > this->length) {
        throw std::out_of_range("el numero de elementos a eliminar es invalido.");
    }

    /* encuentra el nuevo tail */
    SinglyNode<T>* newTail = this->head;
    int targetPosition = this->length - batchRemoveCount - 1;

    for (int i = 0; i < targetPosition; ++i) {
        newTail = newTail->next;
    }

    /* liberar nodos desde newTail->next hasta tail */
    while (newTail->next && newTail->next != this->tail) {
        SinglyNode<T>* temp = newTail->next;
        newTail->next = temp->next;
        delete temp;
        this->length--;
    }

    /* eliminar el tail actual y actualizar el nuevo tail */
    delete this->tail;
    if (newTail) {
        this->tail = newTail;
        this->tail->next = nullptr;
    } else {
        this->head = this->tail = nullptr;  
    }
    this->length -= batchRemoveCount;
}

template <typename T>
void SinglyList<T>::removeBatchBeforeElement(int indexElement) {
    /* verifica si la lista esta vacia */
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /* valida si el indice esta fuera de rango */
    if (indexElement <= 0 || indexElement >= this->length) {
        throw std::out_of_range("el indice esta fuera de rango: " + std::to_string(indexElement));
    }

    /* encuentra el nodo objetivo y su predecesor en una sola pasada */
    SinglyNode<T>* current = this->head;
    for (int i = 0; i < indexElement; ++i) {
        current = current->next;
    }

    /* eliminacion masiva optimizada */
    SinglyNode<T>* oldHead = this->head;
    this->head = current; /* nuevo head es el nodo objetivo */

    /* libera la memoria de los nodos eliminados */
    while (oldHead != current) {
        SinglyNode<T>* temp = oldHead;
        oldHead = oldHead->next;
        delete temp;
        this->length--;  /* actualiza la longitud */
    }

    /* si la lista queda vacia, actualiza tail a nullptr */
    if (this->head == nullptr) {
        this->tail = nullptr;
    }
}

template <typename T>
void SinglyList<T>::removeBatchAfterElement(int indexElement) {
    /* verifica si la lista esta vacia */
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /* valida si el indice esta fuera de rango */
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("el indice esta fuera de rango: " + std::to_string(indexElement));
    }

    /* encuentra el nodo en la posicion indexElement */
    SinglyNode<T>* current = this->head;
    for (int i = 0; i < indexElement; ++i) {
        current = current->next;
    }

    /* si no hay elementos despues del nodo actual, no hay nada que eliminar */
    if (current->next == nullptr) {
        return;
    }

    /* eliminacion masiva optimizada */
    SinglyNode<T>* nodeToDelete = current->next;

    /* libera la memoria de los nodos eliminados */
    while (nodeToDelete != nullptr) {
        SinglyNode<T>* temp = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
        delete temp;
        this->length--;  /* actualiza la longitud */
    }

    /* actualiza el next del nodo actual */
    current->next = nullptr;

    /* si el nodo actual era el penultimo, actualiza tail */
    if (current->next == nullptr) {
        this->tail = current;
    }
}

    /*actualizar elementos de manera indirecta, desde un indexador...*/

/*actualiza un elemento desde el indice especificado*/

template <typename T>
void SinglyList<T>::updateElement(int indexElement, T newElement) {
    /*busca el nodo en la posicion indexElement*/
    SinglyNode<T>* nodeToUpdate = this->findElement(indexElement);
    /*actualiza el dato del nodo*/
    nodeToUpdate->setData(newElement);
}

/*actualiza un conjunto de elementos, inicia en un indice y modifica este + los elementos antes de este*/

template <typename T>
void SinglyList<T>::updateBatchBefore(int indexElement, const std::vector<T>& newElements) {
    /*verifica si el vector de elementos esta vacio*/
    if (newElements.empty()) {
        throw std::invalid_argument("El vector de elementos no puede estar vacío.");
    }

    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("La lista está vacía.");
    }

    /*valida si el índice es válido*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    int k = newElements.size();
    int startIndex = indexElement - (k - 1);

    /*verifica si hay suficientes elementos antes del índice*/
    if (startIndex < 0) {
        throw std::out_of_range("No hay suficientes elementos antes del índice.");
    }

    /*busca el nodo en la posición startIndex*/
    SinglyNode<T>* current = this->findElement(startIndex);

    /*recorre k nodos actualizando sus datos*/
    for (int i = 0; i < k; ++i) {
        current->setData(newElements[i]);
        current = current->getNext();
    }
}

/*actualiza un conjunto de elementos, inicia en un indice y modifica este + los elementos despues de este*/

template <typename T>
void SinglyList<T>::updateBatchAfter(int indexElement, const std::vector<T>& newElements) {
    /*verifica si el vector de elementos esta vacio*/
    if (newElements.empty()) {
        throw std::invalid_argument("El vector de elementos no puede estar vacío.");
    }

    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("La lista está vacía.");
    }

    /*valida si el índice es válido*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("Índice fuera de rango.");
    }

    int k = newElements.size();
    int endIndex = indexElement + k - 1;

    /*verifica si hay suficientes elementos después del índice*/
    if (endIndex >= this->length) {
        throw std::out_of_range("No hay suficientes elementos después del índice.");
    }

    /*busca el nodo en la posición indexElement*/
    SinglyNode<T>* current = this->findElement(indexElement);

    /*recorre k nodos actualizando sus datos*/
    for (int i = 0; i < k; ++i) {
        current->setData(newElements[i]);
        current = current->getNext();
    }
}

/*busqueda*/

/*devuelve el elemento una vez le entregas un index*/
template <typename T>
SinglyNode<T>* SinglyList<T>::findElement(int index) const {
    /*valida si el indice esta fuera de rango*/
    if (index < 0 || index >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }
    
    /*recorre la lista hasta llegar al indice solicitado*/
    SinglyNode<T>* current = this->head;
    for (int i = 0; i < index; ++i) {
        current = current->getNext();
    }
    return current;
}

/*devuelve el index una vez le entregas un elemento*/
template <typename T>
int SinglyList<T>::findIndex(T element) const {
    /*recorre la lista buscando la primera coincidencia*/
    SinglyNode<T>* current = this->head;
    int index = 0;
    while (current != nullptr) {
        if (current->getData() == element) {
            return index;
        }
        current = current->getNext();
        index++;
    }
    /*devuelve -1 si no se encuentra el elemento*/
    return -1;
}

/*devuelve los apuntadores en formato vector a los datos requeridos*/
template <typename T>
std::vector<SinglyNode<T>*> SinglyList<T>::findAllElementsPointers(T element) const {
    /*vector para almacenar los punteros coincidentes*/
    std::vector<SinglyNode<T>*> pointers;
    
    /*recorre toda la lista*/
    SinglyNode<T>* current = this->head;
    while (current != nullptr) {
        if (current->getData() == element) {
            pointers.push_back(current);
        }
        current = current->getNext();
    }
    return pointers;
}

/*devuelve los indexadores en formato vector a los datos requeridos*/
template <typename T>
std::vector<int> SinglyList<T>::findAllElementsIndices(T element) const {
    /*vector para almacenar los indices coincidentes*/
    std::vector<int> indices;
    
    /*recorre toda la lista con un contador de indices*/
    SinglyNode<T>* current = this->head;
    int index = 0;
    while (current != nullptr) {
        if (current->getData() == element) {
            indices.push_back(index);
        }
        current = current->getNext();
        index++;
    }
    return indices;
}

     /*utilidades*/

/*verifica si la lista está vacía*/
template <typename T>
bool SinglyList<T>::isEmpty() const{ return (this->length == 0); }

/*limpia la lista*/
template <typename T>
void SinglyList<T>::clear() {
    /*recorre la lista liberando la memoria de cada nodo*/
    SinglyNode<T>* current = this->head;
    while (current != nullptr) {
        SinglyNode<T>* temp = current;
        current = current->getNext();
        delete temp;
    }
    /*actualiza head y tail a nullptr y la longitud a 0*/
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

    /*copiado*/

/*duplica la lista, creando una nueva instancia desde una instancia existente*/
template <typename T>
SinglyList<T>* SinglyList<T>::copyToList() const {
    /*crea una nueva lista vacia*/
    SinglyList<T>* newList = new SinglyList<T>();

    /*recorre todos los nodos de la lista original*/
    SinglyNode<T>* current = this->head;
    while (current != nullptr) {
        /*añade una copia del dato actual a la nueva lista*/
        newList->addToEnd(current->getData());
        current = current->getNext();
    }

    return newList;
}

/*duplica la lista, creando un vector desde la instancia existente*/
template <typename T>
std::vector<T> SinglyList<T>::copyToVector() const {
    std::vector<T> result;

    /*recorre todos los nodos de la lista*/
    SinglyNode<T>* current = this->head;
    while (current != nullptr) {
        /*copia el dato al vector*/
        result.push_back(current->getData());
        current = current->getNext();
    }

    return result;
}

/*crea una copia compartida del elemento, es decir apuntan ambos a los mismos nodos*/
template <typename T>
SinglyList<T>* SinglyList<T>::shallowCopy() const {
    /*crea una nueva lista sin copiar los nodos*/
    SinglyList<T>* newList = new SinglyList<T>();

    /*comparte los mismos nodos que la lista original*/
    newList->head = this->head;
    newList->tail = this->tail;
    newList->length = this->length;

    return newList;
}

    /*movilidad*/

/*rueda los elementos a la derecha segun k de veces deseada*/
template <typename T>
void SinglyList<T>::rotateRight(int k) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede rotar, la lista esta vacia.");
    }

    /*k no puede ser negativo o mayor a length*/
    if (k < 0) {
        throw std::invalid_argument("k no puede ser negativo: " + std::to_string(k));
    }

    /*calcula la rotacion efectiva*/
    int effective_k = k % this->length;
    if (effective_k == 0) {
        throw std::invalid_argument("no se puede rotar 0 veces o un multiplo del tamaño de la lista.");
    }

    /*encuentra el nuevo tail (posicion length - effective_k - 1)*/
    SinglyNode<T>* new_tail = this->head;
    for (int i = 0; i < this->length - effective_k - 1; ++i) {
        new_tail = new_tail->getNext();
    }

    /*actualiza referencias*/
    SinglyNode<T>* new_head = new_tail->getNext();
    this->tail->setNext(this->head);  //conecta el final con el inicio original
    this->head = new_head;            //nuevo head
    this->tail = new_tail;            //nuevo tail
    this->tail->setNext(nullptr);     //cierra la lista
}

/*rueda los elementos a la izquierda segun k de veces deseada*/
template <typename T>
void SinglyList<T>::rotateLeft(int k) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede rotar, la lista esta vacia.");
    }

    /*k no puede ser negativo o mayor a length*/
    if (k < 0) {
        throw std::invalid_argument("k no puede ser negativo: " + std::to_string(k));
    }

    /*calcula la rotacion efectiva*/
    int effective_k = k % this->length;
    if (effective_k == 0) {
        throw std::invalid_argument("no se puede rotar 0 veces o un multiplo del tamaño de la lista.");
    }

    /*encuentra el nuevo tail (posicion effective_k - 1)*/
    SinglyNode<T>* new_tail = this->head;
    for (int i = 0; i < effective_k - 1; ++i) {
        new_tail = new_tail->getNext();
    }

    /*actualiza referencias*/
    SinglyNode<T>* new_head = new_tail->getNext();
    this->tail->setNext(this->head);  //conecta el final con el inicio original
    this->head = new_head;            //nuevo head
    this->tail = new_tail;            //nuevo tail
    this->tail->setNext(nullptr);     //cierra la lista
}

/*invierte el orden de elementos de la lista*/
template <typename T>
void SinglyList<T>::reverseList() {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("no se puede invertir, la lista esta vacia.");
    }

    /*caso trivial: un solo elemento (no requiere accion)*/
    if (this->head->getNext() == nullptr) {
        throw std::logic_error("no se puede invertir una lista con un solo elemento.");
    }

    SinglyNode<T>* prev = nullptr;     
    SinglyNode<T>* current = this->head; 
    SinglyNode<T>* next = nullptr;     
    SinglyNode<T>* originalHead = this->head; 

    while (current != nullptr) {
        next = current->getNext();    
        current->setNext(prev);        
        prev = current;               
        current = next;               
    }

    this->head = prev;          
    this->tail = originalHead;  
}

/*mueve un elemento indexado al principio*/
template <typename T>
void SinglyList<T>::moveToFront(int indexElement) {
    /*verifica lista vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("la lista esta vacia.");
    }

    /*valida indice*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*si ya es el primer elemento*/
    if (indexElement == 0) {
        throw std::logic_error("el elemento ya esta en la primera posicion.");
    }

    /*busca el nodo objetivo y su anterior*/
    SinglyNode<T>* prevNode = this->findElement(indexElement - 1);
    SinglyNode<T>* targetNode = prevNode->getNext();

    /*desvincula el nodo de su posicion actual*/
    prevNode->setNext(targetNode->getNext());

    /*si el nodo era el tail, actualiza tail*/
    if (targetNode == this->tail) {
        this->tail = prevNode;
    }

    /*vincula el nodo al inicio*/
    targetNode->setNext(this->head);
    this->head = targetNode;
}

/*mueve un elemento especificado al final*/
template <typename T>
void SinglyList<T>::moveToEnd(int indexElement) {
    /*verifica lista vacia*/
    if (this->isEmpty()) {
        throw std::out_of_range("la lista esta vacia.");
    }

    /*valida indice*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*si ya es el ultimo elemento*/
    if (indexElement == this->length - 1) {
        throw std::logic_error("el elemento ya esta en la ultima posicion.");
    }

    /*busca el nodo objetivo y su anterior*/
    SinglyNode<T>* prevNode = nullptr;
    SinglyNode<T>* targetNode = this->head;

    if (indexElement != 0) {
        prevNode = this->findElement(indexElement - 1);
        targetNode = prevNode->getNext();
    }

    /*desvincula el nodo*/
    if (prevNode) {
        prevNode->setNext(targetNode->getNext());
    } else {
        this->head = targetNode->getNext();  //caso cuando es el primer elemento
    }

    /*vincula al final*/
    this->tail->setNext(targetNode);
    this->tail = targetNode;
    targetNode->setNext(nullptr);
}

/*intercambia dos nodos en la lista*/
template <typename T>
void SinglyList<T>::swapNodes(int indexOne, int indexTwo) {
    /*verifica indices validos*/
    if (indexOne < 0 || indexOne >= this->length || 
        indexTwo < 0 || indexTwo >= this->length) {
        throw std::out_of_range("indices fuera de rango.");
    }

    /*no hacer nada si son iguales*/
    if (indexOne == indexTwo) return;

    /*asegura indexOne < indexTwo para simplificar logica*/
    if (indexOne > indexTwo) {
        std::swap(indexOne, indexTwo);
    }

    /*busca nodos y sus anteriores*/
    SinglyNode<T>* prevNode1 = (indexOne == 0) ? nullptr : this->findElement(indexOne - 1);
    SinglyNode<T>* node1 = (prevNode1) ? prevNode1->getNext() : this->head;

    SinglyNode<T>* prevNode2 = this->findElement(indexTwo - 1);  //indexTwo > indexOne >= 0
    SinglyNode<T>* node2 = prevNode2->getNext();

    /*caso especial: nodos adyacentes*/
    if (node1->getNext() == node2) {
        /*actualiza enlaces de nodos anteriores*/
        if (prevNode1) {
            prevNode1->setNext(node2);
        } else {
            this->head = node2;
        }

        /*intercambia los nodos adyacentes*/
        node1->setNext(node2->getNext());
        node2->setNext(node1);

        /*actualiza tail si es necesario*/
        if (node2 == this->tail) {
            this->tail = node1;
        }
    } else {
        /*nodos no adyacentes: actualiza enlaces anteriores*/
        if (prevNode1) {
            prevNode1->setNext(node2);
        } else {
            this->head = node2;
        }

        prevNode2->setNext(node1);

        /*intercambia los next de los nodos*/
        SinglyNode<T>* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);

        /*actualiza tail si node2 era el ultimo*/
        if (node2 == this->tail) {
            this->tail = node1;
        } else if (node1 == this->tail) {
            this->tail = node2;
        }
    }
}

#endif
