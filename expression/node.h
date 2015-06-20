#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <vector>
#include <string>
#include <sstream>

#include "global.h"
#include "lexer.h"

typedef enum {
	K_NUMBER,
	K_OP,
	K_ID,
	K_ASSIGN,
	K_STMTS
}NodeType;



class Node {
public:
    Node(NodeType type): type_(type) {}
    virtual NodeType type() const { return type_; }
protected:
    NodeType type_;
};

class NumberNode: public Node {
public:
    NumberNode(int value): Node(K_NUMBER), value_(value) {}
protected:
    int value_;
};

class OpNode: public Node {
public:
    OpNode(TokenType op, Node *node1, Node *node2): Node(K_OP), 
		op_(op), node1_(node1), node2_(node2) {
		assert(ADD == op_ || MINUS == op_ || MULTI == op_ || DEVI == op_);
    }
protected:
    Node *node1_, *node2_;
	TokenType op_;
};


class IdNode: public Node {
public:
    IdNode(std::string value): Node(K_ID), value_(value) {}
protected:
   std::string value_; 
};

class AssignNode: public Node {
public:
    AssignNode(Node *id, Node *e): Node(K_ASSIGN), id_node_(id), expr_node_(e)  {}
protected:
    Node *id_node_;
    Node *expr_node_;
};

class StmtsNode: public Node {
public:
	StmtsNode(): Node(K_STMTS) {}
	void add_node(Node *node) {
		node_vec_.push_back(node);
	}
protected:
	std::vector<Node *> node_vec_;
};


#endif
