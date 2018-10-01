//Implementation of InsertionSort

#include "sorts.h"

mlb_stats* isort(mlb_stats* arr, int n, const char* order, const char* field) {
  for(int j = 1; j < n; j++) {
    mlb_stats key = arr[j];
    int i = j - 1;
    if(strcmp(order, "incr") == 0) {
      while(i >= 0 && compare(arr[i], key, field) == 1) { // while key > field
        arr[i + 1] = arr[i];
        i--;
      }
    } else { // not incr, so must be decr
      while(i >= 0 && compare(arr[i], key, field) == -1) { // while key < field
        arr[i + 1] = arr[i];
        i--;
      }
    }
    arr[i + 1] = key;
  }
  return arr;
}
