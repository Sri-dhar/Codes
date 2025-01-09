/* parser.y */
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
int result;
%}

%union {
    int value;
}

%token <value> NUMBER
%type <value> expression

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input: /* empty */
     | input expression    { printf("Result: %d\n", $2); }
     ;

expression: expression '+' expression   { $$ = $1 + $3; }
    | expression '-' expression        { $$ = $1 - $3; }
    | expression '*' expression        { $$ = $1 * $3; }
    | expression '/' expression        {
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | '-' expression %prec UMINUS     { $$ = -$2; }
    | '(' expression ')'              { $$ = $2; }
    | NUMBER                          { $$ = $1; }
    ;
%%

int main() {
    printf("Enter arithmetic expressions (one per line):\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}