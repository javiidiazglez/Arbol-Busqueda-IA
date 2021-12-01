#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Celda_t {
    private:
        char valor_;    // Símbolo que representa esa celda: 
                        // # pared.
                        // $ obstáculo.
                        // & coche.
                        // = destino.
        pair<int, int> padre_;
        vector<pair<int, int>> movimientos_;   // Los movimientos van en este orden: izquierda, arriba, derecha, abajo.

        int valorF_; // Valor total acumulado.
        int valorG_; // Valor del movimiento.                     f = g + h
        int valorH_; // Valor heurístico del movimiento.

        void destroyCelda(void);    // Misma idea que el destroyMap.

    public:

        Celda_t(void);      // Constructor por defecto.

        ~Celda_t(void);     // Destructor.

        char getValor(void);    // Devuelve el símbolo de la celda.
        vector<pair<int, int>> getMovimientos(void);   // Devuelve el vector de movimientos.
        pair<int, int> getMovimiento(int i);   // Devuelve un movimiento, según el valor de i sea 0, 1, 2 o 3.
        pair<int, int> getPadre(void);  // Devuelve la posición de la celda "padre".
        int getF(void);                 // Devuelve F getter.
        int getG(void);                 // Devuelve G.
        int getH(void);                 // Devuelve H.

        void setValor(char valor);  // Set del símbolo de la celda.
        void setMovimientos(vector<pair<int, int>> movimientos);   // Set del vector de movimientos de la celda.
        void setPadre(pair<int, int> padre);
        void setF(void);            // Setter de los valores F, G y H.
        void setF(int h);
        void setG(int g);
        void setH(int h);
        void resetCost(void);       // Método para resetear los costes de las celdas.

        ostream& write(ostream& os);    // Método para imprimir por pantalla la celda.
};