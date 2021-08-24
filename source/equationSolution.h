#ifndef EQUATIONSOLUTION_H_
#define EQUATIONSOLUTION_H_

const int INF_ROOTS = -1;

bool isLessZero(float number);
bool isEqualZero(float number);
int solveLinearEquation(float a, float b, float *x);
int solveQuadraticEquation(float a, float b, float c, float *x1, float *x2);

#endif
