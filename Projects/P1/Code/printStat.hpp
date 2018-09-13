#ifndef PRINTSTAT_H
#define PRINTSTAT_H
#include <cstddef>
#include <iostream>

void printStat(mlb_stats s, const char* field) {
  std::cout << value(s, "Team") << ", " << value(s,field) << std::endl;
}

void printStats(mlb_stats* s, int n, const char* field) {
  std::cout << "TEAM   |   " << field << std::endl << "------------------" << std::endl;
  for(int i = 0; i < n; i++) {
    printStat(s[i], field);
  }
}

#endif
