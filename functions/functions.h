#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../platform/platform.h"

#define MAX_FILENAME	100
#define MAX_CONTENT		500
#define PATH_MAX		1024

void fileCopy(FILE *ifp, FILE *ofp);
void showWelcomeInfo(void);
void showHelpInfo(void);

#define NOARG		0
#define SITE		1
#define SEARCH		2
#define OPTION		3
int argParser(int argc, const char *argv[]);

void opener(const char *record);
void searcher(const char *record, char *keywords);

#define HELP			-1
#define LIST			4
#define ADD_SITE		5
#define ADD_SEARCHER	6
#define EDIT_SITE		7
#define EDIT_SEARCHER	8
#define DROP_SITE		9
#define DROP_SEARCHER	10
int optionParser(int argc, const char *argv[]);

void lister(void);
void adder(char *filePath, const char *fileName);
void editor(char *filePath, const char *fileName);
void droper(char *filePath, const char *fileName);

#endif