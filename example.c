#include <stdio.h>
#include <math.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
float identity(int i, int j){
  return i==j? 1.0:0.0;
}
int main(){


  Mat* mat1 = Mat_create(4,1);
  mat1 = Mat_set(mat1, 0, 0, 1);
  mat1 = Mat_set(mat1, 3, 0, 1);
 
  
  Mat* mat3 = Mat_create_4dtranslation(10.0, 10.0, 10.0);
 
  Mat_print(mat1);

  Mat_prints(mat3,"translation");
  
  Mat* result2 = Mat_mult(mat3, mat1);
  Mat_print(result2);

  Mat_destroyAll(3, mat1, result2, mat3);
  //Mat_print(mat2);
  return 0;
}
