#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


    char *line;
    char **args;
    int status;

    #define LSH_RL_BUFFSIZE 1024
    char *lsh_read_line() {
        int position = 0;
        int buffsize = LSH_RL_BUFFSIZE;
        char *buffer = malloc(sizeof(char), buffsize);
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
    #define LSH_TOKEN_BUFFSIZE 64
    #define LSH_TOKEN_DELIM " \t\r\n\a"
    char **lsh_parse_line() {

    } 

    int lsh_execute_line() {

        return 1;
    }
