#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


    char *line;
    char **args;
    int status;
    int position; // POSITION VAR: its a special variable, position is used througout by the reader and parser.
//
//    READ FUNCTIOMALITY:
//    This part of the code should work as:
//    1. read input from user
//    1-1. if EOF insert \0
//    2. if input exceeds buffer size reallocate by 1024
//
    #define LSH_RL_BUFFSIZE 1024
    char *lsh_read_line(void) {
        position = 0;
        int buffsize = LSH_RL_BUFFSIZE;
        char *buffer = malloc(sizeof(char) * buffsize);
        int c;

        if(!buffer) {
            fprintf(stderr, "lsh: allocation error");
            exit(EXIT_FAILURE);
        }

        while (1) {
            c = getchar();
            // every iteration while loop checks if we hit EOF or a newline
            if (c == EOF || c == '\n' ) {
                //if EOF you end the line
                buffer[position] = '\0';
                return buffer;
            }
            else {
                buffer[position] = c;   
            }
            position++;

            if (position >= buffsize){
                buffer += LSH_RL_BUFFSIZE;
                buffer = realloc(buffer, buffsize);
            if (!buffer) {
                    fprintf(stderr, "lsh: allocation error");
                    exit(EXIT_FAILURE);
            }    
        }        
    }
}
//
//      PARSING AND LEXING FUNCTIONALITY
//      
    #define LSH_TOKEN_BUFFSIZE 64
    #define LSH_TOKEN_DELIM " \t\r\n\a"
    char **lsh_parse_line(char *line) {
        position = 0;
        int buffsize = LSH_TOKEN_BUFFSIZE;
        char** tokens = malloc(buffsize * sizeof(char*));
        char* token;

        if (!tokens) {
            fprintf(stderr, "lsh_ allocation error");
            exit(EXIT_FAILURE);
        }

        token = strtok(line, LSH_TOKEN_DELIM);
        while(token =! NULL) {
            tokens[position] = token;
            position++;
            if (position >= buffsize) {
                buffsize += LSH_TOKEN_BUFFSIZE;
                tokens = realloc(tokens, buffsize * sizeof(char*));
                if (!tokens) {
                    printf("lsh: allocation error");
                    exit(EXIT_FAILURE);
                }
            }
            tokens = strtok(NULL, LSH_TOKEN_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
    }

    /** LIST OF TODO'S
     *      @todo lsh_execute_line:
     *      - this function needs to execute the built-in shell commands (cd, ls, exit, help etc.)
     *      - it should compare input (maybe use strcmp to do it) to detect a shell command
     *      - if it detects any, then it should return a shell command function call
     *          @todo create the built-in shell commands                  
    **/

    int lsh_execute_line() {

        return 1;
    }
