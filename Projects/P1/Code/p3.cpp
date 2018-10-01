//Kevin Shannon

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"
#include <time.h>
using namespace std;

void intiSort(int* arr, int n, const char* order);
void intmSort(int* arr, int n, const char* order);
void intmerge(int* arr, int lo, int mid, int hi, const char* order);
void intmergeSort(int* arr, int lo, int hi, const char* order);

int* randArr;
int num, size;

typedef struct _LARGE_INTEGER {
  long long QuadPart;
} LARGE_INTEGER;

int main() {
  cin >> size;
  randArr = new int[size];
  for(int i = 0; i < size; i++) {
    cin >> num;
    randArr[i] = num;
  }
  int* icopy = new int[size];
  int* mcopy = new int[size];
  memcpy(icopy, randArr, size * sizeof *randArr);
  memcpy(mcopy, randArr, size * sizeof *randArr);

  clock_t itime;
  clock_t mtime;
  itime = clock();
  intiSort(icopy, size, "incr");
  itime = clock() - itime;
  mtime = clock();
  intmSort(mcopy, size, "incr");
  mtime = clock() - mtime;
  cout << "isort time: " << itime << endl << "msort time: " << mtime << endl;

  return 0;
}

void intiSort(int* arr, int n, const char* order) {
  for (int j = 1; j < n; j++) {
    int key = arr[j];
    int i = j - 1;
    if(strcmp(order, "incr") == 0) {
      while (i >= 0 && arr[i] > key) {
        arr[i + 1] = arr[i];
        i = i - 1;
      }
    } else { // not incr, so must be decr
      while (i >= 0 && arr[i] < key) {
        arr[i + 1] = arr[i];
        i = i - 1;
      }
    }
    arr[i + 1] = key;
  }
}

void intmSort(int* arr, int n, const char* order) {
  return intmergeSort(arr, 0, n-1, order);
}

void intmerge(int* arr, int lo, int mid, int hi, const char* order) {
  int* tmp = new int[hi - lo + 1];
  int i = lo, j = mid + 1, k = 0;
  while(i <= mid && j <= hi) {
    if(strcmp(order, "incr") == 0) {
      if(arr[i] < arr[j]) // arr[i] > arr[j]
        tmp[k++] = arr[i++];
      else
        tmp[k++] = arr[j++];
    } else { // not incr so must be decr
      if(arr[i] > arr[j]) // arr[i] < arr[j]
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

void intmergeSort(int* arr, int lo, int hi, const char* order) {
  int mid;
  if (lo < hi) {
    mid = (lo + hi)/2;
    intmergeSort(arr, lo, mid, order);
    intmergeSort(arr, mid + 1, hi, order);
    intmerge(arr, lo, mid, hi, order);
  }
}
