#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include "../include/validators.h"
#include "../include/helpers.h"

void create_entry(char* entry_buffer, FILE *fp){
    char id[11];
    char name[101];
    char email[101];
    char course[21];
    char grade[3];

    // get student id
    input_validator("Enter Student ID: ", id, 10, "\nStudent ID is 1-10 digits. Please try again: ", isdigit);

    // get student name
    input_validator("Enter Student Name: ", name, 100, "\nStudent name is 1-100 characters. Please try again: ", name_validator);

    // get email id
    input_validator("Enter Student Email: ", email, 100, "\nStudent email is 1-100 characters. Please try again: ", email_validator);

    // get course id
    input_validator("Enter Course ID: ", course, 20, "\nCourse ID is max 1-20 characters. Please try again: ", str_or_int);

    // get grade
    input_validator("Enter Grade: ", grade, 2, "\nGrade is 1-2 characters. ie. A+, A. Please try again: ", grade_validator);        

    sprintf(entry_buffer, "| %-10s | %-10s | %-10s | %-10s | %-10s |\n", id, name, email, course, grade);

    printf("%s\n", entry_buffer);

    // write the entry to the file
    size_t written = fwrite(entry_buffer, sizeof(char), strlen(entry_buffer) + 1, fp);

    if (ferror(fp)) {
        perror("Error writing to file");
    }
}


void replace_entry(char* exclude, char* replacement, FILE** fp, char* file_name){
    // read the file contents into a buffer, ignoring this entry
    unsigned short buf_size = 250;
    unsigned short buf_pos = 0;
    char *ip = (char *) calloc(buf_size, sizeof(char));
    char temp_bfr[250]; 

    // start reading entries, only write when we have a full entry in mem to make sure we have enough room in ip
    unsigned short index = 0;
    
    while(fread(temp_bfr + index, sizeof(char), sizeof(char), *fp) > 0){

        // a full entry has been buffered
        if(temp_bfr[index] == '\0'){

            // check that it is not the entry to be excluded
            if(!(strncmp(temp_bfr, exclude, strlen(temp_bfr)) == 0)){
                append_char_ptr(&buf_size, &buf_pos, ip, temp_bfr);
            } 
            else {
                printf("\nDeleting: %s\n", temp_bfr);
                printf("\nReplacing with: %s\n", replacement);
                append_char_ptr(&buf_size, &buf_pos, ip, replacement);
            }

            index = 0;
        }
        else index++;
    }


    for(int j = 0; j < buf_size; j++){
        printf("%c", ip[j]);
    }

    // write the buffer contents to the file
    fclose(*fp);
    *fp = fopen(file_name, "w");

    if (*fp == NULL) {
        perror("Error opening file for write");
    } 
    else {
        fwrite(ip, sizeof(char), buf_pos, *fp);
    }

    free(ip);
}


// seeks a specific record from previously made file by name
int seek_by_column(char* entry_buffer, char* compare_to, int column_num, int* found, FILE *fp){

        unsigned char index = 0;
        while(fread(entry_buffer + index, sizeof(char), sizeof(char), fp) > 0){
            // printf(" %d ", index);
            // a full entry has been buffered
            if(entry_buffer[index] == '\0'){
                // extract name from between second pair of | |
                char brackets = 0;
                unsigned char i = 0;

                while(brackets < 3){
                    if(entry_buffer[i] == '|')
                        brackets++;
                    else if(brackets == column_num){
                        // printf("Searching %s\n", &entry_buffer[i+1]);
                        // printf("for %s\n", compare_to);
                        // start reading name after space ahead of this bracket
                        if(strncmp(&entry_buffer[i+1], compare_to, strlen(compare_to)) == 0){
                            *found = 1;
                        }
                        break;
                    } 
                    i++;
                }

                index = 0;
                
                if(*found)
                    break;
            }
            else index++;
        }

        // Reset the file pointer to the beginning of the file
        if (fseek(fp, 0, SEEK_SET) != 0) {
            perror("\nfseek failed\n");
            fclose(fp);
            return 0;
        }

        return 1;
}
