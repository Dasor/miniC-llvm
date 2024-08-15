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


Operacion creaOp(llvm::Value *res, Type type, llvm::BasicBlock* block){

	Operacion operacion;
	operacion.type = type;
	operacion.res = res;
	operacion.block = block;
	return operacion;
}

void concatenaLC(ListaC lista1, ListaC lista2){
	lista1->codigo->insert(lista1->codigo->end(),lista2->codigo->begin(),lista2->codigo->end());
}

llvm::Value *val(ListaC lista){
	return lista->res;
}

llvm::BasicBlock *block(ListaC lista){
	return lista->codigo->front().block;
}

void guardaResLC(ListaC lista, llvm::Value *res){
	lista->res = res;
}

ListaC creaLC(){
	ListaC lista =  new ListaCRep();
	lista->codigo = new std::vector<Operacion>();
	return lista;
}

ListaC creaLineaCodigo(llvm::Value *res, Type type, llvm::BasicBlock* block){
	Operacion operacion = creaOp(res,type,block);
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

void imprimeCodigo(ListaC lista){


	auto codigo = lista->codigo;

	for(auto it = codigo->begin(); it != codigo->end() ; it++){
		auto &elem = *it;
		switch (elem.type){
			case VALUE:
				Builder->Insert(elem.res);
				break;
			case BLOCK:
				Builder->SetInsertPoint(elem.block);
				break;
			case RET:
				Builder->Insert(elem.res);
				while(elem.type != BLOCK && it != codigo->end()){
					it++;
					elem = *it;
				}
				it--;
				break;
		}
	}

	Builder->SetInsertPoint(end);
	llvm::Value* intretval = Builder->CreateLoad(llvm::Type::getInt32Ty(Context),retval,"retval");
	Builder->CreateRet(intretval);
	Module->print(llvm::outs(), nullptr);
	if (llvm::verifyModule(*Module, &llvm::errs())) {
	    llvm::errs() << "Module verification failed!\n";
	}
}



ListaC generateIf(ListaC expr, ListaC stmt){
	  /*
	     expr
	     jump epxr etiq1 etiq2
	     etiq1
	     	stmt
		jump etiq2
	     etiq2
	  */

	ListaC tag1 =  creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"if",MainFunc));
	ListaC tag2 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"notif",MainFunc));

	ListaC jmp1 = creaLineaCodigo(llvm::BranchInst::Create(block(tag1),block(tag2),val(expr)));
	ListaC jmp2 = creaLineaCodigo(llvm::BranchInst::Create(block(tag2)));

	return creaCodigo(6,expr,jmp1,tag1,stmt,jmp2,tag2);

}


ListaC generateIfElse(ListaC expr, ListaC stmt1, ListaC stmt2){
	  /*
	     expr
	     jump epxr etiq1 etiq2
	     etiq1
	     	stmt1
		jump eitq3
	     etiq2
	     	stmt2
		jump etiq3
	     etiq3
	  */

	ListaC tag3 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"endif",MainFunc));
	ListaC jmp3 = creaLineaCodigo(llvm::BranchInst::Create(block(tag3)));
	return creaCodigo(4,generateIf(expr,stmt1),stmt2,jmp3,tag3);


}

ListaC generateWhile(ListaC expr, ListaC stmt){
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


	ListaC tag1 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"loop",MainFunc));
	ListaC jmp1 = creaLineaCodigo(llvm::BranchInst::Create(block(tag1)));
	ListaC tag2 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"enterloop",MainFunc));
	ListaC tag3 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"exitloop",MainFunc));
	ListaC jmp2 = creaLineaCodigo(llvm::BranchInst::Create(block(tag2),block(tag3),val(expr)));
	ListaC jmp3 = creaLineaCodigo(llvm::BranchInst::Create(block(tag3)));

	return creaCodigo(8,jmp1,tag1,expr,jmp2,tag2,stmt,jmp3,tag3);
}

ListaC generateDoWhile(ListaC stmt, ListaC expr){
	/*
	   	jump etiq1
		etiq1
			stmt
			expr
		jump expr etiq1 etiq2
		etiq2
	*/
	ListaC tag1 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"loop",MainFunc));
	ListaC jmp1 = creaLineaCodigo(llvm::BranchInst::Create(block(tag1)));
	ListaC tag2 = creaLineaCodigo(nullptr,BLOCK,llvm::BasicBlock::Create(Context,"exitloop",MainFunc));
	ListaC jmp2 = creaLineaCodigo(llvm::BranchInst::Create(block(tag1),block(tag2),val(expr)));

	return creaCodigo(6,jmp1,tag1,stmt,expr,jmp2,tag2);

}


ListaC generateReturn(ListaC expr){

	ListaC store = creaLineaCodigo(new llvm::StoreInst(val(expr), retval,false, llvm::Align(4)));
	ListaC jmp = creaLineaCodigo(llvm::BranchInst::Create(end),RET);
	return creaCodigo(3,expr,store,jmp);

}

