#pragma once

#include "libs/lua/lua.h"
#include "libs/lua/lauxlib.h"
#include "../lexer/lexer.h"
#include "../fileReader/fileReader.h"

void libLoader(lua_State *L, Token* tokens);