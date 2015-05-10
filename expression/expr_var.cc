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
    ID = - 3,
    UNKONWN= -4
};


static std::string g_token;
static double g_number;

static int get_token() {
    static int last_char = ' ';
    //black tab
    while (' ' == last_char) last_char = getchar();
    //eof
	if (last_char == EOF) return EOI;
    //id
    if (isalpha(last_char)) {
        stringstream ss;
        do {
            ss << last_char;
            last_char =  getchar();
        }while (isalpha(last_char));
        g_token = ss.str();
        return ID;
    }
	//number
	if (isdigit(last_char)) {
        string num_str;
		do{
			num_str += last_char;
			last_char = getchar();
		}while (isdigit(last_char) || last_char == '.');//bug 
		g_number = strtod(num_str.c_str(), 0);
		return NUMBER;
	}
	
	int cur_char = last_char;
	last_char = getchar();
	return cur_char;
}

static int g_token_type;
void error_msg(const string &msg) {
    printf("%s\n", msg.c_str());
    exit(-1);
}

void match(int token_type) {
    if (g_token_type != token_type) {
        stringstream ss;
        ss << "syntax error expected " << static_cast<char>(token_type) << endl;
        error_msg(ss.str());
    }
}

int next_token() {
    g_token_type = get_token();
    if (NUMBER == g_token_type) 
        printf("%lf\n", g_number);
    if (ID == g_token_type) 
        printf("%s\n", g_token.c_str());
    else
        printf("%c\n", g_token_type);
}

class Node {
public:
    Node(int type): type_(type) {}
    virtual string to_string() const {}
    virtual void emit() const {}
    int type() const { return type_; }
protected:
    int type_;
};

class NumberNode: public Node {
public:
    NumberNode(int type, double value): Node(type), value_(value) {}
    virtual string to_string() const {
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
        tid_ = s_count_++;
    }
    virtual string to_string() const {
        stringstream ss;
        ss << "t" << tid_; 
        return ss.str();
    }
    void emit() const { 
        node1_->emit();
        node2_->emit();
        //cout << this->to_string() << " =  " << node1_.to_string() << " " << type_ << " " << node2_.to_string() << endl;
        printf("%s = %s %c %s\n", this->to_string().c_str(), node1_->to_string().c_str(), type_, node2_->to_string().c_str());
    }
protected:
    static int s_count_;
    Node *node1_, *node2_;
    int tid_;
};
int OpNode::s_count_ = 0;

class IdNode: public Node {
public:
    IdNode(int type, string value): Node(type), value_(value) {}
    string to_string() const{
        return value_;
    }
private:
    string value_; 
};

class AssignNode: public Node {
public:
    AssignNode(Node *id, Node *e): Node('='), id_node_(id), expr_node_(e)  {}
    void emit() const { 
        expr_node_->emit();
        printf("%s = %s\n", id_node_->to_string().c_str(), expr_node_->to_string().c_str());
    }
private:
    Node *id_node_;
    Node *expr_node_;
};

Node *expr(); 
Node *term(); 
Node *factor();
Node *assign();
Node *statements();

Node *statements() {
    while (g_token_type != EOI) {
        Node *n = assign();
        n->emit();
    }
}

Node *assign() {
    match(ID);
    string id = g_token;
    Node *id_node = new IdNode(ID, id); 
    next_token();
    match('=');
    next_token();
    Node *expr_node = expr();
    match(';');
    next_token();
    return new AssignNode(id_node, expr_node);
}

Node *expr() {
    Node *node = term();
    while ('+' == g_token_type || '-' == g_token_type) {
        char ch = g_token_type;
        next_token();
        Node *node2 = term();
        node = new OpNode(ch, node, node2);
    }
    return node;
}

Node *term() {
    Node *node = factor();
    while ('*' == g_token_type || '/' == g_token_type) {
        char ch = g_token_type;
        next_token();
        Node *node2 = factor();
        node = new OpNode(ch, node, node2);
    }
    return node;
}

Node *factor() {
    if (NUMBER == g_token_type) { //g_number
        next_token();
        return new NumberNode(NUMBER, g_number);
    }
    else if ('(' == g_token_type) {
        next_token(); 
        Node *node = expr();
        match(')');
        next_token();
        return node;
    }
    else {
        error_msg("syntax error, expected number or (");
        return new Node(UNKONWN);
    }
}


void node_unit_test() {
    NumberNode number_node(NUMBER,1);
    assert(number_node.to_string() == "1");
    NumberNode node1(NUMBER, 1.0);
    NumberNode node2(NUMBER, 1.0);
    OpNode node('+', &node1, &node2);
    node.emit();
}



int main() {
    next_token();
    statements();
  //  Node *node = expr();
  //  node->emit();    
	return 0;
}
