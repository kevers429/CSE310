//Kevin Shannon

#include <iostream>
#include "sorts.h"
#include "find.hpp"
using namespace std;

int year;
int numYears;
int numTeams;
int numCommands;
int index;
char* commandName;
char* field;
char* order;
annual_stats* all_stats;

int main() {
  cin >> numYears;
  for(int i = 0; i < numYears; i++) {
    cin >> year >> numTeams;
    mlb_stats* tmp;
    for(int j = 0; j < numTeams; j++) {
      cin >> tmp[j].Team >> tmp[j].League >> tmp[j].G >> tmp[j].AB >> tmp[j].R >> tmp[j].H >> tmp[j].B2 >> tmp[j].B3 >> tmp[j].HR;
      cin >> tmp[j].RBI >> tmp[j].BB >> tmp[j].SO >> tmp[j].SB >> tmp[j].CS  >> tmp[j].AVG >> tmp[j].OBP >> tmp[j].SLG >> tmp[j].OPS;
    }
    all_stats[i] = annual_stats{year, numTeams, tmp};
  }

  cin >> numCommands >> commandName;
  if(commandName == "isort") {
    cin >> year;
    while(all_stats[index].year != year) {
      index++;
    }
    cin >> field >> order;
    isort(all_stats[index].stats, all_stats[index].no_teams, order, field);
  }

  return 0;
}
