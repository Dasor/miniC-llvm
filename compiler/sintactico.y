%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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

void initializeLLVM() {
    Module = std::make_unique<llvm::Module>("my_module", Context);
    Builder = new llvm::IRBuilder<>(Context);
}

%}

// INICIO BISON

%union{
	char* string;
	ListaC codigo;
}

%token PRINT VAR READ SEMICOLON COMMA WHILE CONST LCORCHETE RCORCHETE LPAREN RPAREN IF DO
%token <string> NUM
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

program: ID LPAREN RPAREN LCORCHETE {l=creaLS();} declarations statement_list RCORCHETE { if(!error){$$ = creaCodigo(2,$6,$7) ;imprimeSegDatos(l); imprimeCodigo($$);}}

declarations: declarations VAR {tipo=VARIABLE;} identifier_list SEMICOLON { if(!error){$$ = creaCodigo(2,$$,$4);}}
	    | declarations CONST error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("se esperaban identificadores tras el token const\n");}
	    | declarations VAR error SEMICOLON {CLEAN_ERROR;PRINT_ERROR("se esperaban identificadores tras el token var\n");}
	    | declarations CONST {tipo=CONSTANTE;} identifier_list SEMICOLON { if(!error){$$ = creaCodigo(2,$$,$4); }}
	    | /* empty */  { if(!error){$$ = creaLC();}};

identifier_list: identifier { if(!error){$$ = $1;}}
	      | identifier_list COMMA identifier {if(!error){$$ = creaCodigo(2,$1,$3);}}  ;


identifier: ID {AÑADIR_ID($1,tipo); if(!error){$$ = creaLC();}}
	  | ID ASSIGNOP expression {
	  				AÑADIR_ID($1,tipo);
					if(!error){
						ListaC aux1 = creaLineaCodigo("store",obtenerId($1),recuperaResLC($3),NULL);
						$$ = creaCodigo(2,$3,aux1);
					}
	  			   };


statement_list: statement_list statement { if(!error){$$ = creaCodigo(2,$1,$2);}}
	      | /* empty */  {if(!error){$$ = creaLC();} };


statement: ID ASSIGNOP expression SEMICOLON {
	 					ASIG_VALIDA($1);
						if(!error){
							ListaC aux1 = creaLineaCodigo("store",obtenerId($1),recuperaResLC($3),NULL);
							$$ = creaCodigo(2,$3,aux1);
						}
					    }
         | LCORCHETE statement_list RCORCHETE { if(!error){$$ = $2; }}
	 | IF LPAREN expression RPAREN statement %prec NOT_ELSE {if(!error){$$ = imprimirIf($3,$5);}}
	 | IF LPAREN expression RPAREN statement ELSE statement {if(!error){$$ = imprimirIfElse($3,$5,$7);}}
	 | WHILE LPAREN expression RPAREN statement { if(!error){$$ = imprimirWhile($3,$5);}}
	 | DO statement WHILE LPAREN expression RPAREN {if(!error){$$ = imprimirDoWhile($2,$5);}}
	 | PRINT LPAREN print_list RPAREN SEMICOLON { if(!error){$$ = $3; }}
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
	 | READ LPAREN read_list RPAREN SEMICOLON { if(!error){$$ = $3; }};

print_list: print_item { if(!error){$$ = $1; }}
	  | print_list COMMA print_item { if(!error){$$ = creaCodigo(2,$1,$3);} };


print_item: expression {
	  		 if(!error){$$ = imprimirExpresion($1);}
		       }
	  | STRING {
	  		añadeEntrada($1,CADENA,l,contCadenas);
			if(!error){
				contCadenas++;
				$$ = imprimirCadena($1,l);
			}
		   };

read_list: ID {
	 	ASIG_VALIDA($1);
		if(!error){$$ = leerId($1);}
	      }
	 | read_list COMMA ID {
				ASIG_VALIDA($3);
	 			if(!error){$$ = creaCodigo(2,$1,leerId($3));}
			      };


expression: expression PLUSOP expression { if(!error){$$ = aritExpr("add",$1,$3);}}
	  | expression MINUSOP expression { if(!error){$$ = aritExpr("sub",$1,$3);}}
	  | expression MULTOP expression { if(!error){$$ = aritExpr("mul",$1,$3);}}
	  | expression DIVOP expression { if(!error){$$ = aritExpr("udiv",$1,$3);}}
	  | expression LTOP expression { if(!error){$$ = compare("slt",$1,$3);}}
	  | expression GTOP expression { if(!error){$$ = compare("sgt",$3,$1);}}
	  | expression GTEOP expression { if(!error){$$ = compare("sge",$1,$3);}}
	  | expression LTEOP expression { if(!error){$$ = compare("sle",$1,$3);}}
	  | expression EQOP expression { if(!error){$$ = compare("eq",$1,$3);}}
	  | expression NOTEQOP expression { if(!error){$$ = compare("ne",$1,$3);}}
	  | expression AND expression { if(!error){$$ = aritExpr("and",$1,$3);}}
	  | expression OR expression { if(!error){$$ = aritExpr("or",$1,$3);}}
	  | UNOT expression { if(!error){$$ = Not($2);}}
	  | MINUSOP expression %prec UMINUS {
						if(!error){
							char *regRes = recuperaResLC($2);
							$$ = creaCodigo(2,$2,creaLineaCodigo("neg",getRegister(),regRes,NULL));
						}
					    }
	  | LPAREN expression RPAREN { $$ = $2; }
	  | ID {
			if(!error){
				if(!pertenece($1,l)){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,$1); error = true ;semErrors++;}
				$$ = creaLineaCodigo("load",getRegister(),obtenerId($1),NULL);
			}
		}
	  | NUM  {  if(!error){ $$ = creaLineaCodigo("add",getRegister(),"0",$1);} }


%%


void yyerror(std::string str){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
}

void yyerror(){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
	error = true;
	sinErrors++;

}
