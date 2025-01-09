%{
#include "parser.tab.h"  // Include the Bison-generated header
%}

%%

[0-9]+   { yylval = atoi(yytext); return NUMBER; }
"+"      { return PLUS; }
[ \t\n]+ { /* Ignore whitespace */ }
.        { return yytext[0]; }
%%
