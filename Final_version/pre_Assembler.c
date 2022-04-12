/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* This file is for writing the lines  between macro and endm to file .am */



/*--------- Headers ---------*/
#include "structs.h"
#include "utils.h"
#include "assembler.h"





void PrintMacroList(MacroLinePtr h);
void removeAll(char * str, const char * toRemove);
char *Save_MacroName(char *line);
char * Save_MacroName1(char *line);
void Add2_MacroTable(MacroLinePtr *hMacroLinePtr, char macro_name_file[],char macro_line_file[],int line_num);
void Delete_Line_Func(FILE *file,FILE *temp,int delete_line);
int Return_Num_Tokens(char *line);
MacroLinePtr Get_Line_DataByString(MacroLinePtr head,char inputString[],FILE *ptr_file_write);



void pre_Assembler(FILE * ptr_file,int file_counter,char input_file_name_as [],char input_file_orginal [])
{
   
    FILE * ptr_file_write;  /* the output file after writing the macro lines */
    MacroLinePtr head=NULL; /* used as head for the MacroLine linked list */
    char macro_name[LABEL_LENGTH];/* store the macro name */
    int macro_lines_Arr[LABEL_LENGTH];/*store the number of macro lines */
    int line_num=1;/*used to count the number of line */
    boolean macro_flag=FALSE; /* identify if there is macro in the file */
    boolean flag1=FALSE;/* flag that indicates to turn on the macro table */
    int i1=1;/*used as index for the delete lines array */
    int i4=0;/* used as index for macro_lines_Arr */
    int macroName_line=-1;/* save the index of line that contains only the macro name */

    strcat(input_file_orginal,".am");/* add file extension .as to the original file name */
    ptr_file_write = fopen(input_file_orginal,"w"); /*open file.am */

    /* fopen() return NULL if unable to open file in given mode. */
    if (ptr_file_write==NULL )
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file :%s.\n",input_file_orginal);
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_SUCCESS);
    }


    macro_lines_Arr[0]=0;
    /*
     * Read line by line from source file
     */
    while ((fgets(line, LINE_LENGTH, ptr_file)) != NULL) /*read the original file line by line */
    {
            /* save the line number that contains the macro */
            if(strstr(line,"macro")!=NULL)
            { 
                
                strcpy(macro_name, Save_MacroName( line));
                
                flag1=TRUE;
                macro_lines_Arr[i1]=line_num;
                i1++;               
            }
            /* add the lines between macro and endm to Macrotable */
            if(flag1==TRUE)
            { 
                macro_flag=TRUE;
                if(strstr(line,"macro")==NULL && strstr(line,"endm")==NULL )
                Add2_MacroTable(&head,macro_name,line,line_num);
            }
            /* add the line that contains the endm to macro_lines_Arr */  
             if(strstr(line,"endm")!=NULL)
             {
                macro_lines_Arr[i1]=line_num;
                i1++;
                flag1=FALSE;
             }

             line_num++;
    } 
    macro_lines_Arr[i1]=line_num;
        
    /* //! Print the linked list that contains the lines between macro and endm; */

    /*
     *  Write line by line to destination file
     */    
    rewind(ptr_file);
    line_num=0;





    /*write into ptr_file */
    while ((fgets(line, LINE_LENGTH, ptr_file)) != NULL)    
    {
        /*if there is no macro write to file.am the same lines as file.as */
        if(macro_flag==FALSE)
                fputs(line, ptr_file_write);
        else if(macro_flag==TRUE)        
            { 
                printf("\n the line :%s",line);
                /*find line that contains word macro & name of macro */
                if(strstr(line,"macro")!=NULL) 
                        strcpy(macro_name, Save_MacroName( line));/* save the macro name */
                    
                /* find the line that contains only the macro name */
                if(strstr(line,macro_name)!=NULL   )
                {           
                    macroName_line=line_num;

                }
                /* print in the new file all the lines that are not associated with the macro operation */
                if(strstr(line,macro_name)==NULL)
                    if(macro_lines_Arr[i4]<=line_num && line_num<(macro_lines_Arr[i4+1]-1)  )
                    {
                        fputs(line, ptr_file_write);
                            if(macro_lines_Arr[i4+1]-2==line_num)
                                i4=i4+2;
                    }
                /*write in the new file the lines between macro and endm */
                if(line_num==macroName_line)
                    while(Get_Line_DataByString(head,macro_name,ptr_file_write)!=NULL);
            }
                line_num++;
    }

    fclose(ptr_file_write);
}

/*used to get the correct lines by the name of the macro */
MacroLinePtr Get_Line_DataByString(MacroLinePtr head,char inputString[],FILE *ptr_file_write)
{
  while(head)
    {
        /* if inputString equles to current data */
        if(strstr(inputString,head->macro_name)!=NULL)
            /* write the lines between macro and endm to new file*/ 
            fputs(head->macro_line, ptr_file_write);
      head=head->next;
    }
  return head;
}


/*used to count the number of tokens for each line*/
int Return_Num_Tokens(char *line)
{
    char *token; /* used to store the token of each line */
    char strtok_string[]= " ,\n";
    int token_counter=0;
    token = strtok(line,strtok_string);
    while( token != NULL  )
    {
        token_counter++;
        token = strtok(NULL,strtok_string); 
    }
    return token_counter;
}

char * Save_MacroName1(char *line)
{
    char *token; /* used to store the token of each line */
    char strtok_string[]= " ,\n";
    int word_counter=0;
    char string[LINE_LENGTH];
    char *macro_name1=string;
    token = strtok(line,strtok_string);
    while( token != NULL  )
    {
        if( word_counter ==1)
        {
            strcpy(macro_name1, token);
            return macro_name1;                    
        }
        word_counter++;
        token = strtok(NULL,strtok_string); 
    }
    return macro_name1;
}



/* used to identify the macro name */
char *Save_MacroName(char *line)
{
    char *token; /* used to store the token of each line */
    char strtok_string[]= " ,\n";
    int word_counter=0;
    char *macro_name=NULL; /* used to store the name of the macro */
    
    token = strtok(line,strtok_string);
    while( token != NULL  )
    {
        if( word_counter ==1)
        {
            macro_name = (char*)calloc(strlen(token), sizeof(char));
            strcpy(macro_name, token);
            return macro_name;                    
        }
        word_counter++;
        token = strtok(NULL,strtok_string); 
        free(macro_name);  
    }
    return macro_name;
}



/*used to print linked list that contains the macro names & lines */
void PrintMacroList(MacroLinePtr h)
{
  printf("\n");
  while(h)
  {
        printf("\nMacroName:%s",h->macro_name);
        printf("\nMacroLine:%s",h->macro_line);
        printf("MacroLineNum:%d",h->macro_line_num);
        printf("--->\n");
        h=h->next;
  }
 printf("*\n");
}

/* add macro name & macro line MacroTable */
void Add2_MacroTable(MacroLinePtr *hMacroLinePtr, char macro_name_file[],char macro_line_file[],int line_num){

   MacroLinePtr p1,p2;
   MacroLinePtr t;

   t= (MacroLinePtr) malloc(sizeof(MacroLine));
   if (!t)
   { 
      printf("\n cannot build list \n");
      exit(0);
   }
   strcpy(t->macro_name, macro_name_file); /* // copy macro_name_file to t->macro_name */
   strcpy(t->macro_line, macro_line_file); /* // copy macro_line_file to t->line_name */
   t->macro_line_num=line_num;/* save the line number in the macro_line_num */

   p1= *hMacroLinePtr;
   while((p1))
   {
      p2= p1; /* //p1=current,p2=previous */
      p1=p1->next;
   }
 
   if (p1==*hMacroLinePtr)
   {
      *hMacroLinePtr = t;
      t->next=p1;
   }
    {
      p2->next = t;
      t-> next=p1;
   }
}