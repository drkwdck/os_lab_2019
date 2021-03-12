#include "sum.h"

int Sum(const struct SumArgs *args) {
  int sum = 0;
  int i = (*args).begin;

  while(i <= (*args).end){
      sum += (*args).array[i];
      i++;
  }
  
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(int)Sum(sum_args);
}
