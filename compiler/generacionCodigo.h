#ifndef __GEN_CODIGO__
#define __GEN_CODIGO__

#include "llvmHelper.h"

enum Type { VALUE, BLOCK, RET};

typedef struct {
	Type type;
	llvm::Value* res;
	llvm::BasicBlock* block;
} Operacion;

typedef struct ListaCRep {
	std::vector<Operacion> *codigo;
	llvm::Value *res;
} *ListaC;

llvm::Value *val(ListaC lista);
ListaC creaLineaCodigo(llvm::Value *res, Type type = VALUE, llvm::BasicBlock* block = nullptr);
ListaC creaCodigo(int n,...);
ListaC creaLC();
void imprimeCodigo(ListaC lista);
ListaC generateIf(ListaC expr, ListaC stmt);
ListaC generateIfElse(ListaC expr, ListaC stmt1, ListaC stmt2);
ListaC generateWhile(ListaC expr, ListaC stmt);
ListaC generateDoWhile(ListaC stmt, ListaC expr);
ListaC generateReturn(ListaC expr);
ListaC generatePrintString(std::string str);
ListaC generatePrintExpr(ListaC expr);

#endif

