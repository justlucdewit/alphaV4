#include "luahelpers.h"

int luah_commandExists (lua_State* L, const char *command) {
    lua_getglobal(L, "commands"); // push command map to top of the stack

    int i = 1;

    while (1) {
        lua_rawgeti(L, -1, i++); // push current value to top of the stack
        if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            return 0; // false
        }

        lua_rawgeti(L, -1, 2); // get string name of command
        const char *currCommand = lua_tostring(L, -1);

        // pop top 2 values from the stack
        lua_pop(L, 2);

        if (strcmp(currCommand, command) == 0) {
            lua_pop(L, 1);
            return 1; //true
        }
    }
}

int luah_commandIndex(lua_State* L, const char *command){
    lua_getglobal(L, "commands"); // push command map to top of the stack

    int i = 1;

    while (1) {
        lua_rawgeti(L, -1, i++); // push current value to top of the stack
        if (lua_isnil(L, -1)) {
            lua_pop(L, 2);
            return 0; // false
        }

        lua_rawgeti(L, -1, 2); // get string name of command
        const char *currCommand = lua_tostring(L, -1);

        // pop top 2 values from the stack
        lua_pop(L, 2);

        if (strcmp(currCommand, command) == 0) {
            lua_pop(L, 1);
            return i-1; //true
        }
    }
}

int luah_commandArgCount(lua_State* L, const char *command, unsigned int i) {
    lua_getglobal(L, "commands"); // push command map to top of the stack
    lua_rawgeti(L, -1, i);// get the command item to the top of the stack
    lua_rawgeti(L, -1, 3);// get command count
    int argCount = lua_tointeger(L, -1);
    lua_pop(L, 3); // clear stack again
    return argCount;
}