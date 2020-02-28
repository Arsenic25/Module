/*
 * link.h
 *
 *  Created on: 2020/2/28
 *      Author: Arsenic
 */

#ifndef MEMMAT_H_
#define MEMMAT_H_

/***vector***/
void vprint(float* a);
float* vadd(float* a, float* b, float* ans);
float* vaddo(float*a, float* b);
float* vdot(float* a, float* b, float* ans);
float* vdoto(float* a, float* b);

/***matrix***/
void mprint(float* a);
float* madd(float* a, float* b, float* ans);
float* maddo(float* a, float* b);


#endif /* MEMMAT_H_ */