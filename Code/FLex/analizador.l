%{
#include <stdio.h>
%}

RFC         [A-Z&Ññ]{4}[0-9]{2}(0[1-9]|1[0-2])(0[1-9]|[12][0-9]|3[01])[A-Z0-9]{3}
CURP        [A-Z]{4}[0-9]{2}(0[1-9]|1[0-2])(0[1-9]|[12][0-9]|3[01])[HM][A-Z]{5}[0-9A-Z][0-9]
EMAIL       [a-zA-Z0-9_.+-]+@([a-zA-Z0-9-]+\.)+edu\.mx
DECIMAL     [+-]?[0-9]+\.[0-9]+
ENTERO      [+-]?[0-9]+
VARIABLE    [a-zA-Z][a-zA-Z0-9_]*

%%

{RFC}       { printf("RFC identificado: %s\n", yytext); }
{CURP}      { printf("CURP identificada: %s\n", yytext); }
{EMAIL}     { printf("Correo institucional identificado: %s\n", yytext); }
{DECIMAL}   { printf("Numero decimal encontrado: %s\n", yytext); }
{ENTERO}    { printf("Numero entero encontrado: %s\n", yytext); }
{VARIABLE}  { printf("Variable (identificador) encontrada: %s\n", yytext); }
[ \t\n]+    { }
.           { printf("Caracter no reconocido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Introduce el texto a analizar:\n");
    yylex();
    return 0;
}
