/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


/*--------- Headers ---------*/
#include "structs.h"
#include "utils.h"
#include "assembler.h"

 /*used  to read the lines of the code  */
void * Read_Line2( char *line,labelPtr head,ErrorType *err3,int line_num,int IC_correct,int *L_value,char input_file_orginal[]);

/* This file manages all the activities of the second pass */
void second_pass(FILE *fp2,labelPtr head,char first_line_ob[],char input_file_orginal[])
{

    int L_value=0;
    int IC_correct=100;
    int line_num=1;
    ErrorType err3=OK;
    MCPtr head_2=NULL;
    char origin_name[LABEL_LENGTH]="z";/* save the origin name of the file */
    strcpy(origin_name,input_file_orginal);

    /* create .ob file */
    create_ob(first_line_ob,head,head_2,first_line_ob,input_file_orginal);

    rewind(fp2);
    while(fgets(line, LINE_LENGTH, fp2) != NULL) 
        {    
               if(err3!=OK)
                {
                   write_error(line_num+1,err3);
                    if( access( input_file_orginal, F_OK ) == 0 ) 
                            if (remove(input_file_orginal) == 0);
                 exit(0);
               }
            head=Read_Line2(line,head,&err3,line_num,IC_correct,&L_value,input_file_orginal);
            IC_correct=IC_correct+L_value;
            line_num++;

             
        }
        /* create .ext & .ent files */
        create_ext_ent(head,origin_name);
   



     /*printlist2(head);  //!print symbole table  */ 
}

 /*used to get each word of the line into a dynamoc array */
void * Read_Line2( char *line,labelPtr head,ErrorType *err3,int line_num,int IC_correct,int *L_value,char input_file_orginal[])
{
     MCPtr head_2=NULL;/* used as pointer to linked list , that sends command line to finale file */
    int L=0;
    int DC=0;
    int word_counter=1;
   
    char *first_word=NULL; /* used to save the first word of each line */
    char *second_word=NULL;/* used to save the second word of each line */
    char *third_word=NULL;/* used to save the third word of each line */ 
    char *label3=NULL;
    int address=default_value;/* used to save the base value of data code */
    int base=default_value;/* store the base value of address */
    int offset=default_value;/* store the offset value of address */
    int opernads_counter=0;/*used to count the operands in each line */
    char machine_line[LABEL_LENGTH];
    boolean command_flag=FALSE;
    m_line1 mach_instruc1;/* used to print 1 line of data code to machine */
    m_line2 mach_instruc2;/* used to print 2 line of data code to machine */
    m_line1 mach_instruc4;/* used for lines that contain base and offset */
    m_line1 mach_instruc3;/* used to print the ascii value of string or each char of string */

    char *first_operand1=NULL; /* used to store the first word after op code */
    char *second_operand2=NULL;/* used to store the second word after op code */
    int type34=-1;/* save the command type */
    char *type34_str=NULL;
    char label_index1[LABEL_LENGTH];/* used to save label,if addressing type of 1 is of type index */
    char label_index2[LABEL_LENGTH];/* used to save label,if addressing type of 2 is of type index */
    char label_index3[LABEL_LENGTH];/* used to save label,if command type does not habe source addr*/
    boolean EXTERN_FLAG=FALSE; /* used to flag if label in symbole tabel and equal to atrribute of type .extern */
    boolean DataFlag=FALSE;
    AttributesType string_or_data;/* identify if data or string */
    int data_counter=0;/* used to count words after .data or .string */
    int counter=0;
    int i=default_value;
    int temp=line_num; /*used to identify when line ends */
    char strtok_string[]=" ,\n";
        *err3=OK;
    *L_value=0;

    token = strtok(line,strtok_string);
    while( token != NULL  ) 
        {

            if(word_counter==1)
            {
                free(first_word);
                first_word = (char*)calloc(strlen(token), sizeof(char));
                strcpy(first_word,(token));
            }
            if(word_counter==2)
            {
                free(second_word);
                second_word = (char*)calloc(strlen(token), sizeof(char));
                strcpy(second_word,(token));
                temp=line_num;
                /* this temp used to distinguish between 2 cases: 
                    1) when line indeed finished meaning there is only one word in the line.
                    2) when line is not finished yet and the second_word=NULL since it did not
                       yet finished reading the tokens of the line.
                */
            
            }
            if(word_counter==3)
            {
                free(third_word);
                third_word = (char*)calloc(strlen(token), sizeof(char));
                strcpy(third_word,(token));
            }
            /* check if word is of type entry */
            if(IS_ENTRY(first_word))
            {
              if(temp==line_num)
              {
                if(second_word!=NULL)
                {
                    if(word_counter==2)
                    {
                          *err3=OK;
                          /* check if second word is already in the label list */
                          if(Compare_SymboleTable(head,second_word,NULL))
                          {
                            /* up date the entry value of label to true */
                             Compare_SymboleTable(head,first_word,second_word);     
                          }
                          else
                            *err3=LABEL_DOES_NOT_EXIST_IN_SYMBOL_LIST;
                    }
                    else if(second_word!=NULL && (2<word_counter))
                        *err3=ENTRY_TOO_MUCH_LABELS;
                }
              }
              else if(temp!=line_num)
                {
                  if(second_word==NULL)
                    *err3=ENTRY_NOT_ENOUGH_LABELS;
                }
            }
 
            if(strchr(token, ':') ) /* identified label */
               {
                  label3=(char*)calloc(strlen(token), sizeof(char));
                  strcpy(label3,RemoveColon(token));

                  
               }

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
                                    Add2_MachinCode(&head_2,machine_line);
                                }
                                    DC=(strlen(token)-1);
                              }
                           }
                              else if(string_or_data==data)
                           {
                              /*check if numbers after .data are legal */
                              if(Legal_Data(token))
                              {
                                 counter++;
                                strcpy(machine_line,conv_data_instruct(&mach_instruc3,atoi(token),counter+IC_correct));
                                Add2_MachinCode(&head_2,machine_line);
                                 DC++;
                              }
                           }
                        }
                  }
                if(DC!=0)
                    *L_value=DC;


            if(0<=(int)Identify_Instruction(token) &&(int)Identify_Instruction(token)<=15)
            {
                type34=(int)Identify_Instruction(token);
                type34_str=(char*)calloc(strlen(token), sizeof(char));
                strcpy(type34_str,token);/* convert comand instruction in string */
               command_flag=TRUE;
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

            source_addr1=Addersing_Type(first_operand1, head);
            target_addr2=Addersing_Type(second_operand2, head);
            swap_operands(type34, source_addr1, target_addr2,&source_addr1,&target_addr2);
            if(Number_Of_Operands(opernads_counter,type34)) /*cheack if number of operands is right accroding the table of page 34*/
                if(Legal_Addressing_methods(type34,source_addr1,target_addr2))
                {
                    L=Calculate_L_Value_According_Operands(type34,L,source_addr1,target_addr2);
                    *L_value=L;
                }
            default_values(&mach_instruc1,&mach_instruc2);
            word_counter++;
        token = strtok(NULL,strtok_string);

        }
        L_value++;
        if(type34_str!=NULL)
            {

                /* for instrction command of type stop and rts */
                if(source_addr1==NoOperand && target_addr2==NoOperand)
                {
                    counter++;
                    build_first_word(type34_str,&mach_instruc1);
                    conv_mach_instruct1(&mach_instruc1,counter+IC_correct);
                    strcpy(machine_line,conv_mach_instruct1(&mach_instruc1,counter+IC_correct) );
                    Add2_MachinCode(&head_2,machine_line);
                    counter++;
                }
                /* for instrction command of type : 5<= command <=13 */
                else if(source_addr1==NoOperand && target_addr2!=NoOperand)
                {
                    counter++;
                    build_first_word(type34_str,&mach_instruc1);
                    conv_mach_instruct1(&mach_instruc1,counter+IC_correct);
                    strcpy(machine_line,conv_mach_instruct1(&mach_instruc1,counter+IC_correct) );
                    Add2_MachinCode(&head_2,machine_line);
                    counter++;
                    build_second_word(type34_str,source_addr1,target_addr2,first_operand1,second_operand2,&mach_instruc2);
                    strcpy(machine_line,conv_mach_instruct2(&mach_instruc2,counter+IC_correct));
                    Add2_MachinCode(&head_2,machine_line);
                }               
                /* for instrction command of type : 0<= command <=4 */
                 else if(source_addr1!=NoOperand && target_addr2!=NoOperand)
                {


                    build_first_word(type34_str,&mach_instruc1);
                    conv_mach_instruct1(&mach_instruc1,counter+IC_correct);
                    strcpy(machine_line,conv_mach_instruct1(&mach_instruc1,counter+IC_correct) );
                    Add2_MachinCode(&head_2,machine_line);

                    counter++;

                    build_second_word(type34_str,source_addr1,target_addr2,first_operand1,second_operand2,&mach_instruc2);
                    strcpy(machine_line,conv_mach_instruct2(&mach_instruc2,counter+IC_correct));
                    Add2_MachinCode(&head_2,machine_line);
                }

            }

        if(first_operand1!=NULL && source_addr1==index )
        {
            
            strcpy(label_index1,return_clean_label(first_operand1,source_addr1));

        }
            /*extract the name of label if the type of adreesing is index */
        if(second_operand2!=NULL && target_addr2==index )
        {
            strcpy(label_index2,return_clean_label(second_operand2,source_addr1));
        }



        /*extract the name of label if the type of adreesing is index
          and there is no source operand ,for commands from 5 to 12  */
        if(first_operand1!=NULL && second_operand2==NULL && target_addr2==index  )
        {
            /* if second_operand2=NULL, then copy the data of first_operand1 to second_operand2 */  
            if(second_operand2==NULL )
            {
                second_operand2 = (char*)calloc(strlen(first_operand1), sizeof(char));
                strcpy(second_operand2,first_operand1);
            }
            return_clean_label(second_operand2,target_addr2);
            strcpy(label_index3,return_clean_label(second_operand2,target_addr2));
        }

        /* get the base & offset of labels that are of type code and their
            command instruction does not have source operand ,
            used for:  5<=command<=14*/
        if(first_operand1!=NULL && (target_addr2==direct || target_addr2==index)  )
        {
            if(target_addr2==index)
            {
                if(!Compare_SymboleTable_2(head,label_index3,NULL) )
                    {
                        address=get_address(head,label_index3);
                        offset=address%16;
                        base=address-offset;
                        EXTERN_FLAG=!Identify_Label_Extern(head,second_operand2);
                        Update_address_External(head,IC_correct+counter,second_operand2);

                        /* print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG) );                        
                        Add2_MachinCode(&head_2,machine_line);

                        counter++;

                        /* print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);



                    }
            }
            else if(target_addr2==direct)
            {
                /* if second_operand2=NULL, then copy the data of first_operand1 to second_operand2 */  
                    if(second_operand2==NULL )
                    {
                        second_operand2 = (char*)calloc(strlen(first_operand1), sizeof(char));
                        strcpy(second_operand2,first_operand1);
                    }
                if(!Compare_SymboleTable_2(head,second_operand2,NULL) )
                    {
                        counter++;
                        address=get_address(head,second_operand2);
                        offset=address%16;
                        base=address-offset;
                        EXTERN_FLAG=!Identify_Label_Extern(head,second_operand2);
                        Update_address_External(head,IC_correct+counter,second_operand2);

                        /* /print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                        counter++;
                        /* print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);
                    }
            }            
        }

                 /* check if second operand 2 exists and if this operand equal to direct or index */
       else if(second_operand2!=NULL && (target_addr2==direct || target_addr2==index)  )
        {

            if(target_addr2==index)
                {
                    if(!Compare_SymboleTable_2(head,label_index2,NULL) )
                    {
                        address=get_address(head,label_index2);
                        offset=address%16;
                        base=address-offset;
                         EXTERN_FLAG=!Identify_Label_Extern(head,label_index2);
                        Update_address_External(head,IC_correct+counter,label_index2);

                        /* //?print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                        counter++;
                        /* //?print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                    }
                }
            else if(target_addr2==direct)
            {
                if(!Compare_SymboleTable_2(head,second_operand2,NULL) )
                    {
                        counter++;
                        address=get_address(head,second_operand2);
                        offset=address%16;
                        base=address-offset;
                        EXTERN_FLAG=!Identify_Label_Extern(head,second_operand2);
                        Update_address_External(head,IC_correct+counter,second_operand2);

                        /* //?print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                        counter++;
                        /* //?print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);
                    }
            }

        }

        /* get the base & offset of labels that are of type of data */
      else if(first_operand1!=NULL && (source_addr1==direct || source_addr1==index)  )
        {
            counter++;   

            if(source_addr1==index)
            {
                if(!Compare_SymboleTable_2(head,label_index1,NULL) )
                    {
                        address=get_address(head,label_index1);
                        offset=address%16;
                        base=address-offset;
                         EXTERN_FLAG=!Identify_Label_Extern(head,label_index1);
                        Update_address_External(head,IC_correct+counter,label_index1);

                        /* //?print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                        counter++;

                        /* //?print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);


                    }
            }
            else if(source_addr1==direct)
            {

                if(!Compare_SymboleTable_2(head,first_operand1,NULL) )
                    {
                        
                        address=get_address(head,first_operand1);
                        offset=address%16;
                        base=address-offset;
                         EXTERN_FLAG=!Identify_Label_Extern(head,first_operand1);
                        Update_address_External(head,IC_correct+counter,first_operand1);

                        /* //?print machine code of base line */
                        conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,base,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);

                            counter++;   

                        /* //?print machine code of offset line */
                        conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG);
                        strcpy(machine_line,conv_base_offset(&mach_instruc4,offset,IC_correct+counter,EXTERN_FLAG));                        
                        Add2_MachinCode(&head_2,machine_line);
                        counter++;
                    }
            }            
        }

      else if (target_addr2==immediate)
      {   
            counter++;
            /* if second_operand2=NULL, then copy the data of first_operand1 to second_operand2 */  
            if(second_operand2==NULL )
            {
                second_operand2 = (char*)calloc(strlen(first_operand1), sizeof(char));
                strcpy(second_operand2,first_operand1);
            }
            strcpy(machine_line,conv_data_instruct(&mach_instruc3,atoi(extract_number(second_operand2)),counter+IC_correct));
            Add2_MachinCode(&head_2,machine_line);

      }
      else if(source_addr1==immediate)
      {
            counter++;
      }
       else if(target_addr2==unknowenAddersing || source_addr1==unknowenAddersing )
        {
            *err3=LABEL_DOES_NOT_EXIST_IN_SYMBOL_LIST;
        }

    create_ob(machine_line,head,head_2,NULL,input_file_orginal);
    return head;

}
