/*Source: assign2.c */
#include "assign2funcs.h" 
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    verify(argc, argv);
    cut(argc, argv); 
    exit(0);
}