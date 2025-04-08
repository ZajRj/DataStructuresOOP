#include <iostream>
#include <string>
#include <List/SinglyList.hpp>
#include <sstream>

using namespace std;

SinglyList<string> readLinesFromInput(); /* convierte la entrada del archivo a una lista de strings, donde cada string es una linea del archivo */
SinglyList<int> parseLineToInts(const string& line); /* procesa la linea de strings y la convierte en una lista de enteros donde cada entero del string es un nodo de la lista */
SinglyList<SinglyList<int> > makeListOfIntLists(); /* crea una lista de listas de enteros */
SinglyList<SinglyList<int> > standardInput();
SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> > listToProcess); /* procesa la lista de listas de enteros y devuelve una lista de listas de enteros donde cada lista esta formateada segun lo esperado */
//void printListOfIntLists(const SinglyList<SinglyList<int> >& listToPrint);
void standardOutput(SinglyList<SinglyList<int> > compactList);

int main() {
    SinglyList<SinglyList<int> > actualList = standardInput();
    //printListOfIntLists(actualList);
    standardOutput(actualList);
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
        listToReturn.addToEnd(associatedLineNumber); /* agrega al final la linea, de forma que se pos(n) = linea(n+1) del archivo */
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

SinglyList<SinglyList<int> > fromInputListToProcessedList(SinglyList<SinglyList<int> >* listToProcess) {
    SinglyList<SinglyList<int> > result;
    /* verificacion de seguridad para evitar datos corruptos */
    if(listToProcess == NULL || listToProcess->isEmpty()) {
        return result;
    }

    /* extrae el número de casos de prueba (primer numero del archivo o primer elemento de la lista del primer elemento de listas)*/
    int numTestCases = 0;
    if(!listToProcess->findElementAt(0).isEmpty()) {
        numTestCases = listToProcess->findElementAt(0).findElementAt(0);
       /* eliminamos el dato leído porque ya no nos interesa mantenerlo */
        listToProcess->findElementAt(0).removeFromStart();
        if(listToProcess->findElementAt(0).isEmpty()) {
            listToProcess->removeElementAt(0);
        }
    }

    /* verificación adicional para seguridad */
    if(numTestCases <= 0 || numTestCases > listToProcess->getLength()) {
        return result; 
    }

    /* procesamos exactamente numTestCases listas */
    for(int currentInnerPosition = 0; currentInnerPosition < numTestCases; currentInnerPosition++) {
        /* creamos una variable llamada currentInnerPosition para saber cual posicion de la lista interna se debe consultar, mientras este cubierta por el maximo numero de casos que pudimos extraer */
        SinglyList<int> auxiliarInnerList;
        if(listToProcess->isEmpty()) break; /* si la lista esta vacia, rompe el for para evitar repeticiones innecesarias y posibles casos de segmentacion */
        for(int currentExternalPosition = 0; currentExternalPosition < listToProcess->getLength(); currentExternalPosition++){ 
            if(currentInnerPosition == 0 && currentExternalPosition == 0){
                listToProcess->removeFromStart();
            }
            /* creamos la variable llamada currentExternalPosition, que esta recorrera cada pos de la lista de listas una a la vez */
            SinglyList<int> auxiliarList = listToProcess->findElementAt(currentExternalPosition); /* para evitar crear punteros innecesarios, utilizaremos una variable para copiar la lista que iteraremos */
            int currentNumber = auxiliarList.findElementAt(currentInnerPosition); /* revisa la posicion que nos interesa al momento */
            if(currentNumber){ /* si el numero entregado por la lista es un numero valido, procedemos a introducirlo en la lista que luego introduciremos a la lista de listas, al final */
                auxiliarInnerList.addToEnd(currentNumber); /* introduce */
            }
        }
    result.addToEnd(auxiliarInnerList); /* al final de cada for interno, introduce la lista creada a la lista de listas */
}
    return result; /* retorna la lista de listas */
}

SinglyList<SinglyList<int> > standardInput(){
    SinglyList<SinglyList<int> > intList = makeListOfIntLists();
    return fromInputListToProcessedList(&intList);
}

/*void printListOfIntLists(const SinglyList<SinglyList<int> >& list) {
    for(int i = 0; i < list.getLength(); i++) {
        std::cout << "Lista " << i << ": [";
        
        SinglyList<int> innerList = list.findElementAt(i);
        for(int j = 0; j < innerList.getLength(); j++) {
            std::cout << innerList.findElementAt(j);
            if(j < innerList.getLength() - 1) {
                std::cout << ", ";
            }
        }
        
        std::cout << "]" << std::endl;
    }
}*/

void standardOutput(SinglyList<SinglyList<int> > compactList){
    while(!compactList.isEmpty()){
        SinglyList<int> auxiliarList = compactList.findElementAt(0);
        compactList.removeFromStart();
        int dayIterator = 1;
        if(auxiliarList.getLength() > 1){
        while(!auxiliarList.isEmpty()){
            if(auxiliarList.findElementAt(0) < auxiliarList.findElementAt(1)){
                cout << dayIterator << endl;
                break; 
            }
        auxiliarList.removeFromStart();
        dayIterator++;
        }
    }else{
        cout << "alive forever" << endl;
    }
}
}