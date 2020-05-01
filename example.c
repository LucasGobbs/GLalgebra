#include <stdio.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
int main(){
  //teste(2);
  Mat* mat1 = Mat_create(2,2);
  Mat* mat2 = Mat_create(2,2);
  mat1 = Mat_fill(mat1, 2.0);
  mat2 = Mat_fill(mat2, 1.0);
  
  //Mat* result 
  mat1 = Mat_add(mat1, mat2);
  Mat_print(mat1);

  Mat_destroyAll(2, mat1, mat2);
  //Mat_print(mat2);
  return 0;
}
