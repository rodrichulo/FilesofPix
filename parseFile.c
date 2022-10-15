#include <parseFile.h>
/**************************************************************
*
*                     parseFile.c
*
*       Assignment: filesofPix
*       Authors:  Rodrigo & Yassin (rcampo01, ykina01) 
*       Date: September 21, 2022
*       Time Spent: 40 hours
*
*       Summary: Implemented a map with injection sequence as keys and lists
*                as values. 
*               
*               
*
**************************************************************/

/*
*       parseFile
*     
*       Parameters:   Takes in a file pointer
*       Purpose:      Taking our input file, parseFile loops through readaline,
*                     calls helper functions to parse the respective line,
*                     add to our Hanson table, prints in P5, and free memory
*       Returns:      Void function, does not return.
*/

void parseFile(FILE *file)
{      
        Table_T table = Table_new(200, NULL, NULL);
        char *line = NULL, *numbers = NULL, *injectSeq = NULL;
        char **datapp = &line, **letters = &injectSeq;
        size_t numBytes = readaline(file, datapp), check = 1;
        int injLen = 0;
        const char *key = NULL;
        while (numBytes != 0) {
                numbers = parseLine(numBytes, letters, line, &injLen);
                check = addToTable(&table, injectSeq, numbers, injLen);
                if (!check) {
                         key = Atom_new(injectSeq, injLen);
                }
                free(injectSeq);  
                free(line);
                check = 0;
                numBytes = readaline(file, datapp);      
        }
        assert (key != NULL);
        printFromTable(&table, key);
        freeAll(&table);
}    

/*
*     parseLine
*     Parameters: numBytes, a double pointer to a char[], and wholeLine char[]
*     Purpose:    This function uses the whole line read from Readaline,
*                 Creates a number array to hold all the digits, and uses
*                 the double pointer to return the injection sequence (letters)
*     Returns:    The number array holding all the digits, but uses the double
*                 pointer to fill out the array of letters
*  
*/

char *parseLine(size_t numBytes, char **letters, char *wholeLine, int *injLen) 
{
        assert(letters != NULL && wholeLine != NULL);
        char *buffer = malloc(2 * numBytes * sizeof(char));
        char *numbers = malloc(2 * numBytes * sizeof(char));
        assert(buffer != NULL && numbers != NULL);
        int numCount = 0, lettCount = 0;
        for (size_t i = 0; i < numBytes; i++) {
                if (wholeLine[i] == '\n') {
                        numbers[numCount] = '\n';
                        break;
                }
                        /* check for number and if next is a nondigit */
                        if (isInt(wholeLine[i])) {
                        numbers[numCount] = wholeLine[i];
                                if (!isInt(wholeLine[i + 1])) {
                                        numCount++;
                                        numbers[numCount] = 32;
                        }
                        numCount++;
                } else {
                        /* we encounter a nondigit number */ 
                        buffer[lettCount] = wholeLine[i];
                        lettCount++;
                }
        }
        /* null terminated string to allow creation of atoms */
        buffer[lettCount] = 0;
        *injLen = lettCount;
        *letters = buffer;
        return numbers;
}

/*
*       freeAll
*     
*       Parameters:   A pointer to Table_T
*       Purpose:      Frees data within our table, calling on listFree helper
*       Returns:      Void function, does  not return.
*/

void freeAll(Table_T *table) 
{
        Table_map(*table, listFree, NULL);
        Table_free(table);
}

/*
*       listFree
*       
*       Parameters:   The key, the value, and the closure. 
*       Purpose:      Given a list (*value), this function will free all the
*                     nodes in the tables which are char * using List_pop
*       Returns:      Nothing, just frees :)
*/

void listFree(const void *key, void **value, void *cl)
{
        (void) key;
        (void) cl;

        /* collecting the value as a List_T */
        List_T currList = *(List_T *) value;
        char *val;

        /* To skip over the list that was popped when printing! */
        if (currList == NULL) return;
        while (List_length(currList) != 0) {
                /* pop element from list, store in pointer, and free pointer */
                currList = List_pop(currList, (void **)&val);

                if (val != NULL) {
                        free(val);
                }
        }  
}






