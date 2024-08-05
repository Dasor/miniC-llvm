%{
#include <stdbool.h>
#include "listaCodigo.h"
#include "sintactico.tab.h"
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define MAX_NUM 2147483648
extern "C" int yylex();
void overflow();
void id_len();
int lexErrors = 0;
extern int sinErrors;
extern int semErrors;
extern bool error;
%}
%option yylineno
%option outfile="lexico.c"

%x com

digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
escape	  	    \\.

%%
[ \n\t\r]+                                  ;
"//"(.*)[\n]                                ;
"/*"					    BEGIN com;
<com>[*]+[/]				    BEGIN 0;
<com>[^*]*				    ;
<com>[*]+[^/*]*			    	    ;
<com><<EOF>>			            PRINT_ERROR("Error lexico comentario multilinea sin cerrar en la linea %d\n",yylineno); error = true ; lexErrors++; return 0;
print                                       return PRINT;
read                                        return READ;
var					    return VAR;
const					    return CONST;
if					    return IF;
else					    return ELSE;
while					    return WHILE;
do					    return DO;
({letra}|_)({letra}|_|{digito})*            id_len(); {yylval.string=strdup(yytext); return ID;}
{entero}                                    overflow(); {yylval.intValue=atoi(yytext); return NUM;}
"{"                                         return LCORCHETE;
"}"                                         return RCORCHETE;
"("                                         return LPAREN;
")"                                         return RPAREN;
";"                                         return SEMICOLON;
","                                         return COMMA;
"="                                         return ASSIGNOP;
"+"                                         return PLUSOP;
"-"                                         return MINUSOP;
"*"                                         return MULTOP;
"/"                                         return DIVOP;
">"                                         return GTOP;
"<"                                         return LTOP;
">="                                        return GTEOP;
"=<"                                        return GTEOP;
"=="					    return EQOP;
"!="					    return NOTEQOP;
"&&"					    return AND;
"||"					    return OR;
"!"					    return UNOT;
\"([^"\n]|{escape})*\"			    yylval.string=strdup(yytext);return STRING;
\"([^"\n]|{escape})*			    PRINT_ERROR("Error lexico cadena sin cerrar en la linea %d\n",yylineno); lexErrors++; error = true; return STRING;
[^a-zA-Z0-9();",=+\-{}*/_<>&|!\n\t\r ]*     PRINT_ERROR("Error lexico en caracter %s linea %d\n",yytext, yylineno); lexErrors++; error = true;
%%

void overflow(){
	if(atoll(yytext) > MAX_NUM){
		PRINT_ERROR("Error lexico entero excede valor absoluto de 2^31\n");
		lexErrors++;
	}
}

void id_len(){
	if(yyleng > 32){
		PRINT_ERROR("Error lexico ID excede 32 caracteres\n");
		lexErrors++;
	}
}
