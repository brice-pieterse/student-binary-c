#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include "../include/validators.h"
#include "../include/helpers.h"
#include "../include/entry.h"

// draws the menu options
void draw_menu(){

    for (int i = 0; i <= 6; i++){
        switch(i){
            case 0:
                printf("\n Welcome - Main Menu \n");
                break;
            case 1:
                printf("1. Create the Binary File\n");
                break;
            case 2:
                printf("2. Display the contents of the file\n");
                break;
            case 3:
                printf("3. Seek a specific record\n");
                break;
            case 4:
                printf("4. Update the contents of a record\n");
                break;
            case 5:
                printf("5. Delete a record for the specific name\n");
                break;            
            case 6:
                printf("6. Exit\n");
                break;
        }
    }
}


// creates a binary file
void write_binary(){

    // get file name
    char file_name[26];
    FILE *fp;
    unsigned char success_op = 0;

    while(!success_op){
        input_validator("Please enter a name for the file: ", file_name, 20, "\nName (max. 20 characters) must consist of alpha or digit characters: ", file_validator);

        short file_nm_index = strlen(file_name);

        // add bin part if not included
        if( file_nm_index <= 4 || strcmp(file_name + file_nm_index - 4, ".bin") ){
            file_name[file_nm_index++] = '.';
            file_name[file_nm_index++] = 'b';
            file_name[file_nm_index++] = 'i';
            file_name[file_nm_index++] = 'n';
            file_name[file_nm_index] = '\0';
        }

        printf("%s\n", file_name);

        fp = fopen(file_name, "w");

        if (fp == NULL) {
            perror("Error opening file");

            // Try again?
            char rpt[2];

            input_validator("Would you like to try again? ", rpt, 1, "\nAnswer must be Y/n", bool_validator);

            if(rpt[0] != 'Y' && rpt[0] != 'y')
                break;
        }
        else success_op = 1;
    }

    if(success_op){
        char header[100]; 

        // Write table header
        sprintf(header, "| %-10s | %-10s | %-10s | %-10s | %-10s |\n", "Student ID", "Name", "Email", "Course ID", "Grade");
        fwrite(header, sizeof(char), strlen(header) + 1, fp);


        char entry_buffer[250]; 
        unsigned char entry = 1;

        // // Write table entries
        for (;;) {

            printf("\n( Entering data for Entry %d )\n", entry);

            create_entry(entry_buffer, fp);

            // Go again?
            char rpt[2];

            input_validator("Would you like to create another entry (Y/n)? ", rpt, 1, "\nAnswer must be Y/n", bool_validator);

            if(rpt[0] == 'Y' || rpt[0] == 'y')
                entry++;
            else 
                break;
        }


        fclose(fp);
    }
}


// reads the contents from a previously made file
void read_binary(){
    
    // get file name
    char file_name[26];
    FILE *fp;
    unsigned char success_op = 0;

    get_file(&success_op, file_name, &fp);

    if(success_op){
        // read all characters out of the file into standard output
        printf("Printing file contents...\n");
        char entry_buffer[250];
        size_t num_chars;
        while((num_chars = fread(entry_buffer, sizeof(char), sizeof(entry_buffer), fp)) > 0){
            fwrite(entry_buffer, sizeof(char), num_chars, stdout);
        }

        fclose(fp);
    }

}


// reads the record, offers to update/delete the record
void seek_record(){

    // get file name
    char file_name[26];
    FILE *fp = fopen(file_name, "r");
    unsigned char success_op = 0;

    get_file(&success_op, file_name, &fp);

    if(success_op){

        // seek by name or id?
        char sk[2];

        for(;;){

            input_validator("Would you like to search by name or ID (N/i)? ", sk, 1, "\nAnswer must be N/i", N_i_validator);

            int found = 0;
            char entry_buffer[250]; 

            // seek by name
            if(sk[0] == 'N' || sk[0] == 'n'){
                char name[101];

                // get student name
                input_validator("Enter Student Name: ", name, 100, "\nStudent names are 1-100 characters. Please try again: ", name_validator);

                printf("\nSearching for name: %s\n", name);

                if(!seek_by_column(entry_buffer, name, 2, &found, fp)){
                    // error seeking
                    break;
                }
            } 
            else {
                char id[11];

                // get student id
                input_validator("Enter Student ID: ", id, 10, "\nStudent ID is 1-10 digits. Please try again: ", isdigit);

                if(!seek_by_column(entry_buffer, id, 1, &found, fp)){
                    // error seeking
                    break;
                }
                
            }

            if(found){
                // print the entry
                printf("%s", entry_buffer);

                // ask if they want to edit or delete it
                // Go again?
                char upd[2];

                input_validator("Would you like to update or delete this entry (U/d)? ", upd, 1, "\nAnswer must be U/d", U_d_validator);

                if(upd[0] == 'U' || upd[0] == 'u'){
                    // write a new entry to the database to replace this one

                    char replacement_buffer[250]; 

                    printf("\n( Updating data for this entry )\n");

                    create_entry(replacement_buffer, fp);
                    replace_entry(entry_buffer, replacement_buffer, &fp, file_name);
                } 
                else {
                    // delete the entry by writing all entries that are not this entry to the file
                    char null_char = '\0';
                    replace_entry(entry_buffer, &null_char, &fp, file_name);
                }

                fclose(fp);
                break;
            }
            else {
                // Go again?
                char rpt[2];

                input_validator("Entry not found. Would you like to try again (Y/n)? ", rpt, 1, "\nAnswer must be Y/n", bool_validator);

                if(rpt[0] == 'N' || rpt[0] == 'n'){
                    fclose(fp);
                    break;
                }
            }
        }

    }

}


// main program
int main(int argc, char *argv[]){

    char running = 1;
    while(running){

        // draw menu
        draw_menu();

        // menu selection
        char selection[2];

        input_validator("Enter Menu Option (1-6): ", selection, 1, "\nMenu options are 1-6. Please try again: ", menu_validator);

        printf("Option selected was: %c\n", selection[0]);

        // exec selection
        switch(selection[0]){
            case '1':
                // option 1: create binary file
                write_binary();
                break;
            break;
            case '2':
                // option 2: display binary file contents
                read_binary();
                break;
            break;
            case '3':
            case '4':
            case '5':
                // seek a record and update/delete it
                seek_record();
                break;
            case '6':
                printf("Goodbye!\n\n");
                running = 0;
            break;
        }
        
    }


    return 0;
}