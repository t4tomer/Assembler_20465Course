
/* this file saves the declaration of the functions that are saved in utils.c */
#ifndef UTILS_H

#define UTILS_H
#include "structs.h"
/* declaration of all the files of project */
void pre_Assembler(FILE * ptr_file,int file_counter,char input_file_name_as [],char input_file_orginal []);
void first_pass(FILE *fp1,char input_file_orginal[]);
void second_pass(FILE *fp2,labelPtr head,char first_line_ob[],char input_file_orginal[]);
void create_ob(char  *machine_line,labelPtr head,MCPtr head_2,char *first_line_ob,char input_file_orginal[] );
void create_ext_ent(labelPtr head,char input_file_orginal[] );


InstructionName Identify_Instruction ( char *token );

char *skip_space(char *ch);

void printWord(char *token);
ErrorType Label_Warning(labelPtr head,char *word);
void PrintWarningType(ErrorType e); 

/* label functions */

char *RemoveColon(char *word);
boolean IS_DATA (char *word); 
boolean IS_REGISTER(char *token);
boolean Wrong_Register(char *token);
boolean IS_LABEL(char *word);
boolean IS_INDEX(char *token,labelPtr head);
boolean IS_EXTERN(char *word); 
boolean IS_INSTRUCTION_COMMAND(char *token);
boolean IS_CODE (char *first_word, char *second_word);
boolean IS_CODE2 (char *first_word,int instruction);
boolean IS_ENTRY(char *word) ;
char *SaveStringData(char *token );
int *Char_To_Bin(char  *token,int i_str);


/*cheack data words */

boolean Legal_Data(char *token);
AttributesType SORT_OF_DATA(char *token,boolean DataFlag);



/* operand functions */

AddersingType Addersing_Type(char *token,labelPtr head);
void swap_operands(int type34,AddersingType source_addr1,AddersingType target_addr2,AddersingType *source_operand3,AddersingType *destination_operand4);
char *swap_addrs(int type34,char * first_operand1,char *second_operand2);

boolean Number_Of_Operands(int word_counter, int type34);
boolean Legal_Addressing_methods(int type34,AddersingType source_addr1,AddersingType target_addr2);
int Calculate_L_Value_According_Operands(int type34,int IC,AddersingType source_addr1,AddersingType target_addr2);

/* symbole table functions*/

void Update_Data_Adress(labelPtr head,int IC);
void Update_address_Value_For_Code(labelPtr head,int IC,char token[]);

void Add2_SymboleTable(labelPtr *hlabelPtr, char word2[],int address,int base,int offset,AttributesType attributes,boolean entry_value);
void UPdate_SymboleTable(labelPtr h,char word2[]); /*---- used to update the value of the entry Symbol list --*/
void printlist2(labelPtr h);/* used to print the real symbol table */



void Set_SymboleTable(labelPtr *hlabelPtr, char label1[],AttributesType attributes);
void Update_AttributesType(labelPtr hlabelPtr,char label2[],int num,AttributesType Att_type,boolean entry_value);

boolean Compare_SymboleTable(labelPtr head,char word1[],char word2[]);
boolean Compare_SymboleTable_2(labelPtr head,char label1[],char word2[]);
void write_error(int line_num,ErrorType err);

/*functions that are used to print to the assembler */

int identify_opcode(char *type34_str);
int identify_funct(char *type34_str);
void default_values(m_line1 *mach_instruc1,m_line2 *mach_instruc2 );
void build_first_word(char *type34_str,m_line1 *mach_instruc1);
void build_second_word(char *type34_str,AddersingType source_addr1,AddersingType target_addr2,char *first_operand1,char *second_operand2,m_line2 *code_word);
char *conv_mach_instruct1(m_line1 *mach_instruc1,int IC_number );
int get_address(labelPtr head,char label_in[]);
char *conv_base_offset(m_line1 *mach_instruc3, int opcode,int IC_number,boolean EXTERN_FLAG);
char *return_clean_label(char *operand,AddersingType operand_type);
boolean Identify_Label_Extern(labelPtr head,char label1[]);

/* functions that are used for utils2.c */
char *conv_data_instruct(m_line1 *mach_instruc3, int token,int IC_number);
char *conv_mach_instruct2(m_line2 *mach_instruc2,int IC_number);
char Hex_conv(int number);
void Add2_MachinCode(MCPtr *hMCPtr, char word2[]);
char *extract_number( char *token);
char *first_line_of_ob(int data_lines,int code_lines);
void Update_address_External(labelPtr head,int IC,char label1[]);



#endif
