#include "luahelpers.h"

int luah_mapHasKey (lua_State* L, const char* map, const char *key) {
    lua_getglobal(L, map); // push map to top of stack
    lua_pushstring(L, key); // push key to top of stack
    lua_gettable(L, -2);  /* get table back */

    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);  /* remove number */
        return 1;//true
    } else {
        lua_pop(L, 1);  /* remove number */
        return 0;//false
    }
}