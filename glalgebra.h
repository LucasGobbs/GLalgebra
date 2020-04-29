/*================================== USAGE ==================================*/
/*
    #define GLALGEBRA_IMPLEMENTATION

*/

#ifndef GLALGEBRA_H
#define GLALGEBRA_H



#ifdef GLALGEBRA_IMPLEMENTATION
#ifndef NAMESPACE_PREFIX
    #define NAMESPACE_PREFIX gla_
#endif //NAMESPACE_PREFIX

#define stringify(arg) #arg
#define concat(p1, p2) _concat(p1, p2) 
#define _concat(p1, p2) p1 ## p2       
#define ns(iden) concat(NAMESPACE_PREFIX, iden)
    
#define TYPE float
#define TYPE_DEBUG %f
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
/*================================== Types ==================================*/
typedef struct{
    TYPE* data;
    int rows, colums;
}ns(Mat);
/*================================== Utility Macros ==================================*/
#define isInside(Mat, i, j) ((i) > 0 && (i) <= (self->rows)) && ((j) > 0 && (j) <= (self->colums))?true:false
#define isNull(data) (data) == NULL? true: false

/*===============================Error handling Macros ==================================*/
#define ERROR(text) fprintf(stderr,"%s at file: %s\nfunction: %s \nline:  %d\n",text,__FILE__,__func__, __LINE__)

#define ALLOC_ERROR ERROR("Memory did not allocate")
#define CHECK_ALLOC(data) if(isNull((data))){ALLOC_ERROR;assert(false);}

#define NULLARG_ERROR ERROR("Null arg received")
#define CHECK_NULL(data) if(isNull((data))){NULLARG_ERROR;assert(false);}

/*================================== Definitions ==================================*/

//  Create Matrix with i rows and j columns
ns(Mat)* ns(Mat_create)(int i, int j);

//  Free Matrix from memory
void     ns(Mat_destroy)(ns(Mat)* self);

//  Get number in [i][j] position in matrix
TYPE     ns(Mat_get)(ns(Mat)* self, int i, int j);

//  Fill matrix with the x value
ns(Mat)* ns(Mat_fill)(ns(Mat)* self,TYPE x);

// Print matrix
void     ns(Mat_print(ns(Mat)* self));

/*================================== Matrix ==================================*/
ns(Mat)* ns(Mat_create)(int rows, int colums){
    ns(Mat)* matrix = malloc(sizeof(ns(Mat)*));
    CHECK_ALLOC(matrix);
    matrix->rows = rows;
    matrix->colums = colums;
    matrix->data = malloc(sizeof(TYPE) * rows * colums);
    CHECK_ALLOC(matrix->data);
    int i;
    matrix = Mat_fill(matrix, 0);
    return matrix;
}
ns(Mat)* Mat_fill(ns(Mat)* self,TYPE x){
    CHECK_NULL(self);
    int i;
    for(i=0;i<self->rows*self->colums;i++){
        self->data[i] = x;
    }
    return self;
}
void ns(Mat_destroy)(ns(Mat)* self){
    CHECK_NULL(self);
    free(self->data);
    free(self);
}
TYPE ns(Mat_get)(ns(Mat)* self, int i, int j){
    if(!isInside(self, i, j)){
        printf("Out of bound");
    }
    return self->data[i*self->colums + j];
}
void ns(Mat_print(ns(Mat)* self)){
    CHECK_NULL(self);
    int i, j;
    printf("Matrix [%d][%d]\n", self->rows, self->colums); 
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            printf("[%d][%d]: %.3f ",i, j, self->data[i*self->colums + j]);
            printf("\n");
        }
    }
}
/*================================== Vec ==================================*/
void ns(teste)(TYPE a){
    
    printf("\n %f \n", a);
}
//#endif //GLNAMESPACE
#endif //GLALGEBRA_IMPLEMENTATION
#endif // GLALGEBRA_H
