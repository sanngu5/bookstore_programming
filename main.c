#include "head.h"

int main(void){

	pid_t child_pid;

	if((child_pid = fork()) == -1){
		perror("fork is failed.");
		return 0;
	}
	if (child_pid > 0){
		
		while(menu());
	}
	else if(child_pid == 0){
		execl("./caption.exe", "./caption.exe", NULL);
	}
	
	kill(child_pid, 9);

	return 0;

}

int menu(void){
	
	char input;
	
	fflush(stdout);
	system("clear");
	printf("1. 판매량 집계\n");
	printf("2. 도서 판매\n");
	printf("3. 도서 삭제\n");
	printf("4. 신규 도서 추가\n");
	printf("5. 기존 도서 입고\n");
	printf("6. 검색\n");
	printf("select the function(q to quit): ");
	scanf("%c", &input);
	
	switch(input){
		case '1':
			fflush(stdin);
			total_selling();
			break;
		case '2':
			fflush(stdin);
			selling_BOOK();
			break;
		case '3':
			fflush(stdin);
			remove_BOOK();
			break;
		case '4':
			fflush(stdin);
			add_NEW();		
			break;
		case '5':
			fflush(stdin);
			add_OLD();
			break;
		case '6':
			fflush(stdin);
			search();
			break;
		case 'q':
			return 0;
		default:
			return 1;
	}
	return 1;
}
