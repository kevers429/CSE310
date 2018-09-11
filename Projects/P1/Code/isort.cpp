//Kevin Shannon
//Templated implementation of InsertionSort

#include "sorts.h"

template <class T>
T* isort(T* arr, int n) {
  for(int j = 1; j < n; j++){
    T key = arr[j];
    i = j - 1;
    while(i >= 0 && arr[i] > key) {
      arr[i+1] = arr[i];
      i--;
    }
    arr[i] = key;
  }
}
