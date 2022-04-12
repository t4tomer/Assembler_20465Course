/* this file save all the functions that are to build the finale files */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "utils.h"
#include "assembler.h"


/* assign default values to all structs */
void default_values(m_line1 *mach_instruc1,m_line2 *mach_instruc2 )
{
      mach_instruc1->opcode=-1;
      mach_instruc1->E=0;
      mach_instruc1->R=0;
      mach_instruc1->A=0;
      mach_instruc1->bit_19=0;
   
      mach_instruc2->bit_19=0;
      mach_instruc2->A=0;
      mach_instruc2->R=0;
      mach_instruc2->E=0;
      mach_instruc2->funct=-1;
      mach_instruc2->source_register1=-1;
      mach_instruc2->source_addr1=-1;
      mach_instruc2->target_register2=-1;
      mach_instruc2->target_addr2=-1;

}

/* convert 0=<number<=15 to Hex representation */
char Hex_conv(int number)
{
  char Hex='z'; /*deafult value */
  if(10<=number && number<=15)
    switch(number)
    {
      
      case 10:
         Hex='a';
      break;

      case 11:
      Hex='b';
      break;

      case 12:
      Hex='c';
      break;

      case 13:
      Hex='d';
      break;

      case 14:
      Hex='e';
      break;

      case 15:
      Hex='f';
      break;
    }
  else 
    Hex=number+'0';



  return Hex;
}
/*used to convert base & offset to machine code */
char *conv_base_offset(m_line1 *mach_instruc3, int opcode,int IC_number,boolean EXTERN_FLAG)
{  
   int A_cofficient1=default_value;
   int B_cofficient1=default_value;
   int C_cofficient1=default_value;
   int D_cofficient1=default_value;
   int E_cofficient1=default_value;
   char finle_line[LABEL_LENGTH]="   Av-Bw-Cx-Dy-Ez";/* machine format */
   int ind_v=strstr(finle_line,"v")-finle_line;/* index v= A-coefficient */  
   int ind_w=strstr(finle_line,"w")-finle_line;/* index w= B-coefficient */
   int ind_x=strstr(finle_line,"x")-finle_line;/* index x= C-coefficient */
   int ind_y=strstr(finle_line,"y")-finle_line;/* index y= D-coefficient */
   int ind_z=strstr(finle_line,"z")-finle_line;/* index z= E-coefficient */


   char *data_line=NULL;/* used to represnt the data line in the ob file */
   char IC_number_str[LABEL_LENGTH];/*store IC_number in string format */
   sprintf(IC_number_str, "%d", IC_number);/* convert IC_number to string format */
   /* check if last char of token is not equal to "*/
      mach_instruc3->opcode=opcode;
      if(EXTERN_FLAG==FALSE)
      {
         mach_instruc3->E=0;
         mach_instruc3->R=1;
         mach_instruc3->A=0;
      }
      if(EXTERN_FLAG==TRUE)
      {
         mach_instruc3->E=1;
         mach_instruc3->R=0;
         mach_instruc3->A=0;

      }


      data_line = (char*) malloc(strlen(finle_line)*sizeof(char));
      
  

      A_cofficient1=(mach_instruc3->E)|(mach_instruc3->R<<1)|(mach_instruc3->A<<2);
      B_cofficient1=( (mach_instruc3->opcode&15<<12)>>12);
      C_cofficient1=( (mach_instruc3->opcode&15<<8)>>8 );
      D_cofficient1=( (mach_instruc3->opcode&15<<4)>>4 );
      E_cofficient1=( (mach_instruc3->opcode&15<<0)>>0 ) ;

      finle_line[ind_v]=Hex_conv(A_cofficient1);
      finle_line[ind_w]=Hex_conv(B_cofficient1);
      finle_line[ind_x]=Hex_conv(C_cofficient1);
      finle_line[ind_y]=Hex_conv(D_cofficient1);
      finle_line[ind_z]=Hex_conv(E_cofficient1);
      strcpy(data_line,finle_line);/* copy machine line to line 1*/
      strcat(IC_number_str, data_line);/*merge IC_number_str & line1 */
      free(data_line);/* free memory */
      data_line = (char*) malloc(strlen(IC_number_str)*sizeof(char));/* create memory with size of IC_number_str & line1*/ 
      strcpy(data_line,IC_number_str);/* store IC_number_str & line1 in line1 */
      return data_line;


}




/* convert data line to machine code (regular lines ) */
char *conv_data_instruct(m_line1 *mach_instruc3, int token,int IC_number)
{
   int A_cofficient1=default_value;
   int B_cofficient1=default_value;
   int C_cofficient1=default_value;
   int D_cofficient1=default_value;
   int E_cofficient1=default_value;
   char finle_line[LABEL_LENGTH]="   Av-Bw-Cx-Dy-Ez";/* machine format */
   int ind_v=strstr(finle_line,"v")-finle_line;/* index v= A-coefficient */  
   int ind_w=strstr(finle_line,"w")-finle_line;/* index w= B-coefficient */
   int ind_x=strstr(finle_line,"x")-finle_line;/* index x= C-coefficient */
   int ind_y=strstr(finle_line,"y")-finle_line;/* index y= D-coefficient */
   int ind_z=strstr(finle_line,"z")-finle_line;/* index z= E-coefficient */
   
   char *data_line=NULL;/* used to represnt the data line in the ob file */
   char IC_number_str[LABEL_LENGTH];/*store IC_number in string format */
   sprintf(IC_number_str, "%d", IC_number);/* convert IC_number to string format */
   /* check if last char of token is not equal to "*/
   if(token!=34)
   {
      mach_instruc3->opcode=token;
      mach_instruc3->E=0;
      mach_instruc3->R=0;
      mach_instruc3->A=1;

    
      data_line = (char*) malloc(strlen(finle_line)*sizeof(char));
      
    

      A_cofficient1=(mach_instruc3->E)|(mach_instruc3->R<<1)|(mach_instruc3->A<<2);
      B_cofficient1=( (mach_instruc3->opcode&15<<12)>>12);
      C_cofficient1=( (mach_instruc3->opcode&15<<8)>>8 );
      D_cofficient1=( (mach_instruc3->opcode&15<<4)>>4 );
      E_cofficient1=( (mach_instruc3->opcode&15<<0)>>0 ) ;

      finle_line[ind_v]=Hex_conv(A_cofficient1);
      finle_line[ind_w]=Hex_conv(B_cofficient1);
      finle_line[ind_x]=Hex_conv(C_cofficient1);
      finle_line[ind_y]=Hex_conv(D_cofficient1);
      finle_line[ind_z]=Hex_conv(E_cofficient1);
      strcpy(data_line,finle_line);/* copy machine line to line 1*/
      strcat(IC_number_str, data_line);/*merge IC_number_str & line1 */
      free(data_line);/* free memory */
      data_line = (char*) malloc(strlen(IC_number_str)*sizeof(char));/* create memory with size of IC_number_str & line1*/ 
      strcpy(data_line,IC_number_str);/* store IC_number_str & line1 in line1 */


      return data_line;


   }
   /* used for the end of string */
   else if(token==34)
   {
     

      char end_of_string[LABEL_LENGTH]="   A4-B0-C0-D0-E0";/* machine format-end of string */
      char IC_number_str[LABEL_LENGTH];/*store IC_number in string format */
      sprintf(IC_number_str, "%d", IC_number);/* convert IC_number to string format */
      strcat(IC_number_str, end_of_string);/*merge IC_number_str & end_of_string */
      data_line = (char*) malloc(strlen(IC_number_str)*sizeof(char));/* create memory with size of IC_number_str & line1*/ 
      strcpy(data_line,IC_number_str);/* store IC_number_str & end_of_string in line1 */



   }
   return data_line;
  

}

/* insert code word into values into the right struct  */
void build_first_word(char *type34_str,m_line1 *mach_instruc1)
{
      mach_instruc1->opcode=identify_opcode(type34_str);
      mach_instruc1->E=0;
      mach_instruc1->R=0;
      mach_instruc1->A=1;
      mach_instruc1->bit_19=0;
}

/* used to extract number from immediate instruction */
char *extract_number( char *token)
{
   int i=0;
   char * number;
   int length=strlen(token);
   number = (char*) malloc(length*sizeof(char));
   for(i=1; i<length;i++)
      number[i-1]=token[i];
   return number;

}

/* used to convert code word to line that contains only opcde */
char *conv_mach_instruct1(m_line1 *mach_instruc1,int IC_number )
{
   
    int A_cofficient1=default_value;
    int B_cofficient1=default_value;
    int C_cofficient1=default_value;
    int D_cofficient1=default_value;
    int E_cofficient1=default_value;

   char finle_line[LABEL_LENGTH]="   Av-Bw-Cx-Dy-Ez";/* machine format */

   int ind_v=strstr(finle_line,"v")-finle_line;/* index v= A-coefficient */  
   int ind_w=strstr(finle_line,"w")-finle_line;/* index w= B-coefficient */
   int ind_x=strstr(finle_line,"x")-finle_line;/* index x= C-coefficient */
   int ind_y=strstr(finle_line,"y")-finle_line;/* index y= D-coefficient */
   int ind_z=strstr(finle_line,"z")-finle_line;/* index z= E-coefficient */
    char *code_line1=NULL;/* used to represnt the data line in the ob file */
    char IC_number_str[LABEL_LENGTH];/*store IC_number in string format */
    sprintf(IC_number_str, "%d", IC_number);/* convert IC_number to string format */



   code_line1 = (char*) malloc(strlen(finle_line)*sizeof(char));



   A_cofficient1=(mach_instruc1->E)|(mach_instruc1->R<<1)|(mach_instruc1->A<<2);

    B_cofficient1=( ( (int)pow(2,mach_instruc1->opcode)&15<<12)>>12 );
    C_cofficient1=( ( (int)pow(2,mach_instruc1->opcode)&15<<8)>>8 );
    D_cofficient1=( ( (int)pow(2,mach_instruc1->opcode)&15<<4)>>4 );
    E_cofficient1=( ( (int)pow(2,mach_instruc1->opcode)&15<<0)>>0 );

    finle_line[ind_v]=Hex_conv(A_cofficient1);
    finle_line[ind_w]=Hex_conv(B_cofficient1);
    finle_line[ind_x]=Hex_conv(C_cofficient1);
    finle_line[ind_y]=Hex_conv(D_cofficient1);
    finle_line[ind_z]=Hex_conv(E_cofficient1);
    strcpy(code_line1,finle_line);
    strcat(IC_number_str,code_line1);
    free(code_line1);/* free memory */
    code_line1 = (char*) malloc(strlen(IC_number_str)*sizeof(char));/* create memory with size of IC_number_str & line1*/ 
    strcpy(code_line1,IC_number_str);/* store IC_number_str & line1 in line1 */
    return code_line1;

}

/*used to build the second -the code word */
void build_second_word(char *type34_str,AddersingType source_addr1,AddersingType target_addr2,char *first_operand1,char *second_operand2,m_line2 *mach_instruc2)
{
   char num_r1[2]={'x','x'};/* used to store the number of first register */
   char num_r2[2]={'y','y'};/* used to store the number of second register */
   int first_bracket=0; /* used to store the index of the first bracket,if adrresing is of type index */
   /* if second_operand2 is null then insert into second_operand2
      the value of first_operand1 */
   if(second_operand2==NULL)
   {
      second_operand2=(char*)calloc(strlen(first_operand1), sizeof(char));
      strcpy(second_operand2,first_operand1);
      first_operand1=NULL;
   }
   /* if there is no operand ,make the target and
      source address equal to zero */
   if(source_addr1==NoOperand)
      source_addr1=0;
   if(target_addr2==NoOperand)   
      target_addr2=0;

   /* if source adress is yet unknowen,change 
      the address is index or direct */   
   if(source_addr1==unknowenAddersing  )
   {
      if(strchr( first_operand1, '[' ) && strchr( first_operand1, ']'))
         {
            mach_instruc2->source_addr1=index;
            /* if addressing is equal to idex
               insert the register number into 
               source_register1 */
            /*store the digits digit of the 
            register between the tow bracktes */
               first_bracket=strstr(first_operand1,"[")-first_operand1;
               num_r1[0] =first_operand1[first_bracket+2];/*first digit of number of register */
               num_r1[1]=first_operand1[first_bracket+3];/*second digit of number of register */
               mach_instruc2->source_register1=atoi(num_r1);

         }
      else
      {
               mach_instruc2->source_addr1=direct;
               mach_instruc2->source_register1=0;

      } 
   }
   /* if target adress is yet unknowen,change 
      the address is index or direct */  
   if(target_addr2==unknowenAddersing )
   {
      if(strchr( second_operand2, '[' ) && strchr( second_operand2, ']'))
         {
            mach_instruc2->target_addr2=index;
            /* if addressing is equal to idex
               insert the register number into 
               target_tegister2 */
            /*store the digits of the 
            register between the tow bracktes */
               first_bracket=strstr(second_operand2,"[")-second_operand2;
               num_r2[0] =second_operand2[first_bracket+2];/*first digit of number of register */
               num_r2[1]=second_operand2[first_bracket+3];/*second digit of number of register */
               mach_instruc2->target_register2=atoi(num_r2);
         }
      else 
         {
            mach_instruc2->target_addr2=direct;
            mach_instruc2->target_register2=0;
         }
   }


   mach_instruc2->bit_19=0;
   mach_instruc2->A=1;
   mach_instruc2->R=0;
   mach_instruc2->E=0;
   mach_instruc2->funct=identify_funct(type34_str);

   /* if there is source operand then define source_register1 */
   /* define source_register1 */
   if(first_operand1!=NULL && source_addr1==register_direct)
   {
      if(IS_REGISTER(first_operand1))
      {
         /* if first first_operand1 is a register,
            insert into source_register1 it's number */
         num_r1[0] =first_operand1[1];
         num_r1[1]=first_operand1[2];
         mach_instruc2->source_register1=atoi(num_r1);
      }
      else
      {
         mach_instruc2->source_register1=0;
      }

   }
   
   if(first_operand1==NULL)
   {
      mach_instruc2->source_register1=0;
      mach_instruc2->source_addr1=0;
   }



   /* define target_register2 */
   if(second_operand2!=NULL && target_addr2==register_direct)
   {
      if(IS_REGISTER(second_operand2))
      {
         num_r2[0] =second_operand2[1];
         num_r2[1]=second_operand2[2];
         mach_instruc2->target_register2=atoi(num_r2);
      }
       else 
         mach_instruc2->target_register2=0;
   }

  
   
   /* if one of the operands is equal to immediate adderising (0) */
   if(source_addr1==immediate)
      {
         mach_instruc2->source_register1=0;
         mach_instruc2->source_addr1=0;
      }
   if(target_addr2==immediate)
      {
         mach_instruc2->target_register2=0;
         mach_instruc2->target_addr2=0;
         
      }
   if(source_addr1==direct)
   {
         mach_instruc2->source_addr1=direct;
         mach_instruc2->source_register1=0;
   }
   if(target_addr2==direct) 
   {
      mach_instruc2->target_register2=0;
      mach_instruc2->target_addr2=direct;
   }  

   if(source_addr1==index)
   {
            mach_instruc2->source_addr1=index;
         if(strchr( first_operand1, '[' ) && strchr( first_operand1, ']'))
            {
            mach_instruc2->source_addr1=index;
            /* if addressing is equal to idex
               insert the register number into 
               source_register1 */
            /*store the digits digit of the 
            register between the tow bracktes */
               first_bracket=strstr(first_operand1,"[")-first_operand1;
               num_r1[0] =first_operand1[first_bracket+2];/*first digit of number of register */
               num_r1[1]=first_operand1[first_bracket+3];/*second digit of number of register */
               mach_instruc2->source_register1=atoi(num_r1);
          }
          else
         {
               mach_instruc2->source_addr1=direct;
               mach_instruc2->source_register1=0;

         } 



   }
   if(target_addr2==index) 
   {
      mach_instruc2->target_addr2=index;
      if(strchr( second_operand2, '[' ) && strchr( second_operand2, ']'))
         {
            mach_instruc2->target_addr2=index;
            /* if addressing is equal to idex
               insert the register number into 
               target_tegister2 */
            /*store the digits of the 
            register between the tow bracktes */
            
               first_bracket=strstr(second_operand2,"[")-second_operand2;
               num_r2[0] =second_operand2[first_bracket+2];/*first digit of number of register */
               num_r2[1]=second_operand2[first_bracket+3];/*second digit of number of register */
               mach_instruc2->target_register2=atoi(num_r2);
         }
   }  

   if(source_addr1==register_direct)
   {
      mach_instruc2->source_addr1=register_direct;
       if(IS_REGISTER(first_operand1))
      {
         num_r1[0] =second_operand2[1];
         num_r1[1]=second_operand2[2];
         mach_instruc2->source_register1=atoi(num_r1);
      }
      
   }
   if(target_addr2==register_direct) 
   {
      mach_instruc2->target_addr2=register_direct;
       if(IS_REGISTER(second_operand2))
      {
         num_r2[0] =second_operand2[1];
         num_r2[1]=second_operand2[2];
         mach_instruc2->target_register2=atoi(num_r2);
      }
   }
   if(source_addr1==NoOperand)
      mach_instruc2->source_addr1=0;
   if(target_addr2==NoOperand)
      mach_instruc2->target_addr2=0;



}




/* used convert second line of code line to machine line to special base */
char *conv_mach_instruct2(m_line2 *mach_instruc2,int IC_number)
{
    int A_cofficient2=default_value;
    int B_cofficient2=default_value;
    int C_cofficient2=default_value;
    int D_cofficient2=default_value;
    int E_cofficient2=default_value;
    char *code_line2=NULL;/* used to represnt the data line in the ob file */
    char IC_number_str[LABEL_LENGTH];/*store IC_number in string format */
    char finle_line[LABEL_LENGTH]="   Av-Bw-Cx-Dy-Ez";
   int ind_v=strstr(finle_line,"v")-finle_line;/* index v= A-coefficient */  
   int ind_w=strstr(finle_line,"w")-finle_line;/* index w= B-coefficient */
   int ind_x=strstr(finle_line,"x")-finle_line;/* index x= C-coefficient */
   int ind_y=strstr(finle_line,"y")-finle_line;/* index y= D-coefficient */
   int ind_z=strstr(finle_line,"z")-finle_line;/* index z= E-coefficient */
   sprintf(IC_number_str, "%d", IC_number);/* convert IC_number to string format */

   A_cofficient2=(mach_instruc2->E)|(mach_instruc2->R<<1)|(mach_instruc2->A<<2);
   B_cofficient2=mach_instruc2->funct;
   C_cofficient2=(mach_instruc2->source_register1);
   /* in order to build the word for our special base ,we use masking */
   D_cofficient2=(mach_instruc2->source_addr1<<2)|(mach_instruc2->target_register2>>2);
   E_cofficient2=((mach_instruc2->target_register2&3)<<2)|(mach_instruc2->target_addr2);

   finle_line[ind_v]=Hex_conv(A_cofficient2);
   finle_line[ind_w]=Hex_conv(B_cofficient2);
   finle_line[ind_x]=Hex_conv(C_cofficient2);
   finle_line[ind_y]=Hex_conv(D_cofficient2);
   finle_line[ind_z]=Hex_conv(E_cofficient2);

   code_line2 = (char*) malloc(strlen(finle_line)*sizeof(char));

    strcpy(code_line2,finle_line);
    strcat(IC_number_str,code_line2);
    free(code_line2);/* free memory */
    code_line2 = (char*) malloc(strlen(IC_number_str)*sizeof(char));/* create memory with size of IC_number_str & line1*/ 
    strcpy(code_line2,IC_number_str);/* copy IC_number_str&code_line2 to code_line2  */

    return code_line2;


}

/* update the the adress of labels that are of type :.data */
void Update_Data_Adress(labelPtr head,int IC)
{
  {
      while(head)
      {
         if(head->Attributes==data )
         {

               head->address+=IC;
               head->offset=(head->address)%16;
               head->Base=(head->address)-(head->offset);
               if(head->Attributes==external)/* external label gets address of 0 */
                  head->address=0;
         } 

         head=head->next;

      }
  }
}

/* add converted line ob .ob the linked list */
void Add2_MachinCode(MCPtr *hMCPtr, char word2[])
{
   MCPtr p1,p2;
   MCPtr t;

   {
      t= (MCPtr) malloc(sizeof(MachinCode));
      if (!t)
      { 
         printf("\n cannot build list \n");
         exit(0);
      }

      strcpy(t->MachinCode_string, word2); /* // copy word2 to t->data */
 

      p1= *hMCPtr;
      while((p1))
      {
         p2= p1; /* //p1=current,p2=previous */
         p1=p1->next;
      }
   
      if (p1==*hMCPtr)
      {
         *hMCPtr = t;
         t->next=p1;
      }
      else {
         p2->next = t;
         t-> next=p1;
      }

   }

}
/* used to remove [] from operand if AddersingType is equal to index */
char *return_clean_label(char *operand,AddersingType operand_type)
{

   int size_word=strlen(operand);
   char *label;
   int i=0;

   int bracket_ind=default_value;/*   index of the bracket */
   label = (char*) malloc((size_word-1)*sizeof(char));

   bracket_ind=strstr(operand,"[")-operand;
   for(i=0;i<bracket_ind;i++)
      label[i]=operand[i];
   


   return label;


}
/* get the address  from label list */
int get_address(labelPtr head,char label_in[])
{
   int num=default_value;
      while(head)
      {
         if(!strcmp(head->Symbol,label_in)   )
         {
            num=head->address;
         } 
         head=head->next;
      }
   return num;
}