#ifndef VALIDATOR_H
#define VALIDATOR_H


// main input validator, takes in one of the validators below
void input_validator(char* msg, char* buffer, short maxline, char* err_msg, int (*validator)(int) );

// various input validator helpers

// is a string or an integer
int str_or_int(int p);

// is a valid file name
int file_validator(int p);

// is a valid grade
int grade_validator(int p);

// is a valid name
int name_validator(int p);

// is a valid email 
int email_validator(int p);

// is a valid yes or no response
int bool_validator(int p);

// is a valid name N or i response
int N_i_validator(int p);

//is a valid U or d response
int U_d_validator(int p);

// is a valid option from the menu
int menu_validator(int p);

#endif /* VALIDATOR_H */