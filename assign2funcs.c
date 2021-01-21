/*Source: assign2funcs.c */
#include "assign2funcs.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

void cut(int argc, char* argv[]) {
    // Populating fields
    int i, numFields;
    numFields = (argc-3);
    int fields[numFields]; 
    for (i = 0; (i+3)<argc; i++)
        fields[i] = atoi(argv[i+3]);

    // Setting input and output delimiters
    char file[100];
    char* inDel= argv[1];
    char* outDel= argv[2];
    int currIndex=0, fieldCount=0;
    int delimiterChecker=0;

    // Iterating through file lines
    while (fgets(file, 100, stdin)) {
        for (int i = 0; i < 100 ; i++) {

            // If end of the line reached
            if (file[i] == '\n') {
                if (delimiterChecker == 0 && fields[0] != 1) {
                    for (int j = 0; j <100 ; j++){
                        delimiterChecker = 0;
                        if (file[j] == '\n') break;
                        printf("%c", file[j]);
                    }
                }
                delimiterChecker = 0;
                currIndex = 0;
                fieldCount = 0;
                break;
            }

            // If character is the input delimeter, print the output delimeter
            if (file[i] == *inDel) {
                delimiterChecker++;
                fieldCount++; 
                for (int currField = 0; currField < fieldCount+1; currField++) {
                    if (fields[currField+1] == fieldCount+1 && fields[currField+1] != fields[fieldCount+1]) {
                        printf("%s",outDel);
                    }
                } 
            }
        
            // If character is not the input delimeter, print the chracter
            else {
                for (int j = 0; j < numFields; j++) {
                    if (fields[j] == fieldCount+1) {
                        printf("%c", file[i]);
                    }
                    if (file[i+1]== '\0' && fieldCount == fields[numFields-1]) {
                        printf("%c", file[i]);
                        break;
                    } 
                }
            currIndex++;
            }
        }
    printf("\n");
    }
}

void verify(int argc, char *argv[]) {
    int i, j, k;
    int len;
    bool valid = true;

    //Error checking: Delimiters
    //Checking for correct number of arguments
    if (argc < 4) valid = false;
    
    //Checking for single character delimeters
    else if (strlen(argv[1]) != 1 || strlen(argv[2]) != 1 ) valid = false;
    
    //Error checking: Fields
    for (i=3; i<argc; i++) {
        //Checking for correct number of fields
        if (i > MAX + 3) valid = false;
    
        for (j=0; j < strlen(argv[i]); j++) {
            //Check if field has digits
            if (argv[i][j] >= '0' && argv[i][j]  <= '9') continue;
            
            //Check if the field contains alpha characters
            else if (isalpha(argv[i][j])) valid = false;
            
            //Check if the field has special characters
            else valid = false;
        }

        //Checking for unique fields
        for (k=i+1; k<argc; k++) { 
            if (strcmp(argv[i], argv[k]) == 0) valid = false;
        }

        //Checking for increasing order of fields
        if (i < argc-1 && atoi(argv[i+1]) < atoi(argv[i])) valid = false;
    }  

    if (!valid) {
        fprintf(stderr, "%s: specify input_delimiter output_delimiter and 1-%d fields in order\n", argv[0], MAX);
        exit(1);
    }
}