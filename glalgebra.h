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

// type that the data in matrix is stored
#ifndef TYPE
    #define TYPE float

    #define TYPE_DEBUG %f
#endif //TYPE


#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
/*=================================================================================*/
/*============================ Types ==================================*/
/*=================================================================================*/
typedef struct{
    TYPE* data;
    int rows, colums;
}ns(Mat);
/*=================================================================================*/
/*============================ Utility Macros ==================================*/
/*=================================================================================*/
// Check if number is inside de matrix
#define isInside(Mat, i, j) ((i) > 0 && (i) <= (self->rows)) && ((j) > 0 && (j) <= (self->colums))?true:false

// Check if data is NULL
#define isNull(data) (data) == NULL? true: false

// Converts two adress to linear 
#define ADDRESS(self,i,j) ((i)*(self->colums)+(j))

#define MGET(self,i,j) (self->data[((i)*(self->colums)+(j))])

// Checks if the size of the two matrix is equal
#define isSizeEqual(a,b) (a->rows==b->rows&&a->colums==b->colums)

/*=================================================================================*/
/*============================ Error handling Macros ==================================*/
/*=================================================================================*/

// Simple interface for error throwing
#define ERROR(text) {\
    fprintf(stderr,"%s at file: %s\nfunction: %s \nline:  %d\n",text,\
                                                                __FILE__,\
                                                                __func__,\
                                                                __LINE__);\
    assert(false);\                                          
}\
// Error in alocation fo memory
#define ALLOC_ERROR ERROR("Memory did not allocate")
#define CHECK_ALLOC(data) if(isNull((data))){ALLOC_ERROR;}

// Error receiving null argument in function 
#define NULLARG_ERROR ERROR("Null arg received")
#define CHECK_NULL(data) if(isNull((data))){NULLARG_ERROR;}

// Error trying to look at data out of the boundary of matrix
#define OUTOFBOUND_ERROR ERROR("Out of boundary request")
#define CHECK_OOB(data, i, j) if(!isInside((self),(i),(j))){OUTOFBOUND_ERROR;}

// Matrices given arent the same size
#define DIFERENTSIZE_ERROR ERROR("Matrix are of diferent size")
#define CHECK_SIZE(a, b) if(!isSizeEqual(a,b)){DIFERENTSIZE_ERROR;assert(false);}
/*=================================================================================*/
/*================================== Definitions ==================================*/
/*=================================================================================*/

//  Create Matrix with i rows and j columns
ns(Mat)* ns(Mat_create)(int i, int j);

//  Free Matrix from memory
void     ns(Mat_destroy)(ns(Mat)* self);

//  Fill matrix with the x value
ns(Mat)* ns(Mat_fill)(ns(Mat)* self,TYPE x);

// Print matrix
void     ns(Mat_print)(ns(Mat)* self);

//  Get number in [i][j] position in matrix
TYPE     ns(Mat_get)(ns(Mat)* self, int i, int j);

// Set number in [i][j] position in matrix to value
ns(Mat)* ns(Mat_set)(ns(Mat)* self, int i, int j, TYPE value);

/*================================== Operations ==================================*/
ns(Mat)* ns(Mat_add)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);
    int i, j;
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            MGET(self,i,j) += MGET(other,i,j);
        }
    }
    return self;
}
ns(Mat)* ns(Mat_addC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat *c = Mat_create(a->rows, a->colums);
    CHECK_ALLOC(c);
    int i, j;
    for(i=0;i<c->rows;i++){
        for(j=0;j<c->colums;j++){
            MGET(c,i,j) = MGET(a,i,j) + MGET(b,i,j);
        }
    }
}
/*=================================================================================*/
/*================================== Implementation ===============================*/
/*=================================================================================*/
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
void ns(Mat_print(ns(Mat)* self)){
    CHECK_NULL(self);
    int i, j;
    printf("Matrix [%d][%d]\n", self->rows, self->colums); 
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            printf("[%d][%d]: %.3f ",i, j, MGET(self,i,j));
            printf("\n");
        }
    }
}
TYPE ns(Mat_get)(ns(Mat)* self, int i, int j){
    CHECK_NULL(self);
    CHECK_OOB(self, i ,j);
    return MGET(self,i,j);
}
ns(Mat)* ns(Mat_set)(ns(Mat)* self, int i, int j, TYPE value){
    CHECK_NULL(self);
    CHECK_OOB(self, i ,j);
    MGET(self,i,j) = value;
    return self;
}
/*================================== Vec ==================================*/
void ns(teste)(TYPE a){
    
    printf("\n %f \n", a);
}
//#endif //GLNAMESPACE
#endif //GLALGEBRA_IMPLEMENTATION
#endif // GLALGEBRA_H
