/*
 * CMemMat.h
 *
 *  Created on: 2020/2/28
 *      Author: Arsenic
 */

#ifndef CMEMMAT_H_
#define CMEMMAT_H_

#include <math.h>

/***vector***/
void vprint(float* a);                              //print vector
float* vadd(float* a, float* b, float* ans);        //ans = a + b
float* vaddo(float*a, float* b);                    //b = a + b
float* vsub(float* a, float* b, float* ans);        //ans = a - b
float* vsubo(float* a, float* b);                   //b = a - b
float vdot(float* a, float* b);                     //inner product a and b
float* vcross(float* a, float* b, float* ans);      //outer product a and b
float* vcrosso(float* a, float* b);                 //b = outer product a and b
float* vA(float* v, float* R);                      //produce Skew symmetric matrix from vector

/***matrix***/
void mprint(float* a);                              //print matrix
float mget(float* a, int n, int m);                 //get element of matrix
float* mset(float* a, int n, int m, float v);       //set element of matrix
float* mT(float* a, float* ans);                    //transposition matrix
float* mTo(float* a);                               //transposition matrix overwrite
float* madd(float* a, float* b, float* ans);        //ans = a + b
float* maddo(float* a, float* b);                   //b = a + b
float* msub(float* a, float* b, float* ans);        //ans = a - b 
float* msubo(float* a, float* b);                   //b = a - b
float* mmult(float* a, float* b, float* ans);       //ans = ab
float* mmulto(float* a, float* b);                  //b = ab
float* mV(float* R, float* v);                      //produce vector from Skew symmetric matrix
float* mrod(float* a, float q, float* ans);         //produce rotation matrix from unit rotation vector and rotation position q[rad]


#endif /* CMEMMAT_H_ */