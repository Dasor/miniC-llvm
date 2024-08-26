#ifndef __LISTA_SIMBOLOS__
#define __LISTA_SIMBOLOS__
#include <stdbool.h>

typedef enum { VARIABLE = 1, CONSTANTE = 2, CADENA = 3 } Tipo;
typedef struct Nodo {
  char *nombre;
  Tipo tipo;
  int valor;
} Simbolo;
typedef struct ListaRep * Lista;
typedef struct PosicionListaRep *PosicionLista;

Lista creaLS();
void liberaLS(Lista lista);
void insertaLS(Lista lista, PosicionLista p, Simbolo s);
Simbolo recuperaLS(Lista lista, PosicionLista p);
PosicionLista buscaLS(Lista lista, char *nombre);
void asignaLS(Lista lista, PosicionLista p, Simbolo s);
int longitudLS(Lista lista);
PosicionLista inicioLS(Lista lista);
PosicionLista finalLS(Lista lista);
PosicionLista siguienteLS(Lista lista, PosicionLista p);
// Añadidas a posteriori
bool pertenece(char *_nombre, Lista l);
void añadeEntrada(char* _nombre, Tipo _tipo, Lista l, int contCadenas);
bool esConstante(char* _nombre, Lista l);

#endif

