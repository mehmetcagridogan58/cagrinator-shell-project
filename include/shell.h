#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>  // This is a POSIX (linux) header so i check if my code compiles through WSL

    char *line;
    char **args;
    int status;

//
//    READ FUNCTIOMALITY:
//    This part of the code should work as:
//    1. read input from user
//    1-1. if EOF insert \0
//    2. if input exceeds buffer size reallocate by 1024
//
    #define SHELL_RL_BUFFSIZE 1024
    char *shell_read_line(void) {
        int position = 0;
        int buffsize = SHELL_RL_BUFFSIZE;
        char *buffer = malloc(sizeof(char) * buffsize);
        int c;

        if(!buffer) {
            fprintf(stderr, "shell: allocation error");
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

            if (position >= buffsize) {
                buffer += SHELL_RL_BUFFSIZE;
                buffer = realloc(buffer, buffsize);
            if (!buffer) {
                    fprintf(stderr, "shell: allocation error");
                    exit(EXIT_FAILURE);
            }    
        }        
    }
}
//
//      PARSING AND LEXING FUNCTIONALITY
//      
    #define SHELL_TOKEN_BUFFSIZE 64
    #define SHELL_TOKEN_DELIM " \t\r\n\a"
    char **lsh_parse_line(char *line) {
        int position = 0;
        int buffsize = SHELL_TOKEN_BUFFSIZE;
        char** tokens = malloc(buffsize * sizeof(char*));
        char* token;

        if (!tokens) {
            fprintf(stderr, "shell: allocation error");
            exit(EXIT_FAILURE);
        }

        token = strtok(line, SHELL_TOKEN_DELIM);
        while(token =! NULL) {
            tokens[position] = token;
            position++;
            if (position >= buffsize) {
                buffsize += SHELL_TOKEN_BUFFSIZE;
                tokens = realloc(tokens, buffsize * sizeof(char*));
                if (!tokens) {
                    printf("shell: allocation error");
                    exit(EXIT_FAILURE);
                }
            }
            tokens = strtok(NULL, SHELL_TOKEN_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
    }

    /** LIST OF TODO'S
     *      @todo lsh_execute_line:
     *      - this function needs to execute the built-in shell commands (cd, ls, exit, help etc.)  // DONE
     *      - it should compare input (maybe use strcmp to do it) to detect a shell command         // DONE
     *      - if it detects any, then it should return a shell command function call, 
     *          @todo create the built-in shell commands                  
    **/
    
    char *builtInCommands[] = {
        "cd",
        "ls",
        "help",
        "exit",
    };

    char **commands[] = {
        "&cd",
        "&ls",
        "&help",
        "&exit"
    };
    //
    // DIRECTORY OPERATIONS FUNCTIONS AND VARIABLES
    //
    int cd(char **args) {
        if (args[1] == NULL || "/0") {
            fprintf(stderr, "shell: directory doesn't exist");
        }
            if (chdir(args[1]) == -1) { //chdir returns 0 on success and -1 on failure
                /** @todo needs to send an error message **/
            }
            
        return 1;
    }

    int exit(char **args) { 
        return 0;
    }

    int builtInCounter() {
        return sizeof(builtInCommands) / sizeof(char *);
    }

    int lsh_execute_line(char **args) {
        int i;

        if (args[0] == NULL) {
            return 1;
        }
        
        for (i = 0; i < builtInCounter(); i++) {
            if (strcmp(args, builtInCommands[i]) == 0) {
                return *builtInCommands[i];
            }
        }   

        return 1;
    }
