#ifndef __GEN_CODIGO__
#define __GEN_CODIGO__

#include "llvmHelper.h"

typedef struct {
	std::string op;
	llvm::Value* res;
} Operacion;

typedef struct ListaCRep {
	std::vector<Operacion> *codigo;
	llvm::Value *res;
} *ListaC;

llvm::Value *val(ListaC lista);
ListaC creaLineaCodigo(std::string op, llvm::Value *res);
ListaC creaCodigo(int n,...);
ListaC creaLC();
void imprimeCodigo(ListaC lista);
void generateIf(llvm::Value* expr, llvm::Value* stmt);
void generateIfElse(llvm::Value* expr, llvm::Value* stmt1, llvm::Value* stmt2);
void generateWhile(llvm::Value* expr, llvm::Value* stmt);
void generateDoWhile(llvm::Value* stmt, llvm::Value* expr);


#endif

