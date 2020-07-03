#include "interpreter.h"

void assertCommand(Token t) {
    if (t.type != command) {
        printf("[ERROR] expected command on line %d", t.lineNumber);
        exit(1);
    }
}

void interpreter(lua_State *L, Token* tokens) {
    //TODO: make sure all the commands in the tokens array are typed as commands, not as identifiers
    unsigned int i = 0;
    Token currentToken = tokens[i];
    assertCommand(currentToken);
}