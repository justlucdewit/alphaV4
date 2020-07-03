cmake_minimum_required(VERSION 3.15)
project(alphaV4 C)

set(CMAKE_C_STANDARD 99)

ADD_LIBRARY(LibsModule libs/lua/lapi.c libs/lua/lcode.c libs/lua/lctype.c libs/lua/ldebug.c libs/lua/ldo.c libs/lua/ldump.c libs/lua/lfunc.c libs/lua/lgc.c libs/lua/llex.c libs/lua/lmem.c libs/lua/lobject.c libs/lua/lopcodes.c libs/lua/lparser.c libs/lua/lstate.c libs/lua/lstring.c libs/lua/ltable.c libs/lua/ltm.c libs/lua/lundump.c libs/lua/lvm.c libs/lua/lzio.c libs/lua/lauxlib.c libs/lua/lbaselib.c libs/lua/lcorolib.c libs/lua/ldblib.c libs/lua/liolib.c libs/lua/lmathlib.c libs/lua/loadlib.c libs/lua/loslib.c libs/lua/lstrlib.c libs/lua/ltablib.c libs/lua/lutf8lib.c libs/lua/linit.c)

add_executable(alphaV4 main.c headers/fileReader/fileReader.c headers/lexer/lexer.c headers/libloader/libloader.c)

target_link_libraries(alphaV4 PRIVATE LibsModule)
target_include_directories(alphaV4 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})