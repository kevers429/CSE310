//Kevin Shannon

#include <iostream>
#include "value.h"
#include "compare.h"
#include "printStat.h"
#include "sorts.h"
#include "find.h"
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
char* select;
annual_stats* all_stats;

int main() {
  cin >> numYears;
  for(int i = 0; i < numYears; i++) {
    cin >> year >> numTeams;
    mlb_stats* tmp = new mlb_stats[numTeams];
    for(int j = 0; j < numTeams; j++) {
      cin.getline(tmp[j].Team, 50, '\t');
      cin >> tmp[j].League >> tmp[j].G >> tmp[j].AB >> tmp[j].R >> tmp[j].H >> tmp[j].B2 >> tmp[j].B3 >> tmp[j].HR;
      cin >> tmp[j].RBI >> tmp[j].BB >> tmp[j].SO >> tmp[j].SB >> tmp[j].CS  >> tmp[j].AVG >> tmp[j].OBP >> tmp[j].SLG >> tmp[j].OPS;
    }
    all_stats = new annual_stats[numYears];
    all_stats[i].year = year;
    all_stats[i].no_teams = numTeams;
    all_stats[i].stats = tmp;
  }

  cin >> numCommands >> commandName >> ws;
  if(commandName == "isort") {
    if(cin.peek() != 'r') {
      cin >> year >> field >> order;
      int i = 0;
      while(all_stats[i].year != year) {
        i++;
      }
      mlb_stats* sorted = isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
      printStats(sorted, all_stats[i].no_teams, field);
    }
    else {
      cin >> commandName >> startYear >> endYear >> field >> order;
      for(int i = 0; i < numYears; i++) {
        if(all_stats[i].year > startYear && all_stats[i].year < endYear) {
          mlb_stats* sorted = isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
          printStats(sorted, all_stats[i].no_teams, field);
        }
      }
    }
  }
  else if(commandName == "ifind") {
    cin >> year >> field >> select;
    int i = 0;
    while(all_stats[i].year != year) {
      i++;
    }
    find(all_stats[i].stats, all_stats[i].no_teams, field, select, "isort");
  }

  return 0;
}
