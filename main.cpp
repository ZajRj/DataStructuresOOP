#include <iostream>
#include <string>
#include <List/SinglyList.hpp>
#include <sstream>

using namespace std;

SinglyList<string> readLinesFromInput(); /* convierte la entrada del archivo a una lista de strings, donde cada string es una linea del archivo */
SinglyList<int> parseLineToInts(const string& line); /* procesa la linea de strings y la convierte en una lista de enteros donde cada entero del string es un nodo de la lista */
SinglyList<SinglyList<int> > makeListOfIntLists(); /* crea una lista de listas de enteros */
void standardInput(SinglyList<SinglyList<int> > &processedList);
SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> > listToProcess); /* procesa la lista de listas de enteros y devuelve una lista de listas de enteros donde cada lista esta formateada segun lo esperado */
void printListOfIntLists(const SinglyList<SinglyList<int> >& listToPrint);

int main() {
    SinglyList<SinglyList<int> > formatInput;
    standardInput(formatInput);
    cout << "Lista Procesada:" << endl;
    printListOfIntLists(formatInput);
    return 0;
}

SinglyList<string> readLinesFromInput(){
    SinglyList<string> listToReturn; /* lista de strings que se va a retornar */
    string currentLine; /* variable donde se guardara la linea :) */
    while (getline(cin, currentLine)) {
        listToReturn.addToEnd(currentLine);
        if (cin.eof()) { /* si se llega al final del archivo, se sale del bucle */
            break;
        }
    }
    return listToReturn; /* retorna la lista de strings */
    /* si se llega al final del archivo, se sale del bucle */
}

SinglyList<int> parseLineToInts(const string& line){
    SinglyList<int> listToReturn; /* lista de enteros que sera retornada */
    stringstream stringstreamedLine(line); /* convierte la linea de string a un stringstream para poder procesarla */
    int associatedLineNumber; /* numero de linea asociado al momento */
    while(stringstreamedLine >> associatedLineNumber){ 
        listToReturn.addToEnd(associatedLineNumber); /* agrega al final la linea, de forma que se pos(n) = linea(n+1) del archivo*/
        if(stringstreamedLine.peek() == ' '){ /* si el siguiente caracter es un espacio, se ignora */
            stringstreamedLine.ignore();
        }
    }
    return listToReturn; /* retorna la lista de enteros :) */
}

SinglyList<SinglyList<int> > makeListOfIntLists(){
    SinglyList<SinglyList<int> > listToReturn;
    SinglyList<string> lines = readLinesFromInput(); /* convierte el archivo de entrada estandar a una lista de strings*/
    while(!lines.isEmpty()){ /* mientras existan lineas aun por procesar */
        listToReturn.addToEnd(parseLineToInts(lines.findElementAt(0))); /* consulta la primera posicion de la lista de strings y la convierte a una lista de enteros */
        lines.removeFromStart(); /* remueve el primer elemento para permitir el flujo normal */
    }
    return listToReturn;
}

SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> > listToProcess){
    SinglyList<SinglyList<int> > listToReturn;
    int currentPosition = 1;
    int currentNumber = 0;

    /* mientras existan lineas aun por procesar */
    while(!listToProcess.isEmpty()){
        SinglyList<int> listToCompact;
        if(!(listToProcess.findElementAt(currentPosition)).isEmpty()){ /* mientras el lugar a dónde apunta el puntero de listas de enteros sea distinto a NULL procederá esta rutina*/
            currentNumber = (listToProcess.findElementAt(currentPosition)).findElementAt(1); /* consulta el primer nodo */
            cout << "pene" << endl;
            listToCompact.addToEnd(currentNumber); /* agrega al final el numero que aparezca allí */
            cout << "pene" << endl;
            (listToProcess.findElementAt(currentPosition)).removeFromStart(); /* remueve ese número de la lista a procesar*/
            cout << "pene" << endl;
        }else{
            listToProcess.removeElementAt(currentPosition);
        }

        if(currentPosition == listToProcess.getLength()){
            listToReturn.addToEnd(listToCompact);
            listToCompact.clear();
        }
    }
    return listToReturn;
};

void standardInput(SinglyList<SinglyList<int> > &processedList){
    SinglyList<SinglyList<int> > intList = makeListOfIntLists();
    processedList = fromInputListToProcessedList(intList);
}

void printListOfIntLists(const SinglyList<SinglyList<int> >& listToPrint){
    if(listToPrint.isEmpty()){
        cout << "La lista de listas está vacía." << endl;
        return;
    }
    for(int i = 0; i < listToPrint.getLength(); ++i){ // Usando getLength()
        cout << "Lista [" << i << "]: ";
        SinglyList<int>* currentList = (listToPrint.findElementAt(i)).shallowCopy();
        if (currentList != NULL) {
            for(int j = 0; j < currentList->getLength(); ++j){ // Usando getLength()
                cout << currentList->findElementAt(j) << " ";
            }
            cout << endl;
            delete currentList;
        } else {
            cout << "Error: No se pudo obtener la sublista en el índice " << i << endl;
        }
    }
}