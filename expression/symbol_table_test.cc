#include <stdio.h>

#include "node.h"
#include "parser.h"

int main() {
	Node *node = statements();
	g_symble_table.print_symble_table();
	return 0;
}
