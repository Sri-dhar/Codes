%{
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   printf("IDENTIFIER\n");
[0-9]+                    printf("NUMBER\n");
"+"                       printf("PLUS\n");
"if"                      printf("KEYWORD_IF\n");
[ \t\n]+                  ; // Ignore whitespace
.                         printf("UNKNOWN CHARACTER: %s\n", yytext); // This should be the last rule
%%


int main() {
    yylex(); // Call the generated lexical analyzer
    return 0;
}
