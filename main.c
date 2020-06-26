#include <stdio.h>
#include <string.h>

#include "headers/fileReader/fileReader.h"
#include "headers/lexer/lexer.h"

#define VERSION "alphaV4.0.1"

int main(int argc, char* argv[]) {

    if (argc >= 2) {
        // run command
        if (strcmp(argv[1], "run") == 0) {
            // need an extra argument for the file name
            if (argc >= 3) {
                char* fileName = argv[2];
                // printf("opening file: %s", fileName);
                char* fileContent = ReadFile(fileName);
                Token* tokens = lexer(fileContent);
                // print all the tokens for debug

                int i = 0;
                Token currToken = tokens[i++];
                while(currToken.type != EOP) {
                    if (currToken.type == string)
                        printf("tokentype: string, value: %s\n", currToken.value.string);
                    else if (currToken.type == integer)
                        printf("tokentype: integer, value: %d\n", currToken.value.integer);
                    else if (currToken.type == decimal)
                        printf("tokentype: decimal, value: %f\n", currToken.value.decimal);
                    currToken = tokens[i++];
                }
            }
        }

        // version command
        else if (strcmp(argv[1], "version") == 0) {
            printf(VERSION);
        }

        return 0;
    }

    // print the version if no args provided
    printf(VERSION);

    return 0;
}
