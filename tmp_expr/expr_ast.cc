#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

enum Token{
    EOI = -1,
    NUMBER = -2,
    UNKONWN= -3
};


static std::string token;
static double number;

static int get_token() {
    static int last_char = ' ';
    //black tab
    while (' ' == last_char) last_char = getchar();
    //eof
	if (last_char == EOF) return EOI;
	//number
	if (isdigit(last_char)) {
        string num_str;
		do {
			num_str += last_char;
			last_char = getchar();
		} while(isdigit(last_char) || last_char == '.');//bug 
		number = strtod(num_str.c_str(), 0);
		return NUMBER;
	}
	
	int cur_char = last_char;
	last_char = getchar();
	return cur_char;
}

static int cur_token;
void error(char* msg) {
    printf("%s\n", msg);
    exit(-1);
}
int next_token() {
    cur_token = get_token();
    if (NUMBER == cur_token) 
        printf("%lf\n", number);
    else
        printf("%c\n", cur_token);
}

class Node {
public:
    Node(int type): type_(type) {}
    virtual string ToString() const {}
    virtual void Emit() const {}
    int GetType() const { return type_; }
protected:
    int type_;
};

class NumberNode: public Node {
public:
    NumberNode(int type, double value): Node(type), value_(value) {}
    virtual string ToString() const {
        stringstream ss;
        ss << value_;
        return ss.str();
    }
private:
    double value_;
};
class OpNode: public Node {
public:
    OpNode(int type, Node *node1, Node *node2): Node(type), node1_(node1), node2_(node2) {
        tid_ = count++;
    }
    virtual string ToString() const {
        stringstream ss;
        ss << "t" << tid_; 
        return ss.str();
    }
    void Emit() const { 
        node1_->Emit();
        node2_->Emit();
        //cout << this->ToString() << " =  " << node1_.ToString() << " " << type_ << " " << node2_.ToString() << endl;
        printf("%s = %s %c %s\n", this->ToString().c_str(), node1_->ToString().c_str(), type_, node2_->ToString().c_str());
    }
protected:
    static int count;
    Node *node1_, *node2_;
    int tid_;
};
int OpNode::count = 0;

Node* expr(); 
Node* term(); 
Node* factor();

Node* expr() {
    Node *node = term();
    while('+' == cur_token || '-' == cur_token) {
        char ch = cur_token;
        next_token();
        Node *node2 = term();
        node = new OpNode(ch, node, node2);
    }
    return node;
}

Node* term() {
    Node *node = factor();
    while('*' == cur_token || '/' == cur_token) {
        char ch = cur_token;
        next_token();
        Node *node2 = factor();
        node = new OpNode(ch, node, node2);
    }
    return node;
}

Node* factor() {
    if(NUMBER == cur_token) { //number
        next_token();
        return new NumberNode(NUMBER, number);
    }
    else if('(' == cur_token) {
        next_token(); 
        Node *node = expr();
        if (')' != cur_token)
            error("expected )");
        next_token();
        return node;
    }
    else {
        error("syntax error, expected number or (");
        return new Node(UNKONWN);
    }
}


void NodeUintTest() {
    NumberNode number_node(NUMBER,1);
    assert(number_node.ToString() == "1");
    NumberNode node1(NUMBER, 1.0);
    NumberNode node2(NUMBER, 1.0);
    OpNode node('+', &node1, &node2);
    node.Emit();
}

int main() {
    //NodeUintTest();
    next_token();
    Node *node = expr();
    node->Emit();    
	return 0;
}
