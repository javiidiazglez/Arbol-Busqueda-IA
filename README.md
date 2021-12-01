# Práctica de búsqueda

Repositorio de la Práctica 1 de Búsqueda de Inteligencia Artificial - **3º Año de carrera**

## Algoritmo A*

En este fichero se exponen las instrucciones de ejecución del programa realizado.

### Compilación
Para compilar el programa, se necesitará una versión **Linux** y el lenguaje de **C++** instalado. 

Para instalar el lenguaje, se deberá escribir
> sudo apt install g++

También es necesario instalar el paquete *make*

> sudo apt install make

Ahora con situarnos en la carpeta del proyecto y ejecutamos el siguiente comando:

> make

Esto nos creará varios ficheros, pero el más importante está en la carpeta carpeta */bin/* que se llama 

> cocheAutonomo

### Ejecución del programa
Para ejecutar el programa escribimos en la terminal:
> ./bin/cocheAutonomo

## Programa:
#### Al principio de la ejecución, bastará con seguir el menú. Se nos pedirá si tendremos que leer el fichero o no. En este caso, seleccionamos que la entrada sea manual.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/leer_fichero_no.png)

#### A continuación se nos pedirá las dimensiones de las *filas y columnas* respectivamentes. Pongamos por ejemplo de un mapa de (50x50).
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/dimensiones.png)

#### Ahora seleccionamos los obstáculos, selecciona donde está la *posición* del vehículo, el *destino* y el *porcentaje* de los obstáculos de forma aleatoria.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/vehiculo_aleatorio.png)

#### Si queremos que la determinación de obstáculo sea manual, se escribirá con sus *filas* y *columnas*, dónde estará cada posición.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/vehiculo_manual.png)

#### Cuando se acaben de introducir todos los datos, se mostrará por pantalla el mapa generado.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/imprimir_tabla.png)

#### Una vez generado el mapa, se mostrará el resultado de utilizar el algoritmo A* en él, con la o las funciones heurísticas que deseemos.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/funcion_heuristica.png)
![alt text](https://github.com/alu0101128894/Arbol-Busqueda-IA/blob/main/img/tabla_existe.png)

#### En el caso que lo lea por fichero, se selecciona por ejemplo, un mapa de (50x50) con 25% de obstáculos.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/leer_fichero_si.png)

#### A continuación se mostrará como quedará un mapa seleccionado por fichero.
![alt text](https://github.com/alu0101128894/Arbol-Busqueda-IA/blob/main/img/tabla-50x50-25.png)
