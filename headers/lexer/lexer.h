#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// an enum that stores what type a token is
typedef enum{
    string,
    integer,
    decimal,
    marker,
    identifier,
    command,
    import,
    EOP, // end of program
} TokenType;

// the struct that will store the tokens
typedef struct {
    int lineNumber;
    TokenType type;
    union{
        double decimal;
        int integer;
        char* string;
    } value;
} Token;

// the function that will transform a raw
// sourceCode string into an array of tokens
// TODO: combine the lexical analyzer modes into one multi-state variable using an enumeration
void lexer(const char* sourceCode, Token**, Token**);

int charIsWhitespace(char c);

int charIsComment(char c);

int charIsDigit(char c);

int charIsMarker(char c);