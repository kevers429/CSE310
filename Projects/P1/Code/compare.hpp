#ifndef COMPARE_H
#define COMPARE_H
#include <cstddef>
#include "value.hpp"

int compare(mlb_stats s1, mlb_stats s2, const char* field) {
  if(value(s1, field) > value(s2, field))
    return 1;
  else if(value(s1, field) < value(s2, field))
    return -1;
  else
    return 0;
}

#endif
