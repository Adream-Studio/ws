#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{ NIL , NO_CONFIG ,WRONG_CONFIG } errType; 

void error(char* errInfo,errType status){
	fprintf(stderr,"%s\n",errInfo);

	switch( status ){
		case NO_CONFIG:
			//add_config(); remain to be done!!!!
		case WRONG_CONFIG:
			//edit_config(); remain to be done!!!
		case NIL:
			exit(1);
	}
}

void fileCopy(FILE *ifp, FILE *ofp){
	register int c;

	while((c=getc(ifp))!=EOF)
		putc(c,ofp);
}

void cmd_construct(const char* whereToLoad, const char* args[], int isSearch, char* cmdStr){
	char src[50];
	strcpy(src,args[0]);
	char* temp = strtok(src,"/ws");
	strcpy(src,temp);
	
	strcat(src,whereToLoad);
	strcat(src,args[1]);

	FILE* filePointer = fopen(src,"r");

	if( filePointer != NULL ){
		char temp[100];
		int i;
		for( i=0 ; i < 100 ; i++ ){
				temp[i] = '\0';
		}

		fgets(temp,100-1,filePointer);

		if( isSearch ){
			fgets(temp,100-1,filePointer);
			strcat(temp,args[2]);
		}

		fclose(filePointer);

		if( strlen(temp) < 6 )
			error("Uho! Your config isn't right !", WRONG_CONFIG);

		strcat(cmdStr,temp);
	}else
		error("Oh! It seems you don't have that config !", NO_CONFIG);
}

void show_usage(const char* path){
	char src[50];
	strcpy(src,path);
	char* temp = strtok(src,"/ws");
	strcpy(src,temp);
	strcat(src,"\\README.txt");

	FILE* filePointer = fopen(src,"r");

	if( filePointer != NULL ){
		fileCopy(filePointer,stdout);
		fclose(filePointer);
	}else
		puts("Your \"README.txt\" file is lost.\nYou can visit \"https://github.com/joenahm/ws\" to get help.");
}

int main(int argc, const char* argv[]){
	if( argc >= 2 ){
		int isSearch = (argc>2)?1:0;
		char cmdStr[150];
		strcpy(cmdStr,"start ");

		cmd_construct("\\config\\",argv,isSearch,cmdStr);

		system(cmdStr);
	}else
		show_usage(argv[0]);

	return 0;	
}