#include <stdio.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
int main(){
  //teste(2);
  Mat* matrix = Mat_create(10,10);
 //Mat_get(0, 0);
  //teste(2);
  Mat_print(matrix);
  printf("%f",Mat_get(matrix, 2, 2));
  Mat_destroy(matrix);
  return 0;
}
