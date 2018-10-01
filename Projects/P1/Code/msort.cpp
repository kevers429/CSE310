//Implementation of MergeSort

#include "sorts.h"

mlb_stats* msort(mlb_stats* arr, int n, const char* order, const char* field) {
  return mergeSort(arr, 0, n-1, order, field);
}

void merge(mlb_stats* arr, int lo, int mid, int hi, const char* order, const char* field) {
  mlb_stats* tmp = new mlb_stats[hi - lo + 1];
  int i = lo, j = mid + 1, k = 0;
  while(i <= mid && j <= hi) {
    if(strcmp(order, "incr") == 0) {
      if(compare(arr[i], arr[j], field) < 1) // arr[i] < arr[j]
        tmp[k++] = arr[i++];
      else
        tmp[k++] = arr[j++];
    } else { // not incr so must be decr
      if(compare(arr[i], arr[j], field) > -1) // arr[i] > arr[j]
        tmp[k++] = arr[i++];
      else
        tmp[k++] = arr[j++];
    }
  }
  while(i <= mid)
    tmp[k++] = arr[i++];
  while(j <= hi)
    tmp[k++] = arr[j++];
  for(k = 0, i = lo; i <= hi; ++i, ++k)
    arr[i] = tmp[k];
  delete[] tmp;
}

mlb_stats* mergeSort(mlb_stats* arr, int lo, int hi, const char* order, const char* field) {
  int mid;
  if (lo < hi) {
    mid = (lo + hi)/2;
    mergeSort(arr, lo, mid, order, field);
    mergeSort(arr, mid + 1, hi, order, field);
    merge(arr, lo, mid, hi, order, field);
    return arr;
  }
}
