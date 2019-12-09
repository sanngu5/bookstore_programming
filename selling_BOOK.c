#include "head.h"

void selling_BOOK(void){

	char book_info[100],trash[100]; //이름, 파일에 입력 되있던 정보
	char *name, *author, *price, *selling, *stock;
	int  sell_amount, int_price, int_selling, int_stock, seek;
	//몇권 파는지, 가격, 판매량, 재고량, 몇번 줄인지
	int sell_price = 0, check_seek = 0;
	long int book_info_len;
	int fd, fd2;
	
	seek = find_BOOK();
	if(seek == -1){
		perror("error : 찾는 책이 없습니다");
		usleep(1000000);
		return;
	}

	system("clear");
	printf("\033[%d;%df",7, 0);
	printf("판매할 책의 수량을 입력해주세요:");
	scanf("%d",&sell_amount);


	chmod("./book_list.txt",0777);
	fd = open("./book_list.txt",O_RDWR|O_CREAT,0777); //파일 이름 변경	
	if(fd == -1){
		perror("failed to open");
		return;
	}
	lseek(fd,0,SEEK_SET);
	for(int i = 0; i <= seek; i++){
		read_line(book_info, fd);
	}	
	book_info_len = strlen(book_info);
	
	// 분리하기 	
	name = strtok(book_info,"/");
	author = strtok(NULL,"/");
	price = strtok(NULL,"/");
	int_price = atoi(price);
	selling = strtok(NULL,"/");
	int_selling = atoi(selling);
	stock = strtok(NULL,"/");
	int_stock = atoi(stock);

	if(sell_amount > int_stock){
		perror("\nerror : 재고가 부족합니다");
		usleep(1000000);
		return;
	}
	
	//책 판매
	int_selling = int_selling + sell_amount;
	int_stock = int_stock - sell_amount;
	sell_price = sell_amount  * int_price;
	sprintf(book_info, "%s/%s/%d/%d/%d\n", name, author, int_price, int_selling, int_stock);
		
	//New 쓰기
	close(fd);
	FILE *fp,*fp1;
	int line_count=0;
	char buffer[MAX_LENGTH];

	fp=fopen("./book_list.txt","r");
	if(fp==NULL){
		printf("failed");
	}
	fp1=fopen("./book_list_copy.txt","w");
	if(fp1==NULL){
                printf("failed");
       }
	while(fgets(buffer,MAX_LENGTH,fp)!=NULL){
		if(line_count==seek){
			fputs(book_info, fp1);
			line_count++;
		}
		else{
			fputs(buffer, fp1);
			line_count++;
		}
	}
	fclose(fp);
	fclose(fp1);

	fp=fopen("./book_list.txt","w");
	if(fp==NULL){
		printf("failed");
       }
	fp1=fopen("./book_list_copy.txt","r");
	if(fp1==NULL){
                printf("failed");
       }
	while(fgets(buffer,MAX_LENGTH,fp1)!=NULL){
		fputs(buffer,fp);
	}
	fclose(fp);
	fclose(fp1);

	

	//매출,베스트셀러,매진 갱신
	chmod("./book_selling.txt", 0777);
	fd2 = open("./book_selling.txt", O_RDWR|O_CREAT, 0777); //파일 이름 변경
	if(fd2 == -1) {
		perror("failed to open");
		return;
	}
	read_line(price, fd2);
	sell_price += atoi(price);
	sprintf(price,"%d\n",sell_price);
	lseek(fd2, 0, SEEK_SET);
	write(fd2, price, strlen(price));
	close(fd2);
	check_bestseller(name, int_selling);	
	check_sold_out(name, int_stock);
	
	
	system("clear");
	printf("\n책이 판매되었습니다");
	fflush(stdout);
	usleep(1000000);
}

void check_bestseller(char* name_c, int compare){

	char book_info[100];
	char* name;
	char *selling;
	int int_selling;
	int fd3;
	
	char* temp = malloc(sizeof(char)*100);
	strcpy(temp, name_c);
	name = strtok(temp, "/");

	chmod("./bestseller.txt", 0777);
	fd3 = open("./bestseller.txt",O_RDWR);
	read_line(book_info, fd3);
	int book_info_len = strlen(book_info);

	// 분리하기 	
	strtok(book_info,"/");
	selling = strtok(NULL,"/");
	int_selling = atoi(selling);

	if(compare > int_selling){
		lseek(fd3, 0, SEEK_SET);
		for(int i = 0; i < book_info_len; i++){
			write(fd3, " ", 1);
		}
		lseek(fd3, 0, SEEK_SET);
		sprintf(book_info, "%s/%d", name, compare);
		write(fd3, book_info, strlen(book_info));
	}
	close(fd3);
	return;
}

void check_sold_out(char* name_c, int compare){
	if(compare != 0)
		return;
	else{	
		int fd4;
		char* temp = malloc(sizeof(char)*100);
		char* name;
		strcpy(temp, name_c);
		name = strtok(temp, "/");
		free(temp);

		chmod("./sold_out.txt", 0777);
		fd4 = open("./sold_out.txt",O_RDWR|O_CREAT,0777);
		lseek(fd4, 0, SEEK_END);
		write(fd4, name, strlen(name));
		write(fd4, "\n", 1);
		close(fd4);
	}
}