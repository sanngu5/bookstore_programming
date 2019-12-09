#include "head.h"

void remove_BOOK(){
	
	system("clear");
	FILE *fp,*fp1;
	int line_count=0;
	int num = find_BOOK();
	char buffer[MAX_LENGTH];
	
	if(num == -1){
		printf("해당 도서가 존재하지 않습니다.");
		fflush(stdout);
		usleep(1000000);
		return;
	}
	
	fp=fopen("./book_list.txt","r");
	if(fp==NULL){
		printf("failed");
	}
	fp1=fopen("./book_list_copy.txt","w");
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

	printf("삭제가 완료되었습니다.");
	fflush(stdout);
	usleep(1000000);
}
