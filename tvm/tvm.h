#ifndef _TVM_H_
#define _TVM_H_

#include <stdio.h>
#include <stdlib.h>

#define DATA_MEM_SIZE 1024
#define CODE_MEM_SIZE 1024
#define NUM_REGISTERS 8

typedef enum { //tvm operator
	OP_ST, OP_LD, OP_LDC, //load store op
	OP_ADD, OP_SUB, OP_MUL, OP_DVI, //arithmetic op
	OP_POP,OP_PUSH, //stack op
	OP_CMP, //compare op
	OP_JMP, OP_JE, OP_JNE, OP_JG, OP_JL, OP_JGE, OP_JLE //jump op
} TvmOpType;

typedef enum {
	ARG_REG, //add r1, r2, r3
	ARG_CONST, //LDC r1, 300
	ARG_JUMP, //jmp l1
	ARG_MEM //LD r1, [r2]; LD r1, [r2, #4]; LD r1, [r2, r3]
}ArgType;


// 
struct Args {
	Args(ArgType t, int v): arg_type(t), val(v) {}
	ArgType arg_type;
	int val;
};

//instruction eg, add r0, r1, r2; etc
struct Instruction{
	Instruction(TvmOpType t, Args a0, Args a1, Args a2): op_type(t), arg0(a0), 
		arg1(a1), arg2(a2) {}
	TvmOpType op_type;
	Args arg0, arg1, arg2;
};


//tiny virtual machine
class Tvm{ 
public:
	int regs[NUM_REGISTERS];
	int pc; //program counter
	int sp; //stack pointer
	int flag; //compare flags
	Instruction code_mem[CODE_MEM_SIZE];
	int data_mem[DATA_MEM_SIZE];	
	//TODO symbol table
};

#endif
