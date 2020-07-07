#include "luahelpers.h"

/* assume that table is on the stack top */
char* getfield (lua_State* L, const char *key) {
    char* result;
    lua_pushstring(L, key);
    lua_gettable(L, -2);  /* get background[key] */

    if (lua_isnil(L, -1))
        puts("i");

    result = (char*)lua_tostring(L, -1);
    lua_pop(L, 1);  /* remove number */
    return result;
}

int luah_mapHasKey (lua_State* L, const char* map, const char *key) {


    lua_getglobal(L, map);

    if (lua_istable(L, -1))
        printf("yeeee");

    char* field = getfield(L, key);
    printf("field = %s\n", field);
    return 1;//true
}

