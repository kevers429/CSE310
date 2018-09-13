#ifndef VALUE_H
#define VALUE_H
#include <cstddef>

float value(mlb_stats s, const char* field) {
  if(field == "G") {
    return s.G;
  }
  else if(field == "AB") {
    return s.AB;
  }
  else if(field == "R") {
    return s.R;
  }
  else if(field == "H") {
    return s.H;
  }
  else if(field == "B2") {
    return s.B2;
  }
  else if(field == "B3") {
    return s.B3;
  }
  else if(field == "HR") {
    return s.HR;
  }
  else if(field == "RBI") {
    return s.RBI;
  }
  else if(field == "BB") {
    return s.BB;
  }
  else if(field == "SO") {
    return s.SO;
  }
  else if(field == "SB") {
    return s.SB;
  }
  else if(field == "CS") {
    return s.CS;
  }
  else if(field == "AVG") {
    return s.AVG;
  }
  else if(field == "OBP") {
    return s.OBP;
  }
  else if(field == "SLG") {
    return s.SLG;
  }
  else if(field == "OPS") {
    return s.OPS;
  }
}

#endif
