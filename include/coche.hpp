#pragma once

#include "mapa.hpp"

#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <unistd.h>


using namespace std;

class Coche_t
{
    private:   
        pair<int, int> posicion_;           // Almacena la posición del vehículo
        vector<pair<int, int>> camino_;     // Guarda el camino mínimo de manera inversa.                                                                                                            
        int contNodosGenerados_;            // Contador que guarda el número de nodos generados

        void destroyCoche(void);            // Destructor

    public:
        Coche_t();                          // Constructor
        Coche_t(pair<int, int> posicion);   // Constructor de copia
        ~Coche_t();                         // Destructor
        
        pair<int, int> getPosicion(void);       // Getter posiciones
        vector<pair<int, int>> getCamino(void); // Getter caminos
        int getContNodosGenerados(void);        // Getter Contador De los nodos ya generados

        void setPosicion(pair<int, int> posicion);          // Setter posiciones
        void setAppendCamino(pair<int, int>);               // Setter Anexar Caminos
        void setContNodosGenerados(int contNodosGenerados); // Setter Contador Nodos ya generados

        ostream& write(ostream& os);
        
        bool aStar(Mapa_t& mapa, bool heur); // Define el algoritmo A*

        int heuristicaManhattan(pair<int, int> actual, pair<int, int> destino); // Devuelve el valor heurístico de Manhattan
        int heuristicaEuclidean(pair<int, int> actual, pair<int, int> destino); // Devuelve el valor heurístico Euclídeo
};
