#ifndef EQUATIONSOLVING_H_
#define EQUATIONSOLVING_H_

const int INF_ROOTS = -1;

int compareZero(double number);

int solveLinearEquation(double a, double b, double *x);

int solveQuadraticEquation(double a, double b, double c, double *x1, double *x2);

#endif

