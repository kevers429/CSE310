#include "compare.h"

int compare(mlb_stats & s1, mlb_stats & s2, const char* field) {
  if(field == "Team" || field == "League") {
    if(cvalue(s1, field) > cvalue(s2, field))
      return 1;
    else if(cvalue(s1, field) < cvalue(s2, field))
      return -1;
    else
      return 0;
  }
  else if(field == "AVG" || field == "OBP" || field == "SLG" || field == "OPS") {
    if(fvalue(s1, field) > fvalue(s2, field))
      return 1;
    else if(fvalue(s1, field) < fvalue(s2, field))
      return -1;
    else
      return 0;
  }
  else {
    if(ivalue(s1, field) > ivalue(s2, field))
      return 1;
    else if(ivalue(s1, field) < ivalue(s2, field))
      return -1;
    else
      return 0;
  }
}
