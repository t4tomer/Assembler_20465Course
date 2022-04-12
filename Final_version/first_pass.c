/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*--------- Headers ---------*/
#include "structs.h"
#include "utils.h"
#include "assembler.h"
void is_colon(char *line);
void read_line( char *line);
void printWord(char *word);

void * Read_Line( char *line,labelPtr head,int IC,ErrorType *err1,int *total_DC); /*used to get each word of the line into a dynamoc array */
int  return_L(char *line,int L,labelPtr head,ErrorType *err2, int line_num,int IC);
void * Read_Line_again( char *line,labelPtr head,int IC,ErrorType *err1,int *total_DC,int L,int *L_value); /*used to get each word of the line into a dynamoc array */


void printlist(ptr h);/* used to print the //? test linked list */



char *COPY_TOKEN(char *word); /* used to copty token */

/* This function manages all the activities of the first pass */
void first_pass(FILE *fp1,char input_file_orginal[])
{



    int line_num = 0; /* Line numbers start from 0 */
    int IC_correct=100;
    int L=0;
    int L_value=0;
    labelPtr head=NULL; /*//used for the linked list */
    ErrorType err1=OK;
    int total_DC=0;


    rewind(fp1);
   /* Read lines until end of file */
    while(fgets(line, LINE_LENGTH, fp1) != NULL)
    {
         line_num++;
         head=Read_Line_again(line,head,IC_correct, &err1,&total_DC,L,&L_value);
         IC_correct=IC_correct+L_value;
    }

      /* used to update the values of atributes of type data */
      Update_Data_Adress(head,IC_correct-total_DC);

      if(err1!=OK)
         write_error(line_num,err1);

      /* //!enter the second pass */
      second_pass(fp1,head,first_line_of_ob(total_DC,IC_correct-total_DC-100),input_file_orginal);

}

void * Read_Line_again( char *line,labelPtr head,int IC_correct,ErrorType *err1,int *total_DC,int L,int *L_value)
{
   

   int counter=0;
   int DC=0;
   m_line1 mach_instruc1;/* used to print 1 line of data code to machine */
   m_line2 mach_instruc2;/* used to print 2 line of data code to machine */
   m_line1 mach_instruc3;/* used to print the ascii value of string or each char of string */
   boolean label_flag=FALSE;
   boolean DataFlag=FALSE;/*used to identify if the label is data */
   boolean ExternFlag=FALSE;/*used to identify if the label is extern */
   boolean CodeFlag=FALSE;
   boolean command_flag=FALSE; /* used to identify if it is command */

   char machine_line[LABEL_LENGTH];
   char *label2=NULL;
   char *first_operand1=NULL; /* used to store the first word after op code */
   char *second_operand2=NULL;/* used to store the second word after op code */
   char *type34_str=NULL;
   int type34=-1;/* save the command type */
   int token_counter=0;/*used to count the token in each line */
   int opernads_counter=0;/*used to count the operands in each line */
   int data_counter=0;/* used to count words after .data or .string */
   int i=default_value;
   AttributesType string_or_data;/* identify if data or string */
   char strtok_string[]= " ,\n";

   * err1=OK; /*save the type of error */
   L=0;
   *L_value=0;
    
   line = skip_space(line);/*  Proceeding to first non-blank character */

    /* start reading the lines of fiel by tokens */
    token = strtok(line,strtok_string);
       while( token != NULL  )

      {


            if(strchr(token, ':')) /* identified label */
               {
                  label_flag=TRUE;
                  label2=(char*)calloc(strlen(token), sizeof(char));
                  strcpy(label2,(token));
                  *err1=Label_Warning(head,label2);
                  if(*err1!=OK)
                        break;
               }
            if(strchr(token, ':') && strlen(token)==1)
               {
                  *err1=COLON_NOT_IN_RIGHT_PLACE;
               }
               token_counter++;

                  if(IS_DATA(token))
                  {
                     DataFlag=TRUE;
                     string_or_data=SORT_OF_DATA(token,IS_DATA(token));

                  }

               if(DataFlag==TRUE) /* if the line is data get the tokens */
                  {
                        data_counter++;
                        /* get the tokens after .data or .string*/
                        if(1<data_counter)
                        {
                           if(string_or_data==string)
                           {
                                 /* cheack if string have 2 " */
                              if(token[0]=='"' && token[strlen(token)-1]=='"')
                              {
                                 for(i=1;i<strlen(token)-0;i++)
                                 {
                                    counter++;
                                    strcpy(machine_line,conv_data_instruct(&mach_instruc3,token[i],counter+IC_correct));

                                }
                                    DC=(strlen(token)-1);
                              }
                              else if((token[0]!='"' || token[strlen(token)-2]!='"') )
                                 *err1=STRING_OPERAND_NOT_VALID;/* string does not have 2 quates */
                           }
                              else if(string_or_data==data)
                           {
                              /*check if numbers after .data are legal */
                              if(Legal_Data(token))
                              {
                                 counter++;
                                 strcpy(machine_line,conv_data_instruct(&mach_instruc3,atoi(token),counter+IC_correct));
                                 DC++;

                              }
                              else if(!Legal_Data(token))
                              *err1=DATA_EXPECTED_NUM;/* error data must contain only numbers */
                           }
                        }
                  }
            if(DC!=0)
               *L_value=DC;

               /*------>START //!identify if label is of type .extern */
            if(IS_EXTERN(token) &&label2==NULL )
            {
               ExternFlag=TRUE;
            }
            if(ExternFlag)
            {
               if(!IS_EXTERN(token))
               {
                  label2=(char*)calloc(strlen(token), sizeof(char));
                  strcpy(label2,token);
                  *err1=Label_Warning(head,label2);


               }

            }

               /*--------->END //!identify if label is of type .extern */

             /*---------------------->START //!cheack if token is instruction name*/

            if(0<=(int)Identify_Instruction(token) &&(int)Identify_Instruction(token)<=15)
            {
               token_counter=0;
               type34=(int)Identify_Instruction(token);
               type34_str=(char*)calloc(strlen(token), sizeof(char));
               strcpy(type34_str,token);/* save command instruct in string */
               command_flag=TRUE;
            }

            else if ((int)Identify_Instruction(token)==16 && token[strlen(token)-1]!=':')
            {
               *err1=COMMAND_NOT_FOUND;
            }
            if(command_flag==TRUE)
            {
                  opernads_counter++;
                  if(opernads_counter==2)
                     {
                        first_operand1 = (char*)calloc(strlen(token), sizeof(char));
                        strcpy(first_operand1, token);
                     }
                  if(opernads_counter==3)
                     {
                        second_operand2 = (char*)calloc(strlen(token), sizeof(char));
                        strcpy(second_operand2, token);
                     }
            }
            /*check if registers are valid */
            if(first_operand1!=NULL)
               if(Wrong_Register(first_operand1))
                  *err1=REGISTER_DOES_NOT_EXIST;
            if(second_operand2!=NULL)
               if(Wrong_Register(second_operand2))
                  *err1=REGISTER_DOES_NOT_EXIST;

            source_addr1=Addersing_Type(first_operand1, head);
            target_addr2=Addersing_Type(second_operand2, head);
            swap_operands(type34, source_addr1, target_addr2,&source_addr1,&target_addr2);

         /*check if number of operands is right accroding the table of page 34 */
         if(Number_Of_Operands(opernads_counter,type34)) 
         {
            /*check if number of operands is right accroding the table of page 34 */
            if(Legal_Addressing_methods(type34,source_addr1,target_addr2))
               {
                  L=Calculate_L_Value_According_Operands(type34,L,source_addr1,target_addr2);
                  default_values(&mach_instruc1,&mach_instruc2);
                  *L_value=L;
               }

         }
           /*-------------->END //!check if token is instruction name */

         if(IS_CODE(label2,type34_str)  && label_flag==TRUE)
         {
            CodeFlag=TRUE;
         }
       
         token = strtok(NULL,strtok_string);
      
      }
         /* erros of operands */
         if(type34!=-1 && !Legal_Addressing_methods(type34,source_addr1,target_addr2))
            *err1=COMMAND_INVALID_METHOD;
         if(type34!=-1 &&!Legal_Addressing_methods(type34,source_addr1,target_addr2))
            *err1=COMMAND_INVALID_NUMBER_OF_OPERANDS;
         
         if(DataFlag==TRUE )
         {                                                      
                                
            if(label2!=NULL)
            {
               if(Compare_SymboleTable_2(head,label2,NULL)  )
               {
                  Add2_SymboleTable(&head,RemoveColon(label2),*total_DC,0,0,data,FALSE);
               }
            }
            *total_DC=*total_DC+DC;
         }

         if(ExternFlag)
         {
            if(Compare_SymboleTable_2(head,label2,NULL))
            {
               Add2_SymboleTable(&head,(label2),0,0,0,external,FALSE);
            }
            else if(!Compare_SymboleTable_2(head,label2,NULL))
            {
               *err1=LABEL_ALREADY_EXISTS;
            }
         }
         if(CodeFlag)
         {
            if(Compare_SymboleTable_2(head,label2,NULL))
            {

               Add2_SymboleTable(&head,RemoveColon(label2),IC_correct,0,0,code,FALSE);
            }
            else if(!Compare_SymboleTable_2(head,label2,NULL))
            {
               *err1=LABEL_ALREADY_EXISTS;
            }
         }

    return head;

 }