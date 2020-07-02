#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// this function is used to read a file, so it can later be parsed and interpreted
// TODO: change reading mode from r to rb to avoid \n\r
// TODO: figgure out the file size before reading to avoid realloc
char*  ReadFile(char* fileName);

uint8_t fileExists(char* fileName);