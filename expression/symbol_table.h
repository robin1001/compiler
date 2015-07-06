#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <stdio.h>

#include <string>
#include <unordered_map>

class SymbolTable {
public:
	SymbolTable(): count_(0) {}
	void put(std::string sym) {
		if (table_.find(sym) == table_.end()) {
			table_.insert(make_pair(sym, count_));
			count_++;
		}
	}
	int get(std::string sym) {
		if (table_.find(sym) == table_.end()) 
			return -1;
		return table_[sym];
	}
	void print_symble_table() {
		using namespace std;
		for (unordered_map<string,int>::iterator it = table_.begin(); it != table_.end(); it++) {
        	printf("%s\t%d\n", it->first.c_str(), it->second);
		}
	}
protected:
	std::unordered_map<std::string, int> table_;
	int count_;
};

#endif
