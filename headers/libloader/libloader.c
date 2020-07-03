#include "libloader.h"

char* typeToString(TokenType tt) {
    switch (tt) {
        case 0: return "string";
        case 1: return "integer";
        case 2: return "decimal";
        case 3: return "marker";
        case 4: return "identifier";
        case 5: return "command";
        case 6: return "import";
        case 7: return "EOP";
        default: return "unknown";
    }
}

void assertType(Token t, TokenType tt){
    if (t.type == tt) {
        return;
    } else {
        printf("[ERROR] type error on line %d, expected %s but got %s", t.lineNumber, typeToString(tt), typeToString(t.type));
        exit(1);
    }
}

void commandLoader(lua_State *L, Token* tokens) {
    unsigned int tokIndex = 0;
    Token currToken = tokens[tokIndex];
    while (currToken.type != EOP) {
        assertType(currToken, 6);

        if (!fileExists(currToken.value.string)) {
            printf("[ERROR] could not import %s", currToken.value.string);
            exit(1);
        }

        //printf("importing %s\n", currToken.value.string);

        luaL_dofile(L, currToken.value.string);
        currToken = tokens[++tokIndex];
    }

    //TODO: look if the funtions are actually imported
}