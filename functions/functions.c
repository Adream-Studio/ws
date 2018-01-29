#include "functions.h"

void fileCopy(FILE *ifp, FILE *ofp){
	register int c;

	while( (c=getc(ifp))!=EOF )
		putc(c,ofp);
}

void showWelcomeInfo(void){
	char infoPath[MAX_PATH];
	getRootPath(infoPath);
	strcat(infoPath,"README.txt");

	FILE *fp = fopen(infoPath,"r");

	if( fp != NULL ){
		fileCopy(fp,stdout);

		fclose(fp);
	}else{
		fprintf(stderr, "WARNING: Failed to load the welcome info.\nYou can visit https://github.com/joenahm/ws for it instead.\n\n");
	}

}

void showHelpInfo(void){
	puts("Usage:\n");
	puts("\t-l : List all of the records.\n");
	puts("\t-a -i <name> : Add site record.");
	puts("\t-a -e <name> : Add searcher record.\n");
	puts("\t-e -i <name> : Edit site record.");
	puts("\t-e -e <name> : Edit searcher record.\n");
	puts("\t-d -i <name> : Delete site record.");
	puts("\t-d -e <name> : Delete searcher record.\n");
	puts("\t-? : the \"?\" can be any thing else to call for this page.");
}

void opener(const char *record){
	char sitePath[MAX_PATH];

	getRootPath(sitePath);
	strcat(sitePath,"sites\\");
	strcat(sitePath,record);

	FILE *fp = fopen(sitePath,"r");

	if( fp != NULL ){
		fgets(sitePath,MAX_PATH,fp);
		browserOpen(sitePath);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: No record for \"%s\".\n", record);
	}
}

void searcher(const char *record, char *keywords){
	char searchPath[MAX_PATH];

	getRootPath(searchPath);
	strcat(searchPath,"searchers\\");
	strcat(searchPath,record);

	FILE *fp = fopen(searchPath,"r");

	if( fp != NULL ){
		fgets(searchPath,MAX_PATH,fp);
		strcat(searchPath,keywords);
		browserOpen(searchPath);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: No record for \"%s\".\n", record);
	}
}

void fileNameVisitor(const char *fileName){
	printf("\t%s\n", fileName);
}

void lister(void){
	char path[MAX_PATH];

	getRootPath(path);
	strcat(path,"sites\\*");
	puts("\nSites:");
	getAllFileName(path,&fileNameVisitor);

	getRootPath(path);
	strcat(path,"searchers\\*");
	puts("\nSearchers:");
	getAllFileName(path,&fileNameVisitor);
}

void editor(const char *filePath, const char *fileName){
	puts("\nWhat do you want to edit ?");
	printf("(1 for \"name\", 2 for \"content\"): ");
	fflush(stdout);

	int type;
	scanf("%d", &type);
	if( type == 1 ){
		char newName[MAX_FILENAME];
		printf("new name: ");
		fflush(stdout);
		//读取文件名
		char temp1[MAX_PATH],temp2[MAX_PATH];
		strcpy(temp1,filePath);
		strcat(temp1,fileName);
		rename();
	}else if( type == 2 ){
		;
	}else{
		fprintf(stderr, "ERROR: Invalid type !\n");
		exit(EXIT_FAILURE);
	}
}

int argParser(int argc, const char *argv[]){
	int status;

	if( argc > 1 ){
		if( argv[1][0] == '-' ){
			status = OPTION;
		}else{
			if( argc > 2 ){
				// 2 real args
				status = SEARCH;
			}else{
				// 2 args 1 real arg
				status = SITE;
			}
		}
	}else{
		// 1 arg 0 real arg
		status = NOARG;
	}

	return status;
}

int optionParser(int argc, const char *argv[]){
	int status;

	if( argc > 3 ){
		if( argv[2][1] == 'i' ){
			if( argv[1][1] == 'a' ){
				status = ADD_SITE;
			}else if( argv[1][1] == 'e' ){
				status = EDIT_SITE;
			}else if( argv[1][1] == 'd' ){
				status = DROP_SITE;
			}else{
				status = HELP;
			}
		}else if( argv[2][1] == 'e' ){
			if( argv[1][1] == 'a' ){
				status = ADD_SEARCHER;
			}else if( argv[1][1] == 'e' ){
				status = EDIT_SEARCHER;
			}else if( argv[1][1] == 'd' ){
				status = DROP_SEARCHER;
			}else{
				status = HELP;
			}
		}else{
			status = HELP;
		}
	}else{
		if( argv[1][1] == 'l' ){
			status = LIST;
		}else{
			status = HELP;
		}
	}

	return status;
}