/*
	Author 	: Joe Nahm
	Version : 0.3

	Modules
	fundamental{
		Web site open	:	OK
		Web search 		:	OK
	}
	configManagement{
		Add 			:	Not yet
		Remove 			:	Not yet
		Edit 			:	Not yet
		Show 			:	Not yet
	}
	errorProcessing		: 	Not yet
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linux.h"
// if you want a windows verson, remove the comments
// #include "win.h"
 

typedef enum{ NIL , NO_CONFIG ,WRONG_CONFIG } errType; 

void error(char* errInfo,errType status){
	fprintf(stderr,"%s\n",errInfo);

	switch( status ){
		case NO_CONFIG:
			//add_config(); remain to be done!!!!
		case WRONG_CONFIG:
			//edit_config(); remain to be done!!!
		case NIL:
			exit(EXIT_FAILURE);
	}
}

void fileCopy(FILE *ifp, FILE *ofp){
	register int c;

	while((c=getc(ifp))!=EOF)
		putc(c,ofp);
}

void cmd_construct(const char* whereToLoad, const char* args[], int isSearch, char* cmdStr){
	char src[50];

	strcpy(src,args[0]);		//init the current directory, with program name
	while( src[strlen(src)-1] != '/' )//remove the program name:ws.xxx from src
		src[strlen(src)-1] = '\0';
	strcat(src,whereToLoad);	//add the file path to src
	strcat(src,args[1]);		//add the file name to src

	FILE* filePointer = fopen(src,"r");

	if( filePointer != NULL ){
		char temp[100];
		int i;
		for( i=0 ; i < 100 ; i++ ){
				temp[i] = '\0';
		}

		fgets(temp,100,filePointer);	//get the first line from the file

		if( isSearch ){		//if with the search part
			fgets(temp,100,filePointer);	//get the second line:search URL from the file
			strcat(temp,args[2]);
		}

		fclose(filePointer);

		if( strlen(temp) < 7 )	//the length is 7, because of "http://"
			error("Uho! Your config isn't right !", WRONG_CONFIG);

		strcat(cmdStr,temp);
	}else	//failed to open the file
		error("Oh! It seems you don't have that config !", NO_CONFIG);
}

void show_usage(const char* path){
	char src[50];
	strcpy(src,path);

	while( src[strlen(src)-1] != '/' )//remove the program name:ws.xxx from src
		src[strlen(src)-1] = '\0';

	strcat(src,"README.txt");

	FILE* filePointer = fopen(src,"r");

	if( filePointer != NULL ){
		putchar('\n');
		fileCopy(filePointer,stdout);
		putchar('\n');
		fclose(filePointer);
	}else
		system(C_T_O_B"https://github.com/joenahm/ws");
}

int main(int argc, const char* argv[]){
	if( argc >= 2 ){
		int isSearch = (argc>2)?1:0;
		char cmdStr[150];
		strcpy(cmdStr,C_T_O_B);

		cmd_construct("config/",argv,isSearch,cmdStr);

		system(cmdStr);
	}else
		show_usage(argv[0]);

	return 0;	
}