#include <iostream>
#include "Queue/queue.hpp"
#include <fstream>  
#include <string>  
#include <sstream>

using namespace std;

class Jugador {
    string nombre;
    Queue<int> mazoActual;

    public:
    Jugador() {
        nombre = "Jugador";
        mazoActual = Queue<int>();
    }

    string getNombre() {
        return nombre;
    }
    
    void setNombre(string nombreEntrada) {
        this->nombre = nombreEntrada;
    }
    
    int obtenerLongitudMazo() {
        return mazoActual.getLength();
    }

    void agregarCarta(int carta) {
        mazoActual.enqueue(carta);
    }
    
    int sacarCarta() {
        if (!mazoActual.isEmpty()) {
            int carta = mazoActual.getFront();
            return carta;
        } else {
            return -1;
        }
    }

    void removerCarta() {
        if (!mazoActual.isEmpty()) {
            mazoActual.dequeue();
        }
    }

    bool tieneMazo() {
        return !mazoActual.isEmpty();
    }

    void vaciarMazo() {
        while (!mazoActual.isEmpty()) {
            mazoActual.dequeue();
        }
    }

    void unirMazoObtenidoDuranteGuerra(Queue<int>& mazoTransferir) {
        while (!mazoTransferir.isEmpty()) {
            mazoActual.enqueue(mazoTransferir.getFront());
            mazoTransferir.dequeue();
        }
    }
};

class Guerra {

    /*es el metodo encargado de obtener el mazo de los jugadores, analiza las primeras dos lineas que 
    representan el numero de cartas de cada jugador y apila su mazo*/
    void obtenerMazo(Jugador& jugadorUno, Jugador& jugadorDos, std::ifstream& archivo) {
        
        /* procesar mazo del jugadorUno */
        for (int i = 0; i < 26; i++) {
                int carta;
                archivo >> carta;
                jugadorUno.agregarCarta(carta);
            }

        /* procesar mazo del jugadorDos */
        for (int i = 0; i < 26; i++) {
            int carta;
            archivo >> carta;
            jugadorDos.agregarCarta(carta);
        }
}

    void jugar(Jugador &jugadorUno, Jugador &jugadorDos) {
        int cartaJugadorUno;
        int cartaJugadorDos;
        int cantidadMovimientos = 0; /* se usa para definir la cantidad de movimientos jugados en una partida */
        Queue<int> mazoTransferir; /*se usa para guardar el mazo que se obtiene durante la guerra*/
        while(jugadorUno.tieneMazo() && jugadorDos.tieneMazo()){
            cartaJugadorUno = jugadorUno.sacarCarta();
            cartaJugadorDos = jugadorDos.sacarCarta();
            jugadorUno.removerCarta();
            jugadorDos.removerCarta();    
            cantidadMovimientos++;
            if(cartaJugadorUno > cartaJugadorDos){
                jugadorUno.agregarCarta(cartaJugadorUno);
                jugadorUno.agregarCarta(cartaJugadorDos);
            } else if (cartaJugadorUno < cartaJugadorDos){
                jugadorDos.agregarCarta(cartaJugadorUno);
                jugadorDos.agregarCarta(cartaJugadorDos);
            } else {
                bool ganoUno = false;
                bool ganoDos = false;
                jugar(jugadorUno, jugadorDos, ganoUno, ganoDos, mazoTransferir,cantidadMovimientos);
                if(ganoUno){
                    jugadorUno.agregarCarta(cartaJugadorUno);
                    jugadorUno.agregarCarta(cartaJugadorDos);
                    jugadorUno.unirMazoObtenidoDuranteGuerra(mazoTransferir);
                } else if (ganoDos){
                    jugadorDos.agregarCarta(cartaJugadorUno);
                    jugadorDos.agregarCarta(cartaJugadorDos);
                    jugadorDos.unirMazoObtenidoDuranteGuerra(mazoTransferir);
                } else {
                break;
                }    
        }
    }
    if(jugadorUno.tieneMazo() && !jugadorDos.tieneMazo()){
        mostrarResultados("ganoUno", jugadorUno, jugadorDos,cantidadMovimientos);
    } else if (!jugadorUno.tieneMazo() && jugadorDos.tieneMazo()){
        mostrarResultados("ganoDos", jugadorUno, jugadorDos,cantidadMovimientos);
    } else if (!jugadorUno.tieneMazo() && !jugadorDos.tieneMazo()){
        mostrarResultados("empate", jugadorUno, jugadorDos,cantidadMovimientos);
    }
}

    void jugar(Jugador& jugadorUno, Jugador& jugadorDos, bool& ganoUno, bool& ganoDos, Queue<int>& mazoTransferir, int &cantidadMovimientos) {
        /* se juega una guerra entre los dos jugadores, se comparan las cartas y se determina el ganador */
        if(jugadorUno.obtenerLongitudMazo() != 0 || jugadorDos.obtenerLongitudMazo() != 0) {

        int cartaJugadorUnoPrimera = jugadorUno.sacarCarta();
        int cartaJugadorDosPrimera = jugadorDos.sacarCarta();
        jugadorUno.removerCarta();
        jugadorDos.removerCarta();
        cantidadMovimientos++;
        int cartaJugadorUnoComparar = jugadorUno.sacarCarta();
        int cartaJugadorDosComparar = jugadorDos.sacarCarta();
        cantidadMovimientos++;
        jugadorUno.removerCarta();
        jugadorDos.removerCarta();
        mazoTransferir.enqueue(cartaJugadorUnoPrimera);
        mazoTransferir.enqueue(cartaJugadorDosPrimera);
        mazoTransferir.enqueue(cartaJugadorUnoComparar);
        mazoTransferir.enqueue(cartaJugadorDosComparar);
        
        if (cartaJugadorUnoComparar == cartaJugadorDosComparar) {
            this->jugar(jugadorUno,jugadorDos, ganoUno, ganoDos, mazoTransferir, cantidadMovimientos);
        } if (cartaJugadorUnoComparar > cartaJugadorDosComparar || jugadorDos.obtenerLongitudMazo() == 0) {
            ganoUno = true;
        } else if (cartaJugadorUnoComparar < cartaJugadorDosComparar || jugadorUno.obtenerLongitudMazo() == 0) {
            ganoDos = true;
        }
}
}
    /*es el metodo encargado de mostrar los resultados de la partida, recibe el estado del juego y los jugadores
    y muestra el resultado correspondiente*/
    void mostrarResultados(string estadoJuego, Jugador& jugadorUno, Jugador& jugadorDos, int cantidadMovimientos) {
        if(estadoJuego == "empate"){
            cout << "Empate " << endl;
        } else if (estadoJuego == "ganoUno"){
            cout << "Ganador: " << jugadorUno.getNombre() << endl;
        } else if (estadoJuego == "ganoDos"){
            cout << "Ganador: " << jugadorDos.getNombre() << endl;
        } else {
            cout << "No se ha jugado ninguna partida." << endl;
        }
        cout << "Cantidad de movimientos: " << cantidadMovimientos << endl;
        jugadorUno.vaciarMazo();
        jugadorDos.vaciarMazo();
    }

    public:

    Guerra(){
        Jugador jugadorUno;
        Jugador jugadorDos;
        ifstream archivo("entrada.txt");
        if(archivo.is_open()) {
        int cantidadPartidas=0;
        int partidaActual;
        string nombreUno, nombreDos;
        archivo >> cantidadPartidas;
        cout << "Ingrese el nombre del jugador uno: ";
        cin >> nombreUno;
        cout << "Ingrese el nombre del jugador dos: ";
        cin >> nombreDos;
        jugadorUno.setNombre(nombreUno);
        jugadorDos.setNombre(nombreDos);
        for(partidaActual = 0; partidaActual < cantidadPartidas; partidaActual++){
        obtenerMazo(jugadorUno, jugadorDos, archivo);
        cout << "Partida " << partidaActual + 1 << ":" << endl;
        cout << jugadorUno.getNombre() << " vs " << jugadorDos.getNombre() << endl;
        jugar(jugadorUno, jugadorDos);
        }
        archivo.close();
        }else {
            cout << "No se pudo obtener la entrada." << endl;
        }
    }
};

int main() {
    /*se crea un objeto de la clase Guerra, que se encarga de gestionar el juego*/
    Guerra guerra;
    return 0;
}