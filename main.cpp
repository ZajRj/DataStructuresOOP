#include <iostream>
#include "Stack/stack.hpp"
#include "List/SinglyList.hpp"
#include "Queue/queue.hpp"
#include <fstream>  
#include <string>  
#include <sstream>

using namespace std;

class Jugador {
    private:
    string nombre;
    Stack<int> mazoActual;
    Stack<int> mazoAuxiliar;

    public:

    Jugador() {
        nombre = "Jugador";
        mazoActual = Stack<int>();
        mazoAuxiliar = Stack<int>();
    }

    void setNombre(string nombreEntrada) {
        this->nombre = nombreEntrada;
    }

    string getNombre() {
        return nombre;
    }
    
    int obtenerLongitudMazo() {
        return mazoActual.getLength();
    }

    void agregarCarta(int carta) {
        mazoAuxiliar.push(carta);
    }
    
    int sacarCarta() {
        if (!mazoActual.isEmpty()) {
            int carta = mazoActual.getTop();
            mazoActual.getTop();
            return carta;
        } else {
            cout << "El mazo esta vacio." << endl;
            return -1; // o cualquier otro valor que indique error
        }
    }

    bool tieneMazo() {
        return !mazoActual.isEmpty();
    }

    bool tieneMazoAuxiliar() {
        return !mazoAuxiliar.isEmpty();
    }

    void moverMazoAuxiliarAMazoActual() {
        while (!mazoAuxiliar.isEmpty()) {
            mazoActual.push(mazoAuxiliar.getTop());
            mazoAuxiliar.pop();
        }
    }

    void vaciarMazo() {
        while (!mazoActual.isEmpty()) {
            mazoActual.pop();
        }
    }

    void transferirCola(Queue<int>& mazoTransferir) {
        while (!mazoTransferir.isEmpty()) {
            mazoActual.push(mazoTransferir.getFront());
            mazoTransferir.dequeue();
        }
    }
};

class Guerra {
    private:
    Jugador jugadorUno;
    Jugador jugadorDos;

    void jugar(Jugador jugadorUno, Jugador jugadorDos) {
        int cartaJugadorUno = jugadorUno.sacarCarta();
        int cartaJugadorDos = jugadorDos.sacarCarta();
        int cantidadMovimientos = 0;

        while(jugadorUno.tieneMazo() && jugadorDos.tieneMazo()){
        if(cartaJugadorUno > cartaJugadorDos){
            jugadorUno.agregarCarta(cartaJugadorUno);
            jugadorUno.agregarCarta(cartaJugadorDos);
            cantidadMovimientos++;
        } else if (cartaJugadorUno < cartaJugadorDos){
            jugadorDos.agregarCarta(cartaJugadorUno);
            jugadorDos.agregarCarta(cartaJugadorDos);
            cantidadMovimientos++;
        } else {
            bool ganoUno = false;
            bool ganoDos = false;
            Queue<int> mazoTransferir;
            jugar(jugadorUno, jugadorDos, ganoUno, ganoDos, mazoTransferir);
            cantidadMovimientos++;

            if(ganoUno){
                jugadorUno.agregarCarta(cartaJugadorUno);
                jugadorUno.agregarCarta(cartaJugadorDos);
                while(!mazoTransferir.isEmpty()){
                    jugadorUno.transferirCola(mazoTransferir);
                }
            } else if (ganoDos){
                jugadorDos.agregarCarta(cartaJugadorUno);
                jugadorDos.agregarCarta(cartaJugadorDos);
                while(!mazoTransferir.isEmpty()){
                    jugadorDos.transferirCola(mazoTransferir);
                }
            } else {
                break;
            }    
        }

        if (!jugadorUno.tieneMazo() && jugadorUno.tieneMazoAuxiliar()) {
            jugadorUno.moverMazoAuxiliarAMazoActual();
        } else if (!jugadorDos.tieneMazo() && jugadorDos.tieneMazoAuxiliar()) {
            jugadorDos.moverMazoAuxiliarAMazoActual();
        }
    }

    if(jugadorUno.tieneMazo() && !jugadorDos.tieneMazo()){
        mostrarResultados("ganoUno", jugadorUno, jugadorDos);
    } else if (!jugadorUno.tieneMazo() && jugadorDos.tieneMazo()){
        mostrarResultados("ganoDos", jugadorUno, jugadorDos);
    } else if (!jugadorUno.tieneMazo() && !jugadorDos.tieneMazo()){
        mostrarResultados("empate", jugadorUno, jugadorDos);
    }

 }

    void mostrarResultados(string estadoJuego, Jugador& jugadorUno, Jugador& jugadorDos) {
        if(estadoJuego == "empate"){
            cout << "Empate" << endl;
        } else if (estadoJuego == "ganoUno"){
            cout << "Gano el jugador uno" << endl;
        } else if (estadoJuego == "ganoDos"){
            cout << "Gano el jugador dos" << endl;
        } else {
            cout << "No se ha jugado ninguna partida." << endl;
        }
        jugadorUno.vaciarMazo();
        jugadorDos.vaciarMazo();
    }

    /*es el metodo encargado de obtener el mazo de los jugadores, analiza las primeras dos lineas que 
    representan el numero de cartas de cada jugador y apila su mazo*/
    void obtenerMazo(Jugador& jugadorUno, Jugador& jugadorDos, std::ifstream& archivo) {
        
        /* procesar mazo del jugadorUno */
        string linea;
        if (getline(archivo, linea)) {
            istringstream iss(linea);
            int carta;
            while (iss >> carta && jugadorUno.obtenerLongitudMazo() < 26) {
                jugadorUno.agregarCarta(carta);
            }
        }
        
        /* procesar mazo del jugadorDos */
        if (getline(archivo, linea)) {
            istringstream iss(linea);
            int carta;
            while (iss >> carta && jugadorDos.obtenerLongitudMazo() < 26) {
                jugadorDos.agregarCarta(carta);
            }
        }
    }

    void jugar(Jugador& jugadorUno, Jugador& jugadorDos, bool& ganoUno, bool& ganoDos, Queue<int>& mazoTransferir) {
        /* se juega una guerra entre los dos jugadores, se comparan las cartas y se determina el ganador */
        int cartaJugadorUnoPrimera = jugadorUno.sacarCarta();
        int cartaJugadorDosPrimera = jugadorDos.sacarCarta();
        int cartaJugadorUnoComparar = jugadorUno.sacarCarta();
        int cartaJugadorDosComparar = jugadorDos.sacarCarta();

        if (cartaJugadorUnoComparar > cartaJugadorDosComparar) {
            ganoUno = true;
            ganoDos = false;
        } else if (cartaJugadorUnoComparar < cartaJugadorDosComparar) {
            ganoUno = false;
            ganoDos = true;
        } else {
            ganoUno = false;
            ganoDos = false;
            jugar(jugadorUno, jugadorDos, ganoUno, ganoDos, mazoTransferir);
        }
        mazoTransferir.enqueue(cartaJugadorUnoPrimera);
        mazoTransferir.enqueue(cartaJugadorDosPrimera);
        mazoTransferir.enqueue(cartaJugadorUnoComparar);
        mazoTransferir.enqueue(cartaJugadorDosComparar);
    }

    public:

    void inicializar(Jugador jugadorUno, Jugador jugadorDos) {
        ifstream archivo("entrada.txt");
        archivo.open("entrada.txt");
        if(archivo.is_open()) {
        int cantidadPartidas=0;
        int partidaActual;
        string nombreUno, nombreDos;
        archivo >> cantidadPartidas;
        nombreUno = "Pedro";
        nombreDos = "Juan";
        jugadorUno.setNombre(nombreUno);
        jugadorDos.setNombre(nombreDos);

        for(partidaActual = 0; partidaActual < cantidadPartidas; partidaActual++){
        obtenerMazo(jugadorUno, jugadorDos, archivo);
        jugar(jugadorUno, jugadorDos);
        }
        archivo.close();
        delete &jugadorUno;
        delete &jugadorDos;
        }else {
            cout << "No se pudo obtener la entrada." << endl;
        }
    }
};

int main() {

    Jugador jugadorUno;
    Jugador jugadorDos;
    Guerra guerra;
    guerra.inicializar(jugadorUno, jugadorDos);

    return 0;
}