#ifndef _PLATFORM_H_
#define _PLATFORM_H_

void getRootPath(char *rootPath);
void getAllFileName(char *dirPath, void (*visit)(const char *fileName));
void browserOpen(char *url);

#endif