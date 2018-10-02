// Kevin Shannon
// usage: g++ p3.cpp -o p3
// ./p3 < file.txt

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
void intfind(int* arr, int n, const char* sort);

int* randArr;
int num, size;

int main() {
  cin >> size;
  randArr = new int[size];
  for(int i = 0; i < size; i++) {
    cin >> num;
    randArr[i] = num;
  }
  int* icopy = new int[size];
  int* mcopy = new int[size];
  memcpy(icopy, randArr, size * sizeof *randArr); //let's perserve the original
  memcpy(mcopy, randArr, size * sizeof *randArr);

  clock_t itime;
  clock_t mtime;
  itime = clock();
  intiSort(icopy, size, "incr");
  itime = (clock() - itime) * 1000 / CLOCKS_PER_SEC; // converst to ms
  mtime = clock();
  intmSort(mcopy, size, "incr");
  mtime = (clock() - mtime) * 1000 / CLOCKS_PER_SEC; // converst to ms
  cout << "isort time: " << itime << endl << "msort time: " << mtime << endl;

  memcpy(icopy, randArr, size * sizeof *randArr); // reset arrays
  memcpy(mcopy, randArr, size * sizeof *randArr);

  itime = clock();
  intfind(icopy, size, "ifind");
  itime = (clock() - itime) * 1000 / CLOCKS_PER_SEC; // converst to ms
  mtime = clock();
  intfind(mcopy, size, "mfind");
  mtime = (clock() - mtime) * 1000 / CLOCKS_PER_SEC; // converst to ms
  cout << "ifind time: " << itime << endl << "mfind time: " << mtime << endl;

  delete[] randArr; // no memory leaks pls
  delete[] icopy;
  delete[] mcopy;
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

void intfind(int* arr, int n, const char* sort) {
  if(strcmp(sort, "ifind") == 0)
    intiSort(arr, n, "incr"); //isort
  else if(strcmp(sort, "mfind") == 0)
    intmSort(arr, n, "incr"); //msort
  int i = n - 1; // start from the end with the higest value
  while(arr[i] == arr[n - 1] && i >= 0) { // print each thing with same value as highest
    cout << arr[i] << " ";
    i--;
  }
  cout << endl;
}
