#include <iostream>
#include <string>
#include <List/SinglyList.hpp>
#include <sstream>

using namespace std;

SinglyList<string> turnStandardInputToStringList(); /* convierte la entrada del archivo a una lista de strings, donde cada string es una linea del archivo */
SinglyList<int> processLine(const string& line); /* procesa la linea de strings y la convierte en una lista de enteros donde cada entero del string es un nodo de la lista */
SinglyList<SinglyList<int> > standardInputProcessing(); /* procesa la entrada del archivo */
SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> > listToProcess); /* procesa la lista de listas de enteros y devuelve una lista de listas de enteros donde cada lista esta formateada segun lo esperado */


int main() {
    return 0;
}

SinglyList<string> turnStandardInputToStringList(){
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

SinglyList<int> processLine(const string& line){
    SinglyList<int> listToReturn; /* lista de enteros que sera retornada */
    stringstream stringstreamedLine(line); /* convierte la linea de string a un stringstream para poder procesarla */
    int associatedLineNumber; /* numero de linea asociado al momento */
    while(stringstreamedLine >> associatedLineNumber){ 
        listToReturn.addToEnd(associatedLineNumber); /* agrega al final la linea, de forma que se pos(n) = linea(n+1) del archivo*/
        if(stringstreamedLine.peek() == ','){ /* si el siguiente caracter es una coma, se ignora */
            stringstreamedLine.ignore();
        }
    }
    return listToReturn; /* retorna la lista de enteros :) */
}

SinglyList<SinglyList<int> > standardInputProcessing(){
    SinglyList<SinglyList<int> > listToReturn;
    SinglyList<string> lines = turnStandardInputToStringList(); /* convierte el archivo de entrada estandar a una lista de strings*/
    while(!lines.isEmpty()){ /* mientras existan lineas aun por procesar */
        listToReturn.addToEnd(processLine(lines.findElementAt(0))); /* consulta la primera posicion de la lista de strings */
        lines.removeFromStart(); /* remueve el primer elemento para permitir el flujo normal */
    }
    return listToReturn;
}

SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> > listToProcess);{
    SinglyList<SinglyList<int> > listToProcess = standardInputProcessing();
    SinglyList<SinglyList<int> > listToReturn;
    int currentPosition = 0;
    /* mientras existan lineas aun por procesar */
        while(!listToProcess.isEmpty()){
            SinglyList<int>* pointerToCurrentLine = new SinglyList<int>(listToProcess.findElementAt(currentPosition)); /* consulta la posicion actual de la lista de listas */
            if(pointerToCurrentLine->isEmpty()){
                listToProcess.removeFromStart(); /* remueve el primer elemento para permitir el flujo normal */
                delete pointerToCurrentLine; /* libera la memoria del puntero */
            }else{
                listToReturn.addToEnd(pointerToCurrentLine->findElementAt(0));
                pointerToCurrentLine->removeFromStart(); /* remueve el primer elemento para permitir el flujo normal */
                if(pointerToCurrentLine->isEmpty()){
                    delete pointerToCurrentLine; /* libera la memoria del puntero */
            }
        }
        currentPosition++;
        if(currentPosition == listToProcess.getSize()){
            currentPosition = 0; /* reinicia la posicion actual */
        }
}
}