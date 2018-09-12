#ifndef SORTS_H
#define SORTS_H
#include <cstddef>
#include "defns(3).h"
#include "compare.h"
#include "isort.cpp"

mlb_stats* isort(mlb_stats* arr, int n, char* order, char* focusField);


#endif
