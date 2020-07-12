#include <headers/lexer/lexer.h>
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

        // create arguments table
        lua_newtable(L);

        // push arguments to stack
        for (int i = 1; i <= currentToken.commandArgCount; i++) {
            Token arg = tokens[readingPosition+i];

            lua_pushnumber(L, i-1);

            if (arg.type == identifier) {
                lua_pushstring(L, arg.value.string);
            }

            if (arg.type == integer) {
                lua_pushnumber(L, arg.value.integer);
            }

            if (arg.type == decimal) {
                lua_pushnumber(L, arg.value.decimal);
            }

            else if (arg.type == string) {
                lua_pushstring(L, arg.value.string);
            }

            lua_settable(L, -3);
        }

        // set the arguments
        lua_setglobal(L, "arguments");

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