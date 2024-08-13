// generación de código
#include "generacionCodigo.h"
#include "listaSimbolos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <iostream>
// LLVM
#define NUM_REGISTERS 10
#define BUFSIZE 34
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define FILEOUT "out/prog.ll"
int cont=1;

// TODO: check type of variadic args


Operacion creaOp(std::string op, llvm::Value *res){

	Operacion operacion;
	operacion.op = op;
	operacion.res = res;
	return operacion;
}

void concatenaLC(ListaC lista1, ListaC lista2){
	lista1->codigo->insert(lista1->codigo->end(),lista2->codigo->begin(),lista2->codigo->end());
}

llvm::Value *val(ListaC lista){
	return lista->res;
}

void guardaResLC(ListaC lista, llvm::Value *res){
	lista->res = res;
}

ListaC creaLC(){
	ListaC lista =  new ListaCRep();
	lista->codigo = new std::vector<Operacion>();
	return lista;
}

ListaC creaLineaCodigo(std::string op, llvm::Value *res){
	Operacion operacion = creaOp(op,res);
	ListaC lista = creaLC();
	lista->codigo->push_back(operacion);
	lista->res = res;
	return lista;
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
		if(val(aux) != nullptr){
			guardaResLC(codigo,val(aux));
		}
	}

	va_end(ap);
	return codigo;

}


void generateIf(llvm::Value* expr, llvm::Value* stmt){
	  /*
	     expr
	     jump epxr etiq1 etiq2
	     etiq1
	     	stmt
		jump etiq2
	     etiq2
	  */

	llvm::Function *theFunction = Builder->GetInsertBlock()->getParent();
	llvm::BasicBlock *tag1 = llvm::BasicBlock::Create(Context,"if",theFunction);
	llvm::BasicBlock *tag2 = llvm::BasicBlock::Create(Context,"notif",theFunction);


	Builder->CreateCondBr(expr,tag1,tag2);
	Builder->SetInsertPoint(tag1);
	Builder->CreateBr(tag2);
	Builder->SetInsertPoint(tag2);
	tag1 = Builder->GetInsertBlock();


}

void imprimeCodigo(ListaC lista){

	auto codigo = lista->codigo;

	std::cout << "INICIO IMPRESION:" << std::endl;

	for(auto & elem : *codigo){
		llvm::outs() << *elem.res << '\n';
	}

	std::cout << "FIN IMPRESION:" << std::endl;
}

void generateIfElse(llvm::Value* expr, llvm::Value* stmt1, llvm::Value* stmt2){
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


}

void generateWhile(llvm::Value* expr, llvm::Value* stmt){
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

}

void generateDoWhile(llvm::Value* stmt, llvm::Value* expr){
	/*
	   	jump etiq1
		etiq1
		stmt
		expr
		jump etiq1 etiq2
		etiq2
	*/

}

