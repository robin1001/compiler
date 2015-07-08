#ifndef _TVM_H_
#define _TVM_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unordered_map>

#define DATA_MEM_SIZE 1024
#define CODE_MEM_SIZE 1024
#define NUM_REGISTERS 8

typedef enum { //tvm operator
	OP_MOV, //mov 
	OP_ST, OP_LD,//load store op
	OP_ADD, OP_SUB, OP_MUL, OP_DVI, //arithmetic op
	OP_POP,OP_PUSH, //stack op
	OP_CMP, //compare op
	OP_JMP, OP_JE, OP_JNE, OP_JG, OP_JL, OP_JGE, OP_JLE //jump op
	OP_HLT// hlt
} TvmOpType;

typedef enum {
	ARG_REG, //add r1, r2, r3
	ARG_CONST, //LDC r1, 300
	ARG_JUMP_ADDR, //jmp l1
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
	Tvm(); 
	void add_instruction(const Instruction &ins) {
		code_mem_[num_ins_++] = ins;	
		assert(num_ins_ < CODE_MEM_SIZE);
	}
	void add_label(std::string label) {
		if (label_map_.find(label) == label_map_.end()) {
			label_map_.insert(std::make_pair(label, num_labels_);	
			num_labels_++;
		}
	}
	void get_label_id(std::string label) {
		assert(label_map_.find(label) != label_map_.end());
		return label_map_[label];
	}
	void set_label_addr(std::string label) {
		assert(label_map_.find(label) != label_map_.end());
		label_addr_.insert(std::make_pair(label_map_[label], num_ins_+1));
	}
protected:
	int regs_[NUM_REGISTERS];
	int pc_; //program counter
	int sp_; //stack pointer
	int flag_; //compare flags
	Instruction code_mem_[CODE_MEM_SIZE];
	int data_mem_[DATA_MEM_SIZE];	
	int num_ins_; 
	//TODO symbol table
	int num_labels_,
	std::unordered_map<std::string, int> label_map_, //map label to int
	std::unordered_map<int, int> label_addr_, //label addr
};

#endif
