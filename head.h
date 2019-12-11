#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

#define MAX_LENGTH 128

int menu(void);
int find_BOOK(void);
int find_BOOK2(char* input_title, int file);
int read_line(char temp_line[], int fd);
void total_selling(void);
void selling_BOOK(void);
void check_bestseller(char* name_c, int compare);
void check_sold_out(char* name_c, int compare);
void remove_BOOK(void);
void add_NEW(void);
void add_OLD(void);
void remove_sold_out(char* name);
void search(void);