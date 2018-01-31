#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

void getRootPath(char *rootPath){
	char path[PATH_MAX];
    readlink("/proc/self/exe",path,PATH_MAX);

    int length = strlen(path)-1;
	while( path[length-1] != '/' ){
		length--;
	}
	path[length] = '\0';
	
	strcpy(rootPath,path);
}

void getAllFileName(char *dirPath, void (*visit)(const char *fileName)){
	DIR *dir;
	dir = opendir(dirPath);

	if( dir == NULL ){
		printf( "WARNING: No file in \"%s\"\n", dirPath);
		return;
	}else{
		struct dirent *ptr;
		while( (ptr=readdir(dir)) != NULL){
			if( strcmp(ptr->d_name,".") && strcmp(ptr->d_name,"..") ){
				visit(ptr->d_name);
			}
		}
	}

	closedir(dir);
}

void browserOpen(char *url){
	char cmdStr[500];
	strcpy(cmdStr,"x-www-browser ");
	strcat(cmdStr,url);
	strcat(cmdStr," 1>&- 2>&- &");
	system(cmdStr);
}