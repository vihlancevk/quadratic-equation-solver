#ifndef TESTPROGRAM_H_
#define TESTPROGRAM_H_

void testCompareZero(float number, int correctAnswer);
void testSolveLinearEquation(float a, float b, float correctX, int correctRootsCount);
void testSolveQuadraticEquation(float a, float b, float c, float correctX1,
                                float correctX2, int correctRootsCount);
void processCommandLineArguments(const int argc, char const *argv[]);
void testProgram();

#endif

