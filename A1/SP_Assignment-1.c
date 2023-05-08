#include <stdio.h>
#define MAX_FILE_NAME 100

int main(){
	FILE *fp;
	int count = 0; 
	char filename[MAX_FILE_NAME];
	char c; 

	printf("Enter file name: ");
	scanf("%s", filename);

	fp = fopen(filename, "r");

	if (fp == NULL){
		printf("Could not open file %s", filename);
		return 0;
	}
    int lineNum=1,flag=0;
	for (c = getc(fp); c != EOF; c = getc(fp)){
        if(flag==0){
            flag=1;
            printf("%d" , lineNum);
            lineNum++;
        }

		if (c == '\n'){
            flag=0; 
			count = count + 1;
        }
        printf("%c",c);
    }

	fclose(fp);
	printf("\nThe file %s has %d lines\n ", filename, count);

	return 0;
}

//cat -n filename - file with line number
//Number of lines - wc -l filename
