#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>

using namespace std;
int main()
{
    unordered_map<string, int> table;
    table["robin1001"] = 24;
    table["susan"] = 23;
    table.insert(make_pair("linzi", 24));
    for (unordered_map<string, int> ::iterator it = table.begin(); it != table.end(); it++) {
        printf("%s\t%d\n", it->first.c_str(), it->second);
    }
    if (table.find("liu") == table.end()) printf("not find liu\n");
    
    return 0;
}
