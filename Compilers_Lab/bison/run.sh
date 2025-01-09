#!/bin/bash

if bison -d parser.y; then
    echo "Generated parser (parser.tab.c and parser.tab.h)"
else
    echo "Failed to generate parser files. Check parser.y for syntax errors."
    exit 1
fi

if flex lexer.l; then
    echo "Generated lexer (lex.yy.c)"
else
    echo "Failed to generate lexer file. Check lexer.l for syntax errors."
    exit 1
fi

if gcc -o parser parser.tab.c lex.yy.c -lfl; then
    echo "Compiled lexer and parser into 'parser'"
else
    echo "Failed to compile the files. Check for missing files."
    exit 1
fi

if [ -f ./parser ]; then
    ./parser
else
    echo "Executable 'parser' not found."
    exit 1
fi
