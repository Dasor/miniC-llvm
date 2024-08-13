#include <iostream>
#include "llvmHelper.h"

llvm::LLVMContext Context;
std::unique_ptr<llvm::Module> Module;
llvm::IRBuilder<> *Builder;
llvm::Function *MainFunc;
llvm::BasicBlock *auxBB;

void initializeLLVM() {
	Module = std::make_unique<llvm::Module>("my_module", Context);
	Builder = new llvm::IRBuilder<>(Context);
	llvm::FunctionType *FuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), false);
	MainFunc = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", *Module);
	llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(Context, "entry", MainFunc);
	Builder->SetInsertPoint(EntryBB);
}

void printValue(llvm::Value* val){
	if(llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(val)){
		if(CI->getBitWidth() <= 32){
			std::cout << "value: " << CI->getSExtValue() << std::endl;
		}
	}
}

