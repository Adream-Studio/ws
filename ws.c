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
				case ADD_SITE:
				break;
				case EDIT_SITE:{
					char path[MAX_PATH];
					getRootPath(path);
					strcat(path,"sites\\");
					editor(path,argv[3]);
				}
				break;
				case DROP_SITE:
				break;
				case HELP:
					showHelpInfo();
				break;
			}
			//现在只剩下这个了
			/*
				-l 查看记录
				-e 编辑记录
				-d 删除记录
				-a 增加记录
			*/
		break;
	}

	return 0;	
}