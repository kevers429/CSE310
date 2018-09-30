#ifndef SORTS_H
#define SORTS_H
#include <cstddef>
#include "compare.h"

mlb_stats* isort(mlb_stats* arr, int n, const char* order, const char* field);
mlb_stats* msort(mlb_stats* arr, int n, const char* order, const char* field);
mlb_stats* mergeSort(mlb_stats* arr, int lo, int hi, const char* order, const char* field);
void merge(mlb_stats* arr, int lo, int mid, int hi, const char* order, const char* field);

#endif
