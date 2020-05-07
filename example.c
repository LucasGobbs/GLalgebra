#include <stdio.h>
#include <math.h>
#define NAMESPACE_PREFIX 
#define GLALGEBRA_IMPLEMENTATION
#include "glalgebra.h"
float identity(int i, int j){
  return i==j? 1.0:0.0;
}
int main(){
  Mat* teste = Mat_create(4, 4);

  
  free(teste);
  /*

  Vec* cam = Vec4_create(10, 0, 0, 1);
  Vec* target = Vec4_create(0, 0, 0, 1);
  Vec* up = Vec4_create(0, 1, 0, 1);

  Matst* teste = Mat_create_tst(4, 4);
  free(teste);
  Mat_print(cam);
  Mat_print(target);
  Mat_print(up);
  Mat* look = Mat_create_lookAt(cam, target, up);

  Mat_print(look);
  Vec4_destroyAll(4, cam, target, up, look);
  */
  return 0;
}
