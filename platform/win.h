#ifndef _WIN_H_
#define _WIN_H_

#include <windows.h>
#include <io.h>
#include <string.h>
#include <stdio.h>

void getRootPath(char *rootPath);
void getAllFileName(char *dirPath, void (*visit)(const char *fileName));
void browserOpen(char *url);

#endif