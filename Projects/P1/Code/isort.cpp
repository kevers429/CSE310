//Kevin Shannon
//Templated implementation of InsertionSort

#include "sorts.h"

template <class T>
T* isort(T* arr, int n, char* order) {
  for(int j = 1; j < n; j++){
    T key = arr[j];
    i = j - 1;
    if(order == "incr") {
      while(i >= 0 && arr[i] > key) {
        arr[i+1] = arr[i];
        i--;
      }
    } else {
      while(i >= 0 && arr[i] < key) {
        arr[i+1] = arr[i];
        i--;
      }
    }
    arr[i] = key;
  }
}
