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
  for(int i = 0; i < numYears; i++) { // parse each year of stats
    cin >> year >> numTeams;
    mlb_stats* tmp = new mlb_stats[numTeams];
    for(int j = 0; j < numTeams; j++) { // parse stat data for each team into an array of mlb_stats
      cin.ignore(10,'\n'); //ignore newline on the input stream
      cin.getline(tmp[j].Team, 50, '\t');
      cin >> tmp[j].League >> tmp[j].G >> tmp[j].AB >> tmp[j].R >> tmp[j].H >> tmp[j].B2 >> tmp[j].B3 >> tmp[j].HR >> tmp[j].RBI;
      cin >> tmp[j].BB >> tmp[j].SO >> tmp[j].SB >> tmp[j].CS  >> tmp[j].AVG >> tmp[j].OBP >> tmp[j].SLG >> tmp[j].OPS;
    }
    all_stats[i].year = year;
    all_stats[i].no_teams = numTeams;
    all_stats[i].stats = tmp;
  }
  cin >> numCommands;
  for(int j = 0; j < numCommands; j++) { // parse each command
    cin >> commandName;
    if(strcmp(commandName, "isort") == 0 || strcmp(commandName, "msort") == 0) { // let's sort
      mlb_stats* sorted; // array to store the sorted version of the stats
      if((cin >> ws).peek() != 'r') { //peek to see if a range is upcoming
        cin >> year >> field >> order;
        startYear = endYear = year;
      } else {
        cin.ignore(6); // ignore range from input stream
        cin >> startYear >> endYear >> field >> order;
      }
      try{
        int first = findIndexOfYear(startYear, all_stats); // see if start-year index is valid
        int last = findIndexOfYear(endYear, all_stats); // see if end-year index is valid
        for(int i = 0; i <= numYears; i++) { // process all indexs between first and last
          if(all_stats[i].year >= startYear && all_stats[i].year <= endYear) {
            if(strcmp(commandName, "isort") == 0)
              sorted = isort(all_stats[i].stats, all_stats[i].no_teams, order, field);
            else // not isort so must be msort
              sorted = msort(all_stats[i].stats, all_stats[i].no_teams, order, field);
            if(first != last) // it must be a range input so display year for clarity
              cout << all_stats[i].year << endl;
            printStats(sorted, all_stats[i].no_teams, field);
          }
        }
      }
      catch(const exception & ex) {
        cerr << ex.what() << endl; // if something went wrong, say so
      }
    }
    else if(strcmp(commandName, "ifind") == 0 || strcmp(commandName, "mfind") == 0) { // let's find
      cin >> year >> field >> select;
      try {
        int i = findIndexOfYear(year, all_stats);
        string sortType(commandName);
        find(all_stats[i].stats, all_stats[i].no_teams, field, select, commandName);
      }
      catch(const exception & ex) {
        cerr << ex.what() << endl; // if something went wrong, say so
      }
    }
    cout << endl;
  }
  return 0;
}

int findIndexOfYear(int year, annual_stats* all_stats) { // returns index of year in array of anual stats
  int i = 0;
  while(all_stats[i].year != year && i < numYears - 1)
    i++;
  if(all_stats[i].year != year) // not found, throw error
    throw runtime_error("Error: no such year");
  return i;
}
