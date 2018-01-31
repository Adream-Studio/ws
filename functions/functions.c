#include "functions.h"

void fileCopy(FILE *ifp, FILE *ofp){
	register int c;

	while( (c=getc(ifp))!=EOF )
		putc(c,ofp);
}

void showWelcomeInfo(void){
	char infoPath[PATH_MAX];
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
	char sitePath[PATH_MAX];

	getRootPath(sitePath);
	strcat(sitePath,"sites/");
	strcat(sitePath,record);

	FILE *fp = fopen(sitePath,"r");

	if( fp != NULL ){
		fgets(sitePath,PATH_MAX,fp);
		browserOpen(sitePath);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: No record for \"%s\".\n", record);
	}
}

void searcher(const char *record, char *keywords){
	char searchPath[PATH_MAX];

	getRootPath(searchPath);
	strcat(searchPath,"searchers/");
	strcat(searchPath,record);

	FILE *fp = fopen(searchPath,"r");

	if( fp != NULL ){
		fgets(searchPath,PATH_MAX,fp);
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
	char path[PATH_MAX];

	getRootPath(path);
	strcat(path,"sites");
	puts("\nSites:");
	getAllFileName(path,&fileNameVisitor);

	getRootPath(path);
	strcat(path,"searchers");
	puts("\nSearchers:");
	getAllFileName(path,&fileNameVisitor);
}

void editor(char *filePath, const char *fileName){
	char tempPath[PATH_MAX];
	strcpy(tempPath,filePath);
	strcat(tempPath,fileName);
	FILE *checkFp = fopen(tempPath,"r");
	if( checkFp == NULL ){
		fprintf(stderr, "ERROR: No record for \"%s\" !\n", tempPath);
		exit(EXIT_FAILURE);
	}else{
		fclose(checkFp);
	}

	puts("\nWhat do you want to edit ?");
	printf("(1 for \"name\", 2 for \"content\"): ");
	fflush(stdout);

	int type;
	scanf("%d", &type);
	if( type == 1 ){
		printf("new name: ");
		fflush(stdout);

		char newName[MAX_FILENAME];
		char c = getchar(); //skip the '\n'
		int i = 0;
		while( (c=getchar())!='\n' && i<MAX_FILENAME ){
			newName[i] = c;
			i++;
		}
		newName[i] = '\0';

		char oldPath[PATH_MAX],newPath[PATH_MAX];
		strcpy(oldPath,filePath);
		strcat(oldPath,fileName);
		strcpy(newPath,filePath);
		strcat(newPath,newName);
		rename(oldPath,newPath);

		printf("\nRename: %s\n", newPath);
	}else if( type == 2 ){
		printf("new content: ");
		fflush(stdout);

		char newContent[MAX_CONTENT];
		char c = getchar(); //skip the '\n'
		int i = 0;
		while( (c=getchar())!='\n' && i<MAX_CONTENT ){
			newContent[i] = c;
			i++;
		}
		newContent[i] = '\0';

		strcat(filePath,fileName);

		FILE *fp = fopen(filePath,"w");
		if( fp != NULL ){
			fputs(newContent,fp);
			printf("\nChange: %s\n", filePath);
			fclose(fp);
		}else{
			fprintf(stderr, "ERROR: Failed to change \"%s\" !\n", filePath);
			exit(EXIT_FAILURE);
		}
	}else{
		fprintf(stderr, "ERROR: Invalid type !\n");
		exit(EXIT_FAILURE);
	}
}

void adder(char *filePath, const char *fileName){
	printf("new content for [%s]: ", fileName);
	fflush(stdout);

	char newContent[MAX_CONTENT];
	char c;
	int i = 0;
	while( (c=getchar())!='\n' && i<MAX_CONTENT ){
		newContent[i] = c;
		i++;
	}
	newContent[i] = '\0';

	strcat(filePath,fileName);
	
	FILE *fp = fopen(filePath,"w");
	if( fp != NULL ){
		fputs(newContent,fp);
		printf("\nCreate: %s\n", filePath);
		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: Failed to create \"%s\" !\n", filePath);
		exit(EXIT_FAILURE);
	}
}

void droper(char *filePath, const char *fileName){
	strcat(filePath,fileName);
	if( remove(filePath) == 0 ){
		printf("\nDelete: %s\n", filePath);
	}else{
		fprintf(stderr, "ERROR: Failed to delete \"%s\" !\n", filePath);
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