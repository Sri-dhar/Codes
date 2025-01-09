bison -d parser.y
flex scanner.l
gcc -o calc parser.tab.c lex.yy.c -ly -lfl
./calc < input.txt