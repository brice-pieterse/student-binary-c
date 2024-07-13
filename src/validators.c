#include <stdio.h>
#include <ctype.h>
#include "../include/helpers.h"

#define IS_CONTROL_CHAR(c) ((c) >= 0 && (c) < 32)

// main input validator, takes in one of the validators below
void input_validator(char* msg, char* buffer, short maxline, char* err_msg, int (*validator)(int) ){
    // get input
    printf("%s", msg);
    int ch;
    int i = 0;

    for(;;){
        ch = getchar();
        // input can't be blank
        if((ch == EOF || ch == '\n') && i >= 1)
            break;
        else if(!IS_CONTROL_CHAR(ch)){

            if(i >= maxline || !validator(ch)){
                printf("%s", err_msg);
                flush_input();
                i = 0;
            }
            else {
                buffer[i] = ch;
                i++;
            }

        }
    }

    buffer[i] = '\0';
}




// various input validators

// is a string or an integer
int str_or_int(int p){
    return isalpha(p) || isdigit(p);
}

// is a valid file name
int file_validator(int p){
    return isalpha(p) || isdigit(p) || p == '.';
}

// is a valid grade
int grade_validator(int p){
    return isalpha(p) || p == '+' || p == '-';
}

// is a valid name
int name_validator(int p){
    return isalpha(p) || p == 32;
}

// is a valid email 
int email_validator(int p){
    return isalpha(p) || isdigit(p) || (p > 32 && p < 123);
}

// is a valid yes or no response
int bool_validator(int p){
    return p == 'Y' || p == 'y' || p == 'N' || p == 'n';
}

// is a valid name N or i response
int N_i_validator(int p){
    return p == 'N' || p == 'n' || p == 'I' || p == 'i';
}

//is a valid U or d response
int U_d_validator(int p){
    return p == 'U' || p == 'u' || p == 'D' || p == 'd';
}

// is a valid option from the menu
int menu_validator(int p){
    return p > '0' && p <= '6';
}