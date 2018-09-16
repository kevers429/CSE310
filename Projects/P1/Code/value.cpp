#include "value.h"
#include <string.h>

std::string cvalue(mlb_stats & s, const char* field) {
  if(strcmp(field, "Team") == 0) {
    return std::string(s.Team);
  }
  else if(strcmp(field, "League") == 0) {
    return std::string(s.League);
  }
}

int ivalue(mlb_stats & s, const char* field) {
  if(strcmp(field, "G") == 0) {
    return s.G;
  }
  else if(strcmp(field, "AB") == 0) {
    return s.AB;
  }
  else if(strcmp(field, "R") == 0) {
    return s.R;
  }
  else if(strcmp(field, "H") == 0) {
    return s.H;
  }
  else if(strcmp(field, "B2") == 0) {
    return s.B2;
  }
  else if(strcmp(field, "B3") == 0) {
    return s.B3;
  }
  else if(strcmp(field, "HR") == 0) {
    return s.HR;
  }
  else if(strcmp(field, "RBI") == 0) {
    return s.RBI;
  }
  else if(strcmp(field, "BB") == 0) {
    return s.BB;
  }
  else if(strcmp(field, "SO") == 0) {
    return s.SO;
  }
  else if(strcmp(field, "SB") == 0) {
    return s.SB;
  }
  else if(strcmp(field, "CS") == 0) {
    return s.CS;
  }
}

float fvalue(mlb_stats & s, const char* field) {
  if(strcmp(field, "AVG") == 0) {
    return s.AVG;
  }
  else if(strcmp(field, "OBP") == 0) {
    return s.OBP;
  }
  else if(strcmp(field, "SLG") == 0) {
    return s.SLG;
  }
  else if(strcmp(field, "OPS") == 0) {
    return s.OPS;
  }
}
