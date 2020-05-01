/*================================== USAGE ==================================*/
/*
    #define GLALGEBRA_IMPLEMENTATION

*/

#ifndef GLALGEBRA_H
#define GLALGEBRA_H




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
#include <stdarg.h>
/*=================================================================================*/
/*===================================== Types ==================================*/
/*=================================================================================*/
typedef struct{
    TYPE* data;
    int rows, colums;
}ns(Mat);

/*=================================================================================*/
/*================================== Definitions ==================================*/
/*=================================================================================*/
//  Create Matrix with i rows and j columns
ns(Mat)* ns(Mat_create)(int i, int j);
ns(Mat)* ns(Mat_clone)(ns(Mat)* paste, ns(Mat)* copy);
ns(Mat)* ns(Mat_create_fill)(int i, int j, TYPE value);
ns(Mat)* ns(Mat_create_fill_op)(int i, int j, TYPE (*operation)(TYPE a, TYPE b));

//  Free Matrix from memory
void     ns(Mat_destroy)(ns(Mat)* self);

// Free n matrices from memory
void     ns(Mat_destroyAll)(int n, ...);

//  Fill matrix with the x value
ns(Mat)* ns(Mat_fill)(ns(Mat)* self,TYPE x);

ns(Mat)* ns(Mat_fill_op)(ns(Mat)* self,TYPE (*operation)(int a, int b));

// Print matrix
void     ns(Mat_print)(ns(Mat)* self);

//  Get number in [i][j] position in matrix
TYPE     ns(Mat_get)(ns(Mat)* self, int i, int j);

// Set number in [i][j] position in matrix to value
ns(Mat)* ns(Mat_set)(ns(Mat)* self, int i, int j, TYPE value);


/*================================== Operations ==================================*/
// Takes matrices self and other and call the operation for each pair of the two
// matrices member 
ns(Mat)* ns(Mat_op)(ns(Mat)* self, ns(Mat)* other, TYPE (*operation)(TYPE a, TYPE b));

// Similar to Mat_op but allocates memory and return a new pointer
ns(Mat)* ns(Mat_opC)(ns(Mat)* a, ns(Mat)* b, TYPE (*operation)(TYPE a, TYPE b));

// Add the two matrices and returns self
ns(Mat)* ns(Mat_add)(ns(Mat)* self, ns(Mat)* other);
// Returns a new pointer to matrice with the sum of the two
ns(Mat)* ns(Mat_addC)(ns(Mat)* a ,ns(Mat)* b);

//Sub
ns(Mat)* ns(Mat_sub)(ns(Mat)* self, ns(Mat)* other);

ns(Mat)* ns(Mat_subC)(ns(Mat)* a ,ns(Mat)* b);

//Multiplication
ns(Mat)* ns(Mat_mult)(ns(Mat)* self, ns(Mat)* other);

ns(Mat)* ns(Mat_multC)(ns(Mat)* a ,ns(Mat)* b);

//Div
ns(Mat)* ns(Mat_div)(ns(Mat)* self, ns(Mat)* other);

ns(Mat)* ns(Mat_divC)(ns(Mat)* a ,ns(Mat)* b);

#ifdef GLALGEBRA_IMPLEMENTATION
/*=================================================================================*/
/*============================ Utility Macros ==================================*/
/*=================================================================================*/
// Check if number is inside de matrix
#define isInside(Mat, i, j) ((i) > 0 && (i) <= (self->rows)) && ((j) > 0 && (j) <= (self->colums))?true:false

// Check if data is NULL
#define isNull(data) (data) == NULL? true: false

// Converts two adress to linear 
#define ADDRESS(self,i,j) ((i)*(self->colums)+(j))

//Macro to quick accesss member in matrice
#define MGET(self,i,j) (self->data[ADDRESS(self,i,j)])

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
    assert(false);}\
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

/*============================ Simple traits ==================================*/
TYPE type_addTrait(TYPE a, TYPE b){
    return a+b;
}
TYPE type_subTrait(TYPE a, TYPE b){
    return a-b;
}
TYPE type_multTrait(TYPE a, TYPE b){
    return a*b;
}
TYPE type_divTrait(TYPE a, TYPE b){
    return a/b;
}
/*=================================================================================*/
/*================================== Implementation ===============================*/
/*=================================================================================*/
ns(Mat)* ns(Mat_create)(int rows, int colums){
    ns(Mat)* matrix = malloc(sizeof(ns(Mat)*));
    CHECK_ALLOC(matrix);
    matrix->rows = rows;
    matrix->colums = colums;
    matrix->data = calloc(rows * colums, sizeof(TYPE));
    CHECK_ALLOC(matrix->data);
    return matrix;
}
ns(Mat)* ns(Mat_clone)(ns(Mat)* paste, ns(Mat)* copy){
    CHECK_NULL(copy);CHECK_NULL(paste);
    CHECK_SIZE(copy, paste);
    int i;
    for(i=0;i<paste->rows*paste->colums;i++){
        paste->data[i] = copy->data[i];
    }
    return paste;
}
ns(Mat)* ns(Mat_create_fill)(int i, int j, TYPE value){
    Mat* a = ns(Mat_create)(i,j);
    a = ns(Mat_fill)(a,value);
    return a;
}
ns(Mat)* ns(Mat_create_fill_op)(int i, int j, TYPE (*operation)(TYPE a, TYPE b)){
    Mat* a = ns(Mat_create)(i,j);
    a = ns(Mat_fill_op)(a, operation);
    return a;
}
ns(Mat)* Mat_fill(ns(Mat)* self,TYPE x){
    CHECK_NULL(self);
    int i;
    for(i=0;i<self->rows*self->colums;i++){
        self->data[i] = x;
    }
    return self;
}
ns(Mat)* ns(Mat_fill_op)(ns(Mat)* self, TYPE (*operation)(int a, int b)){
    CHECK_NULL(self);
    int i, j;
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            MGET(self,i,j) = operation(i,j);
        }
    }
    return self;
}
void ns(Mat_destroy)(ns(Mat)* self){
    CHECK_NULL(self);
    free(self->data);
    free(self);
}
void ns(Mat_destroyAll)(int number, ...){
    va_list list;
    int i;

    va_start(list, number);
    for(i=0;i<number;i++){
        ns(Mat)* garbage = va_arg(list, ns(Mat)*);
        ns(Mat_destroy)(garbage);
    }
    va_end(list);
}
void ns(Mat_print(ns(Mat)* self)){
    CHECK_NULL(self);
    int i, j;
    printf("Matrix [%d][%d]\n", self->rows, self->colums); 
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            if(!MGET(self,i,j)){
                printf("[%d][%d]: 0\t", i, j);
            } else {
                printf("[%d][%d]: %.3f\t",i, j, MGET(self,i,j));
            }
            
        }
        printf("\n");
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

/*================================== Operations ==================================*/
ns(Mat)* ns(Mat_op)(ns(Mat)* self, ns(Mat)* other, TYPE (*operation)(TYPE a, TYPE b)){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);

    int i, j;
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            MGET(self,i,j) = operation(MGET(self,i,j), MGET(other,i,j));
        }
    }
    return self; 
}
ns(Mat)* ns(Mat_opC)(ns(Mat)* a, ns(Mat)* b, TYPE (*operation)(TYPE a, TYPE b)){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat* c = Mat_create(a->rows, a->colums);
    int i, j;
    for(i=0;i<a->rows;i++){
        for(j=0;j<a->colums;j++){
     
            MGET(c,i,j) = operation(MGET(a,i,j), MGET(b,i,j));
        }
    }
    return c; 
}
ns(Mat)* ns(Mat_add)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);
    return ns(Mat_op)(self, other, type_addTrait);
}
ns(Mat)* ns(Mat_addC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat *c = ns(Mat_opC)(a, b, type_addTrait);
    return c;
}
//Sub
ns(Mat)* ns(Mat_sub)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);
    return ns(Mat_op)(self, other, type_subTrait);
}

ns(Mat)* ns(Mat_subC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat *c = ns(Mat_opC)(a, b, type_subTrait);
    return c;
}

//Multiplication
ns(Mat)* ns(Mat_mult)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);
    return ns(Mat_op)(self, other, type_multTrait);
}

ns(Mat)* ns(Mat_multC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat *c = ns(Mat_opC)(a, b, type_multTrait);
    return c;
}

//Div
ns(Mat)* ns(Mat_div)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    CHECK_SIZE(self,other);
    return ns(Mat_op)(self, other, type_divTrait);
}

ns(Mat)* ns(Mat_divC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_SIZE(a,b);
    Mat *c = ns(Mat_opC)(a, b, type_divTrait);
    return c;
}
/*================================== Vec ==================================*/

//#endif //GLNAMESPACE
#endif //GLALGEBRA_IMPLEMENTATION
#endif // GLALGEBRA_H
