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
    0.0, 1.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 2.0,
    3.0, 1.0, 0.0, 1.0
  };
  Mat* a = Mat_create_fromArray(4, 4, data);
  Mat* b = Mat_create_transpose(a);
  //Mat* b = Mat_create_identity(4, 4);
  //printf("Adrees A: %d\n",a);
  
  //DEBUG_CALL(Mat_destroy, (&a));
  Mat_print(a);
  Mat_print(b);
  Mat_destroyAll(&a, &b, NULL);
  if( a == NULL && b ==NULL){
    printf("alou");
  }
  return 0;
}
