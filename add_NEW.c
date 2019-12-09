#include "head.h"

void add_NEW(){
	
	char input_title[100];
	char author[100];
	int price;
	int stock;
	char book_info[100];
	int fd;
	
	system("clear");
	printf("\033[%d;%df",7, 25);
	printf(" title: ");
	scanf("%[^\n]s", input_title);
	
	if(find_BOOK2(input_title) == -1){
		fflush(stdin);
		
		system("clear");
		printf("\033[%d;%df",7, 25);
		printf("author: ");
		scanf("%[^\n]s", author);

		system("clear");
		printf("\033[%d;%df",7, 25);
		printf(" price: ");
		scanf("%d", &price);

		system("clear");
		printf("\033[%d;%df",7, 25);
		printf(" 입고량: ");
		scanf("%d", &stock);
		
		sprintf(book_info, "%s/%s/%d/0/%d", input_title, author, price, stock);
	
		chmod("./book_list.txt",0777);
		fd = open("./book_list.txt", O_WRONLY|O_CREAT,0777);
		lseek(fd, 0, SEEK_END);
		write(fd, "\n", 1);
		write(fd, book_info, strlen(book_info));
		close(fd);
		printf("\n완료되었습니다");
		fflush(stdout);	
		usleep(1000000);			
	}
	else{
		perror("이미 존재하는 책입니다!");
		fflush(stdout);
		usleep(1000000);
		return;
	}	
}