//Kevin Shannon

#include <iostream>
#include <stdexcept>
#include "value.h"
#include "compare.h"
#include "printStat.h"
#include "sorts.h"
#include "find.h"
using namespace std;

int findIndexOfYear(int year, annual_stats* all_stats);

int year, startYear, endYear;
int numYears, numTeams, numCommands;
char* commandName = new char[10];
char* field = new char[8];
char* order = new char[5];
char* select = new char[8];
annual_stats* all_stats;

int main() {
  cin >> numYears;
  all_stats = new annual_stats[numYears];
  for(int i = 0; i < numYears; i++) {
    cin >> year >> numTeams;
    mlb_stats* tmp = new mlb_stats[numTeams];
    for(int j = 0; j < numTeams; j++) {
      cin.ignore(10,'\n');
      cin.getline(tmp[j].Team, 50, '\t');
      cin >> tmp[j].League >> tmp[j].G >> tmp[j].AB >> tmp[j].R >> tmp[j].H >> tmp[j].B2 >> tmp[j].B3 >> tmp[j].HR;
      cin >> tmp[j].RBI >> tmp[j].BB >> tmp[j].SO >> tmp[j].SB >> tmp[j].CS  >> tmp[j].AVG >> tmp[j].OBP >> tmp[j].SLG >> tmp[j].OPS;
    }
    all_stats[i].year = year;
    all_stats[i].no_teams = numTeams;
    all_stats[i].stats = tmp;
  }
  cin >> numCommands;
  for(int j = 0; j < numCommands; j++) {
    cin >> commandName;
    if(strcmp(commandName, "isort") == 0 || strcmp(commandName, "msort") == 0) {
      mlb_stats* sorted;
      if((cin >> ws).peek() != 'r') {
        cin >> year >> field >> order;
        startYear = endYear = year;
      }
      else {
        cin.ignore(6);
        cin >> startYear >> endYear >> field >> order;
      }
      try{
        int first = findIndexOfYear(startYear, all_stats);
        int last = findIndexOfYear(endYear, all_stats);
        for(int i = first; i <= last; i++) {
          if(strcmp(commandName, "isort") == 0)
            sorted = isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
          else
            sorted = msort(all_stats[i].stats, all_stats[i].no_teams, order, field);
          if(first != last)
            cout << all_stats[i].year << endl;
          printStats(sorted, all_stats[i].no_teams, field);
        }
      }
      catch(const exception & ex) {
        cerr << ex.what();
      }
    }
    else if(strcmp(commandName, "ifind") == 0 || strcmp(commandName, "mfind") == 0) {
      cin >> year >> field >> select;
      int i;
      try {
        int i = findIndexOfYear(year, all_stats);
        string sortType(commandName);
        find(all_stats[i].stats, all_stats[i].no_teams, field, select, commandName);
      }
      catch(const exception & ex) {
        cerr << ex.what();
      }
    }
    cout << endl;
  }
  return 0;
}

int findIndexOfYear(int year, annual_stats* all_stats) {
  int i = 0;
  while(all_stats[i].year != year && i < numYears - 1)
    i++;
  if(all_stats[i].year != year)
    throw runtime_error("Error: no such year");
  return i;
}
