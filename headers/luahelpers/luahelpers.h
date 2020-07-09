#pragma once

#include <string.h>

#include "libs/lua/lua.h"
#include "libs/lua/lauxlib.h"


int luah_commandExists(lua_State* L, const char *command);
int luah_commandIndex(lua_State* L, const char *command);
int luah_commandArgCount(lua_State* L, const char *command, unsigned int i);