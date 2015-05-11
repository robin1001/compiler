#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "global.h"
#include "lexer.h"
#include "node.h"

std::string expect_token_map(TokenType expect_type) {
	switch (expect_type) {
		case ID: return "ID";
		case NUMBER: return "NUMBER";
		case ASSIGN: return "=";
		case ADD: return "+";
		case MINUS: return "-";
		case MULTI: return "*";
		case DEVI: return "/";
		case SEMI: return ";";
	}
}

void match(TokenType expect_type) {
	using namespace std;
	if (g_token_type == expect_type) 
		g_token_type = get_token();
    else {
		printf("syntax error: expected %s, but got %s\n", expect_token_map(expect_type).c_str(), g_token.c_str());
		exit(-1);
    }
}


Node *expr(); 
Node *term(); 
Node *factor();
Node *assign();
Node *statements();

//Node *statements() {
//    while (g_token_type != EOI) {
//        Node *n = assign();
//        n->emit();
//    }
//}
//
//Node *assign() {
//    match(ID);
//    string id = g_token;
//    Node *id_node = new IdNode(ID, id); 
//    next_token();
//    match('=');
//    next_token();
//    Node *expr_node = expr();
//    match(';');
//    next_token();
//    return new AssignNode(id_node, expr_node);
//}
//
//Node *expr() {
//    Node *node = term();
//    while ('+' == g_token_type || '-' == g_token_type) {
//        char ch = g_token_type;
//        next_token();
//        Node *node2 = term();
//        node = new OpNode(ch, node, node2);
//    }
//    return node;
//}
//
//Node *term() {
//    Node *node = factor();
//    while ('*' == g_token_type || '/' == g_token_type) {
//        char ch = g_token_type;
//        next_token();
//        Node *node2 = factor();
//        node = new OpNode(ch, node, node2);
//    }
//    return node;
//}
//
//Node *factor() {
//    if (NUMBER == g_token_type) { //g_number
//        next_token();
//        return new NumberNode(NUMBER, g_number);
//    }
//    else if ('(' == g_token_type) {
//        next_token(); 
//        Node *node = expr();
//        match(')');
//        next_token();
//        return node;
//    }
//    else {
//        error_msg("syntax error, expected number or (");
//        return new Node(UNKONWN);
//    }
//}
//
//
