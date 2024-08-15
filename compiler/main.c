#include "sintactico.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html

extern char *yytext;
extern int yyleng;
extern FILE *yyin;
extern int yylex();
FILE *fich;
// manejo de errores
extern bool error;
extern int lexErrors;
extern int sinErrors;
extern int semErrors;

void errors_summary(){
	if(error)
		PRINT_ERROR("Compilación fallida con: \n\t %d errores léxicos \n\t %d errores sintácticos \n\t %d errores semánticos \n",lexErrors,sinErrors,semErrors);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso correcto: %s fichero\n",argv[0]);
		exit(1);
	}
	fich = fopen(argv[1],"r");
	if (fich == 0) {
		printf("No se puede abrir %s\n",argv[1]);
		exit(1);
	}

	initializeLLVM();
	yyin = fich;
	yyparse();
	fclose(fich);

	errors_summary();
	//Module->print(llvm::outs(), nullptr);
}

