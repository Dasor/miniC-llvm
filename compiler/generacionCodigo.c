// generación de código
#include "generacionCodigo.h"
#include "listaSimbolos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#define NUM_REGISTERS 10
#define BUFSIZE 34
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define FILEOUT "out/prog.ll"
int cont=1;

Operacion creaOp(char *op, char *res ,char *arg1, char*arg2){

	Operacion operacion;
	operacion.op = op;
	operacion.res = res;
	operacion.arg1 = arg1;
	operacion.arg2 = arg2;
	return operacion;
}


// devuelve un cadena que representa un registro libre
char *getRegister(){
	char reg[BUFSIZE] = {0};
	sprintf(reg,"%%R%d",cont);
	cont++;
	return strdup(reg);
}


// crea una lista con una sola instrucción
ListaC creaLineaCodigo(char *op, char *res ,char *arg1, char *arg2){
	Operacion operacion = creaOp(op,res,arg1,arg2);
	ListaC codigo = creaLC();
	insertaLC(codigo,finalLC(codigo),operacion);
	guardaResLC(codigo,operacion.res);
	return codigo;
}

// crea una lista de código con n listas
// funcion con argumentos variables basada en la documentación de GNU
// https://www.gnu.org/software/libc/manual/html_node/Variadic-Example.html
ListaC creaCodigo(int n,...){

	va_list ap;
	va_start (ap,n);

	ListaC codigo = creaLC();
	for(int i = 0; i < n; i++){
		ListaC aux = va_arg(ap,ListaC);
		concatenaLC(codigo,aux);
		// el res no tiene porque estar siempre en la última OP ya que por ejemplo codificamos etiquetas como OP
		if(recuperaResLC(aux) != NULL){
			guardaResLC(codigo,recuperaResLC(aux));
		}
		liberaLC(aux);
	}

	va_end(ap);
	return codigo;

}

void imprimeCodigo(ListaC codigo){

	FILE *fptr = fopen(FILEOUT, "a");

	fprintf(fptr,"\ndefine dso_local i32 @main() #0{\n"); // header
	for(PosicionListaC p = inicioLC(codigo); p != finalLC(codigo); p = siguienteLC(codigo,p)){
		Operacion op = recuperaLC(codigo,p);
		if(op.res == NULL){
			fprintf(fptr,"\n%s:\n",op.op);
		}else if(op.arg1 == NULL){ // salto incondicional
			if(op.op[0] == 'a') // allocate
				fprintf(fptr,"  %s = %s i32, align 4\n",op.res,op.op);
			else if(op.op[0] == 'b') // branch
				fprintf(fptr,"  %s label %%%s\n",op.op,op.res);
			else
				fprintf(fptr,"  %s %s\n",op.op,op.res);
		}else if(op.arg2 == NULL){ // un solo operando
			if(op.op[0] == 's') // store
				fprintf(fptr,"  %s i32 %s, i32* %s\n",op.op,op.arg1,op.res);
			else //load
				fprintf(fptr,"  %s = %s i32, i32* %s\n",op.res,op.op,op.arg1);
		}else{
			if(op.op[0] == 'e' || op.op[0] == 'n') // comparison
				fprintf(fptr,"  %s = icmp %s i32 %s, %s\n",op.res,op.op,op.arg1,op.arg2);
			else if(op.op[0] == 'b') // branch
				fprintf(fptr,"  %s i1 %s, label %%%s, label %%%s\n",op.op,op.res,op.arg1,op.arg2);
			else if(op.op[0] == 'c') // printf call
				if(op.arg2[0] == '0') // string
					fprintf(fptr,"  %s = %s i32 (ptr, ...) @printf (ptr noundef %s)\n",op.res,op.op,op.arg1);
				else // integer
					fprintf(fptr,"  %s = %s i32 (ptr, ...) @printf (ptr noundef @.str, i32 noundef %s)\n",op.res,op.op,op.arg1);
			else
				fprintf(fptr,"  %s = %s i32 %s, %s\n",op.res,op.op,op.arg1,op.arg2);
		}
	}

	fprintf(fptr,"  ret i32 0\n");
	fprintf(fptr,"}\n\n");
	fprintf(fptr,"declare i32 @printf(ptr noundef, ...) #1");

	liberaLC(codigo);
	fclose(fptr);

}

// Forma una expresion aritmetica (add,sub,mul o div)
ListaC aritExpr(char *op,ListaC a, ListaC b){
	char *regRes = getRegister();
	char *reg1 = recuperaResLC(a);
	char *reg2 = recuperaResLC(b);
 	ListaC resultado = creaCodigo(3,a,b,creaLineaCodigo(op,regRes,reg1,reg2));
	return resultado;
}


size_t stringlen(char *str){

	size_t i = 0;
	size_t count = 0;
	while(str[i] != '\0'){
		i++;
		count++;
		if(str[i] == '\\'){
			count -=2;
		}
	}

	return count;

}

void imprimeSegDatos(Lista l){

	FILE *fptr = fopen(FILEOUT, "w");
	fprintf(fptr,"@.str = private unnamed_addr constant [3 x i8]  c\"%%d\\00\", align 1\n"); // to print integers
	for(PosicionLista p = inicioLS(l); p != finalLS(l); p = siguienteLS(l,p)){
		Simbolo aux = recuperaLS(l,p);
		if(aux.tipo == CADENA){
			size_t len = strlen(aux.nombre);
			char *str = (char *) malloc(sizeof(char)*len+3);
			strcpy(str,aux.nombre);
			str[len-1] = '\\'; str[len] = '0'; str[len+1] = '0'; str[len+2] = '"'; str[len+3] = '\0';
			fprintf(fptr,"@.str.%d = private unnamed_addr constant [%ld x i8]  c%s, align 1\n",aux.valor,stringlen(str)-2,str);
		}else{
			fprintf(fptr,"@%s = global i32 %d\n",aux.nombre,aux.valor);
		}
	}

	fclose(fptr);
}

char *creaEtiqueta(){
	char tag[BUFSIZE] = {0};
	sprintf(tag,"tag%d",cont);
	cont++;
	return strdup(tag);
}

// dado un nombre de variable la devuelve con el _
char *obtenerId(char *var){
 	char id[BUFSIZE] = {0};
	strcpy(id,"@");
	strcat(id,var);
	return strdup(id);
}

ListaC leerId(char *id){
	ListaC linea1 = creaLineaCodigo("li","$v0","5",NULL);
	ListaC linea2 = creaLineaCodigo("syscall",NULL,NULL,NULL);
	ListaC linea3 = creaLineaCodigo("sw","$v0",obtenerId(id),NULL);
	return creaCodigo(3,linea1,linea2,linea3);

}

ListaC compareConst(char* inst, ListaC expr1, char *constant){
	ListaC linea1 = creaLineaCodigo(inst,getRegister(),recuperaResLC(expr1),constant);
	return creaCodigo(2,expr1,linea1);
}


ListaC imprimirCadena(char *str, Lista l){
	int strnum = recuperaLS(l,buscaLS(l,str)).valor;
	char strid[BUFSIZE] = {0};
	sprintf(strid,"@.str.%d",strnum);
	char *print = strdup(strid);
	return creaLineaCodigo("call",getRegister(),print,"0"); // last field for metadata 0 -> String 1 -> Integer

}

ListaC imprimirExpresion(ListaC exp){
	 ListaC linea1 = creaLineaCodigo("call",getRegister(),recuperaResLC(exp),"1");
	 return creaCodigo(2,exp,linea1);
}

ListaC imprimirIf(ListaC expr, ListaC stmt){
	  /*
	     expr
	     jump epxr etiq1 etiq2
	     etiq1
	     	stmt
		jump etiq2
	     etiq2
	  */

	  ListaC linea1 = compareConst("ne",expr,"0");
	  // second arg here is the condition
	  char *tag1 = creaEtiqueta();
	  char *tag2 = creaEtiqueta();
	  ListaC etiq1 = creaLineaCodigo(tag1,NULL,NULL,NULL);
	  ListaC etiq2 = creaLineaCodigo(tag2,NULL,NULL,NULL);
	  ListaC linea2 = creaLineaCodigo("br",recuperaResLC(linea1),tag1,tag2);
	  ListaC linea3 = creaLineaCodigo("br",tag2,NULL,NULL); // terminator instruction
	  return creaCodigo(6,linea1,linea2,etiq1,stmt,linea3,etiq2);

}

ListaC imprimirIfElse(ListaC expr, ListaC stmt1, ListaC stmt2){
	  /*
	     expr
	     jump epxr etiq1 etiq2
	     etiq1
	     	stmt1
		jump eitq2
	     etiq2
	     	stmt2
		jump
	  */

	ListaC If = imprimirIf(expr,stmt1);
	return creaCodigo(2,If,stmt2);

}

ListaC imprimirWhile(ListaC expr, ListaC stmt){
	/*
	   	jump etiq1
		etiq1
		expr
		jump expr etiq2 etiq3
		etiq2
			stmt
		jump etiq1
		etiq3
	*/
	// second arg here is the condition
	char *tag1 = creaEtiqueta();
	char *tag2 = creaEtiqueta();
	char *tag3 = creaEtiqueta();
	ListaC etiq1 = creaLineaCodigo(tag1,NULL,NULL,NULL);
	ListaC etiq2 = creaLineaCodigo(tag2,NULL,NULL,NULL);
	ListaC etiq3 = creaLineaCodigo(tag3,NULL,NULL,NULL);
	ListaC linea0 = creaLineaCodigo("br",tag1,NULL,NULL);
	ListaC linea1 = compareConst("ne",expr,"0");
	ListaC linea2 = creaLineaCodigo("br",recuperaResLC(linea1),tag2,tag3);
	ListaC linea3 = creaLineaCodigo("br",tag1,NULL,NULL);
	return creaCodigo(8,linea0,etiq1,linea1,linea2,etiq2,stmt,linea3,etiq3);
}

ListaC imprimirDoWhile(ListaC stmt, ListaC expr){
	/*
	   	jump etiq1
		etiq1
		stmt
		expr
		jump etiq1 etiq2
		etiq2
	*/

	// second arg here is the condition
	char *tag1 = creaEtiqueta();
	char *tag2 = creaEtiqueta();
	ListaC etiq1 = creaLineaCodigo(tag1,NULL,NULL,NULL);
	ListaC etiq2 = creaLineaCodigo(tag2,NULL,NULL,NULL);
	ListaC linea1 = compareConst("ne",expr,"0");
	ListaC linea0 = creaLineaCodigo("br",tag1,NULL,NULL);
	ListaC linea2 = creaLineaCodigo("br",recuperaResLC(linea1),tag1,tag2);
	return creaCodigo(6,linea0,etiq1,stmt,linea1,linea2,etiq2);
}


// use cmp + instr
ListaC compare(char* inst, ListaC expr1, ListaC expr2){
	ListaC linea1 = creaLineaCodigo(inst,getRegister(),recuperaResLC(expr1),recuperaResLC(expr2));
	return creaCodigo(3,expr1,expr2,linea1);
}



ListaC Not(ListaC expr){
	ListaC aux = creaLineaCodigo("store",getRegister(),"0",NULL);
	return compare("eq",expr,aux);
}

/*ListaC allocStoreId(char *value, char *regRes){

	ListaC linea1 = creaLineaCodigo("alloca",regRes,NULL,NULL);
	ListaC linea2 = creaLineaCodigo("store",regRes,value,NULL);
	return creaCodigo(2,linea1,linea2);

}*/

/*ListaC allocStore(char *value){
	return allocStoreId(value,getRegister());
}*/

