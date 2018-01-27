#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME	100
#define MAX_CONTENT		500

void fileCopy(FILE *ifp, FILE *ofp);
void showWelcomeInfo(void);
void showHelpInfo(void);

#define NOARG		0
#define SITE		1
#define SEARCH		2
#define OPTION		3
int argParser(int argc, const char *argv[]);

void operner(const char *record);
void searcher(const char *record, char *keywords);

#define HELP	-1
#define LIST	4
#define ADD		5
#define EDIT	6
#define DROP	7 
int optionParser(const char *argv[]);

void lister(void);
void adder(void);
void editor(void);
void deleter(void);

#endif