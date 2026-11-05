%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define YYSTYPE double

extern int linea, tok_linea;
extern FILE *yyin;
int yylex(void);
void yyerror(const char *s);

int n_validas = 0, n_errores = 0;
int es_condicion = 0;   /* 1 si la linea tiene operador de comparacion */
int hay_id = 0;
char *lineas[1000];
int n_lineas = 0;         /* 1 si la linea usa identificadores (no se evalua) */
%}

%token NUM ID ERROR_LEX
%token IGUAL DIST MENIGUAL MAYIGUAL POT

%left IGUAL DIST '<' '>' MENIGUAL MAYIGUAL
%left '+' '-'
%left '*' '/'
%right UMINUS
%right POT

%%

entrada:
      /* vacio */
    | entrada linea
    ;

linea:
      '\n'
    | expresion '\n'
        {
          n_validas++;
          if (hay_id)       printf("  -> VALIDA (usa identificadores, no se evalua)\n");
          else if (es_condicion) printf("  -> VALIDA (condicion = %s)\n", $1 ? "True" : "False");
          else              printf("  -> VALIDA (resultado = %g)\n", $1);
          es_condicion = 0; hay_id = 0;
        }
    | error '\n'
        {
          n_errores++;
          printf("  -> INVALIDA (error sintactico en la linea %d)\n", tok_linea);
          es_condicion = 0; hay_id = 0;
          yyerrok;
        }
    ;

expresion:
      NUM                       { $$ = $1; }
    | ID                        { hay_id = 1; $$ = 0; }
    | expresion '+' expresion   { $$ = $1 + $3; }
    | expresion '-' expresion   { $$ = $1 - $3; }
    | expresion '*' expresion   { $$ = $1 * $3; }
    | expresion '/' expresion   {
                                  if ($3 == 0 && !hay_id) { printf("  [Aviso] division entre cero\n"); $$ = 0; }
                                  else $$ = ($3 == 0) ? 0 : $1 / $3;
                                }
    | expresion POT expresion   { $$ = pow($1, $3); }
    | '-' expresion %prec UMINUS { $$ = -$2; }
    | '(' expresion ')'         { $$ = $2; }
    | expresion IGUAL expresion    { es_condicion = 1; $$ = ($1 == $3); }
    | expresion DIST expresion     { es_condicion = 1; $$ = ($1 != $3); }
    | expresion '<' expresion      { es_condicion = 1; $$ = ($1 <  $3); }
    | expresion '>' expresion      { es_condicion = 1; $$ = ($1 >  $3); }
    | expresion MENIGUAL expresion { es_condicion = 1; $$ = ($1 <= $3); }
    | expresion MAYIGUAL expresion { es_condicion = 1; $$ = ($1 >= $3); }
    ;

%%

void yyerror(const char *s) {
    printf("  [Error] linea %d: %s\n", tok_linea, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 1; }
        /* se guardan las lineas para mostrarlas junto con su resultado */
        char buf[512];
        while (fgets(buf, sizeof buf, yyin) && n_lineas < 1000) {
            buf[strcspn(buf, "\n")] = 0;
            lineas[n_lineas++] = strdup(buf);
        }
        rewind(yyin);
    }
    yyparse();
    printf("\n--- Resumen ---\n");
    printf("Expresiones validas  : %d\n", n_validas);
    printf("Expresiones invalidas: %d\n", n_errores);
    return 0;
}
