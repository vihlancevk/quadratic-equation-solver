#ifndef TESTPROGRAM_H_
#define TESTPROGRAM_H_

void testCompareZero(double number, int correctAnswer);

void testSolveLinearEquation(double a, double b, double correctX, int correctRootsCount);

void testSolveQuadraticEquation(double a, double b, double c, double correctX1,
                                double correctX2, int correctRootsCount);

void processCommandLineArguments(const int argc, char const *argv[]);

void testProgram();

#endif

