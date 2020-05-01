#include <stdio.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
float identity(int i, int j){
  return i==j? 1.0:0.0;
}
int main(){

  float data1[] = {2, 4, 1, 4};
  float data2[] = {1, 4, 1, 3};
  Mat* mat1 = Mat_create_fromArray(2,2,data1);
  Mat* mat2 = Mat_create_fromArray(2,2,data2);

  //mat1 = Mat_fill_op(mat1,identity);
  //mat1 = Mat_add(mat1, mat2);
  Mat_print(mat1);
  Mat_print(mat2);
  Mat* result = Mat_mult(mat1, mat2);
  Mat_print(result);
  Mat_destroyAll(3, mat1, mat2, result);
  //Mat_print(mat2);
  return 0;
}
