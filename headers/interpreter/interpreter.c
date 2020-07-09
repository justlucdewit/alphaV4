#include "interpreter.h"

void assertCommand(Token t) {
    if (t.type != command) {
        printf("[ERROR] expected command on line %d", t.lineNumber);
        exit(1);
    }
}

void interpreter(lua_State *L, Token* tokens) {
    unsigned int readingPosition = 0;
    Token currentToken = tokens[readingPosition];
    lua_getglobal(L, "commands");

    while (1) {
        if (currentToken.type == EOP) {
            break;
        }

        // make sure we are at a command
        assertCommand(currentToken);

        // get the function
        lua_geti(L, -1, currentToken.commandIndex); // pushed command item
        lua_geti(L, -1, 1); // push function

        // push arguments

        // call the function
        lua_pcall(L, 0, 0, 0);

        // clear the stack
        lua_pop(L, 1);

        // go to next command
        readingPosition += currentToken.commandIndex + 1;
        currentToken = tokens[readingPosition];
    }

    lua_pop(L, 1);
}