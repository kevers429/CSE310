#ifndef PRINTSTAT_H
#define PRINTSTAT_H
#include <cstddef>
#include <iostream>

void printStat(mlb_stats s, const char* field){
  std::cout << value(s, "Team") << ", " << value(s,field) << std::endl;
}

#endif
