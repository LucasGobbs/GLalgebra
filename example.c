#include <stdio.h>
#include <math.h>

#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
// to Compile
// gcc -Wall -pedantic -std=c99 -o exe example.c -lm

float op_test(int i, int j, int x){
  if(i==j){
    return x;
  } else {
    return 0.0;
  }
}
float op_test2(int i, int j, int x){
  if(i==j){
    return 0.0;
  } else {
    return x;
  }
}
void example_operations(){
  Mat* a = Mat_create(4, 4);
  a = Mat_fill(a, 2.0);

  Mat* b = Mat_create(4, 4);
  b = Mat_fill_op(b, &op_test);

  Mat* c = Mat_create_fill(4, 4, 3.0);

  Mat* d = Mat_create_fill_op(4, 4, &op_test2);

  Mat_prints(a, "a");
  Mat_prints(b, "b");
  Mat_prints(c, "c");
  Mat_prints(d, "d");

  Mat* add = Mat_create_add(a, b);
  Mat* sub = Mat_create_sub(c, d);
  c = Mat_factor(c, 5.0);

  Mat_prints(add, "a + b");
  Mat_prints(sub, "c - d");
  Mat_prints(c, "c * 5.0");
  GLA_MAT_FREE(&a, &b, &c, &d, &add, &sub);
  //or Mat_destroyAll(&a, &b, &c, &d, &add, &sub, &fact, NULL);
}

int main(){
  example_operations();
  return 0;
}
