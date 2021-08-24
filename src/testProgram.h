#ifndef TESTPROGRAM_H_
#define TESTPROGRAM_H_

void testIsLessZeroAndIsEqualZero(float number, bool correctIsLessZero, bool correctIsEqualZero);
void testSolveLinearEquation(float a, float b, float correctX, int correctRootsCount);
void testSolveQuadraticEquation(float a, float b, float c, float correctX1,
                                float correctX2, int correctRootsCount);
void processCommandLineArguments(int argc, char *argv[]);
void testProgram();

#endif
