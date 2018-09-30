//Kevin Shannon
#include "find.h"

void find(mlb_stats* arr, int n, const char* field, const char* select, const char* sort) {
  if(strcmp(sort, "ifind") == 0)
    arr = isort(arr, n, "incr", field); //isort
  else if(strcmp(sort, "mfind") == 0)
    arr = msort(arr, n, "incr", field); //msort
  if(strcmp(select, "max") == 0) {
    int i = n-1; // start from the end with the higest value
    while(compare(arr[i], arr[n-1], field) == 0 && i >= 0) { // print each thing with same value as highest
      printStat(arr[i], field);
      i--;
    }
  } else if(strcmp(select, "min") == 0) {
    int i = 0; // start at front with lowest value
    while(compare(arr[i], arr[0], field) == 0 && i < n) {
      printStat(arr[i], field);
      i++;
    }
  } else if(strcmp(select, "median") == 0) {
    int mindex = (n % 2 == 0) ? n/2 - 1 : (n-1)/2 - 1; // generate index of median
    if(strcmp(field, "Team") == 0 || strcmp(field, "League") == 0)
      std::cout << cvalue(arr[mindex], field) << std::endl;
    else if(strcmp(field, "AVG") == 0 || strcmp(field, "OBP") == 0 || strcmp(field, "SLG") == 0 || strcmp(field, "OPS") == 0)
      std::cout << fvalue(arr[mindex], field) << std::endl;
    else
      std::cout << ivalue(arr[mindex], field) << std::endl;
  } else if(strcmp(select, "average") == 0) {
    float sum = 0;
    for(int i = 0; i < n; i++) { // sum up all fields
      if(field == "AVG" || field == "OBP" || field == "SLG" || field == "OPS")
        sum = sum + fvalue(arr[i], field);
      else
        sum = sum + ivalue(arr[i], field);
    }
    std::cout << sum/n << std::endl; // average = sum/n
  } else
    throw std::runtime_error("Error: no such selection");
}
