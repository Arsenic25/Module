/*
 * CMemMat.h
 *
 *  Created on: 2020/2/28
 *      Author: Arsenic
 */

#ifndef CMEMMAT_H_
#define CMEMMAT_H_

/***vector***/
void vprint(float* a);
float* vadd(float* a, float* b, float* ans);
float* vaddo(float*a, float* b);
float* vsub(float* a, float* b, float* ans);
float* vsubo(float* a, float* b);
float vdot(float* a, float* b);
float* vcross(float* a, float* b, float* ans);
float* vcrosso(float* a, float* b);

/***matrix***/
void mprint(float* a);
float mget(float* a, int n, int m);
float* mset(float* a, int n, int m, float v);
float* mT(float* a, float* ans);
float* mTo(float* a);
float* madd(float* a, float* b, float* ans);
float* maddo(float* a, float* b);
float* msub(float* a, float* b, float* ans);
float* msubo(float* a, float* b);
float* mmult(float* a, float* b, float* ans);
float* mmulto(float* a, float* b);

#endif /* CMEMMAT_H_ */