#ifndef __GEN_CODIGO__
#define __GEN_CODIGO__

#include "listaCodigo.h"
#include "listaSimbolos.h"

Operacion creaOp(char *op, char *res ,char *arg1, char*arg2);
char *getRegister();
void freeRegister(char *reg);
ListaC creaLineaCodigo(char *op, char *res ,char *arg1, char *arg2);
ListaC creaCodigo(int n,...);
void imprimeCodigo(ListaC codigo);
ListaC aritExpr(char *op,ListaC a, ListaC b);
void imprimeSegDatos();
char *creaEtiqueta();
char *obtenerId(char *var);
ListaC leerId(char *id);
ListaC imprimirCadena(char *str, Lista l);
ListaC imprimirExpresion(ListaC exp);
ListaC imprimirIf(ListaC expr, ListaC stmt);
ListaC imprimirIfElse(ListaC expr, ListaC stmt1, ListaC stmt2);
ListaC imprimirWhile(ListaC expr, ListaC stmt);
ListaC imprimirDoWhile(ListaC stmt, ListaC expr);
ListaC not(ListaC expr);
ListaC equals(ListaC expr1, ListaC expr2);
ListaC notEquals(ListaC expr1, ListaC expr2);
ListaC compare(char* inst, ListaC expr1, ListaC expr2);


#endif

