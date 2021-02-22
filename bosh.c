// header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
//for getting process id
#include <sys/types.h>
#include <unistd.h>
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
        status = bosh_execute(args);
        // free up some memory;
        free(line);
        free(args);
    }while(status);
}

// function to read user commands
char *read_input()
{
    // for memory allocations and initializations
    int buffer_size = RL_BUFFER_SIZE, pos = 0;
    int c;
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
    return buffer;
}

char **split_into_tokens(char* lines)
{
    // initialzing buffer size
    int buffer_size = TK_BUFFER_SIZE, pos = 0;
    // allocating memory
    char** tokens = malloc(buffer_size * sizeof(char*));
    char* token = NULL;
    // checking for proper memory allocation
    if (!tokens)
        allocate_error_message();

    // splitting the lines by strtok
    token = strtok(lines, TOKEN_DEL);
    // while token not null, split it
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;
        // if more means, reallocate it
        if (pos >= buffer_size)
        {
            buffer_size += TK_BUFFER_SIZE;
            tokens = realloc(tokens, buffer_size);
            if (!tokens)
                allocate_error_message();
        }
        token = strtok(lines, TOKEN_DEL);
    }
    tokens[pos] = NULL;
    return tokens;
}

// heart of the bosh, the commands execution
int bosh_execute(char** args)
{
    pid_t cpid;
    int status;
    if (strcmp(args[0], "exit"))
        return bosh_exit();
    cpid = fork();
    if (cpid == 0)
    {
        if (execvp(args[0], args) < 0)
        {
            fprintf(stderr, "bash: %scommand not found%s", RED, RESET);
            exit(EXIT_FAILURE);
        }
    }
    else if (cpid < 0)
    {
        fprintf(stderr, "bash: %sError Forking%s", RED, RESET);
    }
    else
    {
        waitpid(cpid, &status, WUNTRACED);
    }
    return 1;
}

// finally, exit the bosh
int bosh_exit()
{
    return 0;
}
