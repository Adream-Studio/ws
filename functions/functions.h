#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fileCopy(FILE *ifp, FILE *ofp);
void showWelcomeInfo(void);

#define NOARG		0
#define SITE		1
#define SEARCH		2
#define OPTION		3
#define BOOKMARK	4
int argParser(int argc, char const *argv[]);

void operner(const char *site);
void searcher(const char *site, char *keywords);

#endif