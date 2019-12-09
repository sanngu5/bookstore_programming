#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

#define X_INPUT_CURSOR 33
#define Y_INPUT_CURSOR 7

void gotoxy(int x, int y);
void show_and_erase(char* str);
int read_line(char temp_line[], int fd);

int main(){
	fflush(stdout);
	while(1){
		
		int fd;
		char total_selling[50];
		char best_seller[50];
		char sold_out[50];
		strcpy(total_selling,"매출액(원):");
		strcpy(best_seller,"베스트셀러(/부):");
		strcpy(sold_out,"매진된 도서:");
				
		fd = open("./book_selling.txt",O_RDONLY);
		read_line(total_selling + 15, fd);
		close(fd);
		show_and_erase(total_selling);
		
		fd = open("./bestseller.txt",O_RDONLY);
		read_line(best_seller + 22, fd);
		close(fd);
		show_and_erase(best_seller);
		
		fd = open("./sold_out.txt",O_RDONLY);
		while(read_line(sold_out + 17, fd) != -1){
			show_and_erase(sold_out);
		}
		close(fd);
		
	}
}

void gotoxy(int x, int y){
	printf("\33[%d;%df",y,x);
	fflush(stdout);
}

void show_and_erase(char* str){
	
	int x = 45;
	int y = 0;

	gotoxy(x, y);
	printf("%s", str);
	fflush(stdin);
	gotoxy(X_INPUT_CURSOR,Y_INPUT_CURSOR);
	usleep(10000000);
	
	for(int i =0; i < strlen(str) + 1; i++){
		gotoxy(x + i, y);
		printf(" ");
	}

	gotoxy(X_INPUT_CURSOR,Y_INPUT_CURSOR);
}

int read_line(char temp_line[], int fd){
	for(int i = 0; i < 55 ; i++){
		temp_line[i] = '\0';
		read(fd, temp_line + i, 1);
		if(temp_line[i] == '\n' || temp_line[i] == EOF){
			temp_line[i] = '\0';
			return i;
		}
	}
	
	return -1;
}
