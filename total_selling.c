#include"head.h"


void total_selling(){
	
	system("clear");
		
	char book_info[100];
	int fd;

	chmod("./book_list.txt",0777);
	fd = open("./book_list.txt",O_RDWR|O_CREAT,0777); //파일 이름 변경	
	if(fd == -1){
		perror("failed to open");
		return;
	}
	printf("제목/저자/가격/판매량/재고\n\n");
	while(read_line(book_info, fd) != -1){
		printf("%s\n", book_info);
	}
	
	fflush(stdout);
	usleep(5000000);

}