#pragma once

#include "libs/lua/lua.h"
#include "libs/lua/lauxlib.h"

int luah_mapHasKey(lua_State* L, const char* map, const char *key);