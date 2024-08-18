#include <iostream>
#include "llvmHelper.h"

llvm::LLVMContext Context;
std::unique_ptr<llvm::Module> Module;
llvm::IRBuilder<> *Builder;
llvm::Function *MainFunc;
llvm::Value *retval;
llvm::BasicBlock *end;
llvm::FunctionType *printfType;
llvm::FunctionCallee printfFunc;
llvm::GlobalVariable *globalIntStr;


void initializeLLVM() {
	Module = std::make_unique<llvm::Module>("my_module", Context);
	Builder = new llvm::IRBuilder<>(Context);
	llvm::FunctionType *FuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), false);
	MainFunc = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", *Module);
	llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(Context, "entry", MainFunc);
	Builder->SetInsertPoint(EntryBB);
	// for returning
	retval = Builder->CreateAlloca(llvm::Type::getInt32Ty(Context),0,"retval");
	end = llvm::BasicBlock::Create(Context,"end",MainFunc);
	// printf declaration
	 printfType = llvm::FunctionType::get(
	    llvm::Type::getInt32Ty(Context), // Return type
	    llvm::PointerType::get(Context,0),
	    true); // Is variadic

	printfFunc = Module->getOrInsertFunction("printf", printfType);
	llvm::Constant *intFormatStr = llvm::ConstantDataArray::getString(Context, "%d", true);
	globalIntStr = new llvm::GlobalVariable(
						*Module,
						intFormatStr->getType(),
						true, // Constant
						llvm::GlobalValue::PrivateLinkage,
						intFormatStr,
						".str");

}

void printValue(llvm::Value* val){
	if(llvm::ConstantInt* CI = llvm::dyn_cast<llvm::ConstantInt>(val)){
		if(CI->getBitWidth() <= 32){
			std::cout << "value: " << CI->getSExtValue() << std::endl;
		}
	}
}

