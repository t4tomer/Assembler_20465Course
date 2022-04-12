/* this file save all the functions that are used in the project */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "structs.h"
#include "utils.h"
#include "assembler.h"

/* print the type of error */
void write_error(int line_num,ErrorType err)
{
    fprintf(stderr, "ERROR (line %d): ", line_num);

    switch (err)
    {

         case WRONG_ADDERSSING_MODE:
         fprintf(stderr, "wrong addersing mode \n");

         break;

         case LABEL_DOES_NOT_EXIST_IN_SYMBOL_LIST:
         fprintf(stderr, "label does not exist in symbol list \n");

         break;



         case NOT_OK:
         fprintf(stderr, "unrecognized error \n");

         break;


         case ENTRY_TOO_MUCH_LABELS:
         fprintf(stderr, "more then one label after entry \n");

         break;



         case ENTRY_NOT_ENOUGH_LABELS:
         fprintf(stderr, "entry can't be with out labels\n");

         break;



         case TOO_MUCH_STRINGS:
         fprintf(stderr, "too much strings \n");

         break;






          case TOO_MUCH_OPERANDS:
         fprintf(stderr, "too much operands\n");

         break;



          case LABEL_CONSISTS_ONLY_DIGITS:
         fprintf(stderr, "label contains only digits\n");

         break;

         case COLON_NOT_IN_RIGHT_PLACE:
         fprintf(stderr, "colon not in right place\n");

         break;



       case REGISTER_DOES_NOT_EXIST:
         fprintf(stderr, " register does not exist \n");

         break;



       case LABEL_DATA_ALREADY_EXISTS:
         fprintf(stderr, "label allready exists\n");

         break;


      case OK:
         fprintf(stderr, "OK .\n");

         break;
      case LABEL_ALREADY_EXISTS:
         fprintf(stderr, "label already exists.\n");

         break;

      case LABEL_TOO_LONG:
         fprintf(stderr, "label is too long (LABEL_MAX_LENGTH: %d).\n", LABEL_LENGTH);

         break;

      case LABEL_INVALID_FIRST_CHAR:
         fprintf(stderr, "label must start with an alphanumeric character.\n");

         break;

      case LABEL_ONLY_ALPHANUMERIC:
         fprintf(stderr, "label must only contain alphanumeric characters.\n");

         break;

      case LABEL_CANT_BE_COMMAND:
         fprintf(stderr, "label can't have the same name as a command.\n");

         break;

      case LABEL_CANT_BE_REGISTER:
         fprintf(stderr, "label can't have the same name as a register.\n");

         break;

      case LABEL_ONLY:
         fprintf(stderr, "label must be followed by a command or a directive.\n");

         break;

      case DIRECTIVE_NO_PARAMS:
         fprintf(stderr, "directive must have parameters.\n");

         break;

      case DIRECTIVE_INVALID_NUM_PARAMS:
         fprintf(stderr, "illegal number of parameters for a directive.\n");

         break;

      case DATA_COMMAS_IN_A_ROW:
         fprintf(stderr, "incorrect usage of commas in a .data directive.\n");

         break;

      case DATA_EXPECTED_NUM:
         fprintf(stderr, ".data expected a numeric parameter.\n");

         break;

      case DATA_EXPECTED_COMMA_AFTER_NUM:
         fprintf(stderr, ".data expected a comma after a numeric parameter.\n");

         break;

      case DATA_UNEXPECTED_COMMA:
         fprintf(stderr, ".data got an unexpected comma after the last number.\n");

         break;

      case STRING_TOO_MANY_OPERANDS:
         fprintf(stderr, ".string must contain exactly one parameter.\n");

         break;

      case STRING_OPERAND_NOT_VALID:
         fprintf(stderr, ".string operand is invalid.\n");

         break;

      case STRUCT_INVALID_NUM:
         fprintf(stderr, ".struct first parameter must be a number.\n");

         break;

      case STRUCT_EXPECTED_STRING:
         fprintf(stderr, ".struct must have 2 parameters.\n");

         break;

      case STRUCT_INVALID_STRING:
         fprintf(stderr, ".struct second parameter is not a string.\n");

         break;

      case STRUCT_TOO_MANY_OPERANDS:
         fprintf(stderr, ".struct must not have more than 2 operands.\n");

         break;

      case EXPECTED_COMMA_BETWEEN_OPERANDS:
         fprintf(stderr, ".struct must have 2 operands with a comma between them.\n");

         break;

      case EXTERN_NO_LABEL:
         fprintf(stderr, ".extern directive must be followed by a label.\n");

         break;

      case EXTERN_INVALID_LABEL:
         fprintf(stderr, ".extern directive received an invalid label.\n");

         break;

      case EXTERN_TOO_MANY_OPERANDS:
         fprintf(stderr, ".extern must only have one operand that is a label.\n");

         break;

      case COMMAND_NOT_FOUND:
         fprintf(stderr, "invalid command or directive.\n");

         break;

      case COMMAND_UNEXPECTED_CHAR:
         fprintf(stderr, "invalid syntax of a command.\n");

         break;

      case COMMAND_TOO_MANY_OPERANDS:
         fprintf(stderr, "command can't have more than 2 operands.\n");

         break;

      case COMMAND_INVALID_METHOD:
         fprintf(stderr, "operand has invalid addressing method.\n");

         break;

      case COMMAND_INVALID_NUMBER_OF_OPERANDS:
         fprintf(stderr, "number of operands does not match command requirements.\n");

         break;

      case COMMAND_INVALID_OPERANDS_METHODS:
         fprintf(stderr, "operands' addressing methods do not match command requirements.\n");

         break;

      case ENTRY_LABEL_DOES_NOT_EXIST:
         fprintf(stderr, ".entry directive must be followed by an existing label.\n");

         break;

      case ENTRY_CANT_BE_EXTERN:
         fprintf(stderr, ".entry can't apply to a label that was defined as external.\n");

         break;

      case COMMAND_LABEL_DOES_NOT_EXIST:
         fprintf(stderr, "label does not exist.\n");

         break;

      case CANNOT_OPEN_FILE:
         fprintf(stderr, "there was an error while trying to open the requested file.\n");
    }
}




/* update the value of address,base,offset in the symbol table for external labels */
void Update_address_External(labelPtr head,int IC,char label1[])
{
   if(label1!=NULL)
  {
      while(head)
      {
         if( label1!=NULL  && (head->Attributes==external) && !strcmp(head->Symbol, (label1) )   )
         {
            head->address=IC;
         }
         head=head->next;
      }
  }
}

char *first_line_of_ob(int data_lines,int code_lines) 
{
   static char first_line [LABEL_LENGTH];
   char d_l_str[10];/*save the number of data lines in char */
   char c_l_str[10];/* save the number of code lines in char */


   sprintf(c_l_str, "%d", code_lines);
   sprintf(d_l_str, "%d", data_lines);

   strcat(first_line, "   \t\t\t");
   strcat(first_line, c_l_str);
   strcat(first_line, "   ");
   strcat(first_line, d_l_str);



   return first_line;

}


/* cheack if word is legal register */
boolean IS_REGISTER(char *token)
{
   char n_register[2];
   n_register[0] =token[1];
   n_register[1] =token[2];
   
    if(token[0] == 'r'&& (0<=atoi(n_register) && atoi(n_register)<=15))
      return TRUE;
    return FALSE;
           
}

/* return true if  register is nonvalid(larger then 15) */
boolean Wrong_Register(char *token)
{
   /*return true if register does not exist */
   if(token[0]=='r' && !IS_REGISTER(token)) /* if token is not register */         
      return TRUE;
   return FALSE;

}

/* identify type of addressing mode */
 AddersingType Addersing_Type(char *token,labelPtr head)
 {
   
   if(token==NULL)
   {
      /* if there is no operand */
      return NoOperand; /* //! if unknowenAddersing=4 */
   }
    if(token[0]=='#')
      return immediate; /* //! immediate='00'=0 */
   if(Compare_SymboleTable(head,token,token))
    {
       return direct; /* //!direct='01'=1 */
    }
    if(IS_INDEX(token,head))
    {
       return index; /* //!index='10'=2 */
    }
    if(IS_REGISTER(token))
       return register_direct;/* //!register_direct='11'=3 */
    /*if label is not discovered yet return unknowenAddersing */    
    return unknowenAddersing;
 }

 /* used to save the string after .string */
char *SaveStringData(char *token )
{  
   int i=1;
   int j=0;
   int length=strlen(token);
   char *stringData;
   stringData = (char*) malloc((length-1)*sizeof(char));

   for(i=1; i<length-1; i++)
   {
      stringData[j]=token[i];
      j++;
   }
   return stringData;
}


/* used to identify if addersingType is index*/
boolean IS_INDEX(char *token,labelPtr head)
{
   char *string = token;
   char *symbol=NULL;
   char register_1[3];
   char *i1;/* index of [ */
   char *i2;/* index of ] */
   int i;
   int index1;
   int index2;
    i1 = strchr(string, '[');
    i2 = strchr(string, ']');
    index1 = (int)(i1 - string);
    index2 = (int)(i2 - string);  
    if ((index2-index1-1)<=3 && strchr(token,'[')&& strchr(token,']')) 
    {
      symbol = (char*) malloc((index1)*sizeof(char));
       for(i=0;i<3;i++)
         register_1[i]=token[index1+1+i];/* get the register from token */
       if((int)token[index1-1]==0)
         return unknowenAddersing;
      for(i=0;i<index1;i++)      
         symbol[i] =token[i];/*get symbol from token*/
     
      if(Compare_SymboleTable(head,symbol,symbol) && IS_REGISTER(register_1))
      {
         return TRUE; /* //!index='10'=2 */
      }
       if(IS_REGISTER(register_1)==FALSE)
         return FALSE;
    }
   return FALSE;
}

/*used to identify if label is of type code */
boolean IS_CODE (char *first_word,char *second_word)
{
   if(first_word!=NULL && second_word!=NULL)
   {

      if(IS_LABEL(first_word) && IS_INSTRUCTION_COMMAND(second_word))
      {
         return TRUE;
      }
   }
   else if( first_word!=NULL||second_word!=NULL)
         return FALSE;
   return FALSE;
}



/*used to identify if token is legal label */
boolean IS_LABEL(char *word) 
{
    if(strchr(word,':'))/* cheak if ward contais : */
    { 
      long int c1=strstr(word,":")-word-1; /* find index of char be4 colon */
      if(isdigit(word[c1])||isalpha((word[c1]))||islower(word[c1])||isupper(word[c1])) /*cheack if word[i-1]  is digit||letter */
           {            
            return TRUE; 
           }       
    }
   return FALSE;
}

/* used to identify if token is of type .extern */
boolean IS_EXTERN(char *word) 
{

      char extern1[]=".extern";
         if (!strcmp(word,extern1)) 
         {
            return TRUE;
         }
   return FALSE;
}

/* used to identify if token is of type .entry */
boolean IS_ENTRY(char *word) 
{
      char entry1[]=".entry";
         if (!strcmp(word,entry1)) 
         {
            return TRUE;
         }
   return FALSE;
}

 void swap_a(int type34,AddersingType source_addr1,AddersingType target_addr2,AddersingType *source_operand3,AddersingType *destination_operand4)
{
   AddersingType temp1=unknowenAddersing; /* used to save temporary variables */
   
   if(5<=type34 && type34<=13)
      {
       temp1=source_addr1;
       *source_operand3=target_addr2;
       *destination_operand4=temp1;
      }

}

/*used to swap between source operand and target operand for instruction commands that have target operand and not source operand */
 void swap_operands(int type34,AddersingType source_addr1,AddersingType target_addr2,AddersingType *source_operand3,AddersingType *destination_operand4)
{
   AddersingType temp1=unknowenAddersing; /* used to save temporary variables */
   
   if(5<=type34 && type34<=13)
      {
       temp1=source_addr1;
       *source_operand3=target_addr2;
       *destination_operand4=temp1;
      }

}

/* used to identify if the addressing methods are legal as shown in page 34 */
boolean Legal_Addressing_methods(int type34,AddersingType source_addr1,AddersingType target_addr2)
{
   int i=0;
   boolean source_flag =FALSE;
   AddersingType group4[5]={immediate,direct,index,register_direct,unknowenAddersing};
   AddersingType group3[4]={direct,index,register_direct,unknowenAddersing};
   AddersingType group2[3]={direct,index,unknowenAddersing};

   switch(type34)
   {
      case mov: /*blue color */
      case add:
      case sub: 
         {
            for(i=0;i<5;i++)
               if(source_addr1==group4[i])
                  source_flag=TRUE;            
            if(source_flag)
               for(i=0;i<4;i++)
                  if(target_addr2==group3[i])
                     return TRUE;
         }
      break;

      case cmp: /*green color */
         {
            for(i=0;i<5;i++)
               if(source_addr1==group4[i])
                  source_flag=TRUE;            
            if(source_flag)
               for(i=0;i<5;i++)
                  if(target_addr2==group4[i])
                     return TRUE;
         }
      break;

      case lea: /* white color */
         {
            for(i=0;i<4;i++)
               if(source_addr1==group3[i])
                  source_flag=TRUE;            
            if(source_flag)
               for(i=0;i<4;i++)
                  if(target_addr2==group3[i])
                     return TRUE;
         }
      break;

      case clr: /*orange color */
      case not:
      case inc:
      case dec:
         {
            if(source_addr1==NoOperand)
               source_flag=TRUE;
            if(source_flag)
               for(i=0;i<4;i++)
                  if(target_addr2==group3[i])
                     return TRUE;
         }
      break;

      case jmp: /*yellow color */
      case bne:
      case jsr:
         {
            if(source_addr1==NoOperand)
               source_flag=TRUE;
            if(source_flag)
               for(i=0;i<3;i++)
                  if(target_addr2==group2[i])
                     return TRUE;
         }
      break;

      case red: /*white color */
         {
            if(source_addr1==NoOperand)
               source_flag=TRUE;
            if(source_flag)
               for(i=0;i<4;i++)
                  if(target_addr2==group3[i])
                     return TRUE;
         }
      break;

      case prn : /* purple color */
         {
            if(source_addr1==NoOperand)
               source_flag=TRUE;
            if(source_flag)
               for(i=0;i<5;i++)
                  if(target_addr2==group4[i])
                     return TRUE;
         }
      break;

      case rts:/* pink color */
      case stop:
      {
         if(source_addr1==NoOperand)
            source_flag=TRUE;
         if(source_flag)
            if(target_addr2==NoOperand)
               return TRUE;

      }
      break;

   }

      return FALSE;

}



/*used to identify errors for multpliey operands */
boolean Number_Of_Operands(int word_counter, int type34)
{

   switch(type34)
   {
      /* group of commands that get 2 operands */
      case mov:
      case cmp:
      case add:
      case sub:
      case lea:
         if(!(word_counter==3) && type34!=-1)
         {
            return FALSE;
         }
      break;
      /* group of commands that get 1 operand */
      case clr:
      case not:
      case inc:
      case dec:
      case jmp:
      case bne:
      case jsr:
      case red:
      case prn:
         if( !(word_counter==2) && type34!=-1)
         {
            return FALSE;
         }
      break;      
      /* group of commands that does not get any operands */
      case rts:
      case stop:
         if(1<word_counter && type34!=-1)
            return FALSE;
      break;

   }

   return TRUE;
}


/* identify the opcode of the instruction command */
int identify_opcode(char *type34_str)
{
   int opcode=-1;
   if((strstr(type34_str,"mov")-type34_str)==0)
   {  
            opcode=0;
   }
   else if(strstr(type34_str,"cmp")-type34_str==0)
      opcode=1;
   else if(strstr(type34_str,"add")-type34_str==0||strstr(type34_str,"sub")-type34_str==0)
      opcode=2;
   else if(strstr(type34_str,"lea")-type34_str==0)
      opcode=4;
   else if(strstr(type34_str,"clr")-type34_str==0||strstr(type34_str,"not")-type34_str==0||strstr(type34_str,"inc")-type34_str==0||strstr(type34_str,"dec")-type34_str==0)
      opcode=5;
   else if(strstr(type34_str,"jmp")-type34_str==0||strstr(type34_str,"bne")-type34_str==0||strstr(type34_str,"jsr")-type34_str==0)
      opcode=9;
   else if(strstr(type34_str,"red")-type34_str==0)
      opcode=12;
   else if(strstr(type34_str,"prn")-type34_str==0)
      opcode=13;
   else if(strstr(type34_str,"rts")-type34_str==0)
      opcode=14;
   else if(strstr(type34_str,"stop")-type34_str==0)
      opcode=15;
   return opcode;

}

/* identify the funct by the name of the instruction name */
int identify_funct(char *type34_str)
{
   int funct=0;
   
   if(strstr(type34_str,"add")-type34_str==0 ||strstr(type34_str,"clr")-type34_str==0 ||strstr(type34_str,"jmp")-type34_str==0)
      funct=10;
   if(strstr(type34_str,"sub")-type34_str==0 ||strstr(type34_str,"not")-type34_str==0 ||strstr(type34_str,"bne")-type34_str==0)
      funct=11;
   if(strstr(type34_str,"inc")-type34_str==0 )   
      funct=12;
   if(strstr(type34_str,"dec")-type34_str==0 )   
      funct=13;

   return funct;
   
}










/*used to calculate the value of IC  according the value of each operand(for operands 0 to 15) */
int Calculate_L_Value_According_Operands(int type34,int IC,AddersingType source_addr1,AddersingType target_addr2)
{
   
   if(0<=type34 && type34<=13)
   {
      IC=IC+2;
      switch(source_addr1)
      {
         case immediate: /*immdiaite adrresin=00=0 */
         {
            IC++;
         }
         break;

         case direct: /*direct adrresing=01=1 */
         case index: /*index adrresing=10=2 */
         case unknowenAddersing: /* dont know yet the type of adrresing */
         {
            IC=IC+2;
         }
         break;

         case register_direct: /*register adrresing=11=3 */
         {
            IC=IC+0;
         }
         break;

         case NoOperand: /* if there is no operand */
         {
            IC=IC+0;
         }
         break;
      }
      switch(target_addr2)
      {
         case immediate: /*immdiaite adrresin=00=0 */
         {
            IC++;
         }
         break;

         case direct: /*direct adrresing=01=1 */
         case index: /*index adrresing=10=2 */
         case unknowenAddersing: /* dont know yet the type of adrresing */
         {
            IC=IC+2;
         }
         break;

         case register_direct: /*register adrresing=11=3 */
         {
            IC=IC+0;
         }
         break;

         case NoOperand: /*unknowenAddersing */
         {
            IC=IC+0;
         }
         break;
      }

   }
   switch(type34)
      case rts:
      case stop:
      {
         IC++;
      }
   return IC;

}
/* used to decide if instruction name is legal */
boolean IS_INSTRUCTION_COMMAND(char *token)
{
   InstructionName type34=Identify_Instruction ( token );
   if(0<=type34 && type34<=15)
      return TRUE;

   return FALSE;
}


/* identify insturction/command name of token  */
InstructionName Identify_Instruction ( char *token )
{
   InstructionName choice;
     if(strstr(token,"mov")!=NULL)
      { 
         if(strlen(token)==strlen("mov"))
            choice=mov;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"cmp")!=NULL)
      { 
         if(strlen(token)==strlen("cmp"))
            choice=cmp;
         else
            choice=WrongInstruction;
      }
 
   else if(strstr(token,"add")!=NULL)
      { 
         if(strlen(token)==strlen("add"))
            choice=add;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"sub")!=NULL)
      { 
         if(strlen(token)==strlen("sub"))
            choice=sub;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"lea")!=NULL)
      { 
         if(strlen(token)==strlen("lea"))
            choice=lea;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"clr")!=NULL)
      { 
         if(strlen(token)==strlen("clr"))
            choice=clr;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"not")!=NULL)
      { 
         if(strlen(token)==strlen("not"))
            choice=not;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"inc")!=NULL)
      { 
         if(strlen(token)==strlen("inc"))
            choice=inc;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"dec")!=NULL)
      { 
         if(strlen(token)==strlen("dec"))
            choice=dec;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"jmp")!=NULL)
      { 
         if(strlen(token)==strlen("jmp"))
            choice=jmp;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"bne")!=NULL)
      { 
         if(strlen(token)==strlen("bne"))
            choice=bne;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"jsr")!=NULL)
      { 
         if(strlen(token)==strlen("jsr"))
            choice=jsr;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"red")!=NULL)
      { 
         if(strlen(token)==strlen("red"))
            choice=red;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"prn")!=NULL)
      { 
         if(strlen(token)==strlen("prn"))
            choice=prn;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"rts")!=NULL)
      { 
         if(strlen(token)==strlen("rts"))
            choice=rts;
         else
            choice=WrongInstruction;
      }
   else if(strstr(token,"stop")!=NULL)
      { 
         if(strlen(token)==strlen("stop"))
            choice=stop;
         else
            choice=WrongInstruction;
      }
   else
            choice=NotInstruction;/*not instruction */

   return choice;

}

/* used to identify if expression after label is data */
boolean IS_DATA (char *word) 
{

      char string1[]=".string";
      char data1[]=".data";
      if (!strcmp(word,string1)||!strcmp(word,data1)) 
      {
            return TRUE;

      }
   return FALSE;  
}



/*used to sort if data word type is .string or .data */
AttributesType SORT_OF_DATA(char *token,boolean DataFlag)
{
   char string1[]=".string";
   char data1[]=".data";
   if(DataFlag)
   {
      if(!strcmp(token,string1))
         return string;
      else if(!strcmp(token,data1))
         return data;
   }
   return unknowenAttribute;
}

/* used to cheack if each word after .data is a legal number */
boolean Legal_Data(char *token)
{
   
   int i=0;
   for ( i = 0; i<strlen(token); i++)
	   if(isdigit(token[i]))
            return TRUE;

   return FALSE;
}

/* update the value of address,base,offset in the symbol table for code words */
void Update_address_Value_For_Code(labelPtr head,int IC,char label1[])
{

      
   if(label1!=NULL)
  {
      while(head)
      {
         if( label1!=NULL  && (head->Attributes==code)&& !strcmp(head->Symbol, (label1) )   )
         {     
            head->address=IC;
         }
         head=head->next;
      }
  }
}

/* used to check if label is in symbol table and of type .extern */
boolean Identify_Label_Extern(labelPtr head,char label1[])
{
   while(head)
   {
      /*if label!= in the table */
      if( head->Attributes==external && !(strcmp((label1), head->Symbol)) )
      {
         return FALSE;
      }
            head=head->next;
   }
   return TRUE;
}



/* used to check if label is allready exists in the symbol table */
boolean Compare_SymboleTable_2(labelPtr head,char label1[],char word2[])
{
   while(head)
   {
      /*if label!= in the table */
      if( !(strcmp((label1), head->Symbol)) )
      {
         return FALSE;
      }
            head=head->next;
   }
   return TRUE;
}




/* used to compare token to word in  SymboleTable */
boolean Compare_SymboleTable(labelPtr head,char word1[],char word2[])
{

   while(head)
   {

         if(word1!=NULL) /* used to in the adderisng modes for direct addreising & index adderisng */
         {
            if( !(strcmp((word1), head->Symbol)) )  /* if symbol==token */
               {
                  return TRUE;  
               }            
         }
         if(strchr(word1, ':')) /*add word to be label of type data */
         {
            if( !(strcmp((word1), head->Symbol))|| !(strcmp(RemoveColon(word1), head->Symbol))  ) /* if symbol==token */
            {
               return TRUE;  
            }   
         }
         /* cheack if first word is .extern and second word is label */
         if(IS_EXTERN(word1)&& word2!=NULL) 
         {
            if( !(strcmp((word2), head->Symbol))  ) /* if symbol==token */
               {
                  if(head->Attributes!=external)
                  {
                     return TRUE;               
                  }
                  else
                     return FALSE;  
               }   

         }
         /* cheack if first word is .entry and second word is label ,
            if it is true update the entry value of the linked list
             of this label to true */
         if(IS_ENTRY(word1)&& word2!=NULL) 
         {
               if( !(strcmp((word2), head->Symbol)))
                  head->entry = TRUE;
         }
         
         if(IS_CODE(word1,word2) )
         {
               if( !(strcmp((word1), head->Symbol)) )
                {
                  if(head->Attributes!=code)
                  {
                     return TRUE;                 
                  }
                  else
                     return FALSE;  
               }   
         }
                  
      head=head->next;
   }  
   return FALSE;
}

/* set symbol list with out the appropriate attributes type */
void Set_SymboleTable(labelPtr *hlabelPtr, char label1[],AttributesType attributes)
{
   labelPtr p1,p2;
   labelPtr t;


   t= (labelPtr) malloc(sizeof(Labels));
   if (!t)
   { 
      printf("\n cannot build list \n");
      exit(0);
   }
   
   strcpy(t->Symbol,RemoveColon(label1)); /* // copy label1 to t->Symbol */
   t->address=0;
   t->Base=0;
   t->offset=0;
   t->Attributes=attributes;
   t->entry=FALSE;

   p1= *hlabelPtr;
   while((p1))
   {
      p2= p1; /* //p1=current,p2=previous */
      p1=p1->next;
   }
 
   if (p1==*hlabelPtr)
   {
      *hlabelPtr = t;
      t->next=p1;
   }
   else {
      p2->next = t;
      t-> next=p1;
   }
}

/* used to update the attributes type of label to the appropriate */
void Update_AttributesType(labelPtr head,char label2[],int num,AttributesType Att_type,boolean entry_value)
{
   while(head)
   {
      if(!strcmp(head->Symbol,(label2)))
      {
         head->address=num;
         head->Attributes=Att_type;
      }
   }

}





/* add label to symbol table */
void Add2_SymboleTable(labelPtr *hlabelPtr, char word2[],int address,int base,int offset,AttributesType attributes,boolean entry_value)
{
   labelPtr p1,p2;
   labelPtr t;
   {
      t= (labelPtr) malloc(sizeof(Labels));
      if (!t)
      { 
         printf("\n cannot build list \n");
         exit(0);
      }

      strcpy(t->Symbol, word2); /* // copy word2 to t->data */
      t->address=address;
      t->Base=base;
      t->offset=offset;
      t->Attributes=attributes;
      t->entry=entry_value;

      p1= *hlabelPtr;
      while((p1))
      {
         p2= p1; /* //p1=current,p2=previous */
         p1=p1->next;
      }
   
      if (p1==*hlabelPtr)
      {
         *hlabelPtr = t;
         t->next=p1;
      }
      else {
         p2->next = t;
         t-> next=p1;
      }

   }

}

/*used to print the type of error--//? used for testing */
void PrintWarningType(ErrorType e) 
{

   switch(e)
   {
      case LABEL_CONSISTS_ONLY_DIGITS:
         printf("\n LABEL_CONSISTS_ONLY_DIGITS\n ");
         break;
      case COLON_NOT_IN_RIGHT_PLACE:
         printf("\n COLON_NOT_IN_RIGHT_PLACE");
         break;
      case NOT_OK:
         printf("\n NOT_OK");
         break;

      default: printf("\n OK\n ");
   }



}

/* used for testig-print the symbol table*/
void printlist2(labelPtr h)
{
  printf("\n");
  while(h)
  {
    printf("\nSymbol:%s",h->Symbol);
    printf("\naddress:%d",h->address);
    printf("\nBase:%d",h->Base);
    printf("\noffset:%d",h->offset);
      if(h->Attributes==data)
            printf("\nAttributes:data");
      if(h->Attributes==string)
            printf("\nAttributes:string");
      if(h->Attributes==entry)
            printf("\nAttributes:entry");
      if(h->Attributes==external)
            printf("\nAttributes:extern");
      if(h->Attributes==code)
            printf("\nAttributes:code");
      if(h->Attributes==unknowenAttribute)
            printf("\nAttributes:unknowenAttribute");
      if(h->entry==TRUE)
         printf("\nentry:TRUE--> \n");
      else
         printf("\nentry:FALSE--> \n");
    h=h->next;
  }
 printf("*\n");
}

/* used to remove the colon from psoobile label */
char *RemoveColon(char *word) 
{
   int i=0;
   int size_word=strlen(word);
   char *symbol;

   symbol = (char*) malloc((size_word-1)*sizeof(char));
   for(i=0;i<size_word-1;i++)
      symbol[i] = word[i];

   return symbol;
}



/* check if label is valid */
ErrorType Label_Warning(labelPtr head,char *word)
{
   int i=0;
   int length=strlen(word); /*length of the word */

    { 
      int flag1=0;/* used to identify if word made only of letters */
      for(i=0;i<length;i++)
         if(!isalpha((word[i])))/* cheack if word is only alphabetic */        
            flag1++;           
      if(flag1==length-0) 
         return(LABEL_CONSISTS_ONLY_DIGITS);/* if number of digitis is equal to the length of the word ,then the word contains only chars*/
      /* cheack if label is too long */   
      if( LABEL_LENGTH<length)
         return LABEL_TOO_LONG;
      if(length<1)
         return NOT_OK;
      /* cheack if label is instruction name */
      if(IS_INSTRUCTION_COMMAND(RemoveColon(word)) )
      {
         return LABEL_CANT_BE_COMMAND;
      }
      /* cheack if label is register */
      if(IS_REGISTER(RemoveColon(word))) 
         return LABEL_CANT_BE_REGISTER;
       /*check if label allready exists in the label linked list */  
      if(Compare_SymboleTable(head,word,word))
            return LABEL_ALREADY_EXISTS;
    }
   return OK;
}


/* Continue the loop if the character is a whitespace */
char *skip_space(char *ch) 
{   
    if(ch == NULL) return NULL; 
    while (isspace(*ch))
    { 
        ch++;
    }
    return ch;
}






