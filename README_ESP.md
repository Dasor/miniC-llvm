# Compilador de Mini-C a IR de LLVM

Este compilador esta basado en el que se hace en la asginatura de compiladores pero en vez de generar código MIPS genera IR de LLVM. Los objetivos de este proyecto son: familiarizarse con el IR de LLVM y con la API de C++ de LLVM.

Hay que tener varias cosas en cuenta sobre este proyecto:

* Mini-C es muy sencillo no tiene ni funciones, ni bucles for y aunque se podrían implementar no es el objetivo de este proyecto.
* Se usa C++ como lenguaje principal
* Este código no es un ejemplo de como programar en C++ ya que tiene varios puntos a mejorar en ese aspecto.
* Todo programa tiene que tener un return accesible de manera incodicional
* Usa la versión 18.1.8 de LLVM

## Uso

Una vez compilado con make se genera un ejecutable llamado **comp** que dado un fichero de código imprime por salida estandard el IR de LLVM. (Hay algunos ejemplos de código fuente en el directorio test)

### Programas sin entrada (clausula read)

Simplemente podemos usar un tuberia de bash para pasarle el IR al interprete de LLVM

```shell
./comp file | lli
```

### Programas con entrada (clausula read)

El metodo anterior no funciona para programas que contengan la sentencia read, en ese caso podemos usar algo un poco más complejo

```shell
mkfifo /tmp/llvm_ir_pipe && ./comp file > /tmp/llvm_ir_pipe & lli /tmp/llvm_ir_pipe; rm /tmp/llvm_ir_pipe
```

## Breve explicación del funcionamiento

Al igual que no es un ejemplo de como programar en C++ tampoco es un ejemplo de como usar la API de LLVM ya que habría múltiples maneras de hacer un proyecto como este pero he elegido la manera más similar al proyecto original del compilador MIPS.

En este caso tenemos una estructura *ListaC* que contiene un vector con las instrucciones, y bloques (similar a las etiquetas en MIPS) además de un campo de metadatos para diferenciarlos.

En esta lista se van añadiendo las instrucciones en el orden correspondiente y finalmente cuando ya no queda nada por analizar se usa el ``IRBuilder`` para crear el código intermedio. Es decir, el uso de IRBuilder es solo al final del programa el resto de el tiempo se está tratando con la clase llvm::Instruction o derivados lo cual es diferente a lo que se puede encontrar en los tutoriales de LLVM.

Desde la propia documentación y los foros de LLVM se recomienda más el uso directo del ``IRBuilder`` al ser una interfaz ligeramente de más alto nivel sin embargo, esto implicaría que se necesitaria construir un árbol sintactico sin Bison o bien reordenar las instrucciones de otra manera por eso se ha dedicido este enfoque ya que no era el objetivo modificar esa parte del proyecto.

Para la lista de simbolos simplemente se usa un mapa. Además, se añade un nuevo fichero ``llvmHelper`` que se utiliza para incluir las múltiples librerias y inicializar los valores necesarios de LLVM.
