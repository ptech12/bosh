// header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"

// functions declarations
// the starting of shell, bosh()
void bosh();
// function to read user commands
char *read();
// function to split or tokenizing the input
char **split_into_tokens(char *);
// heart of the bosh, the commands execution
int bosh_execute(char **);
// finally, exit the bosh
int bosh_exit();
// main function, and starting the shell
int main(int argc, char const *argv[])
{
    bosh();
    return 0;
}


