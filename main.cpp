#include "Trees/BinaryTree.hpp"
#include <iostream>
#include <string>

using namespace std;

// Functor para imprimir
struct Printer {
    void operator()(const string& val) const {
        cout << val << " ";
    }
};

void testArbolString() {
    cout << "\n=== TEST ARBOL STRING ===" << endl;
    
    BinaryTree<string> arbol("Raiz");
    BinaryTree<string> subIzq("Izquierda");
    BinaryTree<string> subDer("Derecha");
    
    // Insertamos valores como objetos
    subIzq.insertSubTree(BinaryTree<string>("Hoja Izq 1"), true);
    subDer.insertSubTree(BinaryTree<string>("Hoja Der 1"), false);
    
    // Composición del árbol principal
    arbol.insertSubTree(subIzq, true);
    arbol.insertSubTree(subDer, false);
    
    // Recorrido seguro sin punteros
    cout << "Recorrido por niveles: ";
    Printer print;
    arbol.forEach(print);
    cout << endl;
    
    // Eliminación segura
    cout << "\nEliminando subárbol izquierdo..." << endl;
    arbol.removeSubTree(true, false);
    
    cout << "Recorrido después de eliminar: ";
    arbol.forEach(print);
    cout << endl;
}

void testArbolInt() {
    cout << "\n=== TEST ARBOL INT ===" << endl;
    
    BinaryTree<int> arbol(100);
    arbol.insertSubTree(BinaryTree<int>(50), true);
    arbol.insertSubTree(BinaryTree<int>(150), false);
    
    cout << "Tamaño del árbol: " << arbol.getSize() << endl;
    cout << "Altura: " << arbol.getHeight() << endl;
    cout << "Hojas: " << arbol.countLeaves() << endl;
    
    // Eliminación por valor (no por puntero)
    cout << "\nEliminando el valor 50..." << endl;
    arbol.remove(50);
    cout << "Tamaño después de eliminar: " << arbol.getSize() << endl;
}

int main() {
    testArbolString();
    testArbolInt();
    
    cout << "\n=== TODAS LAS PRUEBAS COMPLETADAS ===" << endl;
    return 0;
}