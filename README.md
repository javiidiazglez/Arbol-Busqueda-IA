# Práctica de búsqueda

Repositorio de la Práctica 1 de Búsqueda de Inteligencia Artificial - **2º Año de carrera**

## Algoritmo A*

En este fichero se exponen las instrucciones de ejecución del programa realizado.

### Compilación
Para compilar el programa, basta con situarnos en la carpeta del proyecto y ejecutar el siguiente comando:

> make

Esto nos creará varios ficheros, pero el más importante es el que se llama

> cocheAutonomo

### Ejecución del programa
Para ejecutar el programa escribimos en la terminal:
> ./cocheAutonomo

## Programa:
Al principio de la ejecución, bastará con seguir el menú. Se nos pedirá si tendremos que leer el fichero o no. 
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/leer_fichero_no.png)

En el caso que lo lea por fichero, se selecciona por ejemplo, un mapa de 50x50 con 25% de obstáculo
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/leer_fichero_si.png)

A continuación se nos pedirá las dimensiones de las **filas y columnas** respectivamentes. Pongamos por ejemplo un mapa de 50x50.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/dimensiones.png)

Ahora seleccionamos los obstáculo, selecciona donde está la **posición**del vehículo, el **destino** y el **porcentaje** de obstáculo de forma aleatoria.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/vehiculo_aleatorio.png)

Si queremos que la determinación de obstáculo sea manual, se escribirá con sus filas y columnas donde estará cada posición
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/vehiculo_manual.png)

Cuando se acaben de introducir todos los datos, se mostrará por pantalla el mapa generado.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/imprimir_tabla.png)

Una vez generado el mapa, se mostrará el resultado de utilizar el algoritmo A* en él, con la o las funciones heurísticas que deseemos.
![alt text](https://raw.githubusercontent.com/alu0101128894/Arbol-Busqueda-IA/main/img/funcion_heuristica.png)
![alt text](https://github.com/alu0101128894/Arbol-Busqueda-IA/blob/main/img/tabla_existe.png)

Para finalizar, se mostrará como quedará un mapa de 50x50 con 25% de obstáculos.
![alt text](https://github.com/alu0101128894/Arbol-Busqueda-IA/blob/main/img/tabla-50x50-25.png)