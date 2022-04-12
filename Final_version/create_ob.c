
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "structs.h"
#include "utils.h"
#include "assembler.h"

/* this file is used to create the output file of type.ob */
void create_ob(char  *machine_line,labelPtr head,MCPtr head_2,char *first_line_ob,char input_file_orginal[] )
{
    boolean FLAG=TRUE;/*used to prevent creating multiple files */

    FILE *ptr_file_write;/*write .ob file */

    /* prevent creating multiple files */
    if(strstr(input_file_orginal,"ob")-input_file_orginal>0 )
    {
        FLAG=FALSE;
    }
    if(FLAG==TRUE)
        strcat(input_file_orginal,".ob");/* add file extension .ob to the original file name */
  

    ptr_file_write = fopen(input_file_orginal,"a");

    if( first_line_ob!=NULL)
        fprintf(ptr_file_write,"%s\n",first_line_ob);/*print the first line of ob file */
    /* write .ob file */     
    while(head_2)
    {
        fprintf(ptr_file_write,"%s\n", head_2->MachinCode_string);
        head_2=head_2->next;
    }
    fclose(ptr_file_write);
    
    


}