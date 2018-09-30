#ifndef COMPARE_H
#define COMPARE_H
#include <cstddef>
#include <stdexcept>
#include <string.h>
#include "value.h"

int compare(mlb_stats & s1, mlb_stats & s2, const char* field);

#endif
