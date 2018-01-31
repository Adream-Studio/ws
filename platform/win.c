#include <windows.h>
#include <io.h>
#include <string.h>
#include <stdio.h>

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

void getAllFileName(char *dirPath, void (*visit)(const char *fileName)){
	strcat(dirPath,"\\*");
	struct _finddata_t fa;
	long fHandle;

	if( (fHandle=_findfirst( dirPath, &fa )) == -1L ){
		printf( "WARNING: No file in \"%s\"\n", dirPath);
		return;
	}else{
		do{
			if( strcmp(fa.name,".") && strcmp(fa.name,"..") ){
				visit(fa.name);
			}
		}while( _findnext(fHandle,&fa) == 0 );

		_findclose( fHandle );
	}	
}

void browserOpen(char *url){
	char cmdStr[500];
	strcpy(cmdStr,"start ");
	strcat(cmdStr,url);
	//puts(cmdStr);
	system(cmdStr);
}