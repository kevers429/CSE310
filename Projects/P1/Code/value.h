#ifndef VALUE_H
#define VALUE_H
#include <cstddef>
#include "defns(3).h"
#include <string>

std::string cvalue(mlb_stats & s, const char* field);
int ivalue(mlb_stats & s, const char* field);
float fvalue(mlb_stats & s, const char* field);

#endif
