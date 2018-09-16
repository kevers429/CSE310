#ifndef PRINTSTAT_H
#define PRINTSTAT_H
#include <cstddef>
#include <iostream>
#include "value.h"
#include <string.h>

void printStat(mlb_stats & s, const char* field);
void printStats(mlb_stats* s, int n, const char* field);

#endif
