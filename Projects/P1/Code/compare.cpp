#include "compare.h"

int compare(mlb_stats & s1, mlb_stats & s2, const char* field) { // returns 0 if equal, -1 if s1 < s2, 1 if s1 > s2
  if(strcmp(field, "Team") == 0 || strcmp(field, "League") == 0) {
    if(cvalue(s1, field) > cvalue(s2, field))
      return 1;
    else if(cvalue(s1, field) < cvalue(s2, field))
      return -1;
    else if(cvalue(s1, field) == cvalue(s2, field)) {
      if(cvalue(s1, "Team") > cvalue(s2, "Team"))
        return 1;
      else if(cvalue(s1, "Team") < cvalue(s2, "Team"))
        return -1;
      else
        return 0;
    }
  }
  else if(strcmp(field, "AVG") == 0 || strcmp(field, "OBP") == 0 || strcmp(field, "SLG") == 0 || strcmp(field, "OPS") == 0) {
    if(fvalue(s1, field) > fvalue(s2, field))
      return 1;
    else if(fvalue(s1, field) < fvalue(s2, field))
      return -1;
    else if(fvalue(s1, field) == fvalue(s2, field)) {
      if(fvalue(s1, "Team") > fvalue(s2, "Team"))
        return 1;
      else if(fvalue(s1, "Team") < fvalue(s2, "Team"))
        return -1;
      else
        return 0;
    }
  }
  else if(strcmp(field, "G") == 0 || strcmp(field, "AB") == 0 || strcmp(field, "R") == 0 || strcmp(field, "H") == 0 ||
          strcmp(field, "B2") == 0 || strcmp(field, "B3") == 0 || strcmp(field, "HR") == 0 || strcmp(field, "RBI") == 0 ||
          strcmp(field, "BB") == 0 || strcmp(field, "SO") == 0 || strcmp(field, "SB") == 0 || strcmp(field, "CS") == 0) {
    if(ivalue(s1, field) > ivalue(s2, field))
      return 1;
    else if(ivalue(s1, field) < ivalue(s2, field))
      return -1;
    else if(ivalue(s1, field) == ivalue(s2, field)) {
      if(ivalue(s1, "Team") > ivalue(s2, "Team"))
        return 1;
      else if(ivalue(s1, "Team") < ivalue(s2, "Team"))
        return -1;
      else
        return 0;
    }
  }
  else
    throw std::runtime_error("Error: no such field");
}
