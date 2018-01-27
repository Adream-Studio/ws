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
	puts("\t-l : List all of the records.");
	puts("\t-a : Add records.");
	puts("\t-e : Edit records.");
	puts("\t-d : Delete records.");
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

void editor(void){
	char filePath[MAX_PATH];
	getRootPath(filePath);

	lister();

	char fileName[MAX_FILENAME];
	printf("\nWhat type do you want to edit\n(\"i\" for site/\"e\" for search): ");
	fflush(stdout);

	char type = getchar();
	printf("File name (");
	if( type == 'i' ){
		strcat(filePath,"sites\\");
		printf("sites\\):");
	}else if( type == 'e' ){
		strcat(filePath,"searchers\\");
		printf("searchers\\):");
	}else{
		fprintf(stderr, "\nERROR: Invalid type !\n");
		exit(EXIT_FAILURE);
	}
	fflush(stdout);
	

	char buf = getchar(); //reject the '\n'
	int count = 0;
	while( (buf=getchar()) != '\n' 
		&&	count < MAX_FILENAME ){

		fileName[count] = buf;

		count++;
	}
	fileName[count] = '\0';

	strcat(filePath,fileName);
	puts(filePath);

	FILE *fp;

	fp = fopen(filePath,"r");
	if( fp != NULL ){
		puts("Old: ");
		putchar('\t');
		fileCopy(fp,stdout);
		putchar('\n');

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: Failed to open \"%s\" !\n", filePath);
		exit(EXIT_FAILURE);
	}

	printf("New: ");
	fflush(stdout);
	char content[MAX_CONTENT];
	count = 0;
	while( (buf=getchar()) != '\n' 
		&&	count < MAX_CONTENT ){

		content[count] = buf;

		count++;
	}
	content[count] = '\0';

	fp = fopen(filePath,"w");
	if( fp != NULL ){
		fputs(content, fp);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: Failed to open \"%s\" !\n", filePath);
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

int optionParser(const char *argv[]){
	int status;

	if( argv[1][1] == 'l' ){
		status = LIST;
	}else if( argv[1][1] == 'a' ){
		status = ADD;
	}else if( argv[1][1] == 'e' ){
		status = EDIT;
	}else if( argv[1][1] == 'd' ){
		status = DROP;
	}else{
		status = HELP;
	}

	return status;
}