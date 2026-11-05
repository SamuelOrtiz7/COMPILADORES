%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE double
#include "y.tab.h"

int linea = 1;
int tok_linea = 1;   /* linea del ultimo token leido */

int linea_mostrada = 0;
extern char *lineas[];
extern int n_lineas;

/* Antes de cada token: guarda la linea y, si es la primera vez que se ve
   la linea, imprime su texto para identificar la salida. */
#define YY_USER_ACTION \
    tok_linea = linea; \
    if (yytext[0] != '\n' && linea_mostrada != linea) { \
        linea_mostrada = linea; \
        if (linea <= n_lineas) printf("[%d] %s\n", linea, lineas[linea-1]); \
    }
%}

%option noyywrap

DIGITO  [0-9]
LETRA   [a-zA-Z_]
ID      {LETRA}({LETRA}|{DIGITO})*

%%

{DIGITO}+\.{DIGITO}+    { yylval = atof(yytext); return NUM; }
{DIGITO}+               { yylval = atof(yytext); return NUM; }
{DIGITO}+{ID}           { printf("  [Error lexico] linea %d: identificador mal formado '%s'\n", linea, yytext); return ERROR_LEX; }
{ID}                    { return ID; }

"**"                    { return POT; }
"=="                    { return IGUAL; }
"!="                    { return DIST; }
"<="                    { return MENIGUAL; }
">="                    { return MAYIGUAL; }
"<"                     { return '<'; }
">"                     { return '>'; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"("                     { return '('; }
")"                     { return ')'; }

\n                      { linea++; return '\n'; }
[ \t\r]+                ;
"#".*                   ;
.                       { printf("  [Error lexico] linea %d: caracter no reconocido '%s'\n", linea, yytext); return ERROR_LEX; }

%%
