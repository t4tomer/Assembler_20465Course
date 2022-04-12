assembler_Final: main.o first_pass.o second_pass.o utils.o utils2.o create_ob.o create_ext_ent.o pre_Assembler.o
	gcc -g -ansi -Wall  -pedantic  main.o first_pass.o second_pass.o pre_Assembler.o utils.o utils2.o create_ob.o create_ext_ent.o -lm -o assembler_Final
main.o: main.c assembler.h structs.h utils.h   
	gcc -c -ansi -Wall  -pedantic main.c -o main.o
first_pass.o: first_pass.c assembler.h structs.h  utils.h  
	gcc -c -ansi -Wall  -pedantic first_pass.c  -o first_pass.o
second_pass.o: second_pass.c assembler.h structs.h  utils.h  
	gcc -c -ansi -Wall  -pedantic second_pass.c  -o second_pass.o
pre_Assembler.o: pre_Assembler.c assembler.h structs.h  utils.h 
	gcc -c -ansi -Wall  -pedantic pre_Assembler.c -o pre_Assembler.o
utils.o: utils.c  assembler.h structs.h  utils.h 
	gcc -c -ansi -Wall  -pedantic utils.c -o utils.o -lm
utils2.o: utils2.c  assembler.h structs.h  utils.h 
	gcc -c -ansi -Wall  -pedantic utils2.c -o utils2.o -lm
create_ob.o: create_ob.c  assembler.h structs.h  utils.h 
	gcc -c -ansi -Wall  -pedantic create_ob.c -o create_ob.o -lm
create_ext_ent.o: create_ext_ent.c  assembler.h structs.h  utils.h 
	gcc -c -ansi -Wall  -pedantic create_ext_ent.c -o create_ext_ent.o -lm
