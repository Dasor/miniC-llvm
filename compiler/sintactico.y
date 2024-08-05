%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include "generacionCodigo.h"
// LLVM
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define CLEAN_ERROR yyerrok;yyclearin;
// MACROS tabla de simbolos para acciones que se repiten
#define AÑADIR_ID(nombre,tipo) if (!pertenece(nombre,l)) añadeEntrada(nombre,tipo,l,contCadenas); \
	  		    else { PRINT_ERROR("Error semántico en la linea %d, Variable %s ya declarada \n",yylineno,nombre); error=true; semErrors++;}
#define ASIG_VALIDA(nombre) if (!pertenece(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,nombre); error=true; semErrors++;} \
			    else if(esConstante(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d Asignación a la constante %s\n",yylineno,nombre); error=true;semErrors++;}

extern "C" int yylex();
void yyerror(std::string str);
void yyerror();
extern int yylineno;
bool error = false;
int sinErrors = 0;
int semErrors = 0;
extern int lexErrors;
// tabla de simbolos
Tipo tipo;
Lista l;
int contCadenas=0;

llvm::LLVMContext Context;
std::unique_ptr<llvm::Module> Module;
llvm::IRBuilder<> *Builder;
void initializeLLVM();
void printValue(llvm::Value* val);

std::map<std::string, llvm::Value*> tablaSim; // Tabla de Simbolos

%}

// INICIO BISON
%code requires {
    #include <llvm/IR/LLVMContext.h>
    #include <llvm/IR/Module.h>
    #include <llvm/IR/IRBuilder.h>
    #include <llvm/IR/Verifier.h>
    #include <llvm/Support/raw_ostream.h>
}


%union{
	char* string;
	llvm::Value* value;
	uint64_t intValue;
}

%token PRINT VAR READ SEMICOLON COMMA WHILE CONST LCORCHETE RCORCHETE LPAREN RPAREN IF DO
%token <intValue> NUM
%token <string> ID
%token <string> STRING
%right ASSIGNOP
%left OR
%left AND
%left UNOT
%nonassoc GTOP LTOP GTEOP LTEOP EQOP NOTEQOP
%left PLUSOP MINUSOP
%left MULTOP DIVOP
%left UMINUS
%nonassoc NOT_ELSE
%nonassoc ELSE

%type <value> expression statement statement_list print_list print_item read_list identifier identifier_list declarations program

%%

program: ID LPAREN RPAREN LCORCHETE declarations statement_list RCORCHETE;

declarations: declarations VAR identifier_list SEMICOLON
	    | declarations CONST error SEMICOLON
	    | declarations VAR error SEMICOLON
	    | declarations CONST identifier_list SEMICOLON
	    | /* empty */ ;

identifier_list: identifier {if(!error){$$ = $1;}}
	      | identifier_list COMMA identifier;


identifier: ID {	if(!error){$$ = Builder->CreateAlloca(llvm::Type::getInt32Ty(Context));
	  		   tablaSim.insert({ $1,$$ });
	                }
	       }
	  | ID ASSIGNOP expression {
					if(!error){$$ = Builder->CreateAlloca(llvm::Type::getInt32Ty(Context));
					   tablaSim.insert({ $1,$$ });
					   Builder->CreateStore($3,$$,"");
					}

				   };


statement_list: statement_list statement
	      | /* empty */ ;


statement: ID ASSIGNOP expression SEMICOLON {
			if(!error){
				auto idx = tablaSim.find($1);
				if(idx == tablaSim.end()){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
				llvm::Value* val = idx->second;
				Builder->CreateStore($3,val,"");
			}

	}
         | LCORCHETE statement_list RCORCHETE
	 | IF LPAREN expression RPAREN statement %prec NOT_ELSE
	 | IF LPAREN expression RPAREN statement ELSE statement
	 | WHILE LPAREN expression RPAREN statement
	 | DO statement WHILE LPAREN expression RPAREN
	 | PRINT LPAREN print_list RPAREN SEMICOLON
	 /* ERRORES */
	 | ID ASSIGNOP error {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
	 | PRINT error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("sentencia print mal formada\n");} // se olvida de los ()
	 | PRINT LPAREN print_list RPAREN error {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
	 | PRINT LPAREN error RPAREN SEMICOLON {CLEAN_ERROR;PRINT_ERROR("argumentos de print inválidos\n");}
	 | READ error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("sentencia read mal formada\n");} // se olvida de los ()
	 | READ LPAREN read_list RPAREN error {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
	 | READ LPAREN error RPAREN SEMICOLON {CLEAN_ERROR;PRINT_ERROR("argumentos de read inválidos\n");} // se deja una ,
	 | WHILE LPAREN error RPAREN {CLEAN_ERROR;PRINT_ERROR("expresión inválida en bucle while\n");} // usa = en vez de ==
	 | WHILE error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("sentencia while mal formada\n");} // se olvida de los ()
	 | DO statement WHILE LPAREN error RPAREN {CLEAN_ERROR;PRINT_ERROR("expresión inválida en bucle do-while\n");} // usa = en vez de ==
	 | IF LPAREN error RPAREN {CLEAN_ERROR;PRINT_ERROR("expresión inválida en sentencia if\n");} // usa = en vez de ==
	 | IF error SEMICOLON  {CLEAN_ERROR;PRINT_ERROR("sentencia if mal formada\n");} // se olvida de los ()
	 | error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
	/* FIN ERRORES */
	 | READ LPAREN read_list RPAREN SEMICOLON;

print_list: print_item
	  | print_list COMMA print_item


print_item: expression
	  | STRING;

read_list: ID
	 | read_list COMMA ID;


expression: expression PLUSOP expression { if(!error){$$ = Builder->CreateAdd($1,$3,"addtmp");}}
	  | expression MINUSOP expression { if(!error){$$ = Builder->CreateSub($1,$3,"subtmp");}}
	  | expression MULTOP expression { if(!error){$$ = Builder->CreateMul($1,$3,"multmp");}}
	  | expression DIVOP expression { if(!error){$$ = Builder->CreateUDiv($1,$3,"divtmp");}}
	  | expression LTOP expression { if(!error){$$ = Builder->CreateICmpULT($1,$3,"lttmp");}}
	  | expression GTOP expression { if(!error){$$ = Builder->CreateICmpUGT($1,$3,"gttmp");}}
	  | expression GTEOP expression { if(!error){$$ = Builder->CreateICmpUGE($1,$3,"gtetmp");}}
	  | expression LTEOP expression { if(!error){$$ = Builder->CreateICmpULE($1,$3,"uletmp");}}
	  | expression EQOP expression { if(!error){$$ = Builder->CreateICmpEQ($1,$3,"eqtmp");}}
	  | expression NOTEQOP expression { if(!error){$$ = Builder->CreateICmpNE($1,$3,"netmp");}}
	  | expression AND expression { if(!error){$$ = Builder->CreateAnd($1,$3,"andtmp");}}
	  | expression OR expression  { if(!error){$$ = Builder->CreateOr($1,$3,"ortmp");}}
	  | UNOT expression {$$ = Builder->CreateNeg($2,"nottmp"); }
	  | MINUSOP expression %prec UMINUS {$$ = Builder->CreateNeg($2,"negtmp"); }
	  | LPAREN expression RPAREN { $$ = $2;}
	  | ID {
		if(!error){
			auto idx = tablaSim.find($1);
			if(idx == tablaSim.end()){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
			llvm::Value* val = idx->second;
			$$ = Builder->CreateLoad(val->getType(),val,"");
		}
	  }
	  | NUM  {  if(!error){ $$ = llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context), $1);};}


%%


void yyerror(std::string str){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
}

void yyerror(){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
	error = true;
	sinErrors++;
}

void initializeLLVM() {
	Module = std::make_unique<llvm::Module>("my_module", Context);
	Builder = new llvm::IRBuilder<>(Context);
	llvm::FunctionType *FuncType = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), false);
	llvm::Function *MainFunc = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, "main", *Module);
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
