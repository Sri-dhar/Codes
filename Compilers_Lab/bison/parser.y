%{
#include <stdio.h>
#include <string.h>
extern int yylex(void);
extern char* yytext;
void yyerror(const char* s);
%}

%token NUMBER PLUS

%%

expr:
      expr PLUS term  { printf("Addition: %d + %d = %d\n", $1, $3, $1 + $3); $$ = $1 + $3; }
    | term            { $$ = $1; }
;

term:
      NUMBER          { $$ = $1; }  // Use yylval instead of yytext
;

%%



int main() {
    printf("Enter an expression (e.g., 3 + 4): ");
    yyparse();
    return 0;
}
