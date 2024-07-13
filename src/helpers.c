#include <stdio.h>
#include "../include/validators.h"
#include <string.h>
#include <stdlib.h>

// append a character string to a character buffer
void append_char_ptr(unsigned short * buf_size, unsigned short * buf_pos, char *ip, char *append){
    unsigned short append_len = strlen(append) + 1;
    // if append len is 1 is was a null string '\0', don't append
    if(append_len > 1){

        if( ((*buf_size) - (*buf_pos)) > append_len ){

            // copy append into the buffer
            unsigned short cpy_index = 0;
            while(cpy_index < append_len){
                // write to ip
                ip[*buf_pos] = append[cpy_index];
                (*buf_pos)++;
                cpy_index++;
            }

        } 
        else {
            // else realloc ip before writing to it
            *buf_size += 250;
            ip = (char*) realloc(ip, (*buf_size) * sizeof(char));
        }
    }
}


// finds a file to open for read
void get_file(unsigned char * success_op, char * file_name, FILE** fp){
    while(!(*success_op)){

        input_validator("Please enter file name: ", file_name, 20, "\nFile name(max. 20 characters) consists of alpha or digit characters: ", file_validator);

        short nm_len = strlen(file_name);
        if( nm_len <= 4 || strcmp(file_name + nm_len - 4, ".bin") ){
            file_name[nm_len++] = '.';
            file_name[nm_len++] = 'b';
            file_name[nm_len++] = 'i';
            file_name[nm_len++] = 'n';
            file_name[nm_len] = '\0';
        }

        printf("Trying to open: %s\n", file_name);

        *fp = fopen(file_name, "r");

        if (*fp == NULL) {
            perror("Error opening file");

            // Try again?
            char rpt[2];

            input_validator("Would you like to try again? (Y/n): ", rpt, 1, "Answer must be Y (Yes) / N (No): ", bool_validator);

            if(rpt[0] != 'Y' && rpt[0] != 'y')
                break;
        }
        else {
            printf("file found %s\n", file_name);
            *success_op = 1;
        }
    }
}


// flush remainder of input up to newline or end of line
void flush_input(){
    // Clear the input buffer
    char flush;
    while ((flush = getchar()) != EOF && flush != '\n' );
}

