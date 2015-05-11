#ifndef SCAN_H_
#define SCAN_H_

#include <string>

#include "global.h"

extern std::string g_token;
extern double g_number;
extern int g_token_type;

extern TokenType get_token();

#endif
