#ifndef COMPARE_H
#define COMPARE_H
#include <cstddef>
#include "value.hpp"

int compare(mlb_stats s1, mlb_stats s2, const char* field) {
  if(field == "Team") {
    if(s1.Team > s2.Team)
      return 1;
    else if(s1.Team < s2.Team)
      return -1;
    else
      return 0;
  }
  else if(field == "League") {
    if(s1.League > s2.League)
      return 1;
    else if(s1.League < s2.League)
      return -1;
    else
      return 0;
  }
  else if(value(s1, field) > value(s2, field))
    return 1;
  else if(value(s1, field) < value(s2, field))
    return -1;
  else
    return 0;
}

#endif
