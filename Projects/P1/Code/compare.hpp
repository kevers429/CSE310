#ifndef COMPARE_H
#define COMPARE_H
#include <cstddef>

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
  else if(field == "G") {
    if(s1.G > s2.G)
      return 1;
    else if(s1.G < s2.G)
      return -1;
    else
      return 0;
  }
  else if(field == "AB") {
    if(s1.AB > s2.AB)
      return 1;
    else if(s1.AB < s2.AB)
      return -1;
    else
      return 0;
  }
  else if(field == "R") {
    if(s1.R > s2.R)
      return 1;
    else if(s1.R < s2.R)
      return -1;
    else
      return 0;
  }
  else if(field == "H") {
    if(s1.H > s2.H)
      return 1;
    else if(s1.H < s2.H)
      return -1;
    else
      return 0;
  }
  else if(field == "B2") {
    if(s1.B2 > s2.B2)
      return 1;
    else if(s1.B2 < s2.B2)
      return -1;
    else
      return 0;
  }
  else if(field == "B3") {
    if(s1.B3 > s2.B3)
      return 1;
    else if(s1.B3 < s2.B3)
      return -1;
    else
      return 0;
  }
  else if(field == "HR") {
    if(s1.HR > s2.HR)
      return 1;
    else if(s1.HR < s2.HR)
      return -1;
    else
      return 0;
  }
  else if(field == "RBI") {
    if(s1.RBI > s2.RBI)
      return 1;
    else if(s1.RBI < s2.RBI)
      return -1;
    else
      return 0;
  }
  else if(field == "BB") {
    if(s1.BB > s2.BB)
      return 1;
    else if(s1.BB < s2.BB)
      return -1;
    else
      return 0;
  }
  else if(field == "SO") {
    if(s1.SO > s2.SO)
      return 1;
    else if(s1.SO < s2.SO)
      return -1;
    else
      return 0;
  }
  else if(field == "SB") {
    if(s1.SB > s2.SB)
      return 1;
    else if(s1.SB < s2.SB)
      return -1;
    else
      return 0;
  }
  else if(field == "CS") {
    if(s1.CS > s2.CS)
      return 1;
    else if(s1.CS < s2.CS)
      return -1;
    else
      return 0;
  }
  else if(field == "AVG") {
    if(s1.AVG > s2.AVG)
      return 1;
    else if(s1.AVG < s2.AVG)
      return -1;
    else
      return 0;
  }
  else if(field == "OBP") {
    if(s1.OBP > s2.OBP)
      return 1;
    else if(s1.OBP < s2.OBP)
      return -1;
    else
      return 0;
  }
  else if(field == "SLG") {
    if(s1.SLG > s2.SLG)
      return 1;
    else if(s1.SLG < s2.SLG)
      return -1;
    else
      return 0;
  }
  else if(field == "OPS") {
    if(s1.OPS > s2.OPS)
      return 1;
    else if(s1.OPS < s2.OPS)
      return -1;
    else
      return 0;
  }
}

#endif
