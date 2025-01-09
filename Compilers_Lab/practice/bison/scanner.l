/* scanner.l */
%{
#include <stdio.h>
#include "parser.tab.h"
extern YYSTYPE yylval;
%}

%%
[0-9]+      { yylval.value = atoi(yytext); return NUMBER; }
[-+*/()]    { return yytext[0]; }
[ \t]+      { /* ignore whitespace */ }
\n          { return '\n'; }
.           { printf("Unexpected character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}