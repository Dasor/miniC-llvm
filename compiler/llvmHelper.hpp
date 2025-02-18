#ifndef __LLVM_HELPER
#define __LLVM_HELPER__



#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include "llvm/IR/Instructions.h"
#include <llvm/Support/raw_ostream.h>

extern llvm::LLVMContext Context;
extern std::unique_ptr<llvm::Module> Module;
extern llvm::IRBuilder<> *Builder;
extern llvm::Function *MainFunc;
extern llvm::Value *retval;
extern llvm::BasicBlock *end;
extern llvm::FunctionCallee printfFunc;
extern llvm::FunctionCallee scanfFunc;
extern llvm::GlobalVariable *globalIntStr;



void initializeLLVM();
void printValue(llvm::Value* val);

#endif

