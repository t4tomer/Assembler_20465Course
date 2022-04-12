
/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <math.h> 
#include <string.h>
#include <ctype.h>
#include <unistd.h>


#include "structs.h"
#include "utils.h" /* saving the declare of first_pass */
#include "assembler.h"



 void ReadFiles(int argc, char *argv[], FILE **fp); /* used identityLabels */ 

 int main( int argc, char *argv [] ) 
    {
        FILE *fp; /* input file to the assembler */
        ReadFiles(argc, argv, &fp); /* used to read files */ 
        exit(0);
    } 

void ReadFiles(int argc, char *argv[], FILE **fp) 
    {   
        int i;
        int file_counter=1; /* used to count the number of files */
        char original_file[LABEL_LENGTH];/* save the original name of the input file */
        char original_file_as[LABEL_LENGTH]; /*save the name of the input file with file extension .as */
        char file_am[LABEL_LENGTH]; /*save the name of the input file with file extension .am */
        char file_name[LABEL_LENGTH];/* save the original name of the input file */
        char original_file_del[LABEL_LENGTH]; /* used to delet files from previous runs */


        FILE * post_Macro_file; /* file that stores the file after pre_Assembler pass */
        for(  i = 1; i < argc; ++i )
        {

            strcpy( original_file,argv[i]);/*copy the input file name to original_file*/
            strcpy(file_name,argv[i]);
            strcpy(file_am,argv[i]);/*copy the input file name to file_am*/        
            strcpy(original_file_as,argv[i]);/*copy the input file name to original_file_as*/        
            strcpy(original_file_as,strcat(original_file_as,".as"));/* add file extension .as to the original file name */

            strcpy(original_file_del,argv[i]);/* save in original_file_del the orginal name of the file */
            strcat(original_file_del,".ob");/* add file extension .ob to the original file name */

        /* if file exists from previous runs ,delete it */
            if( access( original_file_del, F_OK ) == 0 ) 
                if (remove(original_file_del) == 0) ;        


            if(!(*fp = fopen(original_file_as,"r"))) 
            {
                printf("\n file: %s can not be open!! \n ",original_file);
                continue;
            }

            pre_Assembler(*fp,file_counter,original_file_as,original_file);/*insert file to cheack the macro commands */                        
            strcat(file_am,".am");/* add file extension .am to the original file name */
            post_Macro_file=fopen(file_am,"r");/* open the file with am extension */
            first_pass(post_Macro_file,file_name);/*enter first_pass */
        }

        exit(0);
    }



