#include <stdio.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
float identity(int i, int j){
  return i==j? 1.0:0.0;
}
int main(){
  //teste(2);
  Mat* mat1 = Mat_create_fill_op(6,6,identity);
  Mat* mat2 = Mat_create_fill(2,2,2);
  //mat1 = Mat_fill_op(mat1,identity);
  //mat1 = Mat_add(mat1, mat2);
  Mat_print(mat1);

  Mat_destroyAll(2, mat1, mat2);
  //Mat_print(mat2);
  return 0;
}
