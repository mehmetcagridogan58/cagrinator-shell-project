#include "../include/shell.h"

int shell_loop() {

    do {
        printf(">");

        line = shell_read_line();
        args = shell_parse_line(line);
        status = shell_execute_line(args);

        free(line);
        free(args);
    } while (status);
    

}

int main(int argc, char **argv[]) {

    lsh_loop();
    
return EXIT_SUCCESS;
}