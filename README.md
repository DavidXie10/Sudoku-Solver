# Proyecto 01 Programación II - Sudoku solver

## Problema a resolver.

### Construir un comando que recibe niveles cuadrados de sudoku y encuentra su solución


El usuario le envía un sudoku al programa ya sea por la entrada estándar o por un archivo y el programa debe imprimir, donde el usuario se lo pida (entrada estándar o archivo) una solución. La primera solución válida que encuentre es suficiente, no hace falta imprimir múltiples soluciones. Para eso el programa debe poder entender la entrada como una matriz, donde deba interpretar los "." como los espacios vacíos que pueden ir los números. La manera a resolver el Sudoku es de izquierda a derecha de arriba hacia abajo. Asimismo, el sudoku debe ser de tamaño ajustable cuadrado y las cajas pueden ser de distintas dimensiones.


Además, el README debe proveer ayuda  al usuario para saber cómo instalarlo, usarlo y cómo agregar casos de pruebas. Se debe llevar un control de versiones a través de repositorios de Git. El programa debe imprimir la versión que se encuentra o el mensaje de ayuda si se pide.


### Conversión de niveles


Otro de los problemas a resolver es el de la conversión de niveles. Es decir que dado un caso de prueba, sea textual o binario, el programa debe ser capaz de convertir dicho nivel de sudoku de formato de texto a binario y viceversa, siempre que se provea la opción `-c` junto al comando. Convertir no resuelve el nivel, sólo lo traduce de un formato a otro. Por otra parte, si tanto el formato de entrada como el de salida es el mismo, sólo transporta los datos de un lugar a otro. 


Hay que tener en cuenta que el orden de las opciones que se proveen es arbitrario y que, si la salida es textual, debe ser con formato y por ello, usar n espacios en blanco como separadores entre bloques verticales y un cambio de línea entre bloques horizontales. Por otro lado, si la salida es binaria y la entrada textual, sale la dimensión y seguidamente, uno tras otro, cada valor de la matriz, en donde los puntos se sustituyen por ceros, todo en formato binario. En los casos en los que el formato sea el mismo, se copian los datos desde la entrada indicada hacia la salida indicada, tal como está.

## Equipo de desarrollo

* **Juan Ignacio Pacheco**
* **David Xie Li**

Este proyecto es parte del curso de [CI-0113 Programacion II](http://jeisson.ecci.ucr.ac.cr/progra2/2020a/proyecto01/) de la Universidad de Costa Rica.
Realizado durante el primer semestre del año 2020.

## Manual de usuario. 
El programa **sudoku** se invoca desde la raíz del proyecto y de la siguiente forma de ejemplo

        $ bin/sudoku -it test/input003.txt -ot test/output003.txt

la versión anterior sería una invocación en donde la entrada y salida es desde y hacia archivos, no obstante, el programa también admite la entrada de datos desde la entrada estandar(**stdin**) y la salida de datos hacia la salida estandar (**stdout**). Para conocer más acerca de la interfaz y las opciones, se puede pedir ayuda al programa de las siguientes formas

        $ bin/sudoku --help
        $ bin/sudoku -h

con lo cual se desplegará cada opción admitida y su significado, los cuales se destacan en la siguiente tabla

| Opciones   |Significado|
|:------------:|-----------|
| `-c` |Únicamente convierte niveles de sudoku de formato de texto a binario y viceversa. El usuario controlará la conversión con los argumentos `-ib`, `-it`, `-ob`, y `-ot`. En caso de que la entrada y salida sea del mismo formato, sólo lo traslada de la entrada indicada a la salida indicada.    |
| `-ib` | Indica que la entrada será vista en formato **binario**.|
| `-it` | Indica que la entrada será vista en formato **textual**. |
| `-ob` | Indica que la salida será desplegada en formato **binario**.|
| `-ot` |Indica que la salida será desplegada en formato **textual**.|
|`-h`  o  `--help` | Imprime la información básica del programa y termina. Además muestra lo que significa cada parámetro y cómo se invoca el programa. |
|`--version` | Imprime la versión del programa y termina.|
|`files` | El archivo opcional ya sea después de `-ib` o `-it` para indicar que los datos provendrán de ese archivo (con su respectivo formato ya sea binario o textual), o después de `-ot` o `-ob` para indicar que la salida será en ese archivo con el formato indicado.|

Cabe destacar que los valores por defecto, es decir si no se proveen alguno de los argumentos anteriores será:
- Entrada = Entrada estándar (**stdin**).
- Salida = Salida estándar (**stdout**).
- Formato de entrada = Textual.
- Formato de salida = Textual.
- Solo convertir el nivel = false
- Resolver el nivel = true

### Solución del nivel
A continuación se mostrarán ejemplos de invocación de las cuatro posibles combinaciones de entrada textual/binaria y salida textual/binaria en caso de que se quiere resolver el nivel dado, tomando como referencia el archivo **input003.txt** en la carpeta **test** que se muestra a continuación

        $ cat input003.txt

        3

        . . 7   . . 3   5 9 .
        6 . 4   7 5 8   2 . .
        . . 5   . . 9   8 7 6

        . . .   . . 4   . . .
        . . 2   8 7 .   6 . .
        . 7 .   . . .   . . 5

        5 8 .   . . .   . . .
        9 . .   . 8 5   3 2 7
        . . .   . 3 6   4 . .


- **Entrada de archivo textual --> Salida estandár textual**


En este caso la entrada va a ser de un archivo textual, primero viene la dimensión, seguidamente dos cambios de línea y luego los valores de la matriz, donde las celdas llenas se indican con el número que contienen y las vacías con el carácter punto ('.'). Todas las celdas se separan por espacios en blanco y los puntos se sutituyen por ceros en la matriz del sudoku.

        $ bin/sudoku -it test/input003.txt -ot

Se carga el nivel de sudoku del archivo **input003.txt**, se resuelve y luego despliega la solución **textual** en la **salida estandar**, como se muestra a continuación, siguiendo el formato de espacios de entrada, solo que no despliega la dimensión del sudoku.

        8 1 7   6 2 3   5 9 4
        6 9 4   7 5 8   2 1 3
        2 3 5   4 1 9   8 7 6

        1 6 8   5 9 4   7 3 2
        3 5 2   8 7 1   6 4 9
        4 7 9   3 6 2   1 8 5

        5 8 3   2 4 7   9 6 1
        9 4 6   1 8 5   3 2 7
        7 2 1   9 3 6   4 5 8


- **Entrada de archivo textual --> Salida a archivo binario**


En este caso la entrada va a ser de un archivo textual, con el mismo formato de entrada explicado anteriormente.

        $ bin/sudoku -it test/input003.txt -ob output003.bin

Se carga el nivel de sudoku del archivo **input003.txt**, se resuelve y luego despliega la solución, pero en formato **binario** y hacia el archivo **output003.bin**. El formato que siguen los datos binarios consta de n^2 * n^2 números, todos enteros sin signo de 2 bytes, que corresponde a los valores de la solucion del sudoku uno por uno, de izquierda a derecha y de arriba hacia abajo.


- **Entrada de archivo binario --> Salida estandár textual**


En este caso la entrada va a ser de un archivo binario. El cuál consta del tamaño del bloque n, o sea la dimensión, seguido de n^2 * n^2 números, todos enteros sin signo de 2 bytes. Los valores faltantes (puntos '.' en la versión de texto) serán representados por el valor cero.

        $ bin/sudoku -ib test/input003.bin -ot

Se carga el nivel de sudoku del archivo **input003.bin**, se resuelve y luego despliega la solución en formato **textual** y hacia la **salida estandar**.


- **Entrada de archivo binario --> Salida a archivo binario**


En este caso la entrada va a ser de un archivo binario, con el mismo formato explicado anteriormente.

        $ bin/sudoku -ib test/input003.bin -ob output003.bin

Se carga el nivel de sudoku del archivo **input003.bin**, se resuelve y luego despliega la solución en formato **binario**, pero hacia el archivo **output003.bin**. Siguiendo la misma notación de salida binaria explicada en el caso 2.

### Convertir el caso de prueba


Ahora se proveerán los ejemplos de invocación de las cuatro posibles combinaciones de entrada textual/binaria y salida textual/binaria para la conversión de niveles de sudoku de formato de texto a binario y viceversa con la opción `-c` o solo el paso de los datos de un medio a otro en caso de que se quiere "convertir" entre los mismos formatos. Igualmente se utilizará el archivo **input003.txt** mostrado anteriormente.

- **Entrada estandar textual --> Salida estandár textual**


En este caso la entrada va a ser de la entrada estándar y vendrá en formato textual, de la misma forma que viene **input003.txt** por ejemplo para uno de dimensión 3. Todas las celdas se separan por espacios en blanco y los puntos se sutituyen por ceros en la matriz del sudoku. Además para cada **dimensión** dígitos que se ingresan, combinando números y puntos, se deben poner **dimensión** espacios y por cada **dimensión** columnas, hay que poner un cambio de línea adicional.

        $ bin/sudoku -it -c -ot

Con el comando anterior, se espera el ingreso de los datos, y luego despliega en la salida estándar la misma entrada. Cabe destacar que este es el caso en el que solo se copian los datos hacia la salida indicada y no hay conversión porque el formato de entrada y salida es la misma. También se puede redireccionar la entrada con el siguiente comando

        $ bin/sudoku -it -c -ot < test/input003.txt

lo cual produciría en la salida estándar el mismo contenido del archivo

        3

        . . 7   . . 3   5 9 .
        6 . 4   7 5 8   2 . .
        . . 5   . . 9   8 7 6

        . . .   . . 4   . . .
        . . 2   8 7 .   6 . .
        . 7 .   . . .   . . 5

        5 8 .   . . .   . . .
        9 . .   . 8 5   3 2 7
        . . .   . 3 6   4 . .

- **Entrada de archivo textual --> Salida a archivo binario**


En este caso la entrada va a ser de un archivo textual, con el mismo formato de entrada explicado anteriormente.

        $ bin/sudoku -c test/input003.txt -ob input003.bin

Se carga el nivel de sudoku del archivo **input003.txt**, y luego despliega la conversión, pero en formato **binario** por el `-ob` y hacia el archivo **input003.bin**. El formato que siguen los datos binarios, en los casos de prueba, consta de la dimensión, seguido de n^2 * n^2 números, todos enteros sin signo de 2 bytes. Si se desea ver el contenido con un volcado hexadecimal, se ejecuta, desde la carpeta **test/**, el siguiente comando

        $ od -t x1 input003.bin

- **Entrada de archivo binario --> Salida estandár textual**


En este caso la entrada va a ser de un archivo binario por el `-ib`

        $ bin/sudoku -ib test/input003.bin -c

Se carga el nivel de sudoku del archivo **input003.bin**, y luego despliega la converión del caso de prueba en formato **textual** y hacia la **salida estandar**.

- **Entrada de archivo binario --> Salida a archivo binario**


En este caso la entrada va a ser de un archivo binario, con el mismo formato explicado anteriormente y la salida será hacia la salida estandar, pero en formato binario, ya que el `-ib` de entrada se proveyó al igual que el `-ob` de salida

        $ bin/sudoku -ib test/input003.bin -c -ob


Se carga el nivel de sudoku del archivo **input003.bin**, y luego mueve los datos (ya que el formato de entrada es el mismo que el de salida, por lo que no hace falta la conversión, solo el transporte de los datos) en formato **binario**, pero hacia la salida estandar (**stdout**). Siguiendo la misma notación de salida binaria explicada en el caso 2. Cabe notar que en la salida no se verá nada o se verán símbolos raros, por lo que se recomienda que si la salida es binaria, que sea hacia un archivo.

Y otros ejemplos de invocación del programa que se encuentran en el enunciado del proyecto son:

        $ bin/sudoku -c               # text stdin -> text stdout
        $ bin/sudoku -it -c           # text stdin -> text stdout
        $ bin/sudoku -c -ib           # bin  stdin -> text stdout
        $ bin/sudoku -c f1            # text f1 file -> text stdout
        $ bin/sudoku -ib f1 -c        # bin f1 file -> text stdout
        $ bin/sudoku -ob f2 -c        # text stdin -> bin f2 file
        $ bin/sudoku -c f1 -ob f2     # text f1 file -> bin f2 file
        $ bin/sudoku -ib f1 -c -ob f2 # bin f1 file -> bin f2 file


## Manual de desarrollador. 

### Compilación
La manera de compilar la solución es a travéz del Makefile. Para compilar solo ocupa poner la siguiente instrucción desde la raíz del proyecto:

        $ make

Para borrar el bin, build, doc y lib se usa la siguiente instrucción:

        $ make clean

### Agregar casos de prueba
En un editor de texto el primer número indica la dimensión que va a tener cada caja del sudoku. Seguido de dos cambios de línea puede comenzar a escribir el Sudoku. Cada ´.´ representa una posición a llenar y cada número es el número en esa posición del Sudoku. Separe los puntos y números con espacios. Podemos ver un ejemplo a continuación:

        3

        . . 7   . . 3   5 9 .
        6 . 4   7 5 8   2 . .
        . . 5   . . 9   8 7 6

        . . .   . . 4   . . .
        . . 2   8 7 .   6 . .
        . 7 .   . . .   . . 5

        5 8 .   . . .   . . .
        9 . .   . 8 5   3 2 7
        . . .   . 3 6   4 . .

Una vez hecho el caso de prueba, guardelo en un archivo y póngalo en la carpeta llamada **test/**.

### Instalar el ejecutable
Hacer git clone, make y ya se tiene el ejecutable en la carpeta bin.
Primero tiene que hacer usar el comando:

        $ git clone https://git.ucr.ac.cr/DAVID.XIE/progra2-20a-sudoku-juan_ignacio-david_xie.git

Ahi se obtendría el código fuente, los tests, el makefile, Doxyfile y el README y luego con

        $ make

compila el código fuente y obtiene el ejecutable en la carpeta bin.

### Estructura del codigo fuente


De primero tenemos a la clase **Sudoku**. Esta es la clase controladora que el main usará para correr. Lo primero que genera esta clase es una instancia de la clase **Arguments**. Esta clase analiza los argumentos con los que se invocó. Una vez analizado los argumentos se genera una instancia de la clase **Convert** en Sudoku. Si el usuario quiere la ayuda o la version con los parámetros `--help` o `--version` respectivamente, lo imprime y acaba la ejecución del programa.


Si el usuario quiere convertir el documento, dentro de la instancia Convert se genera una instancia de SudokuLevel que va a funcionar como colchón donde guardar la matriz con los datos que se quiere para convertirlos al formato, esto con el fin de reutilizar el código de lectura y escritura de SudokuLevel. Por último si el usuario quiere la solución del sudoku, en la clase Sudoku se genera una instancia de **SudokuLevel** que va a proceder a solucionarse si es que tiene solución o a imprimir que no es posible resolverlo.

* Los archivos que pertenecen a la biblioteca dinámica son: SudokuLevel.cpp, SudokuLevel.h, Convert.cpp, Convert.h.
* Los archivos que pertenecen al comando: Arguments.cpp, Arguments.h.
* Los archivos que pertenecen al programa de pruebas: main.cpp, Sudoku.cpp, Sudoku.h.

## Licencia

CC BY Proyecto 01 Programación II - Sudoku solver
