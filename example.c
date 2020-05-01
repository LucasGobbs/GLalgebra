#include <stdio.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
int main(){
  //teste(2);
  Mat* mat1 = Mat_create_fill(2,2,1);
  Mat* mat2 = Mat_create_fill(2,2,2);
  
  mat1 = Mat_add(mat1, mat2);
  Mat_print(mat1);

  Mat_destroyAll(2, mat1, mat2);
  //Mat_print(mat2);
  return 0;
}
