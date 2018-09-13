//Kevin Shannon

#ifndef FIND_H
#define FIND_H
#include <cstddef>
#include <iostream>
#include "value.hpp"
#include "printStat.hpp"

void find(mlb_stats* arr, int n, const char* field, const char* select, const char* sort) {
    if(sort == "isort") {
      isort(arr, n, "incr", field);
    }

    if(select == "max") {
      int i = n;
      while(compare(arr[i], arr[n-1], field) == 0 && i >= 0) {
        printStat(arr[i], field);
        i--;
      }
    }
    else if(select == "min") {
      int i = 0;
      while(compare(arr[i], arr[0], field) == 0 && i < n) {
        printStat(arr[i], field);
        i++;
      }
    }
    else if(select == "median") {
      int mindex = (n % 2 == 0) ? n/2 : (n-1)/2;
      std::cout << value(arr[mindex], field) << std::endl;
    }
    else if(select == "average") {
      float sum = 0;
      for(int i = 0; i < n; i++) {
        sum = sum + value(arr[i], field);
      }
       std::cout << sum/n << std::endl;
    }

    return;
}

#endif
