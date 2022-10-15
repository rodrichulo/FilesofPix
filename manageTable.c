#include <manageTable.h>

/**************************************************************
*
*                     manageTable.c
*
*       Assignment: filesofPix
*       Authors:  Rodrigo & Yassin (rcampo01, ykina01) 
*       Date: September 21, 2022
*       
*
*       Summary: Holds all functions related to storing and printing from the
*                table which holds the injection sequences as keys of atoms,
*                and lists as the values.
*
**************************************************************/



/*
*     addToTable
*     Authors:  Rodrigo & Yassin (rcampo01, ykina01) 
*     Parameters:     Takes in a pointer to Table_T, a char *injectsequence,
*                     array for the numbers, and injection length. 
*                      
*      Purpose:       Adds character sequences to a table as a key, and the
*                     sequence of numbers as a value. Sequences of 
*                     number corresponding to the same key are chained s a 
*                     List.
*      Returns:       An integer value determining if we made a new list.                     
*/

int addToTable(Table_T *table, char *injectSeq, char *numbers, int injLen) 
{
        const char *atom = Atom_new(injectSeq, injLen);
        List_T listChain = Table_get(*table, atom);
        
        if (listChain != NULL) {
                /* found the correct injection sequence */
                addCorrectInjection(listChain, numbers);
                return 0;
        } else {
                /* create a new entry in the table since listChain is NULL */
                List_T list = List_list(numbers, NULL);
                assert (list != NULL);
                Table_put(*table, atom, list);
                return 1;
        }   
}


/*
*     addCorrectInjection
*     
*     Parameters:   Takes a list pointer and a pointer to an array of chars
*     Purpose:      Modularize adding to our table.
*     Returns:      Nothing, void function.
*/

void addCorrectInjection(List_T listChain, char *numbers) {
        List_T appendList = List_list(numbers, NULL);
        listChain = List_append(listChain, appendList);
}


/*
*     isInt
*     
*     Parameters:   Takes in a char value
*     Returns:      An integer value that is 1 if the char is a digit or 0
*                   if the character is a non-digit
*/

int isInt(char val) 
{
        if (val >= 48 && val <= 57) {
                return 1;
        }
        return 0;
}


/*
*       printFromTable
*     
*       Parameters:   Takes in a pointer to Table_T and const char*
*       Purpose:      Prints the  values associate with the correct
*                     injection sequence using List_pop
*       Returns:      Void function, does  not return.
*/

void printFromTable(Table_T *table, const char *key) 
{
        assert(key != NULL);
        /* Getting the correct List */
        List_T finalList = Table_put(*table, key, NULL);
        assert(finalList != NULL);
        void *currNode;
        
        /* Get the rows and columns */
        int rows = List_length(finalList);

        /* calling pop once to get the number of cols */
        finalList = List_pop(finalList, &currNode);
        int columns = calculateCols((char*) currNode);
        assert (columns >= 2 && rows >= 2);

        /* print the header and first node already popped. deallocate string */
        printf("P5\n%d %d\n%d\n", columns, rows, 255);
        printP5((char*)currNode);
        int counter = 1;
        free(currNode);
        currNode = NULL;
        
        /* Loop and print for the number of rows */
        while (counter < rows) {
                finalList = List_pop(finalList, &currNode);
                printP5((char*)currNode);
                free(currNode);
                currNode = NULL;
                counter++;
        }
        List_free(&finalList);
}


/*
*     calculateCols
*     
*     Parameters:   Takes in a char* to the current seqeunce of numbers
*     Purpose:      Calculate the numbers of columns in the given sequence
*                   of numbers
*     Returns:      An int value representing the number of columns
*/

int calculateCols(char *currNode) 
{
        int index = 0;
        int columns = 0;
         while (currNode[index] != '\n') {
                if (currNode[index] == 32)  {
                        columns++;
                }
                index++;
        }
        return columns;
}


/*
*     printP5
*     
*     Parameters:   Takes in a char * value
*     Purpose:      Prints the passed value in P5 format
*     Returns:      Void, returns nothing
*
*/

void printP5(char *currNode)
{
        int counter = 0;
        int toReturn = 0;
        while (currNode[counter] != '\n') {
                /* check for whitespace */
                if (currNode[counter] == 32) {
                        /* counter is correct and print */
                        printf("%c", toReturn);
                        toReturn = 0;
                } else {
                        /* multiplying counter by base 10 */
                        toReturn = (toReturn * 10) + (currNode[counter] - '0');
                }

                counter++;
        }

}
