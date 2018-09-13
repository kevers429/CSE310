//Kevin Shannon

#include <iostream>
#include "sorts.h"
#include "find.hpp"
using namespace std;

int year;
int startYear;
int endYear;
int numYears;
int numTeams;
int numCommands;
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

  cin >> numCommands >> commandName >> ws;
  if(commandName == "isort") {
    if(cin.peek() != 'r') {
      cin >> year >> field >> order;
      int i = 0;
      while(all_stats[i].year != year) {
        i++;
      }
      isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
    }
    else {
      cin >> commandName >> startYear >> endYear >> field >> order;
      for(int i = 0; i < numYears; i++) {
        if(all_stats[i].year > startYear && all_stats[i].year < endYear) {
          isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
        }
      }
    }
  }

  return 0;
}
