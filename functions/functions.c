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

void opener(const char *site){
	char sitePath[MAX_PATH];

	getRootPath(sitePath);
	strcat(sitePath,"sites\\");
	strcat(sitePath,site);

	FILE *fp = fopen(sitePath,"r");

	if( fp != NULL ){
		fgets(sitePath,MAX_PATH,fp);
		browserOpen(sitePath);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: No record for \"%s\".\n", site);
	}
}

void searcher(const char *site, char *keywords){
	char searchPath[MAX_PATH];

	getRootPath(searchPath);
	strcat(searchPath,"searchers\\");
	strcat(searchPath,site);

	FILE *fp = fopen(searchPath,"r");

	if( fp != NULL ){
		fgets(searchPath,MAX_PATH,fp);
		strcat(searchPath,keywords);
		browserOpen(searchPath);

		fclose(fp);
	}else{
		fprintf(stderr, "ERROR: No record for \"%s\".\n", site);
	}
}

int argParser(int argc, char const *argv[]){
	int status;

	if( argc > 1 ){
		if( argv[1][0] == '-' ){
			if( argv[1][1] == '-' ){
				status = BOOKMARK;
			}else{
				status = OPTION;
			}
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