#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int sieve(int targetPrime){
  if(targetPrime == 1){
    return 2;
  }
  if(targetPrime == 2){
    return 3;
  }
  int len;
  if(targetPrime > 5000){
    len = 1.31 * targetPrime * log(targetPrime);
  }else{
    len = 1.3 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc(len, sizeof(int));
  int i = 3;
  int j;
  int index = 6;
  while(i <= targetPrime){
    if(i == targetPrime){
      if(!(cur[index-1])){
        return index-1;
      }
      return index+1;
    }
    if(i == targetPrime - 1){
      if(cur[index-1] || cur[index+1]){
        if(!(cur[index+5])){
          return index+5;
        }
        return index+7;
      }
      return index+1;
    }
    if(!(cur[index-1])){
      for(j = 2 * (index-1); j < len; j += index - 1){
        cur[j] = 1;
      }
      i++;
    }
    if(!(cur[index+1])){
      for(j = 2 * (index+1); j < len; j += index + 1){
        cur[j] = 1;
      }
      i++;
    }
    index += 6;
  }
  return 0;
}

int fastsieve(int targetPrime){
  if(targetPrime == 1){
    return 2;
  }
  if(targetPrime == 2){
    return 3;
  }
  int len;
  if(targetPrime > 5000){
    len = 1.31 * targetPrime * log(targetPrime);
  }else{
    len = 1.3 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc((len * 2) / 192, sizeof(int));
  int offset = 0;
  int mult3 = 1;
  int index = 5;
  int i = 3;
  while(i <= targetPrime){
    if(i == targetPrime){
      if(!(cur[(index*2) / 192] & ((1 << (((index - offset) >> 1) & 31)) >> 2))){
        return index;
      }
      if(mult3 == 2){
        return index + 4;
      }
      return index+2;
    }
    if(!(cur[(index*2) / 192] & ((1 << (((index - offset) >> 1) & 31)) >> 2))){
      for(int j = index * index; j < len; j += 2 * index){
        cur[(j * 2) / 192] |= (1 << (((j - (((j+1) / 3) - 2)) >> 1) & 31)) >> 2;
      }
      i++;
    }
    mult3++;
    mult3 %= 3;
    if(!(mult3)){
      index += 4;
      mult3++;
      offset += 2;
    }else{
      index += 2;
    }
  }
  return 0;
}

int main(){
  int i;
  printf("%d\n", fastsieve(16));
  return 0;
}
