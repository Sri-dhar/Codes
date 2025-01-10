%{
    #include<stdio.h>
    #define MAX 100
    #define IF 1
    #define ELSE 2
    #define NUM 3
    #define OP 4
    #define ERR 5
    #define CHAR 6
    extern FILE *yyin;
%}

%%
if          { return(IF); }
else        { return(ELSE); }
[0-9]+      { return(NUM); }
[+-]        { return(OP); }
[a-zA-Z]    { return(CHAR); }
.           { return(ERR); }
%%

int main() {
    FILE *file = fopen("input", "r");  
    if (!file) {  
        perror("Error opening file");
        return 1; 
    }
    
    yyin = file; 

    int ntokens;
    while ((ntokens = yylex()) != 0) {
        if (ntokens == IF) printf("IF token: %s\n", yytext);
        else if (ntokens == ELSE) printf("ELSE token: %s\n", yytext);
        else if (ntokens == NUM) printf("NUM token: %s\n", yytext);
        else if (ntokens == OP) printf("OP token: %s\n", yytext);
        else if (ntokens == CHAR) printf("CHAR token: %s\n", yytext);
        else printf("I don't know what this is: %s\n", yytext);
    }

    fclose(file);  
    return 0;  
}

int yywrap() {
    return 1;  
}
