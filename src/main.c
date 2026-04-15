#include "../include/shell.h"

int lsh_loop() {

    do {
        printf(">");

        line = lsh_read_line();
        args = lsh_parse_line(line);
        status = lsh_execute_line(args);

        free(line);
        free(args);
    } while (status);
    

}

int main(int argc, char **argv[]) {

    lsh_loop();
    
return EXIT_SUCCESS;
}