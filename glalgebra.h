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

#if !defined(GLA_PI)
    #define GLA_PI 3.14159265359
    #define GLA_HALFPI 1.57079632679
    #define GLA_180DIVPI 57.2957795131
#endif


#if !defined(GLA_DEGREES_MODE)
    #define GLA_ANGLE(angle) ((angle) * GLA_180DIVPI)
#else
    #define GLA_ANGLE(angle) (angle)
#endif


#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
/*=================================================================================*/
/*===================================== Types ==================================*/
/*=================================================================================*/

typedef struct{
    size_t rows, colums;
    TYPE data[];
}ns(Mat);

typedef ns(Mat) ns(Vec);

/*==================================== Matrix ======================================*/
/*================================== Definitions ==================================*/
/*=================================================================================*/
//  Creating
ns(Mat)* ns(Mat_create)          (size_t rows, size_t colums);
ns(Mat)* ns(Mat_create_noInit)   (size_t rows, size_t colums);
ns(Mat)* ns(Mat_create_fromArray)(size_t rows, size_t colums, const TYPE* data);
ns(Mat)* ns(Mat_create_copy)     (ns(Mat)* origin);
ns(Mat)* ns(Mat_create_fill)     (size_t rows, size_t colums, TYPE value);
ns(Mat)* ns(Mat_create_fill_op)  (size_t rows, size_t colums, TYPE (*operation)(int i, int j, int x));
ns(Mat)* ns(Mat_create_transpose)(ns(Mat)* origin);

//Creating by operations
ns(Mat)* ns(Mat_create_op)    (ns(Mat)* a, ns(Mat)* b, TYPE (*operation)(TYPE a, TYPE b));
ns(Mat)* ns(Mat_create_add)   (ns(Mat)* a ,ns(Mat)* b);
ns(Mat)* ns(Mat_create_sub)   (ns(Mat)* a ,ns(Mat)* b);
ns(Mat)* ns(Mat_create_div)   (ns(Mat)* a ,ns(Mat)* b);
ns(Mat)* ns(Mat_create_schur) (ns(Mat)* a ,ns(Mat)* b);
//========================================================================================
// Multiplications 
ns(Mat)* ns(Mat_create_naive_mult)      (ns(Mat)* a, ns(Mat)* b);
ns(Mat)* ns(Mat_create_strassen_mult)   (ns(Mat)* a, ns(Mat)* b);
ns(Mat)* ns(Mat_create_mult)            (ns(Mat)* a, ns(Mat)* b);

void     ns(Mat_naive_mult)             (ns(Mat)** result, ns(Mat)* a, ns(Mat)* b);
void     ns(Mat_strassen_mult)          (ns(Mat)** result, ns(Mat)* a, ns(Mat)* b);
void     ns(Mat_mult)                   (ns(Mat)** result, ns(Mat)* a, ns(Mat)* b);
//========================================================================================
//Useful matrices 
ns(Mat)* ns(Mat_create_identity)      (int i, int j);
ns(Mat)* ns(Mat_create_4drotationX)   (float angle);
ns(Mat)* ns(Mat_create_4drotationY)   (float angle);
ns(Mat)* ns(Mat_create_4drotationZ)   (float angle);
ns(Mat)* ns(Mat_create_4dtranslation) (TYPE x, TYPE y, TYPE z);
ns(Mat)* ns(Mat_create_4dscale)       (TYPE x, TYPE y, TYPE z);
ns(Mat)* ns(Mat_create_4dperspective) (TYPE fov, TYPE ratio, TYPE near, TYPE far);
ns(Mat)* ns(Mat_create_lookAt)        (ns(Vec)* cam_pos, ns(Vec)* target,ns(Vec)* up);

// TODO
void ns(Mat_to_identity)        (ns(Mat)** self);
void ns(Mat_to_4drotationX)     (ns(Mat)** self, float angle);
void ns(Mat_to_4drotationY)     (ns(Mat)** self, float angle);
void ns(Mat_to_4drotationZ)     (ns(Mat)** self, float angle);
void ns(Mat_to_4dtranslation)   (ns(Mat)** self, TYPE x, TYPE y, TYPE z);
void ns(Mat_to_4dscale)         (ns(Mat)** self, TYPE x, TYPE y, TYPE z);
void ns(Mat_to_4dperspective)   (ns(Mat)** self, TYPE fov, TYPE ratio, TYPE near, TYPE far);
void ns(Mat_to_lookAt)          (ns(Mat)** self, ns(Vec)* cam_pos, ns(Vec)* target, ns(Vec)* up);
//========================================================================================
//  Destructors
void     ns(Mat_destroy)    (ns(Mat)** self);
void     ns(Mat_destroyAll) (ns(Mat)** first, ...);
//========================================================================================
//  Filling matrix
ns(Mat)* ns(Mat_fill)    (ns(Mat)* self, TYPE x);
ns(Mat)* ns(Mat_fill_op) (ns(Mat)* self, TYPE (*operation)(int i, int j, int x));
//========================================================================================
// Print matrix
void     ns(Mat_print)  (ns(Mat)* self);
void     ns(Mat_prints) (ns(Mat)* self, char* text);

//========================================================================================
//  Get / Set
TYPE     ns(Mat_get)    (ns(Mat)* self, int i, int j);
ns(Mat)* ns(Mat_set)    (ns(Mat)* self, int i, int j, TYPE value);
void     ns(Mat_set_fromArray)    (ns(Mat)** self, TYPE* data);

//========================================================================================
// Operations
ns(Mat)* ns(Mat_op)     (ns(Mat)* self, ns(Mat)* other, TYPE (*operation)(TYPE a, TYPE b));
ns(Mat)* ns(Mat_add)    (ns(Mat)* self, ns(Mat)* other);
ns(Mat)* ns(Mat_sub)    (ns(Mat)* self, ns(Mat)* other);
ns(Mat)* ns(Mat_div)    (ns(Mat)* self, ns(Mat)* other);
ns(Mat)* ns(Mat_factor) (ns(Mat)* a, TYPE factor);




/*==================================== Vector ======================================*/
/*================================== Definitions ==================================*/
/*=================================================================================*/
// Constructors
ns(Vec)* ns(Vec4_create)(TYPE x, TYPE y, TYPE z, TYPE w);

// Destructors
void ns(Vec4_destroy)    (ns(Vec)* self);
void ns(Vec4_destroyAll) (int n, ...);

// Get 
TYPE ns(Vec4_getX)  (ns(Vec)* self);
TYPE ns(Vec4_getY)  (ns(Vec)* self);
TYPE ns(Vec4_getZ)  (ns(Vec)* self);
TYPE ns(Vec4_getW)  (ns(Vec)* self);
TYPE ns(Vec4_get)   (ns(Vec)* self, int x);
// Set
ns(Vec)* ns(Vec4_setX) (ns(Vec)* self, TYPE x);
ns(Vec)* ns(Vec4_setY) (ns(Vec)* self, TYPE y);
ns(Vec)* ns(Vec4_setZ) (ns(Vec)* self, TYPE z);
ns(Vec)* ns(Vec4_setW) (ns(Vec)* self, TYPE w);
ns(Vec)* ns(Vec4_set)  (ns(Vec)* self, TYPE x, TYPE y, TYPE z, TYPE w);
TYPE     ns(Vec4_length)(ns(Vec)*);
TYPE     ns(Vec4_lengthSq)(ns(Vec)*);
ns(Vec)* ns(Vec4_normalize)(ns(Vec)*);
//Operations
ns(Vec)* ns(Vec4_add)(ns(Vec)* self,ns(Vec)* other);
ns(Vec)* ns(Vec4_sub)(ns(Vec)* self,ns(Vec)* other);
ns(Vec)* ns(Vec4_mult)(ns(Vec)* self,ns(Vec)* other);
ns(Vec)* ns(Vec4_div)(ns(Vec)* self,ns(Vec)* other);
TYPE     ns(Vec4_dot)(ns(Vec)* self,ns(Vec)* other);
ns(Vec)* ns(Vec4_cross)(ns(Vec)* self,ns(Vec)* other);
bool     ns(Vec4_naive_equal)(ns(Vec)* a,ns(Vec)* b);
bool     ns(Vec4_safe_equal)(ns(Vec)* a,ns(Vec)* b);
bool     ns(Vec4_equal)(ns(Vec)* a, ns(Vec)* b);
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
#define MGETL(self,x) ((self)->data[x])
#define MGET(self,i,j) ((self)->data[ADDRESS(self,i,j)])

#define MCOLUMS(matrix) ((matrix)->colums)
#define MROWS(matrix) ((matrix)->rows)
#define MSIZE(matrix) (((matrix)->rows)*((matrix)->colums))
//#define MITER(matrix, iter) iter = 0; iter <= MSIZE(matrix); iter++


#define VGET(self,i)   (MGET(self,i,1))
#define VX(self) (VGET(self, 0))
#define VY(self) (VGET(self, 1))
#define VZ(self) (VGET(self, 2))

#define RADIANS2DEGREES(angle) ((angle) * GLA_180DIVPI)

#define GLA_MAT_FREE(...) (ns(Mat_destroyAll)(__VA_ARGS__, NULL))

// Checks if the size of the two matrix is equal
#define isSizeEqual(a,b) ((a)->rows==(b)->rows&&(a)->colums==(b)->colums)
#define isSizeEqual3(a, b, c) (((a)->rows==(b)->rows&&(a)->rows==(c)->rows)&&((a)->colums==(b)->colums&&(a)->colums==(c)->colums))
#define isMultPossibly(a,b) ((a)->colums == (b)->rows)

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
#define COMPARE_SIZE2(a, b) if(!isSizeEqual(a,b)){DIFERENTSIZE_ERROR;}
#define COMPARE_SIZE3(a, b, c) if(!isSizeEqual3(a,b, c)){DIFERENTSIZE_ERROR;}

#define NOTPROPERSIZE_ERROR ERROR("Matrices arent the proper size for multiplication")
#define CHECK_MULTSIZE(a, b) if(!isMultPossibly(a,b)){NOTPROPERSIZE_ERROR;}

#define DEBUG_CALL(func, ...) {\
    printf("\nDebug Call at:\t|Funcion: %s\t|File: %s\t|Line: %d\n",__func__,\
                                                                    __FILE__,\
                                                                    __LINE__ );\
    printf("\t\t|Calling func: " stringify(func) "\n\n");\
    func(__VA_ARGS__);\
}\


                                       

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
ns(Mat)* ns(Mat_create)(size_t rows,size_t colums){
    ns(Mat)* matrix = malloc(sizeof(*matrix)*sizeof(TYPE [rows*colums]));
    CHECK_ALLOC(matrix);
    matrix->rows = rows;
    matrix->colums = colums;
    int x;
    for(x=0;x<rows * colums;x++){
        MGETL(matrix, x) = 0.0;
    }
    return matrix;
}
ns(Mat)* ns(Mat_create_noInit)(size_t rows, size_t colums){
    ns(Mat)* matrix = malloc(sizeof(*matrix)*sizeof(TYPE [rows*colums]));
    CHECK_ALLOC(matrix);
    matrix->rows = rows;
    matrix->colums = colums;

    return matrix;
}
ns(Mat)* ns(Mat_create_fromArray)(size_t rows, size_t colums, const TYPE* data){
    ns(Mat)* matrix = ns(Mat_create_noInit)(rows, colums);
    int i;
    for(i=0;i<rows * colums;i++){
        MGETL(matrix, i) = data[i];
    }
    return matrix;
}
ns(Mat)* ns(Mat_create_copy)(ns(Mat)* origin){
    ns(Mat)* matrix = ns(Mat_create_noInit)(origin->rows,origin->colums);
    int i;
    for(i=0;i<origin->rows * origin->colums;i++){
        MGETL(matrix, i) = MGETL(origin, i);
    }
    return matrix;
}
ns(Mat)* ns(Mat_clone)(ns(Mat)* paste, ns(Mat)* copy){
    CHECK_NULL(copy);CHECK_NULL(paste);
    COMPARE_SIZE2(copy, paste);
    int i;
    for(i=0;i<paste->rows*paste->colums;i++){
        MGETL(paste, i) = MGETL(copy, i);
    }
    return paste;
}
ns(Mat)* ns(Mat_create_fill)(size_t rows, size_t colums, TYPE value){
    ns(Mat)* a = ns(Mat_create)(rows,colums);
    a = ns(Mat_fill)(a,value);
    return a;
}
ns(Mat)* ns(Mat_create_fill_op)(size_t rows, size_t colums, TYPE (*operation)(int i, int j, int x)){
    ns(Mat)* a = ns(Mat_create_noInit)(rows,colums);
    a = ns(Mat_fill_op)(a, operation);
    return a;
}
ns(Mat)* ns(Mat_create_transpose)(ns(Mat)* origin){
    CHECK_NULL(origin);
    ns(Mat)* a = ns(Mat_create_noInit)(origin->colums, origin->rows);
    CHECK_ALLOC(a);
    int i, j;
    for(i=0;i<origin->colums;i++){
        for(j=0;j<origin->rows;j++){
            //printf("%f", MGET(origin, j, i));
            MGET(a, i, j) = MGET(origin, j, i);
        }
    }

    return a;
}
//useful matrix
/*
TYPE data[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
};
*/
ns(Mat)* ns(Mat_create_identity)(int rows, int colums){
    ns(Mat)* a = ns(Mat_create_noInit)(rows,colums);
    int i, j;
    for(i=0;i<rows;i++){
        for(j=0;j<colums;j++){
            if(i==j){
                MGET(a,i,j) = 1.0;
            }
        }
    }
    return a;
}
ns(Mat)* ns(Mat_create_4drotationX)(float angle){

    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));

    TYPE data[] = {
        1.0,  0.0,   0.0, 0.0,
        0.0, _cos, -_sin, 0.0,
        0.0, _sin,  _cos, 0.0,
        0.0,  0.0,   0.0, 1.0
    };
    return Mat_create_fromArray(4,4,data);
}
ns(Mat)* ns(Mat_create_4drotationY)(float angle){

    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));
    
    TYPE data[] = {
         _cos, 0.0, _sin, 0.0,
          0.0, 1.0,  0.0, 0.0,
        -_sin, 0.0, _cos, 0.0,
          0.0, 0.0,  0.0, 1.0
    };

    return Mat_create_fromArray(4,4,data);
}
ns(Mat)* ns(Mat_create_4drotationZ)(float angle){

    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));

    TYPE data[] = {
        _cos, -_sin, 0.0, 0.0,
        _sin,  _cos, 0.0, 0.0,
         0.0,   0.0, 1.0, 0.0,
         0.0,   0.0, 0.0, 1.0
    };
    return Mat_create_fromArray(4,4,data);
}
ns(Mat)* ns(Mat_create_4dtranslation)(TYPE x, TYPE y, TYPE z){
    TYPE data[] = {
        1.0, 0.0, 0.0,   x,
        0.0, 1.0, 0.0,   y,
        0.0, 0.0, 1.0,   z,
        0.0, 0.0, 0.0, 1.0
    };
    return Mat_create_fromArray(4,4,data);
}
ns(Mat)* ns(Mat_create_4dscale)(TYPE x, TYPE y, TYPE z){
    TYPE data[] = {
          x, 0.0, 0.0, 0.0,
        0.0,   y, 0.0, 0.0,
        0.0, 0.0,   z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    return Mat_create_fromArray(4,4,data);
}
ns(Mat)* ns(Mat_create_4dperspective)(TYPE fov, TYPE ratio, TYPE near, TYPE far){
    TYPE t = near * tan(fov / 2.0);
    TYPE r = t * ratio;
    TYPE data[] = {
        near/r, 0.0,    0.0,                      0.0,
        0.0,    near/t, 0.0,                      0.0,
        0.0,    0.0,    -(far+near)/(far-near),   -1, 
        0.0,    0.0,    (-2*far*near)/(far-near), 1.0,
    };
    ns(Mat)* a = Mat_create_fromArray(4,4, data);
    return a;
}
ns(Mat)* ns(Mat_create_lookAt)(ns(Vec)* cam_pos, ns(Vec)* target,ns(Vec)* up){
    ns(Vec)* foward = Vec4_create((VX(cam_pos)-VX(target)),
                                  (VY(cam_pos)-VY(target)),
                                  (VZ(cam_pos)-VZ(target)),
                                  (0));
    ns(Vec)* right = Vec4_cross(up,foward);
    ns(Vec)* newup = Vec4_cross(right, foward);
    TYPE data[] = {
        VX(right),  VY(right),  VZ(right),  0,
        VX(newup),  VY(newup),  VZ(newup),  0,
        VX(foward), VY(foward), VZ(foward), 0,
        VX(target), VY(target), VZ(target), 1,
    };
    ns(Mat)* result = Mat_create_fromArray(4, 4, data);

    ns(Mat_destroyAll)(&foward, &right, NULL);
    return result;
}
void ns(Mat_to_identity)(ns(Mat)** self){
    CHECK_NULL((*self));
    int i, j;
    for(i=0;i<(*self)->rows;i++){
        for(j=0;j<(*self)->colums;j++){
            if(i==j){
                MGET((*self),i,j) = 1.0;
            }
        }
    }
}
void ns(Mat_to_4drotationX)(ns(Mat)** self, float angle){
    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));

    TYPE data[] = {
        1.0,  0.0,   0.0, 0.0,
        0.0, _cos, -_sin, 0.0,
        0.0, _sin,  _cos, 0.0,
        0.0,  0.0,   0.0, 1.0
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_4drotationY)     (ns(Mat)** self, float angle){
    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));
    
    TYPE data[] = {
         _cos, 0.0, _sin, 0.0,
          0.0, 1.0,  0.0, 0.0,
        -_sin, 0.0, _cos, 0.0,
          0.0, 0.0,  0.0, 1.0
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_4drotationZ)     (ns(Mat)** self, float angle){
    TYPE _cos = cosf(GLA_ANGLE(angle));
    TYPE _sin = sinf(GLA_ANGLE(angle));

    TYPE data[] = {
        _cos, -_sin, 0.0, 0.0,
        _sin,  _cos, 0.0, 0.0,
         0.0,   0.0, 1.0, 0.0,
         0.0,   0.0, 0.0, 1.0
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_4dtranslation)   (ns(Mat)** self, TYPE x, TYPE y, TYPE z){
    TYPE data[] = {
        1.0, 0.0, 0.0,   x,
        0.0, 1.0, 0.0,   y,
        0.0, 0.0, 1.0,   z,
        0.0, 0.0, 0.0, 1.0
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_4dscale)         (ns(Mat)** self, TYPE x, TYPE y, TYPE z){
    TYPE data[] = {
          x, 0.0, 0.0, 0.0,
        0.0,   y, 0.0, 0.0,
        0.0, 0.0,   z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_4dperspective)   (ns(Mat)** self, TYPE fov, TYPE ratio, TYPE near, TYPE far){
    TYPE t = near * tan(fov / 2.0);
    TYPE r = t * ratio;
    TYPE data[] = {
        near/r, 0.0,    0.0,                      0.0,
        0.0,    near/t, 0.0,                      0.0,
        0.0,    0.0,    -(far+near)/(far-near),   -1, 
        0.0,    0.0,    (-2*far*near)/(far-near), 1.0,
    };
    Mat_set_fromArray(self, data);
}
void ns(Mat_to_lookAt)          (ns(Mat)** self, ns(Vec)* cam_pos, ns(Vec)* target, ns(Vec)* up){
    ns(Vec)* foward = Vec4_create((VX(cam_pos)-VX(target)),
                                  (VY(cam_pos)-VY(target)),
                                  (VZ(cam_pos)-VZ(target)),
                                  (0));
    ns(Vec)* right = Vec4_cross(up,foward);
    ns(Vec)* newup = Vec4_cross(right, foward);
    TYPE data[] = {
        VX(right),  VY(right),  VZ(right),  0,
        VX(newup),  VY(newup),  VZ(newup),  0,
        VX(foward), VY(foward), VZ(foward), 0,
        VX(target), VY(target), VZ(target), 1,
    };


    ns(Mat_destroyAll)(&foward, &right, &newup, NULL);
    ns(Mat_set_fromArray)(self, data);
}
ns(Mat)* Mat_fill(ns(Mat)* self,TYPE x){
    CHECK_NULL(self);
    int i;
    for(i=0;i<self->rows*self->colums;i++){
        self->data[i] = x;
    }
    return self;
}
ns(Mat)* ns(Mat_fill_op)(ns(Mat)* self, TYPE (*operation)(int i, int j, int x)){
    CHECK_NULL(self);
    int i, j, x=0;
    for(i=0;i<self->rows;i++){
        for(j=0;j<self->colums;j++){
            MGET(self,i,j) = operation(i,j,x);
            x++;
        }
    }
    return self;
}
void ns(Mat_destroy)(ns(Mat)** self){
    free(*self);
    *self = NULL;
}

void ns(Mat_destroyAll)(ns(Mat)** first, ...){
    va_list list;
    va_start(list, first);
    ns(Mat)** temp;
    while((temp = va_arg(list, ns(Mat)**)) != NULL ){
        ns(Mat_destroy)(temp);
    }
    Mat_destroy(first);
    va_end(list);
}
void ns(Mat_print)(ns(Mat)* self){
    CHECK_NULL(self);
    int i, j;
    printf("Matrix [%zd][%zd]\n", self->rows, self->colums); 
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
void ns(Mat_prints)(ns(Mat)* self, char* text){
    CHECK_NULL(self);
    int i, j;
    printf("Matrix [%zd][%zd]: %s\n", self->rows, self->colums, text); 
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
// TODO
void ns(Mat_set_fromArray)(ns(Mat)** self, TYPE* data){
    CHECK_NULL(*self);
    int x;

    for(x = 0; x < (*self)->rows*(*self)->colums;x++){
        MGETL((*self),x) = data[x];
    }
}

/*================================== Operations ==================================*/
ns(Mat)* ns(Mat_op)(ns(Mat)* self, ns(Mat)* other, TYPE (*operation)(TYPE a, TYPE b)){
    CHECK_NULL(self);CHECK_NULL(other);
    COMPARE_SIZE2(self,other);

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
    COMPARE_SIZE2(a,b);
    ns(Mat)* c = Mat_create(a->rows, a->colums);
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
    COMPARE_SIZE2(self,other);
    return ns(Mat_op)(self, other, type_addTrait);
}
ns(Mat)* ns(Mat_addC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    COMPARE_SIZE2(a,b);
    ns(Mat) *c = ns(Mat_opC)(a, b, type_addTrait);
    return c;
}
//Sub
ns(Mat)* ns(Mat_sub)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    COMPARE_SIZE2(self,other);
    return ns(Mat_op)(self, other, type_subTrait);
}

ns(Mat)* ns(Mat_subC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    COMPARE_SIZE2(a,b);
    ns(Mat) *c = ns(Mat_opC)(a, b, type_subTrait);
    return c;
}

//Multiplication
ns(Mat)* ns(Mat_schur_mult)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    COMPARE_SIZE2(self,other);
    return ns(Mat_op)(self, other, type_multTrait);
}

ns(Mat)* ns(Mat_schur_multC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    COMPARE_SIZE2(a,b);
    ns(Mat) *c = ns(Mat_opC)(a, b, type_multTrait);
    return c;
}
// Dot product
// O³ complexity
ns(Mat)* ns(Mat_create_naive_mult)(ns(Mat)* a, ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    CHECK_MULTSIZE(a,b);
    ns(Mat)* c = Mat_create(a->rows, b->colums);
   
    ns(Mat_naive_mult)(&c, a, b);
    return c;
}
// not yet implemented
// https://www.geeksforgeeks.org/strassens-matrix-multiplication/
// TODO, implement strassen multiplication
ns(Mat)* ns(Mat_create_strassen_mult)(ns(Mat)* a, ns(Mat)* b){
    ns(Mat)* rt = ns(Mat_create)(a->rows, a->colums);
    return rt;
}

// TODO, verify macro and use strassen or naive
ns(Mat)* ns(Mat_create_mult)(ns(Mat)* a, ns(Mat)* b){
    return ns(Mat_create_naive_mult)(a,b);
}


void ns(Mat_naive_mult)(ns(Mat)** result, ns(Mat)* a, ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);CHECK_NULL((*result));
    COMPARE_SIZE3(a,b,*result);
    int i, j, k; 
    for (i = 0; i < a->rows; i++){ 
        for (j = 0; j < b->colums; j++) { 
            for (k = 0; k < a->colums; k++) {
                MGET((*result),i,j) += MGET(a,i,k) *  MGET(b,k,j); 
            }
        }
    }
}
// TODO, implement
void ns(Mat_strassen_mult)(ns(Mat)** result, ns(Mat)* a, ns(Mat)* b);
void ns(Mat_mult)(ns(Mat)** result, ns(Mat)* a, ns(Mat)* b);
//Div
ns(Mat)* ns(Mat_div)(ns(Mat)* self, ns(Mat)* other){
    CHECK_NULL(self);CHECK_NULL(other);
    COMPARE_SIZE2(self,other);
    return ns(Mat_op)(self, other, type_divTrait);
}

ns(Mat)* ns(Mat_divC)(ns(Mat)* a ,ns(Mat)* b){
    CHECK_NULL(a);CHECK_NULL(b);
    COMPARE_SIZE2(a,b);
    ns(Mat) *c = ns(Mat_opC)(a, b, type_divTrait);
    return c;
}
ns(Mat)* ns(Mat_factor) (ns(Mat)* a, TYPE factor){
    CHECK_NULL(a);
    int x;
    for(x=0;x<a->rows*a->colums;x++){
        MGETL(a, x) *= factor;
    }
    return a;
}
/*================================== Vec ==================================*/
// Constructors
ns(Vec)* ns(Vec4_create)(TYPE x, TYPE y, TYPE z, TYPE w){
    ns(Mat)* a = Mat_create(4, 1);
    a->data[0] = x;
    a->data[1] = y;
    a->data[2] = z;
    a->data[3] = w;

    return a;
}

// Destructors
void ns(Vec4_destroy)(ns(Vec)* self){
    CHECK_NULL(self);
   // ns(Mat_destroy)(self);
}
void ns(Vec4_destroyAll) (int n, ...){
    va_list list;
    int i;

    va_start(list, n);
    for(i=0;i<n;i++){
        //ns(Mat_destroy)(va_arg(list, ns(Vec)*));
    }
    va_end(list);
}

// Get 
TYPE ns(Vec4_getX)(ns(Vec)* self){
    return ns(Vec4_get)(self, 0);
}
TYPE ns(Vec4_getY)(ns(Vec)* self){
    return ns(Vec4_get)(self, 1);
}
TYPE ns(Vec4_getZ)  (ns(Vec)* self){
    return ns(Vec4_get)(self, 2);
}
TYPE ns(Vec4_getW)  (ns(Vec)* self){
    return ns(Vec4_get)(self, 3);
}
TYPE ns(Vec4_get)   (ns(Vec)* self, int x){
    CHECK_NULL(self);
    return ns(Vec4_get)(self, x);
}
// Set
ns(Vec)* ns(Vec4_setX) (ns(Vec)* self, TYPE x){
    CHECK_NULL(self);
    self->data[0] = x;
    return self;
}
ns(Vec)* ns(Vec4_setY) (ns(Vec)* self, TYPE y){
    CHECK_NULL(self);
    self->data[1] = y;
    return self;
}
ns(Vec)* ns(Vec4_setZ) (ns(Vec)* self, TYPE z){
    CHECK_NULL(self);
    self->data[2] = z;
    return self;
}
ns(Vec)* ns(Vec4_setW) (ns(Vec)* self, TYPE w){
    CHECK_NULL(self);
    self->data[3] = w;
    return self;
}
ns(Vec)* ns(Vec4_set)  (ns(Vec)* self, TYPE x, TYPE y, TYPE z, TYPE w){
    CHECK_NULL(self);
    self->data[0] = x;
    self->data[1] = y;
    self->data[2] = z;
    self->data[3] = w;
    return self;
}
TYPE ns(Vec4_length)(ns(Vec)* self){
    return sqrtf(ns(Vec4_lengthSq)(self));
}
TYPE ns(Vec4_lengthSq)(ns(Vec)* self){
    CHECK_NULL(self);
    return  (self->data[0] * self->data[0])+
            (self->data[1] * self->data[1])+
            (self->data[2] * self->data[2]);
}
ns(Vec)* ns(Vec4_normalize)(ns(Vec)* self){
    TYPE lng = ns(Vec4_length)(self);
    self->data[0] /= lng;
    self->data[1] /= lng;
    self->data[2] /= lng;
    return self;
}
//Operations
ns(Vec)* ns(Vec4_add)(ns(Vec)* self,ns(Vec)* other){
    return ns(Mat_add)(self,other);
}
ns(Vec)* ns(Vec4_sub)(ns(Vec)* self,ns(Vec)* other){
    return ns(Mat_sub)(self,other);
}
ns(Vec)* ns(Vec4_mult)(ns(Vec)* self,ns(Vec)* other){
    return ns(Mat_creat_mult)(self,other);
}
ns(Vec)* ns(Vec4_div)(ns(Vec)* self,ns(Vec)* other){
    return ns(Mat_div)(self,other);
}
TYPE     ns(Vec4_dot)(ns(Vec)* self,ns(Vec)* other){
    return (((VGET(self,0)*VGET(other,0)))+
            ((VGET(self,1)*VGET(other,1)))+
            ((VGET(self,2)*VGET(other,2))));
}
ns(Vec)* ns(Vec4_cross)(ns(Vec)* a,ns(Vec)* b){
    ns(Vec)* newVec = ns(Vec4_create)(0,0,0,0);
    VGET(newVec,0) = VGET(a,1) * VGET(b,2) - VGET(a,2) * VGET(b,1);
    VGET(newVec,1) = VGET(a,2) * VGET(b,0) - VGET(a,0) * VGET(b,2);
    VGET(newVec,2) = VGET(a,0) * VGET(b,1) - VGET(a,1) * VGET(b,0);
    return newVec;
}
bool     ns(Vec4_naive_equal)(ns(Vec)* a,ns(Vec)* b){
    return ((VGET(a,0)==VGET(b,0))&&
            (VGET(a,1)==VGET(b,1))&&
            (VGET(a,2)==VGET(b,2)));
}
//TODO 
bool     ns(Vec4_safe_equal)(ns(Vec)* a,ns(Vec)* b);
bool     ns(Vec4_equal)(ns(Vec)* a, ns(Vec)* b){
    return ns(Vec4_naive_equal)(a,b);
}

//#endif //GLNAMESPACE
#endif //GLALGEBRA_IMPLEMENTATION
#endif // GLALGEBRA_H
