#include "commandIdentifier.h"

void commandIdentifier(lua_State* L, Token** tokens) {
    unsigned int i = 0;
    while ((*tokens)[i].type != EOP) {
        if ((*tokens)[i].type == identifier) {
            printf("identifier found: %s\n", (*tokens)[i].value.string);
            if (luah_mapHasKey(L, "commands", (*tokens)[i].value.string)) {
                puts("it is a command");
            } else {
                puts("its not a command");
            }
        }
        i++;
    }
}