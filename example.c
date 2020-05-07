#include <stdio.h>
#include <math.h>

#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
float identity(int i, int j){
  return i==j? 1.0:0.0;
}

int main(){
  float data[] = {
    2.0, 0.0,
    1.0, 0.0,
  };
  Mat* a = Mat_create_fromArray(2, 2, data);
  Mat* b = Mat_create_transpose(a);
  Mat* c = Mat_mult(a, b);
  Mat* d = Mat_create_copy(a);
  d = Mat_mult(d, b);
  //Mat* b = Mat_create_identity(4, 4);
  //printf("Adrees A: %d\n",a);
  
  //DEBUG_CALL(Mat_destroy, (&a));
  Mat_print(a); 
  Mat_print(b);
  Mat_print(c);
  DEBUG_CALL(Mat_prints, d, "alou");

  GLA_MAT_FREE(&a, &b, &c, &d);
  //Mat_destroyAll(&a, &b, &c, &d, NULL);
  return 0;
}
