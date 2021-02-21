// header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
// functions declarations
// the starting of shell, bosh()
void bosh();
// function to read user commands
char *read_input();
// function to split or tokenizing the input
char **split_into_tokens(char *);
// heart of the bosh, the commands execution
int bosh_execute(char **);
// finally, exit the bosh
int bosh_exit();
// display error mesages
void allocate_error_message()
{
    fprintf(stderr, "%sAllocation Error%s", RED, RESET);
    exit(EXIT_FAILURE);
}
// main function, and starting the shell
int main(int argc, char const *argv[])
{
    bosh();
    return 0;
}

// the starting of shell, bosh()
void bosh()
{
    // this holds the entire command entered by user;
    char *line;
    // 2-D, this holds splited commands for further execution
    char **args;
    // status stores the return value of bosh_execute
    int status = 1;
    // do, infinite times
    do{
        printf("> ");
        // read input
        line = read_input();
        args = split_into_tokens(line);
        status = bosh_execute();
        // free up some memory;
        free(line);
        free(args);
    }while(status);
}

// function to read user commands
char *read_input()
{
    // for memory allocations and initializations
    int buffer_size = RL_BUFFER_SIZE, pos = 0, c;
    // allocate some memory
    char *buffer = malloc(buffer_size * sizeof(char));
    // checking buffer allocated or not
    if(!buffer)
    {
        allocate_error_message();
    }
    // read untill line break
    while(1)
    {
        c = getchar();
        // END-of-FILE or newline
        if(c == EOF || c == '\n')
        {
            buffer[pos] = '\0';
            return buffer;
        }else{
            buffer[pos] = c;
        }
        pos++;
        // Reallocation, if memory not enough
        if(pos >= buffer_size){
            buffer_size += RL_BUFFER_SIZE;
            buffer = realloc(buffer, buffer_size);
            if(!buffer)
                allocate_error_message();
        }
    }
}