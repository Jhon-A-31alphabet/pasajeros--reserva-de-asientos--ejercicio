

# Compilación y Ejecución de gestion_pasajeros
=============================================

## Requisitos previos
--------------------

* Tener instalado un compilador C++ que soporte el estándar C++2a (por ejemplo, GCC 11 o superior).
* Tener instalado Make.

### Compilación

Para compilar el programa, se deben seguir los siguientes pasos:

* Clonar el repositorio o copia los archivos en un directorio local.
* Abrir una terminal y navega hasta el directorio donde se encuentran los archivos.
* Ejecutar el comando `make` para compilar el programa.

El comando `make` leerá el archivo `Makefile` y compilará el programa `gestion_pasajeros` utilizando las banderas de compilación especificadas.

### Ejecución

Una vez compilado el programa, se debe ejecutarlo de la siguiente manera:

* Abrir una terminal y navega hasta el directorio donde se encuentra el ejecutable `gestion_pasajeros`.
* Ejecuta el comando `make run` para ejecutar el programa.

También puedes ejecutar el programa directamente escribiendo `./gestion_pasajeros` en la terminal.

### Limpieza

Para eliminar el ejecutable y otros archivos objeto generados durante la compilación, se debe ejecutar el comando `make clean`.

## Notas
------

* El programa se compila con las banderas `-Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors` para habilitar warnings y errores en la compilación.
* El programa se compila con la bandera `-ggdb` para habilitar la depuración con GDB.
* El programa se compila con la bandera `-O2` para habilitar optimizaciones en la compilación.
* El programa se compila con el estándar C++2a.
