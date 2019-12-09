#include"head.h"

void search(){
	
	char book_info[100];
	int seek;	
	int fd;

	seek = find_BOOK();
	if(seek == -1){
		perror("error : 찾는 책이 없습니다");
		usleep(1000000);
		return;
	}

	chmod("./book_list.txt",0777);
	fd = open("./book_list.txt",O_RDWR|O_CREAT,0777);
	for(int i = 0; i <= seek; i++){
		read_line(book_info, fd);
	}
	system("clear");
	printf("\033[%d;%df",6, 0);
	printf("제목/저자/가격/판매량/재고\n");
	printf("%s", book_info);
	fflush(stdout);
	usleep(3000000);

}