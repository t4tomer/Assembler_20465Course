
/* final version of MAMAN 14- TOMER POLSKY 204512834 */ 

/*
	This file contains definitions of types and structures that are being used in the program.
*/
#ifndef STRUCTS_H

#define STRUCTS_H

#include "assembler.h"


/* Defining a boolean type (it doesn't exist in ANSI C) */
typedef enum {FALSE, TRUE} boolean; 
/* used as deafault values for all structs  */
typedef enum {default_value} Default_Values;

/* typedef enum{external,code,entry,data} AttributesType; */
typedef enum{data,string,entry,external,code,unknowenAttribute} AttributesType;

/* legal names of instructions //? original form */
typedef enum{mov,cmp,add,sub,lea,clr,not,inc,dec,jmp,bne,jsr,red,prn,rts,stop,WrongInstruction,NotInstruction}InstructionName;

/* adderssing modes */
typedef enum{immediate,direct,index,register_direct,unknowenAddersing,NoOperand}AddersingType;



/**-- global variables --**/
char line[LINE_LENGTH];/* This string will contain each line at a time(for all files) */
char *token; /* used to store the token of each line */
AddersingType target_addr2;/* used to store the type of the second operand after op code */
AddersingType source_addr1;/* used to store the type of the first operand after op code */



/*struct that is used store the data of first line of code line */
typedef struct m_line1
{
  unsigned int opcode:16;
  unsigned int E:1;
  unsigned int R:1;
  unsigned int A:1;
  unsigned int bit_19:1;

}m_line1;


/*struct that is used store the data of first line of code line */

typedef struct m_line2
{
  unsigned int bit_19:1;/*bit 19 */
  unsigned int A:1;/*bit 18 */
  unsigned int R:1;/*bit 17 */
  unsigned int E:1;/*bit 16 */
  unsigned int funct:4;/* 12 to 15 bits */
  unsigned int source_register1:4;/* 8 to 11 bits */
  unsigned int source_addr1:2;/* 6 to 7 bits */
  unsigned int target_register2:4;/* 2 to 5 bits */
  unsigned int target_addr2:2;/* 0 to 1 bits */
} m_line2;






/*  //?Define the linked lists */

/* Defining linked list of labels and a pointer to that list-used for the symbol list */

/*Setting the pointer for the symbol list */
typedef struct structLabels * labelPtr;

/*Seeting the linked list of labels */
typedef struct structLabels {
	char Symbol[LABEL_LENGTH]; /* the name of the label(Symbol)-1 colom */
	int address; /* the address of the label(Value)-2 colom */
	int Base; /* used to stored Base address-3 colom */
	int offset; /* used to save the offset-4 colom */
	AttributesType Attributes; /* used to save the attributes-5 colom */
	boolean entry; /* used to store true if entry is true else false */
	labelPtr next; /* a pointer to the next label in the list */
} Labels;





/*Setting the pointer for the MachinCode list */
typedef struct MachinCode * MCPtr;

/*Seeting the linked list of labels */
typedef struct MachinCode {
	char MachinCode_string[LABEL_LENGTH]; /* the machine line */
	MCPtr next; /* a pointer to the next machine line in the list */
} MachinCode;




/*Defining linked list of labels and a pointer that is used for storing the lines between macro and endm*/

/*Setting the pointer for the macro linked list */
typedef struct structMacroLine * MacroLinePtr;

/*Seeting the linked list of macro lines */
typedef struct structMacroLine {
	char macro_name[LABEL_LENGTH]; /* keep the macro name  */
	char macro_line[LABEL_LENGTH]; /* keep the macro line */
    int macro_line_num;/* keep the line number of the macro in the original file */
	MacroLinePtr next; /* a pointer to the next label in the list */
} MacroLine;

/*--------//! used to save data from type .data */ 
typedef struct node * ptr;
typedef struct node {
  char data[LABEL_LENGTH];/*data of the label */
  int data_Size; /* used to store the size of the label including the colon */
  ptr next;
} item;

#endif
