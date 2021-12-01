#include "mapa.hpp"

Mapa_t::Mapa_t(void):       // Inicializa todo a 0
    m_(0),
    n_(0),
    mapa_(),
    destino_()
{}

Mapa_t::Mapa_t(int n, int m)    // Inicializa a los valores que se le pasan, creo que no lo vamos a utilizar nunca
{
    setM(m);
    setN(n);
    setMapa(n, m);
}

Mapa_t::~Mapa_t(void)   // Limpia la memoria
{
    destroyMapa();
}

void Mapa_t::destroyMapa(void)  // Se encarga de vaciar el contenido de los atributos, hay que hacerlo para mapa
{
    setM(0);
    setN(0);
}

int Mapa_t::getM(void)  // Devuelve las columnas
{
    return m_;
}

int Mapa_t::getN(void)  // Devuelve las filas
{
    return n_;
}

Celda_t* Mapa_t::getMapa(void)  // Devuelve el mapa
{
    return mapa_;
}

int Mapa_t::getMapaPos(int i, int j)    // Como el mapa es un array de una dimensión, sirve para convertir los índices de una matriz
{                                       // para acceder en el array de una dimensión. Ejemplo: en vez de mapa_[4][4], tenemos mapa_[4 + 4 * n_]
    //cout << "Sale: " << (i+j*getN()) << endl;
    return i * getN() + j;
}

Celda_t& Mapa_t::getCeldaPos(pair<int, int> pos)
{
    return mapa_[getMapaPos(pos.first, pos.second)];
}

pair<int, int> Mapa_t::getDestino(void)
{
    return destino_;
}

void Mapa_t::setM(int m)    // Modifica el valor de las columnas
{
    m_ = m; 
}

void Mapa_t::setN(int n)    // Modifica el valor de las filas
{
    n_ = n;
}

void Mapa_t::setMapa(int n, int m)  // Cambia el tamaño del mapa
{
    mapa_ = new Celda_t[n * m];
    rellenarMapa();     // Y genera el mapa vacío
}

fstream& Mapa_t::setMapa(int n, int m, fstream& fichero, pair<int, int> coche, pair<int, int> destino)    // Crea el mapa desde un fichero que se pasa por referencia
{
    setN(n);
    setM(m);
    setMapa(n, m);
    rellenarCoche(coche, destino);
    rellenarObstaculos(fichero);

    return fichero;
}

void Mapa_t::setDestino(pair<int, int> pos)
{
    destino_= pos;
}

void Mapa_t::rellenarMapa(void)     // Rellena el mapa vacío
{
    for(int i = 0; i < getN(); i++)
    {
        for(int j = 0; j < getM(); j++)
        {
            if(i == 0 || j == 0 | i == (getN() - 1) | j == (getM() -1))
            {
                mapa_[getMapaPos(i, j)].setValor('#');      // Asigna el símbolo a las paredes
            }
            else
                mapa_[getMapaPos(i, j)].setValor('.');      // Asigna el símbolo al centro del mapa
        }
    }
}

void Mapa_t::rellenarCoche(pair<int, int> coche, pair<int, int> destino)
{
    mapa_[getMapaPos(coche.first, coche.second)].setValor('&');

    mapa_[getMapaPos(destino.first, destino.second)].setValor('=');
    setDestino(destino);
}

fstream& Mapa_t::rellenarObstaculos(fstream& fichero)               // Rellena al mapa con los obstáculos
{
    pair<int, int> aux;                                             // Son dos enteros juntos, por ejemplo <1, 1>
    while(!fichero.eof())                                           // Lee el fichero hasta el final
    {
        fichero >> aux.first >> aux.second;                         // Lee las coordenadas como un punto en una gráfica, es decir (1,1)

        mapa_[getMapaPos(aux.first, aux.second)].setValor('#');     // Asigna el símbolo a los obstáculos
    }

    for(int i = 1; i < (getN() - 1); i++)                           // Los dos for recorren el mapa evitando los bordes
    {
        for (int j = 1; j < (getM() - 1); j++)
        {
            if(mapa_[getMapaPos(i, j)].getValor() != '#')
            {
                rellenarMovimientos(i, j);                          // Se rellenan los movimientos posibles para cada celda
            }
        }
    }
    
    return fichero;
}

void Mapa_t::rellenarManual(int n, int m, char c)           // Relenar de forma Manual
{
    mapa_[getMapaPos(n, m)].setValor(c);
}

void Mapa_t::rellenarMovimientos(int i, int j)              // Comprueba los 4 posibles movimientos y les pone un 1 en caso de no poder realizarlos
{
    vector<pair<int, int>> aux;
    pair<int, int> dummy;

    if(mapa_[getMapaPos(i, (j - 1))].getValor() != '#')     // Comprueba que el valor a la izquierda de la casilla (i,j) no sea ni un // obstáculo ni un borde
    {
        dummy.first = i;
        dummy.second = j - 1;
        aux.push_back(dummy);                               // Se añade la celda vecina visitable
    }

    if(mapa_[getMapaPos((i - 1), j)].getValor() != '#')     // Comprueba que el valor a la arriba de la casilla (i,j) no sea ni un // obstáculo ni un borde
    {
        dummy.first = i - 1;
        dummy.second = j;  
        aux.push_back(dummy);                               // Se añade la celda vecina visitable
    }

    if(mapa_[getMapaPos(i, (j + 1))].getValor() != '#')     // Comprueba que el valor a la derecha de la casilla (i,j) no sea ni un // obstáculo ni un borde
    {
        dummy.first = i;
        dummy.second = j + 1;
        aux.push_back(dummy);                               // Se añade la celda vecina visitable
    }

    if(mapa_[getMapaPos((i + 1), j)].getValor() != '#')     // Comprueba que el valor a la abajo de la casilla (i,j) no sea ni un // obstáculo ni un borde
    {
        dummy.first = i + 1;
        dummy.second = j;
        aux.push_back(dummy);                               // Se añade la celda vecina visitable
    }
    
    mapa_[getMapaPos(i, j)].setMovimientos(aux);            // Se pasa el vector a la celda para que actualice los movimientos posibles
}

ostream& Mapa_t::write(ostream& os)
{
    cout << endl << "\E[33mImprimiendo...\E[33m" << endl << endl;

    for(int i = 0; i < getN(); i++)                         // Recorre el mapa y va imprimiendo las celdas de una en una
    {
        for(int j = 0; j < getM(); j++)
        {
            mapa_[getMapaPos(i, j)].write(os);   
        }
        cout << endl;
    }
    cout << endl;

    return os;
}

void Mapa_t::resetMapa(pair<int, int> coche)
{
    pair<int, int> aux, dummy = {0, 0};

    for(int i = 1; i < (getN() - 1); i++)
    {
        for(int j = 1; j < (getM() - 1); j++)
        {
            aux.first = i;
            aux.second = j;
            getCeldaPos(aux).setPadre(dummy);
            getCeldaPos(aux).resetCost();
            if(getCeldaPos(aux).getValor() == '&' || getCeldaPos(aux).getValor() == '%')
                getCeldaPos(aux).setValor('.');
        }
    }

    getCeldaPos(coche).setValor('&');
}
