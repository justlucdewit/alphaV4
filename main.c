#include <stdio.h>
#include <string.h>
#include "libs/lua/lua.h"
#include "libs/lua/lauxlib.h"
#include "libs/lua/lualib.h"

#include "headers/libloader/libloader.h"
#include "headers/interpreter/interpreter.h"
#include "headers/commandIdentifier/commandIdentifier.h"

#define VERSION "alphaV4.0.1"
#define DEPS_MADE 1

int main(int argc, char* argv[]) {

    if (argc >= 2) {
        // run command
        if (strcmp(argv[1], "run") == 0) {
            // need an extra argument for the file name
            if (argc >= 3) {

                // the state of the lua program
                lua_State *L = luaL_newstate();

                luaL_openlibs(L);
                luaL_dostring(L, "commands = {}\nalpha_string = 1"
                                 "\nalpha_identifier");

                char* fileName = argv[2];
                // printf("opening file: %s", fileName);
                char* fileContent = ReadFile(fileName);
                Token* tokens = NULL;
                Token* imports = NULL;

                lexer(fileContent, &tokens, &imports);

                // import all the commands into the lua state
                commandLoader(L, imports);
                free(imports);

                // mark commands as commands, instead of identifier
                commandIdentifier(L, &tokens);

                // run the program
                interpreter(L, tokens);
            }
        }

        // version command
        else if (strcmp(argv[1], "version") == 0) {
            printf(VERSION);
        }

        return 0;
    }

    // print the version if no args provided
    printf(VERSION);

    return 0;
}
