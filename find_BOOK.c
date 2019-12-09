#include "head.h"

int read_line(char temp_line[], int fd){
	for(int i = 0; i < 100 ; i++){
		temp_line[i] = '\0';
		read(fd, temp_line + i, 1);
		if(temp_line[i] == '\n' || temp_line[i] == EOF){
			temp_line[i] = '\0';
			return i;
		}
	}
	
	return -1;
}

int find_BOOK(){
	
	int fd, check;
	char input_title[100];
	char temp_line[100];
	
	system("clear");
	printf("\033[%d;%df",7, 26);
	printf("title: ");
	scanf("%[^\n]s", input_title);	

	fd = open("./book_list.txt",O_RDONLY);
	if(fd == -1)
		perror("failed to open");
	
	else{
		for(int i = 0; check != -1 ; i++){
			check = read_line(temp_line, fd);
			strtok(temp_line, "/");
			if(!strcmp(temp_line, input_title)){
				close(fd);
				return i;
			}
		}
	}	
	close(fd);
	return -1;
}

int find_BOOK2(char* input_title){
	
	int fd, check;
	char temp_line[100];
	
	fd = open("./book_list.txt",O_RDONLY);
	if(fd == -1)
		perror("failed to open");
	
	else{
		for(int i = 0; check != -1 ; i++){
			check = read_line(temp_line, fd);
			strtok(temp_line, "/");
			if(!strcmp(temp_line, input_title)){
				close(fd);
				return i;
			}
		}
	}	
	close(fd);
	return -1;
}