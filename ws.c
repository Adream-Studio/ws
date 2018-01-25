#include "ws.h"

int main(int argc, const char *argv[]){
	switch( argParser(argc,argv) ){
		case NOARG:
			showWelcomeInfo();
		break;
		case SITE:
			opener(argv[1]);
		break;
		case SEARCH:{
			char keywords[MAX_PATH];
			keywords[0] = '\0';
			int count = 2;
			while( count < argc ){
				strcat(keywords,argv[count]);
				strcat(keywords,"%20");

				count++;
			}
			searcher(argv[1],keywords);
		}
		break;
		case OPTION:
			puts("option mode");
		break;
		case BOOKMARK:
			puts("bookmark mode");
		break;
	}

	return 0;	
}