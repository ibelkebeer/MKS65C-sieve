#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int sieve(int targetPrime){
  int len;
  if(targetPrime > 5000){
    len = 1.15 * targetPrime * log(targetPrime);
  }else{
    len = 1.3 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc(len, sizeof(int));
  int i;
  int index = 2;
  for(i = 1; i <= targetPrime; i++){
    while(cur[index]){
      index++;
    }
    if(i == targetPrime){
      return index;
    }
    int j;
    for(j = 2 * index; j < len; j += index){
      cur[j] = 1;
    }
    index += 2;
  }
}

int main(){
  printf("%d\n", sieve(1000000));
  return 0;
}
