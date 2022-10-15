/*
*     manageTable.h
*     by: rcampo01, ykina01
*     filesofpix
*     
*
*     Function prototypes of manageTable and includes of Hanson data structures
*/ 

/* declare buildTable Includes */
#ifndef MANAGETABLE_H_INCLUDED
#define MANAGETABLE_H_INCLUDED

/*regular includes*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <table.h>
#include <list.h>
#include <atom.h>

int addToTable(Table_T *table, char *injectSeq, char *numbers, int injLen);
int isInt(char val);
int calculateCols(char *numbers);
void addCorrectInjection(List_T listChain, char *numbers);
void printFromTable(Table_T *table, const char *key);
void printP5(char *currNode);

#endif