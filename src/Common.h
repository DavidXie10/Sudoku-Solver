//Source: http://jeisson.ecci.ucr.ac.cr/progra2/2019b/ejemplos/#_trivia_versi%C3%B3n_1
// Impede the use of copies

/**
 * \mainpage
 * # Proyecto 01 Programación II - Sudoku solver
 * 
 * ## Problema a resolver.
 * 
 * ### Construir un comando que recibe niveles cuadrados de sudoku y encuentra su solución
 * 
 * El usuario le envía un sudoku al programa ya sea por la entrada estándar o por un archivo y el programa debe imprimir, donde el usuario se lo pida (entrada estándar o archivo) una solución. La primera solución válida que encuentre es suficiente, no hace falta imprimir múltiples soluciones. Para eso el programa debe poder entender la entrada como una matriz, donde deba interpretar los "." como los espacios vacíos que pueden ir los números. La manera a resolver el Sudoku es de izquierda a derecha de arriba hacia abajo. Asimismo, el sudoku debe ser de tamaño ajustable cuadrado y las cajas pueden ser de distintas dimensiones.
 * 
 * 
 * Además, el README debe proveer ayuda  al usuario para saber cómo instalarlo, usarlo y cómo agregar casos de pruebas. Se debe llevar un control de versiones a través de repositorios de Git. El programa debe imprimir la versión que se encuentra o el mensaje de ayuda si se pide.


* ### Conversión de niveles
* Otro de los problemas a resolver es el de la conversión de niveles. Es decir que dado un caso de prueba, sea textual o binario, el programa debe ser capaz de convertir dicho nivel de sudoku de formato de texto a binario y viceversa, siempre que se provea la opción ``-c`` junto al comando. Convertir no resuelve el nivel, sólo lo traduce de un formato a otro. Por otra parte, si tanto el formato de entrada como el de salida es el mismo, sólo transporta los datos de un lugar a otro. 
* 
* 
* Hay que tener en cuenta que el orden de las opciones que se proveen es arbitrario y que, si la salida es textual, debe ser con formato y por ello, usar n espacios en blanco como separadores entre bloques verticales y un cambio de línea entre bloques horizontales. Por otro lado, si la salida es binaria y la entrada textual, sale la dimensión y seguidamente, uno tras otro, cada valor de la matriz, en donde los puntos se sustituyen por ceros, todo en formato binario. En los casos en los que el formato sea el mismo, se copian los datos desde la entrada indicada hacia la salida indicada, tal como está.

* ## Equipo de desarrollo

* * **Juan Ignacio Pacheco**
* 
* 
* * **David Xie Li**

* Este proyecto es parte del curso de [**CI-0113 Programacion II**](http://jeisson.ecci.ucr.ac.cr/progra2/2020a/proyecto01/) de la Universidad de Costa Rica.
Realizado durante el primer semestre del año 2020.

* ### Links a las clases del proyecto y estructura del código fuente
* - Sudoku
* - Arguments
* - SudokuLevel
* - Convert

* De primero tenemos a la clase **Sudoku**. Esta es la clase controladora que el main usará para correr. Lo primero que genera esta clase es una instancia de la clase **Arguments**. Esta clase analiza los argumentos con los que se invocó. Una vez analizado los argumentos se genera una instancia de la clase **Convert** en Sudoku. Si el usuario quiere la ayuda o la version con los parámetros `--help` o `--version` respectivamente, lo imprime y acaba la ejecución del programa.
* 
* 
* Si el usuario quiere convertir el documento, dentro de la instancia Convert se genera una instancia de SudokuLevel que va a funcionar como colchón donde guardar la matriz con los datos que se quiere para convertirlos al formato, esto con el fin de reutilizar el código de lectura y escritura de SudokuLevel. Por último si el usuario quiere la solución del sudoku, en la clase Sudoku se genera una instancia de **SudokuLevel** que va a proceder a solucionarse si es que tiene solución o a imprimir que no es posible resolverlo.

* * Los archivos que pertenecen a la biblioteca dinámica son: SudokuLevel.cpp, SudokuLevel.h, Convert.cpp, Convert.h.
* * Los archivos que pertenecen al comando: Arguments.cpp, Arguments.h.
* * Los archivos que pertenecen al programa de pruebas: main.cpp, Sudoku.cpp, Sudoku.h.

* ## Licencia

* CC BY Proyecto 01 Programación II - Sudoku solver
*/

#ifndef COMMON_H
#define COMMON_H

#define DECLARE_RULE5(Class, action) \
        Class(const Class& other) = action; \
        Class(Class&& other) = action; \
        Class& operator=(const Class& other) = action; \
        Class& operator=(Class&& other) = action

#define DISABLE_COPY(Class) \
        DECLARE_RULE5(Class, delete)

#endif // COMMON_H
