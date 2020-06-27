#include "lexer.h"

int charIsWhitespace(char c) {
    return c == ' '||c == '\t'||c == '\n';
}

int charIsIdentifier(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '-';
}

int charIsComment(char c) {
    return c == '#';
}

int charIsDigit(char c) {
    return (c >= '0' && c <= '9') || c == '-' || c == '.';
}

int charIsMarker(char c) {
    return c == ':';
}

int charIsString(char c) {
    if (c == '"') {
        return 1;
    } else if (c == '\'') {
        return 2;
    } else if (c == '`') {
        return 3;
    }
    return 0;
}

Token* lexer(const char* sourceCode) {
    // create storage for the tokens
    int tokensCapacity = 100;
    int tokensIndex = 0;
    Token* tokensArray = (Token*) malloc(tokensCapacity * sizeof(Token));

    // lexer states
    Token currToken;
    int readingIndex = 0;
    int lineCount = 1;
    char currentChar = sourceCode[readingIndex++];
    int commentMode = 0;
    int stringMode = 0;
    int stringCapacity = 100;
    int stringSize = 0;
    int digitMode = 0;
    int foundDot = 0;
    int markerMode = 0;
    int identifierMode = 0;

    while(currentChar != '\0') {
        // increment line counter
        if (currentChar == '\n') {
            lineCount++;
        }

        // handle comment mode
        if (commentMode) {
            if (currentChar == '\n') {
                commentMode = 0;
            }
            currentChar = sourceCode[readingIndex++];
            continue;
        }

        // handle marker mode
        if (markerMode) {
            if (charIsIdentifier(currentChar)) {
                //add it to the string
                currToken.value.string[stringSize++] = currentChar;
                if (stringSize >= stringCapacity) {
                    stringCapacity = (int)((double)stringCapacity*1.5);
                    currToken.value.string = (char*) realloc(currToken.value.string, stringCapacity);
                }
                currentChar = sourceCode[readingIndex++];
                continue;
            } else {
                markerMode = 0;

                // add null terminator to string and resize it to fit
                currToken.value.string = (char*) realloc(currToken.value.string, stringSize+1);
                currToken.value.string[stringSize] = '\0';
                currToken.lineNumber = lineCount;

                // push curr token to array
                tokensArray[tokensIndex++] = currToken;
                if (tokensIndex >= tokensCapacity) {
                    tokensCapacity = (int)((double)tokensCapacity*1.5);
                    tokensArray = (Token*) realloc(tokensArray, tokensCapacity);
                }
            }
        }

        // handle digit mode
        if (digitMode) {
            if ((currentChar >= '0' && currentChar <= '9') || (currentChar == '.' && !foundDot)) {
                if (currentChar == '.') {
                    foundDot = 1;
                }
                currToken.value.string[stringSize++] = currentChar;
                if (stringSize >= stringCapacity) {
                    stringCapacity = (int)((double)stringCapacity*1.5);
                    currToken.value.string = (char*) realloc(currToken.value.string, stringCapacity);
                }
            } else {
                digitMode = 0;

                // add null terminator to string and resize it to fit
                currToken.value.string = (char*) realloc(currToken.value.string, stringSize+1);
                currToken.value.string[stringSize] = '\0';
                currToken.lineNumber = lineCount;

                // convert from string to number
                char* origString = currToken.value.string;
                if (foundDot) {
                    currToken.type = decimal;
                    currToken.value.decimal = atof(origString);
                } else {
                    currToken.value.integer = atoi(origString);
                }

                free(origString);

                foundDot = 0;

                // push curr token to array
                tokensArray[tokensIndex++] = currToken;
                if (tokensIndex >= tokensCapacity) {
                    tokensCapacity = (int)((double)tokensCapacity*1.5);
                    tokensArray = (Token*) realloc(tokensArray, tokensCapacity);
                }
            }
            currentChar = sourceCode[readingIndex++];
            continue;
        }

        // handle string mode
        if (stringMode) {
            if ((stringMode == 1 && currentChar == '"') || (stringMode == 2 && currentChar == '\'') || (stringMode == 3 && currentChar == '`')) {
                stringMode = 0;
            } else {
                // add char to token
                currToken.value.string[stringSize++] = currentChar;

                if (stringSize >= stringCapacity) {
                    stringCapacity = (int)((double)stringCapacity*1.5);
                    currToken.value.string = (char*) realloc(currToken.value.string, stringCapacity+1);
                }

                currentChar = sourceCode[readingIndex++];
                continue;
            }
            currentChar = sourceCode[readingIndex++];

            // add null terminator to string and resize it to fit
            currToken.value.string = (char*) realloc(currToken.value.string, stringSize);
            currToken.value.string[stringSize] = '\0';
            currToken.lineNumber = lineCount;

            // push curr token to array
            tokensArray[tokensIndex++] = currToken;
            if (tokensIndex >= tokensCapacity) {
                tokensCapacity = (int)((double)tokensCapacity*1.5);
                tokensArray = (Token*) realloc(tokensArray, tokensCapacity);
            }
            continue;
        }

        // look for next token possibility
        if (charIsWhitespace(currentChar)) {
            // ignore it
        } else if (charIsIdentifier(currentChar)) {
            identifierMode = 1;
            currToken.type = identifier;
            stringCapacity = 100;
            stringSize = 0;
            currToken.value.string = (char*) malloc(stringCapacity);
        } else if (charIsMarker(currentChar)) {
            markerMode = 1;
            currToken.type = marker;
            stringCapacity = 100;
            stringSize = 0;
            currToken.value.string = (char*) malloc(stringCapacity);
        } else if (charIsDigit(currentChar)) {
            digitMode = 1;
            currToken.type = integer;
            stringCapacity = 100;
            stringSize = 0;
            currToken.value.string = (char*) malloc(stringCapacity);
            currToken.value.string[stringSize++] = currentChar;
        } else if (charIsString(currentChar)) {
            stringMode = charIsString(currentChar);
            currToken.type = string;
            stringCapacity = 100;
            stringSize = 0;
            currToken.value.string = (char*) malloc(stringCapacity);
        } else if (charIsComment(currentChar)) {
            commentMode = 1;
        } else {
            printf("[ERROR 002] unknown character found: %c\n", currentChar);
            //exit(2);
        }

        // go to next character
        currentChar = sourceCode[readingIndex++];
    }

    currToken.type = EOP;
    tokensArray[tokensIndex++] = currToken;

    return tokensArray;
}