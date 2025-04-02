#include "SinglyList.hpp"
#include <algorithm>

/*metodos privados*/
template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* node) const {
    return node == NULL;
} /*O(1)*/

template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* firstNode,SinglyNode<T>* secondNode) const{
    return this->isNullNode(firstNode) || this->isNullNode(secondNode);
} /*O(1)*/

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
    this->head= NULL;
    this->tail= NULL;
} /*O(1)*/

/* seccion de metodos privados del mergesort */

/* precondición: head no debe ser NULL (a menos que la lista este vacia) */
template <typename T>
SinglyNode<T>* SinglyList<T>::mergeSortRec(SinglyNode<T>* head){
    /* si la lista esta vacia o tiene un solo elemento, ya esta ordenada. */
    if (isNullNode(head) || isNullNode(head->getNext())){
        return head;
    }

    /* divide la lista en dos mitades */
    SinglyNode<T>* middle = getMiddle(head);
    SinglyNode<T>* nextOfMiddle = middle->getNext();
    middle->setNext(NULL); /* separa la lista en dos mitades: head -> middle y nextOfMiddle -> tail */

    /* ordena recursivamente ambas mitades */
    SinglyNode<T>* left = mergeSortRec(head);
    SinglyNode<T>* right = mergeSortRec(nextOfMiddle);

    /* une las mitades ordenadas*/
    return sortedMerge(left, right);
} /*O(n log n)*/

/* precondición: head no debe ser NULL (a menos que la lista este vacia) */
template <typename T>
SinglyNode<T>* SinglyList<T>::getMiddle(SinglyNode<T>* head){
    /* si la lista esta vacia devolvera NULL */
    if (isNullNode(head)){
        return NULL;
    }

    /* usamos dos punteros: slow avanza un nodo a la vez, fast avanza dos nodos a la vez */
    SinglyNode<T>* slow = head;       
    SinglyNode<T>* fast = head;       

    /* avanzamos hasta que fast llegue al final de la lista */
    while (!isNullNode(fast->getNext()) && !isNullNode(fast->getNext()->getNext())){
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    /*si fast llego al final, slow esta en el medio*/
    return slow;
} /*O(n)*/

/* precondición: left y right deben ser listas ordenadas */
template <typename T>
SinglyNode<T>* SinglyList<T>::sortedMerge(SinglyNode<T>* left, SinglyNode<T>* right) {
    /* si una de las listas es NULL, devuelve la otra */
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
SinglyList<T>::SinglyList(): length(0), head(NULL), tail(NULL){} /* O(1) */

/* constructor de tipo copia: */
template <typename T>
SinglyList<T>::SinglyList(const SinglyList<T>& other) : length(0), head(NULL), tail(NULL) {
    SinglyNode<T>* current = other.head;
    while (current != NULL) {
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
            SinglyNode<T>* prevNode = this->findElementP(indexElement - 1);

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

        /* si la lista queda vacia despues de la eliminacion, actualiza tail a NULL */
        if (this->head == NULL) {
            this->tail = NULL;
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
            /* actualiza head y tail a NULL */
            this->head = NULL;
            this->tail = NULL;
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

            /* actualiza el next del nuevo tail a NULL */
            this->tail->setNext(NULL);

            /* libera la memoria del nodo eliminado */
            delete nodeToRemove;
        }

        /* reduce la longitud de la lista en 1 */
        this->length--;
    }
} /* O(n) */

/*remueve el elemento indicado*/
template <typename T>
void SinglyList<T>::removeElementAt(int indexElement) {
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
            SinglyNode<T>* prevNode = this->findElementP(indexElement - 1);

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
    /* verifica si la lista tiene elementos y el numero a eliminar es valido */
    if (!this->isEmpty() && batchRemoveCount >= 1) {
        
        /* si se debe eliminar toda la lista */
        if (batchRemoveCount >= this->length) {
            this->clear();
        }
        /* elimina los primeros batchRemoveCount nodos */
        else {
            /* usa removeFromStart() en un bucle para mejor legibilidad */
            for (int i = 0; i < batchRemoveCount; ++i) {
                this->removeFromStart();  /* O(1) por operacion */
            }
        }
    }
} /*O(k)*/

template <typename T>
void SinglyList<T>::removeBatchFromEnd(int batchRemoveCount) {
    /* verifica si la lista tiene elementos y el numero a eliminar es valido */
    if (!this->isEmpty() && batchRemoveCount >= 1) {
        
        /* si se debe eliminar toda la lista */
        if (batchRemoveCount >= this->length) {
            this->clear();
            return;
        }

        /* calcula cuantos nodos se conservaran */
        int nodesToKeep = this->length - batchRemoveCount;
        
        /* encuentra el nuevo tail (nodo en posicion nodesToKeep-1) */
        SinglyNode<T>* newTail = this->findElementP(nodesToKeep - 1);
        
        /* libera los nodos desde newTail->next hasta tail */
        SinglyNode<T>* current = newTail->next;
        newTail->next = NULL;  // desconecta la parte a eliminar
        
        while (current != NULL) {
            SinglyNode<T>* temp = current;
            current = current->next;
            delete temp;
            this->length--;
        }

        /* actualiza el tail usando removeUpdateLastElement */
        this->removeUpdateLastElement(newTail);
        
        /* si no quedan nodos, actualiza head y tail */
        if (nodesToKeep == 0) {
            this->emptyElementsUpdate();
        }
    }
} /*O(n)*/

template <typename T>
void SinglyList<T>::removeBatchBeforeIndex(int indexElement) {
    /* verifica si la lista tiene elementos y el indice es valido */
    if (!this->isEmpty() && indexElement > 0) {
        
        /* si el indice es mayor o igual al length, limpia toda la lista */
        if (indexElement >= this->length) {
            this->clear();
        }
        /* caso normal: elimina nodos antes del indice */
        else {
            /* encuentra el nodo en la posicion indexElement */
            SinglyNode<T>* newHead = this->findElementP(indexElement);
            
            /* guarda el head actual para liberar memoria */
            SinglyNode<T>* oldHead = this->head;
            
            /* actualiza el head de la lista */
            this->head = newHead;
            
            /* libera los nodos desde el viejo head hasta el nuevo head */
            while (oldHead != newHead) {
                SinglyNode<T>* temp = oldHead;
                oldHead = oldHead->next;
                delete temp;
                this->length--;
            }
            
            /* si la lista quedo vacia, actualiza tail */
            if (this->head == NULL) {
                this->tail = NULL;
            }
        }
    }
} /*O(n)*/

template <typename T>
void SinglyList<T>::removeBatchAfterIndex(int indexElement) {
    /* solo procede si la lista no esta vacia y el indice es valido */
    if (!this->isEmpty() && indexElement >= 0 && indexElement < this->length - 1) {
        
        /* encuentra el nodo en la posicion indexElement */
        SinglyNode<T>* current = this->findElementP(indexElement);
        
        /* si hay nodos despues del actual */
        if (current->next != NULL) {
            /* guarda el primer nodo a eliminar */
            SinglyNode<T>* nodeToDelete = current->next;
            
            /* desconecta la sublista a eliminar */
            current->next = NULL;
            
            /* libera la memoria de los nodos eliminados */
            while (nodeToDelete != NULL) {
                SinglyNode<T>* temp = nodeToDelete;
                nodeToDelete = nodeToDelete->next;
                delete temp;
                this->length--;
            }
            
            /* actualiza el tail usando removeUpdateLastElement */
            this->removeUpdateLastElement(current);
        }
    }
} /*O(n)*/

/*actualizar elementos de manera indirecta, desde un indexador...*/

/*actualiza un elemento desde el indice especificado*/

template <typename T>
void SinglyList<T>::updateElement(int indexElement, T newElement) {
    /* si el indice es menor a 0, actualiza el primer elemento */
    if (indexElement <= 0) {
        if (!this->isEmpty()) {
            this->head->setData(newElement);
        }
    }
    /* si el indice es mayor o igual al length, actualiza el ultimo elemento */
    else if (indexElement >= this->length - 1) {
        if (!this->isEmpty()) {
            this->tail->setData(newElement);
        }
    }
    /* caso normal: actualiza el elemento en la posicion indicada */
    else {
        this->findElementP(indexElement)->setData(newElement);
    }
} /* O(n) en caso normal, O(1) para extremos */

/*actualiza un conjunto de elementos, inicia en un indice y modifica este + los elementos antes de este*/

template <typename T>
void SinglyList<T>::updateBatchBefore(int indexElement, const SinglyList<T>& newElements) {
    /* solo procede si ambas listas tienen elementos */
    if (!this->isEmpty() && !newElements.isEmpty()) {
        
        /* ajusta indice a rango valido */
        int adjustedIndex = indexElement;
        if (indexElement < 0) adjustedIndex = 0;
        if (indexElement >= this->length) adjustedIndex = this->length - 1;

        /* calcula nodos a actualizar */
        int maxUpdate = newElements.getLength();
        int startPos = adjustedIndex - (maxUpdate - 1);
        if (startPos < 0) startPos = 0;

        /* encuentra nodo inicial y recorre ambas listas */
        SinglyNode<T>* currentTarget = this->findElementP(startPos);
        SinglyNode<T>* currentSource = newElements.getHead();

        /* actualiza mientras haya nodos en ambas listas */
        while (currentTarget != NULL && 
               currentSource != NULL && 
               startPos <= adjustedIndex) {
            
            currentTarget->setData(currentSource->getData());
            currentTarget = currentTarget->getNext();
            currentSource = currentSource->getNext();
            startPos++;
        }
    }
} /* O(n + m) */

template <typename T>
void SinglyList<T>::updateBatchAfter(int indexElement, const SinglyList<T>& newElements) {
    /* solo procede si ambas listas tienen elementos */
    if (!this->isEmpty() && !newElements.isEmpty()) {
        
        /* ajusta indice a rango valido */
        int adjustedIndex = indexElement;
        if (indexElement < 0) adjustedIndex = 0;
        if (indexElement >= this->length) adjustedIndex = this->length - 1;

        /* encuentra nodo inicial */
        SinglyNode<T>* currentTarget = this->findElementP(adjustedIndex);
        SinglyNode<T>* currentSource = newElements.getHead();

        /* actualiza mientras haya nodos en ambas listas */
        while (currentTarget != NULL && currentSource != NULL) {
            currentTarget->setData(currentSource->getData());
            currentTarget = currentTarget->getNext();
            currentSource = currentSource->getNext();
        }
    }
} /* O(n + m) */

/*busqueda*/

/*devuelve el puntero elemento una vez le entregas un index*/
template <typename T>
SinglyNode<T>* SinglyList<T>::findElementP(int index) const {
    /* si la lista esta vacia o el indice es invalido, retorna NULL */
    if (this->isEmpty() || index < 0 || index >= this->length) {
        return NULL;
    }

    /* si es el primer elemento */
    if (index == 0) {
        return this->head;
    }

    /* si es el ultimo elemento */
    if (index == this->length - 1) {
        return this->tail;
    }

    /* caso general: busca el nodo en la posicion indicada */
    SinglyNode<T>* current = this->head;
    int currentIndex = 0;
    
    while (current != NULL && currentIndex < index) {
        current = current->getNext();
        currentIndex++;
    }

    return current;
} /*O(n)*/

/*devuelve el elemento una vez le entregas un index*/
template <typename T>
T SinglyList<T>::findElementAt(int index) const {
    /* obtiene el nodo en la posicion indicada */
    SinglyNode<T>* node = this->findElementP(index);
    
    /* si el nodo es valido, retorna su dato */
    if (node != NULL) {
        return node->getData();
    }
    
    /* si el indice es invalido, retorna el valor por defecto de T */
    return T();
}

/*devuelve el index una vez le entregas un elemento*/
template <typename T>
int SinglyList<T>::findIndex(T element) const {
    /* recorre la lista buscando la primera coincidencia */
    SinglyNode<T>* current = this->head;
    int index = 0;
    while (current != NULL) {
        if (current->getData() == element) {
            return index;  /* elemento encontrado */
        }
        current = current->getNext();
        index++;
    }
    /* elemento no encontrado */
    return -1;
} /*O(n)*/

/* devuelve una nueva lista con los nodos que contienen el elemento buscado */
template <typename T>
SinglyList<SinglyNode<T>*> SinglyList<T>::findAllElementsPointers(T element) const {
    /* lista para almacenar los punteros coincidentes */
    SinglyList<SinglyNode<T>*> resultList;
    
    /* recorre toda la lista */
    SinglyNode<T>* current = this->head;
    while (current != NULL) {
        if (current->getData() == element) {
            /* añade el puntero al nodo a la lista resultante */
            resultList.addToEnd(current);
        }
        current = current->getNext();
    }
    return resultList;
} /*O(n)*/

/* devuelve una nueva lista con los indices de los elementos coincidentes */
template <typename T>
SinglyList<int> SinglyList<T>::findAllElementsIndices(T element) const {
    /* lista para almacenar los indices coincidentes */
    SinglyList<int> resultList;
    
    /* recorre toda la lista con un contador de indices */
    SinglyNode<T>* current = this->head;
    int index = 0;
    while (current != NULL) {
        if (current->getData() == element) {
            /* añade el indice a la lista resultante */
            resultList.addToEnd(index);
        }
        current = current->getNext();
        index++;
    }
    return resultList;
} /*O(n)*/

/*utilidades*/

/*verifica si la lista está vacía*/
template <typename T>
bool SinglyList<T>::isEmpty() const{ return (this->length == 0); }

/*limpia la lista*/
template <typename T>
void SinglyList<T>::clear() {
    /* libera la memoria de todos los nodos en O(n) */
    while (this->head != NULL) {
        SinglyNode<T>* temp = this->head;
        this->head = this->head->getNext();
        delete temp;
    }
    /* actualiza el estado de la lista en O(1) */
    this->emptyElementsUpdate();
} /* Complejidad total: O(n) */

/*copiado*/

/*duplica la lista, creando una nueva instancia desde una instancia existente*/
template <typename T>
SinglyList<T>* SinglyList<T>::copyToList() const {
    /* crea una nueva lista vacia - O(1) */
    SinglyList<T>* newList = new SinglyList<T>();
    
    /* optimización para listas vacias - O(1) */
    if (this->isEmpty()) {
        return newList;
    }

    /* pointers para recorrer y construir la nueva lista */
    SinglyNode<T>* originalCurrent = this->head;
    SinglyNode<T>* newCurrent = NULL;

    /* copia el primer elemento - O(1) */
    newList->head = new SinglyNode<T>(originalCurrent->getData());
    newList->length = 1;
    newCurrent = newList->head;

    /* copia los elementos restantes - O(n-1) */
    originalCurrent = originalCurrent->getNext();
    while (originalCurrent != NULL) {
        newCurrent->setNext(new SinglyNode<T>(originalCurrent->getData()));
        newCurrent = newCurrent->getNext();
        newList->length++;
        originalCurrent = originalCurrent->getNext();
    }

    /* establece el tail de la nueva lista - O(1) */
    newList->tail = newCurrent;
    
    return newList;
} /*O(n)*/

/*crea una copia compartida del elemento, es decir apuntan ambos a los mismos nodos*/
template <typename T>
SinglyList<T>* SinglyList<T>::shallowCopy() const {
    /* crea una nueva lista en O(1) */
    SinglyList<T>* newList = new SinglyList<T>();
    
    /* comparte la estructura de nodos existente */
    if (!this->isEmpty()) {
        newList->head = this->head;
        newList->tail = this->tail;
        newList->length = this->length;
    }
    /* si la lista original esta vacia, newList ya esta inicializada correctamente */

    return newList;
} /*O(1)*/

/*movilidad*/

/*rueda los elementos a la derecha segun k de veces deseada*/
template <typename T>
void SinglyList<T>::rotateRight(int k) {
    /* no hace nada si la lista está vacía o tiene un solo elemento */
    if (this->isEmpty() || this->length == 1) {
        return;
    }

    /* ajusta k para evitar rotaciones innecesarias */
    k = k % this->length;
    if (k <= 0) {  /* si k es 0 o negativo, no rotar */
        return;
    }

    /* encuentra el nuevo tail (posición length - k - 1) */
    SinglyNode<T>* new_tail = this->head;
    for (int i = 0; i < this->length - k - 1; ++i) {
        new_tail = new_tail->getNext();
    }

    /* actualiza referencias */
    SinglyNode<T>* new_head = new_tail->getNext();
    this->tail->setNext(this->head);  /* conecta el final con el inicio */
    this->head = new_head;
    this->tail = new_tail;
    this->tail->setNext(NULL);     /* cierra la lista */
} /*O(n)*/

/*rueda los elementos a la izquierda segun k de veces deseada*/
template <typename T>
void SinglyList<T>::rotateLeft(int k) {
    /* no hace nada si la lista está vacía o tiene un solo elemento */
    if (this->isEmpty() || this->length == 1) {
        return;
    }

    /* ajusta k para evitar rotaciones innecesarias */
    k = k % this->length;
    if (k <= 0) {  /* si k es 0 o negativo, no rotar */
        return;
    }

    /* encuentra el nuevo tail (posición k - 1) */
    SinglyNode<T>* new_tail = this->head;
    for (int i = 0; i < k - 1; ++i) {
        new_tail = new_tail->getNext();
    }

    /* actualiza referencias */
    SinglyNode<T>* new_head = new_tail->getNext();
    this->tail->setNext(this->head);  /* conecta el final con el inicio */
    this->head = new_head;
    this->tail = new_tail;
    this->tail->setNext(NULL);     /* cierra la lista */
} /* Complejidad: O(n) */

/*invierte el orden de elementos de la lista*/
template <typename T>
void SinglyList<T>::reverseList() {
    /* solo procede si la lista tiene mas de un elemento */
    if (this->length > 1) {
        SinglyNode<T>* prev = NULL;
        SinglyNode<T>* current = this->head;
        SinglyNode<T>* originalHead = this->head;

        /* invierte los enlaces */
        while (current != NULL) {
            SinglyNode<T>* next = current->getNext();
            current->setNext(prev);
            prev = current;
            current = next;
        }

        /* actualiza head y tail */
        this->head = prev;
        this->tail = originalHead;
    }
    /* si length <= 1, no se hace nada */
} /* O(n) */

/*mueve un elemento indexado al principio*/
template <typename T>
void SinglyList<T>::moveToFront(int indexElement) {
    /* solo procede si la lista tiene elementos y el índice es válido */
    if (!this->isEmpty() && indexElement > 0 && indexElement < this->length) {
        
        /* encuentra el nodo anterior al objetivo */
        SinglyNode<T>* prevNode = this->findElementP(indexElement - 1);
        SinglyNode<T>* targetNode = prevNode->getNext();

        /* desconecta el nodo de su posición actual */
        prevNode->setNext(targetNode->getNext());

        /* actualiza tail si el nodo movido era el último */
        if (targetNode == this->tail) {
            this->tail = prevNode;
        }

        /* mueve el nodo al frente */
        targetNode->setNext(this->head);
        this->head = targetNode;
    }
} /* O(n) */

/*mueve un elemento especificado al final*/
template <typename T>
void SinglyList<T>::moveToEnd(int indexElement) {
    /* solo procede si la lista tiene elementos y el índice es válido */
    if (!this->isEmpty() && indexElement >= 0 && indexElement < this->length - 1) {
        
        /* caso especial: mover head al final */
        if (indexElement == 0) {
            SinglyNode<T>* oldHead = this->head;
            this->head = this->head->getNext();
            this->tail->setNext(oldHead);
            oldHead->setNext(NULL);
            this->tail = oldHead;
        } 
        /* caso general: mover nodo intermedio al final */
        else {
            SinglyNode<T>* prevNode = this->findElementP(indexElement - 1);
            SinglyNode<T>* targetNode = prevNode->getNext();

            /* desconecta el nodo */
            prevNode->setNext(targetNode->getNext());

            /* mueve al final */
            this->tail->setNext(targetNode);
            targetNode->setNext(NULL);
            this->tail = targetNode;
        }
    }
} /* O(n) */

/*intercambia dos nodos en la lista*/
template <typename T>
void SinglyList<T>::swapNodes(int indexOne, int indexTwo) {
    /* solo procede si la lista tiene al menos 2 elementos */
    if (this->length < 2) return;

    /* ajusta índices para que indexOne <= indexTwo */
    if (indexOne > indexTwo) {
        std::swap(indexOne, indexTwo);
    }

    /* verifica índices válidos */
    if (indexOne < 0 || indexTwo >= this->length) return;
    if (indexOne == indexTwo) return;

    /* encuentra nodos y sus anteriores */
    SinglyNode<T>* prevNode1 = (indexOne == 0) ? NULL : this->findElementP(indexOne - 1);
    SinglyNode<T>* node1 = (prevNode1) ? prevNode1->getNext() : this->head;

    SinglyNode<T>* prevNode2 = this->findElementP(indexTwo - 1);
    SinglyNode<T>* node2 = prevNode2->getNext();

    /* caso especial: nodos adyacentes */
    if (node1->getNext() == node2) {
        if (prevNode1) {
            prevNode1->setNext(node2);
        } else {
            this->head = node2;
        }

        node1->setNext(node2->getNext());
        node2->setNext(node1);

        /* actualiza tail si es necesario */
        if (node2 == this->tail) {
            this->tail = node1;
        }
    } 
    /* caso general: nodos no adyacentes */
    else {
        if (prevNode1) {
            prevNode1->setNext(node2);
        } else {
            this->head = node2;
        }

        prevNode2->setNext(node1);

        /* intercambia los next de los nodos */
        SinglyNode<T>* temp = node1->getNext();
        node1->setNext(node2->getNext());
        node2->setNext(temp);

        /* actualiza tail si es necesario */
        if (node2 == this->tail) {
            this->tail = node1;
        } else if (node1 == this->tail) {
            this->tail = node2;
        }
    }
} /*O(n)*/

/* Une la lista actual con otra lista (operación destructiva sobre otherList) */
template <typename T>
void SinglyList<T>::mergeList(const SinglyList<T>& otherList) {
    /* No hace nada si la lista a unir está vacía */
    if (otherList.isEmpty()) return;

    /* Si la lista actual está vacía, toma todos los elementos de otherList */
    if (this->isEmpty()) {
        this->head = otherList.head;
        this->tail = otherList.tail;
        this->length = otherList.length;
    } else {
        /* Conecta el final de la lista actual con el inicio de otherList */
        this->tail->setNext(otherList.head);
        this->tail = otherList.tail;
        this->length += otherList.length;
    }
} /*O(1)*/

/* Ordena la lista usando Merge Sort (utiliza métodos privados existentes) */
template <typename T>
void SinglyList<T>::mergeSort() {
    /* Listas vacías o de un elemento ya están ordenadas */
    if (this->length <= 1) return;

    /* Ordena recursivamente usando los métodos privados */
    this->head = mergeSortRec(this->head);

    /* Actualiza el tail recorriendo la lista */
    SinglyNode<T>* current = this->head;
    while (current != NULL && current->getNext() != NULL) {
        current = current->getNext();
    }
    this->tail = current;
} /*O(n log n)*/
