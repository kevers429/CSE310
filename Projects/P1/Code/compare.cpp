#include "compare.h"

int compare(mlb_stats & s1, mlb_stats & s2, const char* field) {
  if(strcmp(field, "Team") == 0 || strcmp(field, "League") == 0) {
    if(cvalue(s1, field) > cvalue(s2, field))
      return 1;
    else if(cvalue(s1, field) < cvalue(s2, field))
      return -1;
    else
      return 0;
  }
  else if(strcmp(field, "AVG") == 0 || strcmp(field, "OBP") == 0 || strcmp(field, "SLG") == 0 || strcmp(field, "OPS") == 0) {
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
