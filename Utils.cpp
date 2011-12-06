#include "WProgram.h"

// Insert sort. From "whistler" - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1283456170/0
void isort(int *a, byte n){
  for (int i = 1; i < n; ++i){
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--){
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

int findMedian(int *data, byte arraySize){
  isort(data, arraySize);
  
  return data[arraySize/2];
}

// Low pass filter, kept as regular C function for speed
float filterSmooth(float currentData, float previousData, float smoothFactor){
  if (smoothFactor != 1.0) //only apply time compensated filter if smoothFactor is applied
    return (previousData * (1.0 - smoothFactor) + (currentData * smoothFactor)); 
  else
    return currentData; //if smoothFactor == 1.0, do not calculate, just bypass!
}
