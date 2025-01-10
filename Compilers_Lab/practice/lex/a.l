%{
    #include<stdio.h>
    #define MAX 100
    #define IF 1
    #define ELSE 2
    #define NUM 3
    #define OP 4
    #define ERR 5
%}

%%
if      { printf("IF token: %d\n", IF); return(IF); }
else    { printf("ELSE token: %d\n", ELSE); return(ELSE); }
[0-9]+  { printf("NUM token: %d\n", NUM); return(NUM); }
[+-]    { printf("OP token: %d\n", OP); return(OP); }
.       { printf("ERR token: %d\n", ERR); return(ERR); }
%%

int main() {
    printf("Enter input: \n");
    while(yylex()); 
    return 0;       
}

int yywrap() {
    return 1;
}


// When yylex() is invoked, it reads the input file and scans through
// the input looking for a matching pattern.
// • When the input or a part of the input matches one of the given
// patterns, yylex() executes the corresponding action associated
// with the pattern as specified in the Rules section.
// • yylex() continues scanning the input
// (a) till one of the actions corresponding to a matched pattern
// executes a return statement or
// (b) till the end of input has been encountered.
// • Note that if none of the actions in the Rules section executes a
// return statement, yylex() continues scanning for more matching
// patterns in the input file till the end of the file.