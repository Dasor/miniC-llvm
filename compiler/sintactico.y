%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include "listaSimbolos.hpp"
#include "generacionCodigo.hpp"
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define CLEAN_ERROR yyerrok;yyclearin;
// MACROS tabla de simbolos para acciones que se repiten
#define AÑADIR_ID(nombre,tipo) if (!pertenece(nombre,l)) añadeEntrada(nombre,tipo,l,contCadenas); \
	  		    else { PRINT_ERROR("Error semántico en la linea %d, Variable %s ya declarada \n",yylineno,nombre); error=true; semErrors++;}
#define ASIG_VALIDA(nombre) if (!pertenece(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,nombre); error=true; semErrors++;} \
			    else if(esConstante(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d Asignación a la constante %s\n",yylineno,nombre); error=true;semErrors++;}

#define ONE llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context), 1)
#define ZERO llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context), 0)

extern "C" int yylex();
void yyerror(std::string str);
void yyerror();
extern int yylineno;
bool error = false;
int sinErrors = 0;
int semErrors = 0;
extern int lexErrors;
// tabla de simbolos
int contCadenas=0;

std::map<std::string, llvm::Value*> tablaSim; // Tabla de Simbolos

%}

// INICIO BISON
%code requires {
	#include "generacionCodigo.hpp"
}


%union{
	char* string;
	ListaC codigo;
	uint64_t intValue;
}

%token PRINT VAR READ SEMICOLON COMMA WHILE CONST LCORCHETE RCORCHETE LPAREN RPAREN IF DO RETURN
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

%type <codigo> expression statement statement_list print_list print_item read_list identifier identifier_list declarations program

%%

program: ID LPAREN RPAREN LCORCHETE declarations statement_list RCORCHETE {if(!error){ imprimeCodigo(creaCodigo(2,$5,$6));}};

declarations: declarations VAR identifier_list SEMICOLON { if(!error){$$ = creaCodigo(2,$$,$3);}}
	    | declarations CONST error SEMICOLON
	    | declarations VAR error SEMICOLON
	    | declarations CONST identifier_list SEMICOLON { if(!error){$$ = creaCodigo(2,$$,$3); }}
	    | /* empty */ {if(!error){$$ = creaLC();} };


identifier_list: identifier {if(!error){$$ = $1;}}
	      | identifier_list COMMA identifier {if(!error){$$ = creaCodigo(2,$1,$3);}}  ;


identifier: ID {	if(!error){
	  		   $$ = creaLineaCodigo(new llvm::AllocaInst(llvm::Type::getInt32Ty(Context),0,ONE,llvm::Align(4),"allocatmp"));
	  		   tablaSim.insert({ $1,val($$) });
	                }
	       }
	  | ID ASSIGNOP expression {
					if(!error){
	  		   			ListaC inst1 = creaLineaCodigo(new llvm::AllocaInst(llvm::Type::getInt32Ty(Context),0,ONE,llvm::Align(4),"allocatmp"));
						ListaC inst2 = creaLineaCodigo(new llvm::StoreInst(val($3), val(inst1), false, llvm::Align(4)));
						tablaSim.insert({ $1,val(inst1) });
						$$ = creaCodigo(3,$3,inst1,inst2);
					}

				   };


statement_list: statement_list statement { if(!error){$$ = creaCodigo(2,$1,$2);} }
	      | /* empty */ {if(!error){$$ = creaLC();} };


statement: ID ASSIGNOP expression SEMICOLON {
			if(!error){
				auto idx = tablaSim.find($1);
				if(idx == tablaSim.end()){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
				llvm::Value* value = idx->second;
				ListaC linea1 = creaLineaCodigo(new llvm::StoreInst(val($3), value,false, llvm::Align(4)));
				$$ = creaCodigo(2,$3,linea1);
			}

	}
         | LCORCHETE statement_list RCORCHETE { if(!error){$$ = $2;}}
	 | IF LPAREN expression RPAREN statement %prec NOT_ELSE { if(!error){$$ = generateIf($3,$5);}}
	 | IF LPAREN expression RPAREN statement ELSE statement { if(!error){$$ = generateIfElse($3,$5,$7);}}
	 | WHILE LPAREN expression RPAREN statement { if(!error){$$ = generateWhile($3,$5);}}
	 | DO statement WHILE LPAREN expression RPAREN { if(!error){$$ = generateDoWhile($2,$5);}}
	 | PRINT LPAREN print_list RPAREN SEMICOLON { if(!error){$$ = $3;}}
	 | RETURN expression SEMICOLON { if(!error){$$ = generateReturn($2);}}
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
	 | RETURN error {CLEAN_ERROR;PRINT_ERROR("se esperaba ; tras return\n");}
	 | error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
	/* FIN ERRORES */
	 | READ LPAREN read_list RPAREN SEMICOLON { if(!error){$$ = $3; }};

print_list: print_item { if(!error){$$ = $1; }}
	  | print_list COMMA print_item { if(!error){$$ = creaCodigo(2,$1,$3);} };


print_item: expression { if(!error){$$ = generatePrintExpr($1);}}
	  | STRING {if(!error){$$ = generatePrintString($1);}};

read_list: ID { if(!error){
			auto idx = tablaSim.find($1);
			if(idx == tablaSim.end()){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
			llvm::Value* value = idx->second;
		 	$$ = generateRead(value);}
	      }
	 | read_list COMMA ID { if(!error){
					auto idx = tablaSim.find($3);
					if(idx == tablaSim.end()){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
					llvm::Value* value = idx->second;
	 				$$ = creaCodigo(2,$1,generateRead(value));
				}
			      };


expression: expression PLUSOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::Add, val($1), val($3))));}}
	  | expression MINUSOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::Sub, val($1), val($3))));}}
	  | expression MULTOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::Mul, val($1), val($3))));}}
	  | expression DIVOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::SDiv, val($1), val($3))));}}
	  | expression LTOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT, val($1), val($3))));}}
	  | expression GTOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT, val($1), val($3))));}}
	  | expression GTEOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE, val($1), val($3))));}}
	  | expression LTEOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE, val($1), val($3))));}}
	  | expression EQOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ, val($1), val($3))));}}
	  | expression NOTEQOP expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::ICmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, val($1), val($3))));}}
	  | expression AND expression { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::And, val($1), val($3))));}}
	  | expression OR expression  { if(!error){$$ = creaCodigo(3,$1,$3,creaLineaCodigo(llvm::BinaryOperator::Create(llvm::Instruction::Or, val($1), val($3))));}}
	  | UNOT expression {if(!error) {$$ = generateNot($2);}}
	  | MINUSOP expression %prec UMINUS {if(!error) {$$ = creaCodigo(2,$2,creaLineaCodigo(llvm::BinaryOperator::CreateNeg(val($2))));}}
	  | LPAREN expression RPAREN { $$ = $2;}
	  | ID {
		if(!error){
			auto idx = tablaSim.find($1);
			if(idx == tablaSim.end()){PRINT_ERROR("error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
			llvm::Value* val = idx->second;
			$$ = creaLineaCodigo(new llvm::LoadInst(llvm::Type::getInt32Ty(Context), val, llvm::Twine($1),false, llvm::Align(4)));
		}
	  }
	  | NUM  {  if(!error){ $$ = creaLineaCodigo(llvm::ConstantInt::get(llvm::Type::getInt32Ty(Context), $1));};}


%%


void yyerror(std::string str){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
}

void yyerror(){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
	error = true;
	sinErrors++;
}
