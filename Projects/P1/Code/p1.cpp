//Kevin Shannon

#include <iostream>
#include "sorts.h"
#include "defns.h"
using namespace std;

int year;
int numYears;
int numTeams;
int numCommands;

int main() {
  cin >> numYears;
  for(int i = 0; i < numYears; i++) {
    cin >> year >> numTeams;
    annual_stats* all_stats;
    for(int j = 0; j < numTeams; j++) {
      mlb_stats tmp;
      cin >> tmp.Team >> tmp.League >> tmp.G >> tmp.AB >> tmp.R >> tmp.H >> tmp.B2 >> tmp.B3 >> tmp.HR;
      cin >> tmp.RBI >> tmp.BB >> tmp.SO >> tmp.SB >> tmp.CS  >> tmp.AVG >> tmp.OBP >> tmp.SLG >> tmp.OPS;
      all_stats[i] = {year, numTeams, tmp};
    }
  }
  
  return 0;
}
