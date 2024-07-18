# Compilador de Mini-C a IR de LLVM

Este Compilador esta basado en el que se hace en la asginatura de compiladores pero en vez de generar código MIPS genera IR de LLVM. LOs objetivos de este proyecto son: familiarizarse con el IR de LLVM y posteriormente probar las transformaciones.

Hay que tener varias cosas en cuenta sobre este proyecto:

* Se usa fprintf y se escribe el código IR directamente a un fichero en vez de usar la API de LLVM. Esto para evitar una mayor complejidad ya que no es el objetivo principal del proyecto aprender la API de LLVM.
* No está implementada la sentencia read()
* En en lenguaje fuente en vez de usar \n usaremos \0A
* No está testeado intensivamente
* Mini-C es muy sencillo no tiene ni funciones, ni bucles for y aunque se podrían implementar de momento no es uno de los objetivos principales.

## Estado actual

Ahora mismo el compilador funciona con las limitaciones ya expuestas y es un buen punto de partida para ver como se aplican las optimizaciones de LLVM al código IR.Es decir, el objetivo de la práctica inicial (la de la asignatura) es entender la parte de back-end (lexer y arbol sintáctico) ahora el objetivo es ir más hacía el front end (generación de código y **optimizaciones**)
