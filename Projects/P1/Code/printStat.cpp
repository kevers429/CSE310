#include "printStat.h"

void printStat(mlb_stats & s, const char* field) {
  if(strcmp(field, "Team") == 0 || strcmp(field, "League") == 0) {
    std::cout << cvalue(s, "Team") << ", " << cvalue(s, field) << std::endl;
  }
  else if(strcmp(field, "AVG") == 0 || strcmp(field, "OBP") == 0 || strcmp(field, "SLG") == 0 || strcmp(field, "OPS") == 0) {
    std::cout << cvalue(s, "Team") << ", " << fvalue(s, field) << std::endl;
  }
  else {
    std::cout << cvalue(s, "Team") << ", " << ivalue(s, field) << std::endl;
  }
}

void printStats(mlb_stats* s, int n, const char* field) {
  std::cout << "TEAM   |   " << field << std::endl << "------------------" << std::endl;
  for(int i = 0; i < n; i++) {
    printStat(s[i], field);
  }
}
