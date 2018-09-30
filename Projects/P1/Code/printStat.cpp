#include "printStat.h"
#include <iomanip>

void printStat(mlb_stats & s, const char* field) { // prints a single stat
  if(strcmp(field, "Team") == 0 || strcmp(field, "League") == 0) {
    std::cout << std::setw(30) << std::left << cvalue(s, "Team") << cvalue(s, field) << std::endl;
  }
  else if(strcmp(field, "AVG") == 0 || strcmp(field, "OBP") == 0 || strcmp(field, "SLG") == 0 || strcmp(field, "OPS") == 0) {
    std::cout << std::setw(30) << std::left << cvalue(s, "Team") << fvalue(s, field) << std::endl;
  }
  else {
    std::cout << std::setw(30) << std::left << cvalue(s, "Team") << ivalue(s, field) << std::endl;
  }
}

void printStats(mlb_stats* s, int n, const char* field) { // prints all stats up to size n
  std::cout << std::setw(25) << std::left << "Team" << std::setw(5) << std::left << "|"  << field << std::endl << std::setfill('-') << std::setw(35) << "-" << std::setfill(' ') << std::endl;
  for(int i = 0; i < n; i++) {
    printStat(s[i], field);
  }
  std::cout << std::endl;
}
