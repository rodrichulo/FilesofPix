#include <readaline.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Readaline.c
 * Authors:  Rodrigo & Yassin (rcampo01, ykina01) 
 *      Parameters: Input File, and double pointer char **datapp
 *      Purpose: This function takes a file, and retrieves the line of the file
 *               which is found by the newline character "\n"
 *               If at any point we encounter EOF, we discard what we had,
 *               and return 0 from improperly formatted line.
 *      Returns: size_t representing the number of bytes read in the string  
 *  
 */

size_t readaline(FILE *inputfd, char **datapp) 
{
        Except_T null_files =  { "one or both supplied files are NULL" };
        Except_T badFile = { "Could not read from file" };
        Except_T memAlloc = { "failed mem alloc" };

        if (inputfd == NULL || datapp == NULL) {
                RAISE(null_files);
        }

        char *buffer;
        int size = 1000; /* original starting size */
        int counter = 0, currEl = 0;
        buffer = malloc(size *sizeof(*datapp));

        if (buffer == NULL) {
            RAISE(memAlloc);
        }

        /*get the next character until we hit eof*/
        currEl = fgetc(inputfd);
        while (currEl != -1) {
                if (ferror(inputfd) != 0) {
                        RAISE(badFile);
                }
                /* expand when needed */
                if (counter >= size - 1) { 
                    size = size * 2;
                    buffer = (char *) realloc(buffer, size);
                    assert(buffer != NULL); 
                } 

                /*if currEl is a newline we return properly*/
                if (currEl == 10) {
                    buffer[counter] = currEl;
                    *datapp = buffer;
                    return counter + 1;
                }
                /* add element to our array*/           
                buffer[counter] = currEl;   
                counter++;
                currEl = fgetc(inputfd);
        }

        /*if currEl is EOF we set datapp to null*/
        *datapp = NULL;
        free(buffer);
        return 0;
}