#ifndef HELPER_H
#define HELPER_H

// append a character string to a character buffer
void append_char_ptr(unsigned short * buf_size, unsigned short * buf_pos, char **ip, char *append);

// flush stdin
void flush_input();

// finds a file to open
void get_file(unsigned char * success_op, char * file_name, FILE ** fp);

#endif /* HELPER_H */