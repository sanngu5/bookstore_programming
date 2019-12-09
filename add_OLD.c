#include "head.h"

void add_OLD(void){
	
	int input_amount ,fd, int_price, int_selling, int_stock;
	int seek;
	int check_seek = 0;
	char *name, *author, *price, *selling, *stock;
	char book_info[100], trash[50];
	long int book_info_len;
	
	seek = find_BOOK();
	if(seek == -1) {
		perror("error : 찾는 책이 없습니다");
		return;
	}
	
	system("clear");
	printf("\033[%d;%df",7, 0);
	printf("입고할 책의 수를 입력 해주세요: ");
	scanf("%d", &input_amount);
	fflush(stdin);
	
	
	chmod("./book_list.txt",07777);
	fd = open("./book_list.txt",O_RDWR|O_CREAT,0777);	
	if(fd == -1){
		perror("failed to open");
		return;
	}
	lseek(fd,0,SEEK_SET);
	for(int i = 0; i <= seek; i++){
		read_line(book_info,fd);
	}
	book_info_len = strlen(book_info);


	//분리
	name = strtok(book_info,"/");
	author = strtok(NULL,"/");
	price = strtok(NULL,"/");
	int_price = atoi(price);
	selling = strtok(NULL,"/");
	int_selling = atoi(selling);
	stock = strtok(NULL,"/");
	int_stock = atoi(stock);
	if(int_stock == 0)
		remove_sold_out(name);


	// 오류 검사
	if(input_amount < 1){
		perror("\nerror : 입고는 최소 1권 이상 해야 합니다.");
		return;
	}

	//입고
	int_stock += input_amount;
	sprintf(book_info,"%s/%s/%d/%d/%d\n", name, author, int_price, int_selling, int_stock);
	

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

	system("clear");
	printf("\n입고 되었습니다");
	fflush(stdout);
	usleep(1000000);
}

void remove_sold_out(char* name){
	
	system("clear");
	FILE *fp,*fp1;
	int line_count=0;
	int num = find_BOOK2(name);
	char buffer[MAX_LENGTH];
	
	fp=fopen("./sold_out.txt","r");
	if(fp==NULL){
		printf("failed");
	}
	fp1=fopen("./sold_out_copy.txt","w");
	if(fp1==NULL){
                printf("failed");
        }

	while(fgets(buffer,MAX_LENGTH,fp)!=NULL){
		if(line_count==num)line_count++;
		else{
			fputs(buffer,fp1);
			line_count++;
		}
	}
	fclose(fp);
	fclose(fp1);

	fp=fopen("./sold_out.txt","w");
	if(fp==NULL){
		printf("failed");
        }

	fp1=fopen("./sold_out_copy.txt","r");
	if(fp1==NULL){
                printf("failed");
        }

	while(fgets(buffer,MAX_LENGTH,fp1)!=NULL){
		fputs(buffer,fp);
	}
	fclose(fp);
	fclose(fp1);

}
