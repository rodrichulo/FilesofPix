#include <readaline.h>
#include <assert.h>
#include <stdlib.h>
#include <parseFile.h>

/**************************************************************
*
*                     restoration.c
*
*       Assignment: filesofPix
*       Authors:  Rodrigo & Yassin (rcampo01, ykina01) 
*       Date: September 21, 2022
*
*       Summary: main function that takes input from an input
*                stream depending on argc and begins parsing
*                on the specified input. Terminates on 
*                EXIT_SUCCESS if a proper file is supplied.
*               
*               
*
**************************************************************/
      
int main(int argc, char *argv[]) 
{
        char *filename = NULL;
        FILE *fp = NULL;
        assert(argc < 3);
        if (argc == 2) {
                /* read from file */
                filename = argv[1];
                fp = fopen(filename, "r");
                assert(fp != NULL);
                parseFile(fp);
                fclose(fp);

        } else if(argc == 1) {
                /* read from stdin */
                fp = stdin;
                assert(fp != NULL);
                parseFile(fp);
        }

        return EXIT_SUCCESS;
}
