/*
*     parseFile.h
*     by: rcampo01, ykina01
*     filesofpix
*
*     Prototypes of parseFile, including Hanson's data structures
*/ 

/* declare parseFile Includes */
#ifndef PARSEFILE_H_INCLUDED
#define PARSEFILE_H_INCLUDED

/*regular includes*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Data structure includes */
#include <readaline.h>
#include <manageTable.h>
#include <atom.h>
#include <table.h>
#include <list.h>


char *parseLine(size_t numBytes, char **letters, char *wholeLine, int *injLen);
void parseFile(FILE *file);
void listFree(const void *key, void **value, void *cl);
void freeAll(Table_T *table);
void applyFree(void **ptr, void *cl);


#endif