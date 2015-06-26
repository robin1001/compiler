#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "global.h"
#include "lexer.h"
#include "node.h"
#include "symbol_table.h"

SymbolTable g_symble_table;

std::string token_map(TokenType expect_type) {
	switch (expect_type) {
		case ID: return "ID";
		case NUMBER: return "NUMBER";
		case ASSIGN: return "=";
		case ADD: return "+";
		case MINUS: return "-";
		case MULTI: return "*";
		case DEVI: return "/";
		case LEFT_PAREN: return "(";
		case RIGHT_PAREN: return ")";
		case SEMICOLON: return ";";
		default: return "unexpected";
	}
}

void match(TokenType expect_type) {
	if (g_token_type == expect_type) {
		//printf("%s\t%s\n", token_map(expect_type).c_str(), g_token.c_str());
		g_token_type = get_token();
	}
    else {
		printf("syntax error: expected %s, but get %s\n", token_map(expect_type).c_str(), g_token.c_str());
		exit(-1);
    }
}

void syntax_error(std::string error_msg) {
	printf("%s\n", error_msg.c_str());
	exit(-1);
}


Node *expr(); 
Node *term(); 
Node *factor();
Node *assign();
Node *statements();

Node *statements() {
	g_token_type = get_token();	
	StmtsNode *node = new StmtsNode;	
    while (g_token_type != EOI) {
        Node *n = assign();
		node->add_node(n);
    }
	return static_cast<Node *>(node);
}

Node *assign() {
	std::string id = g_token;
    match(ID);
    Node *id_node = new IdNode(id); 
	//add to symbol_table
	g_symble_table.put(id);
    match(ASSIGN);
    Node *expr_node = expr();
    match(SEMICOLON);
    return new AssignNode(id_node, expr_node);
}

Node *expr() {
    Node *node = term();
    while (ADD == g_token_type || MINUS == g_token_type) {
        TokenType op = g_token_type;
		match(op);
        Node *node2 = term();
        node = new OpNode(op, node, node2);
    }
    return node;
}

Node *term() {
    Node *node = factor();
    while (MULTI == g_token_type || DEVI == g_token_type) {
        TokenType op = g_token_type;
		match(op);
        Node *node2 = factor();
        node = new OpNode(op, node, node2);
    }
    return node;
}

Node *factor() {
	Node * node;
	switch(g_token_type) {
		case NUMBER:
			{
				int val = atoi(g_token.c_str());
				match(NUMBER);
				node = new NumberNode(val);
			}
			break;
		case ID:
			{
				std::string id = g_token;
    			match(ID);
    			node = new IdNode(id); 
				//add to symbol_table
				g_symble_table.put(id);
			}
			break;
		case LEFT_PAREN: 
			match(LEFT_PAREN);
 	   		node = expr();
 	   		match(RIGHT_PAREN);
			break;
		default:
			std::stringstream ss;
			ss << "syntax error: unexpected token " << g_token;
			syntax_error(ss.str());
			break;
	}
	return node;
}	


