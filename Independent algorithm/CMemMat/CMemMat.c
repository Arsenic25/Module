/*
 * CMemMat.c
 *
 *  Created on: 2020/2/28
 *      Author: Arsenic
 */

#include"CMemMat.h"

/***vector***/
void vprint(float* a) {

}

float* vadd(float* a, float* b, float* ans) {
    ans[0] = a[0] + b[0];
    ans[1] = a[1] + b[1];
    ans[2] = a[2] + b[2];
    return ans;
}

float* vaddo(float*a, float* b) {
    b[0] = a[0] + b[0];
    b[1] = a[1] + b[1];
    b[2] = a[2] + b[2];
    return b;
}

float* vsub(float* a, float* b, float* ans) {
    ans[0] = a[0] - b[0];
    ans[1] = a[1] - b[1];
    ans[2] = a[2] - b[2];
    return ans;
}

float* vsubo(float* a, float* b) {
    b[0] = a[0] - b[0];
    b[1] = a[1] - b[1];
    b[2] = a[2] - b[2];
    return b;
}

float vdot(float* a, float* b) {
    float ans = 0;
    ans = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

float* vcross(float* a, float* b, float* ans) {
    ans[0] = a[1]*b[2] - a[2]*b[1];
    ans[1] = a[2]*b[0] - a[0]*b[2];
    ans[2] = a[0]*b[1] - a[1]*b[0];
    return ans;
}

float* vcrosso(float* a, float* b) {
    float ans[3];
    ans[0] = a[1]*b[2] - a[2]*b[1];
    ans[1] = a[2]*b[0] - a[0]*b[2];
    ans[2] = a[0]*b[1] - a[1]*b[0];
    b[0] = ans[0];
    b[1] = ans[1];
    b[2] = ans[2];
    return b;
}

float* vA(float* v, float* R) {
    R[0] = 0.0f;
    R[1] = -v[2];
    R[2] = v[1];

    R[3] = v[2];
    R[4] = 0.0f;
    R[5] = -v[0];
    
    R[6] = -v[1];
    R[7] = v[0];
    R[8] = 0.0f;

    return R;
}

/***matrix***/
void mprint(float* a) {
    for (int n = 0; n < 3; n++) {
        for (int m = 0; m < 3; m++) {
            printf("\t%f,", a[3*n + m]);
        }
        printf("\n");
    }
}

float mget(float* a, int n, int m) {
    return a[n*3 + m];
}

float* mset(float* a, int n, int m, float v) {
    a[3*n + m] = v;
    return &a[3*n + m];
}

float* mT(float* a, float* ans) {
    for (int n = 0; n < 3; n++) {
        for(int m = 0; m < 3; m++) {
            ans[3*n + m] = a[3*m + n];
        }
    }
    return ans;
}

float* mTo(float* a) {
    float ans[3][3];
    float* p = mT(a, ans);
    for (int n = 0; n < 9; n++) {
        a[n] = p[n];
    }   
}

float* madd(float* a, float* b, float* ans) {
    for (int n = 0; n < 9; n++) {
        ans[n] = a[n] + b[n];
    }
    return ans;
}

float* maddo(float* a, float* b) {
    float ans[3][3];
    float* p = madd(a, b, ans);
    for (int n = 0; n < 9; n++) {
        b[n] = p[n];
    }
}

float* msub(float* a, float* b, float* ans) {
    for (int n = 0; n < 9; n++) {
        ans[n] = a[n] - b[n];
    }
    return ans;
}

float* msubo(float* a, float* b) {
    float ans[3][3];
    float* p = msub(a, b, ans);
    for (int n = 0; n < 9; n++) {
        b[n] = p[n];
    }
}

float* mmult(float* a, float* b, float* ans) {
    for (int i = 0; i < 9; i++) ans[i] = 0.0f;
    for (int n = 0; n < 3; n++) 
        for(int m = 0; m < 3; m++)
            for (int i = 0; i < 3; i++) 
                ans[3*n + m] += a[3*n + i]*b[3*i + m];
    return ans;
}

float* mmulto(float* a, float* b) {
    float ans[3][3];
    float* p = mmult(a, b, ans);
    for (int n = 0; n < 9; n++) {
        b[n] = p[n];
    }
}

float* mV(float* R, float* v) {
    v[0] = R[7];
    v[1] = R[2];
    v[2] = R[3];
    return v;
}

float* mrod(float* a, float q, float* ans) {
    float s = sin(q);
    float c = cos(q);
    float inc = 1 - c;
    float xyc = a[0]*a[1]*inc;
    float yzc = a[1]*a[2]*inc;
    float zxc = a[2]*a[0]*inc;
    float xs = a[0]*s;
    float ys = a[1]*s;
    float zs = a[2]*s;

    ans[0] = c + a[0]*a[0]*inc;
    ans[1] = xyc - zs;
    ans[2] = zxc + ys;

    ans[3] = xyc + zs;
    ans[4] = c + a[1]*a[1]*inc;
    ans[5] = yzc - xs;
    
    ans[6] = zxc - ys;
    ans[7] = yzc + xs;
    ans[8] = c + a[2]*a[2]*inc;
    
    return ans;
}

float* rotv(float* R, float* v, float* ans) {
    ans[0] = R[0]*v[0] + R[1]*v[1] + R[2]*v[2];
    ans[1] = R[3]*v[0] + R[4]*v[1] + R[5]*v[2];
    ans[1] = R[6]*v[0] + R[7]*v[1] + R[8]*v[2];
}

float* rotvo(float* R, float* v) {

}