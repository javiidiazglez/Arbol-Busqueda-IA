/** Universidad de La Laguna, Escuela Superior de Ingeniería y Tecnología.
 *  INTELIGENCIA ARTIFICIAL: **PRÁCTICA DE BÚSQUEDA**.
 *  Integrantes del grupo:
 *  - Daniel Nuez Wehbe
 *  - José Javier Díaz González
 *  - Ricardo Fariña Mesa 
 *
 *  Enunciado del problema:
 * 
 *   Un coche autónomo se puede suponer rectangular de dimensiones M x N 
 *   y constituido por celdas libres y ocupadas, donde el coche puede efectuar acciones 
 *   de movimiento, una cada vez, desde la casilla actual a una de las 4-vecinas 
 *   (Norte, Sur, Este u Oeste) que no se encuentre ocupada. Las casillas ocupadas 
 *   corresponden a obstáculos. Las casillas libres corresponden con celdas libres 
 *   de obstáculos.
 **/

#include "coche.hpp"

#include <string>
#include <chrono>

bool esValido(int& valor)   // Cuando haces una entrada revisa la entrada
{
    if(!(cin >> valor))
    {
        cin.clear();    // Limpiamos
        cin.ignore(1000, '\n');   // Eliminamos el contenido
        cout << endl << "\E[31mLa respuesta no ha sido un número\E[39m" << endl;
        return 1;
    }    

    return 0;
}

pair<int, int> crearVehiculo(Mapa_t mapa, int filas, int columnas)      // Método para introducir el vehículo en el mapa.
{
    pair<int, int> v;
    cout << endl << "\E[93mDETERMINACIÓN DEL VEHÍCULO.\E[93m"<<endl;
        do
        {
            cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m del vehículo: \E[97m";
            cin >> v.first;
            cout << "\E[94m- Introduzca la posición \E[97mj\E[94m del vehículo: \E[97m";
            cin >> v.second;

            if(v.first > 0 && v.second > 0 && v.first < (filas - 1) && v.second < (columnas - 1))           // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
            {                                                                                               // Arriba, izquierda, abajo y derecha.
                mapa.rellenarManual(v.first, v.second, '&');                                                // Guarda en la posición pair 'v' el vehículo, '&'               
            }
            else
            {
                cout << endl << "\E[31m--> Error de posición: Introduzca el vehículo en una posición \E[93mviable \E[93m\E[97m(no en los bordes)." << endl;
            }
        } 
        while (v.first <= 0 || v.second <= 0 || v.first >= (filas - 1) || v.second >= (columnas - 1));      // if(-1)
    
    return v;
}

pair<int, int> crearDestino(Mapa_t mapa, int filas, int columnas, pair<int, int> v)     // Método para introducir el destino en el mapa.
{
    pair<int, int> d;

    cout << endl << "\E[93mDETERMINACIÓN DEL DESTINO.\E[93m" << endl;
        do
        {
            cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m del destino: \E[97m";
            cin >> d.first;
            
            cout <<  "\E[94m- Introduzca la posición \E[97mj\E[94m del destino: \E[97m";
            cin >> d.second;

            if(d.first > 0 && d.second > 0 && d.first < (filas - 1) && d.second < (columnas - 1) && d != v)         // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
            {                                                                                                       // Arriba, Izquierda, abajo y derecha, además de que no esté en la posición del vehículo.
                mapa.rellenarManual(d.first, d.second, '=');                                                        // Guarda en la posición pair 'd' el destino, '='.
            }
            else
            {
                cout << endl << "\E[31m--> Error de posición: Introduzca el destino en una posición válida. \E[31m" << endl;
            }
        } 
        while (d.first <= 0 || d.second <= 0 || d.first >= (filas - 1) || d.second >= (columnas - 1) || d == v);

    return d;
}

/**
 * GENERACIÓN DE MAPAS ALEATORIOS
 **/

// void crearAleatorio(Mapa_t& mapa, Coche_t& coche)
// {
//     // int tam = ((mapa.getN() * mapa.getM()) * 2) / 100;

//     srand(time(NULL)); // Caso random = NULL

//     pair<int, int> v = {1, 1};
//     pair<int, int > d, o;
//     int contador = 0;

//     for(int i = 0; i < 2; i++)
//     {   
//         do
//         {
//             contador++;
            
//             o.first = rand() % mapa.getN(); // caso random first
//             o.second = rand() % mapa.getM(); // caso random second
//         }
//         while (o.first <= 0 || o.second <= 0 || o.first >= (mapa.getN() - 1) || o.second >= (mapa.getM() - 1) || v == d);
                
//         if(i == 0)
//         {
//             v = o;
//             coche.setPosicion(v);
//         }
//         else
//         {
//             d = o;
//         }
//     }

//     mapa.rellenarCoche(v, d);
// }

bool algoritmoBusqueda(Mapa_t& mapa, Coche_t& coche, int heur)      // Ejecución del algoritmo de búsqueda con la función heurística especificada.
{
    bool heuristica = false;
    string heuristicaString;

    if(heur == 1)
    {
        heuristica = true;
        heuristicaString = "Manhattan"; 
    }
    else
    {
        heuristica = false;
        heuristicaString = "Euclídea";
    }

    cout << "\E[96m\e[7mA* con heurística " << heuristicaString << ".\E[96m\e[0m\e[0m" << endl << endl;

    auto t1 = chrono::high_resolution_clock::now();     // Antes de ejecutar el algoritmo, tomamos el instante de inicio.
    
    if(coche.aStar(mapa, heuristica))
    {
        auto t2 = chrono::high_resolution_clock::now(); // Después de ejecutar el algoritmo de manera satisfactoria,
                                                        // tomamos el instante de finalización.

        cout << "\E[95mExiste el camino.\E[95m" << endl;        

        mapa.write(cout);

        auto duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();     // Calculamos la duración total de ejecución del algoritmo.

        mapa.resetMapa(coche.getPosicion());       // Preparamos el mapa por si fuera necesario ejecutar otro algoritmo heurístico.

        cout << "\E[97m--> La función " << "\E[94m" << heuristicaString << "\E[97m toma: " << "\E[93m" << duration << " milisegundos.\E[93m" << endl;
        cout << "\E[97m--> El tamaño del camino seguido es de: " << "\E[93m" << coche.getCamino().size() <<".\E[93m" << endl;
        cout << "\E[97m--> Los nodos generados son: " << "\E[93m" << coche.getContNodosGenerados() << ".\E[93m" << endl << endl;

        return 0;
    }
    else
    {
        cout << "\E[31mNo existe solución para este caso expuesto.\E[31m" << endl;
        return 1;
    }
}

int main(void)
{
    int opcion;
    int filas, columnas, porcentajes_obstaculos, numero_porcentajes;
    fstream ficheroEntrada;     // Variable que almacena el fichero del que se lee
    string nombreFichero;       // Variable que almacena el nombre del fichero para después abrirlo
    pair<int, int> o, v, d;     // obstáculo, vehículo y destino
    Mapa_t mapa;                // Mapa vacío
    Coche_t coche;              // Coche declarado a posición (0, 0)

    /**
     * GENERACIÓN DE MAPAS ALEATORIOS
     **/
    // ofstream outfile;
    // outfile.open("prueba.txt", ofstream::out | ofstream::trunc);

    cout << "\nPractica 1: INTELIGENCIA ARTIFICIAL. PRÁCTICA DE BÚSQUEDA.\n";
    do
    {
        cout << "\n\E[32m¿Desea leer desde fichero? \e[95m\e[1m(0 NO, 1 SI)\e[0m\e[95m: \E[97m"; // Si el usuario presiona 1 lee desde fichero, no está hecho de momento la opción manual
        cin >> opcion;
        
        //system("clear");
    }
    while (opcion !=0 && opcion != 1);
    
    if(opcion)
    {
        do
        { 
            cout << endl << "\E[93m- Introduzca el nombre del fichero: \E[97m";
            cin >> nombreFichero;

            ficheroEntrada.open(nombreFichero.c_str(), fstream::in);    // Se abre el fichero de entrada
            if(ficheroEntrada.is_open())    // Comprobamos que el fichero se haya abierto bien
            {
                ficheroEntrada >> filas >> columnas;    // Las dos primeras líneas del fichero son las filas y las columnas, las almacenamos en sus respectivas variables
                
                ficheroEntrada >> v.first >> v.second;
                ficheroEntrada >> d.first >> d.second;

                coche.setPosicion(v);
                mapa.setDestino(d);

                mapa.setMapa(filas, columnas, ficheroEntrada, v, d);  // Se pasa al método setMapa lo necesario para construir todo el mapa sin punto de salida ni de llegada
            }
            else    // En caso de error al abrir el fichero se indica al usuario y termina la ejecución del programa
            {
                cout << endl << "\E[31m--> Error: El fichero no existe o no tiene permisos\E[31m" << endl;
            }
        }    
        while(ficheroEntrada.is_open() != 1);
    }
    else    // Opción manual
    {      
        cout << endl << "\E[93mDIMENSIONES DEL TABLERO.\E[93m" << endl;

        do
        {
            cout << endl << "\E[94m- Introduzca el número de \E[97mfilas\E[94m de la tabla \e[92m\e[4m(>= 4)\e[0m: \E[97m";        
        } 
        while (esValido(filas) || filas < 4);
        

        do
        {
            cout << "\E[94m- Introduzca el número de \E[97mcolumnas\E[94m de la tabla \e[92m\e[4m(>= 4)\e[0m: \E[97m";      
        } 
        while (esValido(columnas) || columnas < 4 || columnas != filas);

        //system("clear");

        mapa.setN(filas);
        mapa.setM(columnas);
        mapa.setMapa(filas, columnas);

        do
        {
            cout << endl << "\E[32m¿Desea introducir manualmente los obstáculos o generarlos aleatoriamente? \e[95m\e[1m(0 Aleatorio, 1 Manual)\e[95m\e[0m: \E[97m";     
            cin >> opcion;
        }
        while (opcion !=0 && opcion != 1);

        //system("clear");

        v = crearVehiculo(mapa, filas, columnas);
        d = crearDestino(mapa, filas, columnas, v);
        coche.setPosicion(v);
        mapa.setDestino(d);
        
        if(opcion) //  manual obstaculos
        {

            cout << endl << "\E[93mDETERMINACIÓN DE OBSTÁCULOS.\E[93m"<<endl;

            do
            {
                cout << endl << "\E[91m-> (Introduzca \E[97m0 0\E[91m para salir) \E[91m" << endl;      
                cout << endl << "\E[94m- Introduzca la posición \E[97mi\E[94m de un obstáculo: \E[97m";      
                cin >> o.first;
                cout  << "\E[94m- Introduzca la posición \E[97mj\E[94m de un obstáculo: \E[97m";      
                cin >> o.second;
                               
                if(d.first > 0 && d.second > 0 && d.first < (filas - 1) && d.second < (columnas - 1) && o != v && o != d 
                && '#' != mapa.getMapa()[mapa.getMapaPos(o.first, o.second)].getValor())           // Comprueba si la posición seleccionada no está en ninguna pared, el orden:
                {                                                                                  // Arriba, Izquierda, abajo y derecha, además de que no esté en la posición del vehículo ni del destino.
                    mapa.rellenarManual(o.first, o.second, '#');  
                    //system("clear");                                                               // Guarda en la posición pair 'o' un obstáculo, '#'.                                                                           
                }
                else
                {
                    cout << endl << "\E[31m--> Error de posición: Introduzca el obstáculo en una posición válida. \E[31m" << endl;
                }
            } 
            while ((o.first != 0) && (o.second != 0));              // Si ambas posiciones del pair 'o' son 0, se sale del bucle.
                
            for(int i = 1; i < (filas - 1); i++)       
            {
                for (int j = 1; j < (columnas - 1); j++)
                {
                    if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
                    {
                        mapa.rellenarMovimientos(i, j);     
                    }
                }
            }
        }
        else // Caso aleatorios 
        {               
            cout << endl << "\E[93mDETERMINACIÓN DE OBSTÁCULOS.\E[93m"<<endl;
            do
            {
                do
                {
                    cout << endl << "\E[94mIntroduza el \E[97mporcentaje\E[94m de obstaculos que desee: \E[97m";    // El usuario introduce un %
                } 
                while(esValido(porcentajes_obstaculos));

                if(porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100)
                {
                    cout << endl << "\E[31m--> Error: Introduzca un porcentaje dentro del rango \E[97m0-100\E[31m.\E[39m" << endl;  // Error rango
                }
                
            } while (porcentajes_obstaculos < 0 || porcentajes_obstaculos > 100);  // Hasta < 0 o > 100            

            int tam = ((filas * columnas) * porcentajes_obstaculos) / 100;      // Ejemplo: 10x10 10% tam = 10

            srand(time(NULL)); // Caso random = NULL

            for(int i = 0; i < tam; i++)
            {   
                do
                {
                    o.first = rand() % filas; // caso random first
                    o.second = rand() % filas; // caso random second
                }
                while (o.first <= 0 || o.second <= 0 || o.first >= (filas - 1) 
                || o.second >= (columnas - 1) || o == v || o == d);
                    
                mapa.rellenarManual(o.first, o.second, '#');
            }

            for(int i = 1; i < (filas - 1); i++)       
            {
                for (int j = 1; j < (columnas - 1); j++)
                {
                    if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
                    {
                        mapa.rellenarMovimientos(i, j);
                    }
                }
            }
        }
    }

    //system("clear");

    int heuristica = 0;

    cout << endl<<"\E[93mFUNCIÓN HEURÍSTICA.\E[93m"<<endl;

    do{
        cout << endl <<"\E[94m1.-Distancia de \E[94m\E[97mManhattan.\E[0m" << endl <<"\E[94m2.-Distancia de \E[94m\E[97mEuclidean.\E[0m" << endl;
        cout << "\E[94m3.-Ambas\E[94m" << endl << endl <<"\E[92mIndique con un valor numérico la \E[97mfunción heurística\E[0m \E[92mque desea emplear \e[95m(1|2|3): \E[97m";
    }
    while ((esValido(heuristica)) && (heuristica == 1 || heuristica == 2 || heuristica == 3));

    //system("clear");

    mapa.write(cout);   // Al final, se imprime por pantalla el contenido del mapa.    

    vector<pair<int, int>> resultado;
    bool res;

    if(heuristica == 3) // Ambas (Las dos)
    {
        if(!algoritmoBusqueda(mapa, coche, 1)) 
        {
            res == !algoritmoBusqueda(mapa, coche, 0);
        }
    }
    else if(heuristica == 2)
    {
        res = !algoritmoBusqueda(mapa, coche, 0);
    }
    else if(heuristica == 1)
    {
        res = !algoritmoBusqueda(mapa, coche, 1);
    }

    if(res)
        return 0;
    else
        return 1;


    /**
     * GENERACIÓN DE MAPAS ALEATORIOS
     **/

    // pair<int, int> fichero;
    // int iteracion = 1;
    

    // while(1)
    // {
    //     cout << "Iteración: " << iteracion << endl;
    //     for(int i = 1; i < (filas - 1); i++)
    //     {
    //         for(int j = 1; j < (columnas - 1); j++)
    //         {
    //             fichero.first = i;
    //             fichero.second = j;
    //             if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() == '#')
    //                 mapa.getCeldaPos(fichero).setValor('.');
    //         }
    //     }        

    //     crearAleatorio(mapa, coche);

    //     mapa.resetMapa(coche.getPosicion());        

    //     int tam = ((filas * columnas) * porcentajes_obstaculos) / 100;      // Ejemplo: 10x10 10% tam = 10

    //     srand(time(NULL)); // Caso random = NULL

    //     for(int i = 0; i < tam; i++)
    //     {   
    //         do
    //         {
    //             o.first = rand() % filas; // caso random first
    //             o.second = rand() % filas; // caso random second
    //         }
    //         while (o.first <= 0 || o.second <= 0 || o.first >= (filas - 1) || o.second >= (columnas - 1) || o == v || o == d);
                    
    //         mapa.rellenarManual(o.first, o.second, '#');
    //     }

    //     for(int i = 1; i < (filas - 1); i++)       
    //     {
    //         for (int j = 1; j < (columnas - 1); j++)
    //         {
    //             if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() != '#')
    //             {
    //                 mapa.rellenarMovimientos(i, j);     
    //             }
    //         }
    //     }

    //     if(coche.aStar(mapa, 1))
    //     {
    //         opcion = 1;
    //         outfile << filas << ' ' << columnas << endl;
    //         outfile << coche.getPosicion().first << ' ' << coche.getPosicion().second << endl;
    //         outfile << mapa.getDestino().first << ' ' << mapa.getDestino().second << endl;

    //         for(int i = 1; i < (filas - 1); i++)
    //         {
    //             for(int j = 1; j < (columnas - 1); j++)
    //             {
    //                 if(mapa.getMapa()[mapa.getMapaPos(i, j)].getValor() == '#')
    //                     outfile << i << ' ' << j << endl;
    //             }
    //         }
    //         outfile.close();
    //     }
    //     else
    //     {
    //         opcion = 0;
    //     }


    //     mapa.resetMapa(coche.getPosicion());


    //     if(coche.aStar(mapa, 0) && opcion)
    //     {
    //         return 0;
    //     }

    //     iteracion++;

    // }

    return 1;
}
