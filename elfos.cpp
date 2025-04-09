#include <iostream>
#include <string>
#include <sstream>
#include "List/SinglyList.hpp"

using namespace std;

SinglyList<SinglyList<string>*> standardInput(); /* funcion que procesa la entrada estandar y la convierte en una lsita de listas de strings*/
void printListOfLists(SinglyList<SinglyList<string>*>& stringListOfList); /* funcion que imprime la lista actual lol temporal esta funcion ejejejeje */
void freeListOfLists(SinglyList<SinglyList<string>*>& stringListOfList);

int main() {

    /* procesa la entrada estandar y la retorna a la lista que operaremos */
    SinglyList<SinglyList<string>*> stringListOfList = standardInput();

    /* printea los resultados */
    printListOfLists(stringListOfList);

    /* liberar memoria */
    freeListOfLists(stringListOfList);

    return 0;
}

SinglyList<SinglyList<string>*> standardInput() {
    int innerListCounter;
    cin >> innerListCounter;
    cin.ignore(); /* ignoramos primera linea \n */
    SinglyList<SinglyList<string>*> returnList; /* lista que sera retornada */

    for (int currentListCounter = 0; currentListCounter < innerListCounter; currentListCounter++) { /* crea innerListCounter de punteros de listas de strings */
        returnList.addToEnd(new SinglyList<string>());
    }

    string currentLine; /* la linea actual procesada */
    while (getline(cin, currentLine)) { /* "mientras que existan lineas de entrada por procesar (no sea el final)" */
        istringstream auxiliarLine(currentLine); /* permite el parsing de la cadena a libertad */
        string nameOrAka; /* name or aka es nombre o apodo, dependiendo de la posicion del archivo */

        for (int currentIterationList = 0; currentIterationList < innerListCounter && (auxiliarLine >> nameOrAka); currentIterationList++) { /* recorre cada palabra de la linea hasta completar la lista interna */
            SinglyList<string>* innerList = returnList.findElementAt(currentIterationList); /* obtiene la lista interna en su posicion i */
            if (innerList != NULL) { /* verifica que tenga un valor valido */
                innerList->addToEnd(nameOrAka); /* agrega la palabra al final */
            }
        }
    }

    return returnList;
}

void printListOfLists(SinglyList<SinglyList<string>*>& lista_de_listas) {
    int innerListCounter = lista_de_listas.getLength();
    for (int i = 0; i < innerListCounter; ++i) {
        cout << "Lista " << i+1 << ": ";
        SinglyList<string>* lista_actual = lista_de_listas.findElementAt(i);
        if (lista_actual != NULL) {
            // Usamos findElementAt para recorrer las palabras
            for (int j = 0; j < lista_actual->getLength(); ++j) {
                string palabra = lista_actual->findElementAt(j);
                cout << palabra << " ";
            }
        }
        cout << endl;
    }
}

void freeListOfLists(SinglyList<SinglyList<string>*>& lista_de_listas) {
    int innerListCounter = lista_de_listas.getLength();
    for (int i = 0; i < innerListCounter; ++i) {
        SinglyList<string>* lista_actual = lista_de_listas.findElementAt(i);
        if (lista_actual != NULL) {
            delete lista_actual;
        }
    }
}