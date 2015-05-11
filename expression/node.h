#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <sstream>

class Node {
public:
    Node(int type): type_(type) {}
    virtual std::string to_string() const {}
    virtual void emit() const {}
    int type() const { return type_; }
protected:
    int type_;
};

class NumberNode: public Node {
public:
    NumberNode(int type, double value): Node(type), value_(value) {}
    std::string to_string() const {
        std::stringstream ss;
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
    std::string to_string() const {
        std::stringstream ss;
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


class IdNode: public Node {
public:
    IdNode(int type,std::string value): Node(type), value_(value) {}
   std::string to_string() const{
        return value_;
    }
private:
   std::string value_; 
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



#endif
