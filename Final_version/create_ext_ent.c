/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


#include "structs.h"
#include "utils.h"
#include "assembler.h"

/* this file is used to create files of ext and ent of the project . */
void create_ext_ent(labelPtr head,char input_file_orginal[] )
{
    FILE *ptr_file_write3;/*write into  ent file */
    FILE *ptr_file_write2;/*write into  ext file */

    char file_ent[LABEL_LENGTH];
    char file_ext[LABEL_LENGTH];
    strcpy(file_ent,input_file_orginal);
    strcpy(file_ext,input_file_orginal);

    strcat(file_ent,".ent");/* add file extension .ext to the original file name */
    ptr_file_write3 = fopen(file_ent,"w");
   /* //! START create files and write to it */
    
    strcat(file_ext,".ext");/* add file extension .ext to the original file name */
    ptr_file_write2 = fopen(file_ext,"w");
    

     while(head)
            {
                /*print to ext file base &offset of extern */            
                if(head->Attributes==external)
                {
                    fprintf(ptr_file_write2,"%s base %d\n", head->Symbol,head->address-((head->address)%16));
                    fprintf(ptr_file_write2,"%s offset %d\n", head->Symbol,(head->address)%16);

                }
                /*print to ent file line number of entry symbols of extern */            

                 if(head->entry==TRUE)
                 {
                    fprintf(ptr_file_write3,"%s,%d,%d \n", head->Symbol,(head->address)-(head->address)%16,(head->address)%16);

                 }

                head=head->next;
            }

    fclose(ptr_file_write2);

    
}