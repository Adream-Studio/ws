#include "win.h"

void getRootPath(char *rootPath){
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);

	int length = strlen(exeFullPath)-1;
	while( exeFullPath[length-1] != '\\' ){
		length--;
	}
	exeFullPath[length] = '\0';
	
	strcpy(rootPath,exeFullPath);	
}

void browserOpen(char *url){
	char cmdStr[500];
	strcpy(cmdStr,"start ");
	strcat(cmdStr,url);
	//puts(cmdStr);
	system(cmdStr);
}