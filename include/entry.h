#include <stdio.h>
#ifndef ENTRY_H
#define ENTRY_H

void create_entry(char* entry_buffer, FILE *fp);

void replace_entry(char* exclude, char* replacement, FILE**, char* file_name);

// seeks a specific record from previously made file by name
int seek_by_column(char* entry_buffer, char* compare_to, int column_num, int* found, FILE *fp);

#endif /* ENTRY_H */