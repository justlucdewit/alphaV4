#include "commandIdentifier.h"

void commandIdentifier(lua_State* L, Token** tokens) {
    unsigned int i = 0;
    while ((*tokens)[i].type != EOP) {

        if ((*tokens)[i].type == identifier){
            if (luah_commandExists(L, (*tokens)[i].value.string)) {

                (*tokens)[i].type = command;
                (*tokens)[i].commandIndex = luah_commandIndex(L, (*tokens)[i].value.string);
                (*tokens)[i].commandArgCount = luah_commandArgCount(L, (*tokens)[i].value.string, (*tokens)[i].commandIndex);
                //printf("command %s is at index %d and needs %d arguments\n", (*tokens)[i].value.string, (*tokens)[i].commandIndex, (*tokens)[i].commandArgCount);
            }
        }
        i++;
    }

}