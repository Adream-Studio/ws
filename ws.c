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
			switch( optionParser(argc,argv) ){
				case LIST:
					lister();
				break;
				case ADD_SITE:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"sites\\");
					adder(path,argv[3]);
				}
				break;
				case ADD_SEARCHER:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"searchers\\");
					adder(path,argv[3]);
				}
				break;
				case EDIT_SITE:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"sites\\");
					editor(path,argv[3]);
				}
				break;
				case EDIT_SEARCHER:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"searchers\\");
					editor(path,argv[3]);
				}
				break;
				case DROP_SITE:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"sites\\");
					droper(path,argv[3]);
				}
				break;
				case DROP_SEARCHER:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"searchers\\");
					droper(path,argv[3]);
				}
				break;
				case HELP:
					showHelpInfo();
				break;
			}
		break;
	}

	return 0;	
}