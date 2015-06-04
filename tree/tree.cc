#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <vector>

typedef enum {
	UNKNOWN = -2,
	EOI = -1,
	CURELY_LEFT = 0,
	CURELY_RIGHT = 1,
	SQUARE_LEFT = 2,
	SQUARE_RIGHT = 3,
	NUMBER = 4, 
}TokenType;

int g_number;

TokenType scan() {
	char ch = getchar();
	while ('\n' == ch || ch == '\t' || ' ' == ch) ch = getchar();
	switch (ch) {
		case EOF: return EOI;
		case '{': return CURELY_LEFT;
		case '}': return CURELY_RIGHT;
		case '[': return SQUARE_LEFT;
		case ']': return SQUARE_RIGHT;
	}
	if (isdigit(ch)) {
		int num = 0; 
		do {
			num = num * 10 + (ch - '0');
			ch = getchar();
		} while (isdigit(ch));
		g_number = num;
		ungetc(ch, stdin);
		return NUMBER;
	}
	printf("unknown character %c", ch);
	exit(-1);
	return UNKNOWN;
}

struct Node {
	std::vector<int> iterms;
	std::vector<Node *> childs;
	void print() {
		for (int i = 0; i < iterms.size(); i++) {
			printf("%d ", iterms[i]);
		}
		printf("\n");
		for (int i = 0; i < childs.size(); i++) {
			childs[i]->print();	
		}
	}
};


TokenType g_token;

void match(TokenType type) {
	if (type == g_token) g_token = scan();
	else {
		printf("syntax error, expected %d\n", type);	
		exit(-1);
	}
}

Node *node() {
	Node * n = new Node;
	match(CURELY_LEFT);	
	match(SQUARE_LEFT);
	while(NUMBER == g_token) {
		n->iterms.push_back(g_number);
		match(NUMBER);
	}
	match(SQUARE_RIGHT);
	while (CURELY_LEFT == g_token) {
		Node *child = node();		
		n->childs.push_back(child);
	}
	match(CURELY_RIGHT);
	return n;
}


void test_scan() {
	TokenType token;
	token = scan();
	while (token >= 0) {
		if (NUMBER == token) 
			printf("%d\n", g_number);
		token = scan();
	}
}

int main(int argc, char *argv[]) {
	g_token = scan();			
	Node * tree = node();
	tree->print();
	return 0;
}

