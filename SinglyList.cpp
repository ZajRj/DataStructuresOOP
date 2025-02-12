#ifndef SINGLYLIST_H
#define SINGLYLIST_H
#include "SinglyNode.h"

/*METODOS PRIVADOS USADOS EN OTROS METODOS PUBLICOS*/

template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* node) const{

    return this->node == nullptr;
}

template <typename T>
bool SinglyList<T>::isNullNode(SinglyNode<T>* firstNode,SinglyNode<T>* secondNode) const{
    return this->isNullNode(firstNode) || this->isNullNode(secondNode);
}

/*seccion para actualizar los atributos de la lista (head, tail, length) despues de operaciones de eliminacion o de insercion en cualquier
punto.
    *estos metodos son utilizados por los metodos publicos para mantener consistencia y evitar repeticion de codigo
    *addUpdateLastElement actualiza la tail despues de agregar un nodo al final
    *removeUpdateLastElement actualiza la tail despues de eliminar un nodo al final
    *addUpdateFirstElement actualiza la head despues de agregar un nodo al principio
    *removeUpdateFirstElement actualiza la head despues de eliminar un nodo al principio
    *uniqueElementUpdate actualiza la head y tail, usado en caso que sea el primer elemento
*/

template <typename T>
void SinglyList<T>::addUpdateLastElement(SinglyNode<T>* newTail){
    if(isNullNode(newTail)){
        throw std::invalid_argument("El nuevo nodo no puede ser un puntero a null.");
    }
    this->tail= newTail;
    this->length++;
}

template <typename T>
void SinglyList<T>::removeUpdateLastElement(SinglyNode<T>* newTail){
    if(isNullNode(newTail)){
        throw std::invalid_argument("El nuevo nodo no puede ser un puntero a null.");
    }
    this->tail= newTail;
    this->length--;
}

template <typename T>
void SinglyList<T>::addUpdateFirstElement(SinglyNode<T>* newHead){
    if(isNullNode(newHead)){
        throw std::invalid_argument("El nuevo nodo no puede ser un puntero a null.");
    }
    this->head= newHead;
    this->length++;
}

template <typename T>
void SinglyList<T>::removeUpdateFirstElement(SinglyNode<T>* newHead){
    if(isNullNode(newHead)){
        throw std::invalid_argument("El nuevo nodo no puede ser un puntero a null.");
    }
    this->head= newHead;
    this->length--;
}

template <typename T>
void SinglyList<T>::uniqueElementUpdate(SinglyNode<T>* newHead, SinglyNode<T>* newTail){
    if(isNullNode(newHead, newTail)){
        throw std::invalid_argument("Los nuevos nodos no pueden ser un punteros a null.");
    }
            this->head = newHead;
            this->tail = newTail;
            this->length++;
}

template <typename T>
void SinglyList<T>::emptyElementsUpdate(){

    this->length=0; 
    this->head= nullptr;
    this->tail= nullptr;
}

/*seccion de metodos privados del mergesort*/
template <typename T>
SinglyNode<T>* SinglyList<T>::mergeSortRec(SinglyNode<T>* head) {
    /*si la lista esta vacia o tiene un solo elemento, ya esta ordenada. */
    if (isNullNode(head) || isNullNode(head->getNext())) {
        return head;
    }

    /* divide la lista en dos mitades */
    SinglyNode<T>* middle = getMiddle(head);
    SinglyNode<T>* nextOfMiddle = middle->getNext();
    middle->setNext(nullptr);/*separa ambas mitades*/

    /* ordena recursivamente ambas mitades */
    SinglyNode<T>* left = mergeSortRec(head);
    SinglyNode<T>* right = mergeSortRec(nextOfMiddle);

    /* une las mitades ordenadas*/
    return sortedMerge(left, right);
}

template <typename T>
SinglyNode<T>* SinglyList<T>::getMiddle(SinglyNode<T>* head) {
    /*si la lista esta vacia devuelve nullptr*/
    if (isNullNode(head)) {
        return nullptr;
    }

    SinglyNode<T>* slow = head;       /*avanza de uno en uno*/
    SinglyNode<T>* fast = head;       /*avanza de dos en dos*/

    /*cada uno avanza segun el comportamiento comentado anteriormente*/
    while (!isNullNode(fast->getNext()) && !isNullNode(fast->getNext()->getNext())) {
        slow = slow->getNext();
        fast = fast->getNext()->getNext();
    }

    /*si fast llego al final, slow esta en el medio*/
    return slow;
}

template <typename T>
SinglyNode<T>* SinglyList<T>::sortedMerge(SinglyNode<T>* left, SinglyNode<T>* right) {
    /*nodos ficticios para simplificar*/
    SinglyNode<T> dummy;
    SinglyNode<T>* tail = &dummy;

    /*fusiona ambas listas*/
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

    /*conecta con la lista no vacia*/
    if (!isNullNode(left)) {
        tail->setNext(left);
    } else {
        tail->setNext(right);
    }

    /*devuelve la lista fusionada excepto el nodo ficticio*/
    return dummy.getNext();
}

/*METODOS PUBLICOS*/

/*constructores*/

/*constructor base: inicializa una lista vacia con longitud 0 y punteros head y tail nulos al no existir elementos*/
template <typename T>
SinglyList<T>::SinglyList(): length(0), head(nullptr), tail(nullptr){}

/*constructor de tipo copia:*/
template <typename T>
SinglyList<T>::SinglyList(const SinglyList<T>& other) : length{0}, head{nullptr}, tail{nullptr} {
    SinglyNode<T>* current = other.head;
    while (current != nullptr) {
        this->addToEnd(current->getData());
        current = current->getNext();
    }
}

/*destructor: libera la memoria de todos los nodos de la lista */
template <typename T>
SinglyList<T>::~SinglyList(){
    this->clear();
}

/*getters*/
template <typename T>
SinglyNode<T>* SinglyList<T>::getHead() const{ return (this->head); }

template <typename T>
SinglyNode<T>* SinglyList<T>::getTail() const{ return (this->tail); }

template <typename T>
int SinglyList<T>::getLength() const{ return (this->length); }

/*metodos que operan la lista*/

/*añadir un elemento en...*/

/*agrega un nuevo elemento al principio de la lista*/
template <typename T>
void SinglyList<T>::addToStart(T newElement){
    /*construye el nodo con el elemento*/
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);
    /*verifica si la lista esta vacia*/
    if(this->isEmpty()){ 
        /*en caso de estar vacia, anexa tail y head al nuevo nodo, al ser elemento unico*/
        this->uniqueElementUpdate(newNode,newNode);
    }else {
        /*conecta el next del nuevo nodo a donde apuntaba anteriormente la lista con head*/
        newNode->setNext(this->head);
        /*este metodo actualiza el apuntador de head hacia el nuevo nodo*/
        this->addUpdateFirstElement(newNode);
    }
}

/*agrega un nuevo elemento al final de la lista*/
template <typename T>
void SinglyList<T>::addToEnd(T newElement){
    /*construye el nodo con el elemento*/
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);
    /*verifica si la lista esta vacia*/
    if(this->isEmpty()){
        /*en caso de estar vacia, anexa tail y head al nuevo nodo, al ser elemento unico*/
        this->uniqueElementUpdate(newNode,newNode);
    }else {
        /*en caso de no estar vacia, conecta el next del apuntado de tail al nuevo nodo*/
        this->tail->setNext(newNode);
        /*este metodo actualiza el apuntador de tail hacia el nuevo nodo*/
        this->addUpdateLastElement(newNode);
    }
}

/*añade antes de algún elemento en específico*/
template <typename T>
void SinglyList<T>::addBeforeElement(int indexElement, T newElement){
    /*construye el nodo con el elemento*/
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);

    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*en caso de estar vacia, anexa tail y head al nuevo nodo, al ser elemento unico*/
        this->uniqueElementUpdate(newNode, newNode);
    } else {
        /*valida si el índice es válido, es decir que no sea menor a 0 ni mayor a length*/
        if (indexElement < 0 || indexElement >= this->length) {
            throw std::out_of_range("Índice fuera de rango.");
        }

        /*caso especial: agregar antes del primer elemento (índice 0)*/
        if (indexElement == 0) {
            newNode->setNext(this->head);
            this->addUpdateFirstElement(newNode);
        } else {
            /*busca el nodo en la posición (indexElement - 1), el apuntador del nodo recibido por el metodo findElement
            es ahora recibido por una variable apuntadora, por lo tanto prevNode ahora es el nodo previo al 
            elemento que se desea indexar en su direccion de memoria*/
            SinglyNode<T>* prevNode = this->findElement(indexElement - 1);
            /*el nodo nuevo se le asigna en su campo next el apuntador del nodo insertar antes*/
            newNode->setNext(prevNode->getNext());
            /*al nodo anterior al que se desea insertar se le actualiza su campo next al nuevo nodo creado*/
            prevNode->setNext(newNode);
            /*aumenta el length un valor*/
            this->length++;
        }
    }
}

/*añade despues de algún elemento en específico*/
template <typename T>
void SinglyList<T>::addAfterElement(int indexElement, T newElement){
    SinglyNode<T>* newNode = new SinglyNode<T>(newElement);

    if (this->isEmpty()) {
        this->uniqueElementUpdate(newNode, newNode);
    } else {
        if (indexElement < 0 || indexElement >= this->length) {
            throw std::out_of_range("Índice fuera de rango.");
        }

        if (indexElement == this->length - 1) {
            this->tail->setNext(newNode);
            this->addUpdateLastElement(newNode);
        } else {
            SinglyNode<T>* currentNode = this->findElement(indexElement);
            newNode->setNext(currentNode->getNext());
            currentNode->setNext(newNode);
            this->length++;
        }
    }
}

/*añadir varios elementos en...*/

 /*recibe un conjunto de elementos desde un array y los añade en conjunto al inicio*/
template <typename T>
void SinglyList<T>::addBatchToStart(const std::vector<T>& newElements){
    /*verifica si el vector de elementos está vacío*/
    if (newElements.empty()) {
        /*si esta vacio, lanza una excepcion indicando que no se puede proceder*/
        throw std::invalid_argument("el vector de elementos no puede estar vacío.");
    }

    /*inicializa un puntero para el nuevo inicio de la lista*/
    SinglyNode<T>* newHead = nullptr;
    /*inicializa un puntero para seguir el nodo actual mientras se crean los nuevos nodos*/
    SinglyNode<T>* current = nullptr;

    /*recorre cada elemento del vector*/
    for (const T& element : newElements) {
        /*crea un nuevo nodo con el elemento actual*/
        SinglyNode<T>* newNode = new SinglyNode<T>(element);

        /*si newHead es nullptr, significa que es el primer nodo*/
        if (!newHead) {
            /*asigna el nuevo nodo como el inicio de la lista*/
            newHead = newNode;
        } else {
            /*si no es el primer nodo, enlaza el nodo actual con el nuevo nodo*/
            current->setNext(newNode);
        }

        /*mueve el puntero current al nuevo nodo creado*/
        current = newNode;
    }

    /*verifica si la lista original está vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, actualiza tanto el inicio como el final de la lista*/
        this->uniqueElementUpdate(newHead, current);
    } else {
        /*si no esta vacia, enlaza el ultimo nodo de la nueva cadena con el inicio original*/
        current->setNext(this->head);
        /*actualiza el inicio de la lista*/
        this->addUpdateFirstElement(newHead);
    }

    /*incrementa la longitud de la lista con el tamaño del vector*/
    this->length += newElements.size();
}

/*recibe un conjunto de elementos desde un array y los añade en conjunto al final*/
template <typename T>
void SinglyList<T>::addBatchToEnd(const std::vector<T>& newElements){
    /*verifica si el vector de elementos está vacío*/
    if (newElements.empty()) {
        /*si está vacio, lanza una excepción indicando que no se puede proceder*/
        throw std::invalid_argument("el vector de elementos no puede estar vacío.");
    }

    /*inicializa un puntero para el inicio y el final de la nueva cadena de nodos*/
    SinglyNode<T>* batchHead = nullptr;
    SinglyNode<T>* batchTail = nullptr;

    /*recorre cada elemento del vector*/
    for (const T& elem : newElements) {
        /*crea un nuevo nodo con el elemento actual*/
        SinglyNode<T>* newNode = new SinglyNode<T>(elem);

        /*si batchHead es nullptr, significa que es el primer nodo*/
        if (!batchHead) {
            /*asigna el nuevo nodo como el inicio de la nueva cadena*/
            batchHead = newNode;
            /*tambien es el final de la nueva cadena por ahora*/
            batchTail = newNode;
        } else {
            /*si no es el primer nodo, enlaza el último nodo de la cadena con el nuevo nodo*/
            batchTail->setNext(newNode);
            /*mueve batchTail al nuevo nodo*/
            batchTail = newNode;
        }
    }

    /*verifica si la lista original está vacia*/
    if (this->isEmpty()) {
        /*si está vacia, asigna el inicio y el final de la lista a la nueva cadena */
        this->head = batchHead;
        this->tail = batchTail;
    } else {
        /* si no está vacia, enlaza el último nodo de la lista original con el inicio de la nueva cadena */
        this->tail->setNext(batchHead);
        /* actualiza el final de la lista al final de la nueva cadena */
        this->tail = batchTail;
    }

    /* incrementa la longitud de la lista con el tamaño del vector */
    this->length += newElements.size();
}

/*recibe un conjunto de elementos dónde vector[0] es apuntado por el elemento anterior del punto de inicio*/
template <typename T>
void SinglyList<T>::addBatchToBeforeElement(int indexElement, const std::vector<T>& newElements) {
    /*verifica si el vector de elementos esta vacio*/
    if (newElements.empty()) {
        /*si esta vacio, lanza una excepcion indicando que no se puede proceder*/
        throw std::invalid_argument("el vector de elementos no puede estar vacio.");
    }

    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion porque no se puede agregar antes de un elemento inexistente*/
        throw std::out_of_range("no se puede agregar antes de un elemento, la lista esta vacia.");
    }

    /*valida si el indice es valido, es decir que no sea menor a 0 ni mayor o igual a length*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*caso especial: agregar antes del primer elemento (indice 0)*/
    if (indexElement == 0) {
        /*crea nodos para los nuevos elementos y enlazalos entre si*/
        SinglyNode<T>* batchHead = nullptr;
        SinglyNode<T>* batchTail = nullptr;
        for (const T& elem : newElements) {
            SinglyNode<T>* newNode = new SinglyNode<T>(elem);
            if (!batchHead) {
                batchHead = newNode;
                batchTail = newNode;
            } else {
                batchTail->setNext(newNode);
                batchTail = newNode;
            }
        }

        /*enlaza el ultimo nodo de la nueva cadena con el head original*/
        batchTail->setNext(this->head);
        /*actualiza el head de la lista*/
        this->head = batchHead;
    } else {
        /*busca el nodo en la posicion (indexElement - 1), que es el nodo anterior al punto de insercion*/
        SinglyNode<T>* prevNode = this->findElement(indexElement - 1);

        /*crea nodos para los nuevos elementos y enlazalos entre si*/
        SinglyNode<T>* batchHead = nullptr;
        SinglyNode<T>* batchTail = nullptr;
        for (const T& elem : newElements) {
            SinglyNode<T>* newNode = new SinglyNode<T>(elem);
            if (!batchHead) {
                batchHead = newNode;
                batchTail = newNode;
            } else {
                batchTail->setNext(newNode);
                batchTail = newNode;
            }
        }

        /*enlaza el ultimo nodo de la nueva cadena con el nodo en la posicion indexElement*/
        batchTail->setNext(prevNode->getNext());
        /*enlaza el nodo anterior al punto de insercion con el inicio de la nueva cadena*/
        prevNode->setNext(batchHead);
    }

    /*incrementa la longitud de la lista con el tamaño del vector*/
    this->length += newElements.size();
}

/*recibe un conjunto de elementos dónde vector[0] es apuntado por el elemento del punto de inicio*/
template <typename T>
void SinglyList<T>::removeAfterElement(int indexElement) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*valida si el indice es valido, es decir que no sea menor a 0 ni mayor o igual a length*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*caso especial: no se puede eliminar despues del ultimo elemento*/
    if (indexElement == this->length - 1) {
        throw std::invalid_argument("no existe un elemento despues del ultimo nodo.");
    }

    /*busca el nodo en la posicion indexElement*/
    SinglyNode<T>* currentNode = this->findElement(indexElement);

    /*guarda el nodo que se va a eliminar (el siguiente al currentNode)*/
    SinglyNode<T>* nodeToRemove = currentNode->getNext();

    /*actualiza el next del currentNode para que apunte al nodo siguiente al que se va a eliminar*/
    currentNode->setNext(nodeToRemove->getNext());

    /*si el nodo eliminado era el tail, actualiza tail para que apunte al currentNode*/
    if (nodeToRemove == this->tail) {
        this->tail = currentNode;
    }

    /*libera la memoria del nodo eliminado*/
    delete nodeToRemove;

    /*reduce la longitud de la lista en 1*/
    this->length--;
}

/*eliminar un elemento en...*/

/*remueve el primer elemento de la lista*/
template <typename T>
void SinglyList<T>::removeFromStart() {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*guarda el nodo que se va a eliminar (el primer nodo)*/
    SinglyNode<T>* nodeToRemove = this->head;

    /*actualiza el head para que apunte al siguiente nodo*/
    this->head = this->head->getNext();

    /*si la lista queda vacia despues de la eliminacion, actualiza tail a nullptr*/
    if (this->head == nullptr) {
        this->tail = nullptr;
    }

    /*libera la memoria del nodo eliminado*/
    delete nodeToRemove;

    /*reduce la longitud de la lista - 1*/
    this->length--;
}

/*remueve el ultimo elemento de la lista*/
template <typename T>
void SinglyList<T>::removeFromEnd() {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*si la lista tiene un solo nodo*/
    if (this->head == this->tail) {
        /*libera la memoria del unico nodo*/
        delete this->head;
        /*actualiza head y tail a nullptr*/
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        /*si la lista tiene mas de un nodo, busca el nodo anterior al tail*/
        SinglyNode<T>* current = this->head;
        while (current->getNext() != this->tail) {
            current = current->getNext();
        }

        /*guarda el nodo que se va a eliminar (el tail actual)*/
        SinglyNode<T>* nodeToRemove = this->tail;

        /*actualiza tail para que apunte al nodo anterior*/
        this->tail = current;

        /*actualiza el next del nuevo tail a nullptr*/
        this->tail->setNext(nullptr);

        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    }

    /*reduce la longitud de la lista en 1*/
    this->length--;
}

/*remueve el elemento indicado*/
template <typename T>
void SinglyList<T>::removeElement(int indexElement) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*valida si el indice es valido, es decir que no sea menor a 0 ni mayor o igual a length*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*caso especial: eliminar el primer elemento (indice 0)*/
    if (indexElement == 0) {
        /*guarda el nodo que se va a eliminar (el head actual)*/
        SinglyNode<T>* nodeToRemove = this->head;
        /*actualiza head para que apunte al siguiente nodo*/
        this->head = this->head->getNext();
        /*si la lista queda vacia despues de la eliminacion, actualiza tail a nullptr*/
        if (this->head == nullptr) {
            this->tail = nullptr;
        }
        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    } else {
        /*busca el nodo en la posicion (indexElement - 1), que es el nodo anterior al que se desea eliminar*/
        SinglyNode<T>* prevNode = this->findElement(indexElement - 1);
        /*guarda el nodo que se va a eliminar (el siguiente al prevNode)*/
        SinglyNode<T>* nodeToRemove = prevNode->getNext();
        /*actualiza el next del prevNode para que apunte al nodo siguiente al que se va a eliminar*/
        prevNode->setNext(nodeToRemove->getNext());
        /*si el nodo eliminado era el tail, actualiza tail para que apunte al prevNode*/
        if (nodeToRemove == this->tail) {
            this->tail = prevNode;
        }
        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    }

    /*reduce la longitud de la lista en 1*/
    this->length--;
}

/*remueve el elemento anterior al indicado*/
template <typename T>
void SinglyList<T>::removeBeforeElement(int indexElement) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*valida si el indice es valido, es decir que no sea menor a 0 ni mayor o igual a length*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*caso especial: no se puede eliminar antes del primer elemento (indice 0)*/
    if (indexElement == 0) {
        throw std::invalid_argument("no existe un elemento antes del primer nodo.");
    }

    /*si se va a eliminar antes del segundo elemento (indice 1)*/
    if (indexElement == 1) {
        /*guarda el nodo que se va a eliminar (el head actual)*/
        SinglyNode<T>* nodeToRemove = this->head;
        /*actualiza head para que apunte al siguiente nodo*/
        this->head = this->head->getNext();
        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    } else {
        /*busca el nodo en la posicion (indexElement - 2), que es el nodo anterior al nodo que se desea eliminar*/
        SinglyNode<T>* prevNode = this->findElement(indexElement - 2);
        /*guarda el nodo que se va a eliminar (el siguiente al prevNode)*/
        SinglyNode<T>* nodeToRemove = prevNode->getNext();
        /*actualiza el next del prevNode para que apunte al nodo siguiente al que se va a eliminar*/
        prevNode->setNext(nodeToRemove->getNext());
        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    }

    /*reduce la longitud de la lista en 1*/
    this->length--;
}

/*remueve el elemento posterior al indicado*/
template <typename T>
void SinglyList<T>::removeAfterElement(int indexElement) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*valida si el indice es valido, es decir que no sea menor a 0 ni mayor o igual a length*/
    if (indexElement < 0 || indexElement >= this->length) {
        throw std::out_of_range("indice fuera de rango.");
    }

    /*caso especial: no se puede eliminar despues del ultimo elemento*/
    if (indexElement == this->length - 1) {
        throw std::invalid_argument("no existe un elemento despues del ultimo nodo.");
    }

    /*busca el nodo en la posicion indexElement*/
    SinglyNode<T>* currentNode = this->findElement(indexElement);

    /*guarda el nodo que se va a eliminar (el siguiente al currentNode)*/
    SinglyNode<T>* nodeToRemove = currentNode->getNext();

    /*actualiza el next del currentNode para que apunte al nodo siguiente al que se va a eliminar*/
    currentNode->setNext(nodeToRemove->getNext());

    /*si el nodo eliminado era el tail, actualiza tail para que apunte al currentNode*/
    if (nodeToRemove == this->tail) {
        this->tail = currentNode;
    }

    /*libera la memoria del nodo eliminado*/
    delete nodeToRemove;

    /*reduce la longitud de la lista en 1*/
    this->length--;
}

/*eliminar varios elementos en...*/

template <typename T>
void SinglyList<T>::removeBatchFromStart(int batchRemoveCount) {
    /*verifica si la lista esta vacia*/
    if (this->isEmpty()) {
        /*si esta vacia, lanza una excepcion indicando que no se puede eliminar*/
        throw std::out_of_range("no se puede eliminar, la lista esta vacia.");
    }

    /*valida si el numero de elementos a eliminar es valido, es decir que no sea menor a 1 ni mayor a length*/
    if (batchRemoveCount < 1 || batchRemoveCount > this->length) {
        throw std::out_of_range("el numero de elementos a eliminar es invalido.");
    }

    /*recorre la lista para eliminar los primeros batchRemoveCount nodos*/
    for (int i = 0; i < batchRemoveCount; ++i) {
        /*guarda el nodo que se va a eliminar (el head actual)*/
        SinglyNode<T>* nodeToRemove = this->head;
        /*actualiza head para que apunte al siguiente nodo*/
        this->head = this->head->getNext();
        /*libera la memoria del nodo eliminado*/
        delete nodeToRemove;
    }

    /*si la lista queda vacia despues de la eliminacion, actualiza tail a nullptr*/
    if (this->head == nullptr) {
        this->tail = nullptr;
    }

    /*reduce la longitud de la lista en batchRemoveCount*/
    this->length -= batchRemoveCount;
}

template <typename T>
bool SinglyList<T>::isEmpty() const{ return (this->length == 0); }

#endif
