#include <stdio.h>
#include <string.h>
#include "../include/testProgram.h"
#include "../include/userInteraction.h"
#include "../include/equationSolving.h"

//==========================================================================================
//! @brief Тестирование функции compareZero на корректность работы.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//! @param [in] correctAnswer ответ, который должна вернуть функция
//!             campareZero при корректной работе, если в качестве аргумента
//!             ей передать число number
//!
//! @note В случае коректной работы функции compareZero, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testCompareZero(double number, int correctAnswer)
{
    int returnAnswer = compareZero(number);

    printf("[%s]compareZero(%.4f) returned: %d, expected: %d\n",
           (returnAnswer == correctAnswer) ? "correct" : "incorrect",
           number, returnAnswer, correctAnswer);
}

//==========================================================================================
//! @brief Тестирование функции solveLinearEquation,
//!        решающей линейные уравнения вида a*x + b = 0, на корректность работы.
//!
//! @param [in] a линейный коэффициент линейного уравнения.
//! @param [in] b коэффициент линейного уравнения (свободный член).
//! @param [in] correctX корень, который должна вернуть функция
//!        solveLinearEquation при корректной работе, если в качестве аргументов
//!        ей передать числа a и b.
//! @param [in] correctRootsCount количество кореней, которые должна вернуть функция
//!        solveLinearEquation при корректной работе, если в качестве аргументов
//!        ей передать числа a и b.
//!
//! @note В случае коректной работы функции solveLinearEquation, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testSolveLinearEquation(double a, double b, double correctX, int correctRootsCount)
{
    double x = 0;
    int rootsCount = solveLinearEquation(a, b, &x);

    printf("[%s]solveLinearEquation(%.3f, %.3f) returned: "
           "%.3f and %d, expected: %.3f and %d\n",
           (compareZero(x - correctX) == 0 && rootsCount == correctRootsCount) ? "correct" : "incorrect",
           a, b, x, rootsCount, correctX, correctRootsCount);
}

//==========================================================================================
//! @brief Тестирование функции solveQuadraticEquation,
//!        решающей квадратные уравнения вида a*x^2 + b*x + c = 0, на корректность работы.
//!
//! @param [in] a коэффициент квадратного уравнения (старший коэффициент).
//! @param [in] b коэффициент квадратного уравнения (коэффициент при x).
//! @param [in] c коэффициент квадратного уравнения (свободный член).
//! @param [in] correctX1 первый корень, который должна вернуть функция
//!        solveQuadraticEquation при корректной работе, если в качестве аргументов
//!        ей передать числа a, b и c.
//! @param [in] correctX2 второй корень, который должна вернуть функция
//!        solveQuadraticEquation при корректной работе, если в качестве аргументов
//!        ей передать числа a, b и c.
//! @param [in] correctRootsCount количество кореней, которые должна вернуть функция
//!        solveQuadraticEquation при корректной работе, если в качестве аргументов
//!        ей передать числа a, b и c.
//!
//! @note В случае коректной работы функции solveQuadraticEquation, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testSolveQuadraticEquation(double a, double b, double c, double correctX1, double correctX2, int correctRootsCount)
{
    double x1 = 0, x2 = 0;
    int rootsCount = solveQuadraticEquation(a, b, c, &x1, &x2);

    printf("[%s]solveQuadraticEquation(%.3f, %.3f, %.3f) returned: "
           "%.3f, %.3f and %d, expected: %.3f, %.3f and %d\n",
           (compareZero(x1 - correctX1) == 0 && compareZero(x2 - correctX2) == 0 && rootsCount == correctRootsCount) ? "correct" : "incorrect",
           a, b, c, x1, x2, rootsCount,
           correctX1, correctX2, correctRootsCount);
}

//==========================================================================================
//! @brief Функция обработки аргументов командной строки.
//!
//! @param [in] argc количество аргументов командной строки.
//! @param [in] argv массив аргументов командной строки.
//!
//! @note В случае, если одним из элементов массива argv будет строка "--test"
//!       или "-t", то будет вызвана функция testProgram.
//------------------------------------------------------------------------------------------
void processCommandLineArguments(const int argc, const char *argv[])
{
    #ifdef DEBUG
        testProgram();
    #endif

    for (int i = 0; i < argc; i += 1)
    {
        if (!strcmp(argv[i], "--test") || !strcmp(argv[i], "-t"))
        {
            testProgram();
            break;
        }
    }
}

//==========================================================================================
//! @brief Функция тестирование программы на коректность работы.
//!
//! @note  Функция testProgram вызывает тестирующие функции: testIsLessZero,
//!        testIsEqualZero, testSolveLinearEquation и testSolveQuadraticEquation,
//!        которые в свою очередь проверят на корректность работы соответствующие им
//!        функции: isLessZero, isEqualZero, solveLinearEquation и solveQuadraticEquation.
//------------------------------------------------------------------------------------------
void testProgram()
{
    testCompareZero(-1.0f,    -1);
    testCompareZero(-0.0011f, -1);
    testCompareZero(-0.001f,   0);
    testCompareZero( 0.0f,     0);
    testCompareZero( 0.001f,   0);
    testCompareZero( 0.0011f,  1);
    testCompareZero( 1.0f,     1);

    testSolveLinearEquation(0, 0,  0, INF_ROOTS);
    testSolveLinearEquation(0, 1,  0, 0);
    testSolveLinearEquation(1, 1, -1, 1);

    testSolveQuadraticEquation(1, 1,  1,  0, 0, 0);
    testSolveQuadraticEquation(0, 0,  0,  0, 0, INF_ROOTS);
    testSolveQuadraticEquation(1, 2,  1, -1, 0, 1);
    testSolveQuadraticEquation(1, 5, -6, -6, 1, 2);
}
