#include "celda.hpp"

Celda_t::Celda_t():     // Constructor por defecto.
    valor_('\0'),
    padre_(),
    movimientos_(),
    valorF_(),
    valorG_(0),
    valorH_()
    {}

Celda_t::~Celda_t(void) //Destructor.
{
    destroyCelda();
}

void Celda_t::destroyCelda(void)    // Se encarga de vaciar el contenido de los atributos, hay que hacerlo para el vector de mmovimientos.
{
    setValor('\0');
}

char Celda_t::getValor(void)    // Devuelve el símbolo de la celda.
{
    return valor_;
}

vector<pair<int, int>> Celda_t::getMovimientos(void)   // Devuelve el vector de movimientos.
{
    return movimientos_;
}

pair<int, int> Celda_t::getMovimiento(int i)   // Devuelve un movimiento, según el valor de i sea 0, 1, 2 o 3.
{
    return movimientos_[i];
}

pair<int, int> Celda_t::getPadre(void)  // Devuelve la posición de la celda "padre".
{
    return padre_;
}

int Celda_t::getF(void)    // Devuelve el valor total acumulado.
{
    return valorF_;
}

int Celda_t::getG(void)     // Devuelve el valor del movimiento  .
{
    return valorG_;
}

int Celda_t::getH(void)     // Devuelve el valor heurístico del movimiento.
{
    return valorH_;
}

void Celda_t::setValor(char valor)  // Set del símbolo de la celda.
{
    valor_ = valor;
}

void Celda_t::setMovimientos(vector<pair<int, int>> movimientos)   // Set del vector de movimientos de la celda.
{
    movimientos_ = movimientos;
}

void Celda_t::setPadre(pair<int, int> padre)
{
    padre_ = padre;
}

void Celda_t::setF(void)
{
    valorF_ = valorG_ + valorH_;
}

void Celda_t::setF(int h)
{
    valorF_ = h;
    setH(h);
}

void Celda_t::setG(int g)
{
    valorG_ = g; 
}

void Celda_t::setH(int h)
{
    valorH_ = h;    
}

void Celda_t::resetCost(void) // Método para resetear los costes de las celdas.
{
    setG(0);
    setH(0);
    setF();
}

ostream& Celda_t::write(ostream& os)    // Método para imprimir por pantalla la celda.
{
    if (valor_ == '%')          // amarillo
    {
        os << "\E[33m" << setw(2) << valor_ << "\E[33m";
    }
    else if(valor_ == '&')       // azul
    {
        os << "\E[34m" << setw(2) << valor_ << "\E[34m";
    }
    else if(valor_ == '=')      // rojo
    {
        os << "\E[31m" << setw(2) << valor_ << "\E[31m";
    }
    else if( valor_ == '#')     // verde
    {
        os<< "\E[32m" << setw(2) << valor_ << "\E[32m";
    }
    else                        // blanco
    {
        os << "\E[97m" << setw(2) << valor_ << "\E[97m";
    }

    return os;
}