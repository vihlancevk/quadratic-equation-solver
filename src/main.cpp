//==========================================================================================
//! @brief Вычисление корней квадратного уравнения.
//!
//! @author Костя Вихлянцев (https://github.com/vihlancevk/quadratic-equation-solver)
//! @file main.cpp
//! @date 22.08.2021
//!
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------------------

#include <stdio.h>
#include "../include/testProgram.h"
#include "../include/userInteraction.h"
#include "../include/equationSolving.h"

int main(const int argc, const char *argv[])
{
    processCommandLineArguments(argc, argv);

    printf("Enter coefficients in quadratic equation in format a*x^2 + b*x + c = 0\n");

    float a = readCoefficient('a');
    float b = readCoefficient('b');
    float c = readCoefficient('c');

    float x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation(a, b, c, &x1, &x2);

    outputAnswer(x1, x2, rootsCount);

    return 0;
}
