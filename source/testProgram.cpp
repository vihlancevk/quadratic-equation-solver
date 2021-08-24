#include <stdio.h>
#include <string.h>
#include"testProgram.h"
#include"userInteraction.h"
#include"equationSolution.h"

//------------------------------------------------------------------------------------------
//! @brief Тестирование функций isLessZero и isEqualZero на корректность работы.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//! @param [in] correctIsLessZero ответ, который должна вернуть функция
//!             isLessZero при корректной работе, если в качестве аргумента
//!             ей передать число number.
//! @param [in] correctIsEqualZero ответ, который должна вернуть функция
//!             isLessZero при корректной работе, если в качестве аргумента
//!             ей передать число number.
//!
//! @note в случае коректной работы функций isLessZero и isEqualZero, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testIsLessZeroAndIsEqualZero(float number, bool correctIsLessZero, bool correctIsEqualZero)
{
    bool returnIsLessZero = isLessZero(number);
    bool returnIsEqualZero = isEqualZero(number);

    printf("[%s]isLessZero(%.4f) returned: %d, expected: %d\n",
           returnIsLessZero == correctIsLessZero ? "correct" : "incorrect",
           number, returnIsLessZero, correctIsLessZero);

    printf("[%s]isEqualZero(%.4f) returned: %d, expected: %d\n",
           returnIsEqualZero == correctIsEqualZero ? "correct" : "incorrect",
           number, returnIsEqualZero, correctIsEqualZero);
}

//------------------------------------------------------------------------------------------
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
//! @note в случае коректной работы функции solveLinearEquation, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testSolveLinearEquation(float a, float b, float correctX, int correctRootsCount)
{
    float x = 0;
    int rootsCount = 0;

    rootsCount = solveLinearEquation(a, b, &x);
    printf("[%s]solveLinearEquation(%.3f, %.3f) returned: "
           "%.3f and %d, expected: %.3f and %d\n",
           isEqualZero(x - correctX) && rootsCount == correctRootsCount ? "correct" : "incorrect",
           a, b, x, rootsCount, correctX, correctRootsCount);
}

//------------------------------------------------------------------------------------------
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
//! @note в случае коректной работы функции solveQuadraticEquation, в консоль будет выведенно
//!       соответствующее сообщение.
//------------------------------------------------------------------------------------------
void testSolveQuadraticEquation(float a, float b, float c, float correctX1, float correctX2, int correctRootsCount)
{
    float x1 = 0;
    float x2 = 0;
    int rootsCount = 0;

    rootsCount = solveQuadraticEquation(a, b, c, &x1, &x2);
    printf("[%s]solveQuadraticEquation(%.3f, %.3f, %.3f) returned: "
           "%.3f, %.3f and %d, expected: %.3f, %.3f and %d\n",
           isEqualZero(x1 - correctX1) && isEqualZero(x2 - correctX2)&& rootsCount == correctRootsCount ? "correct" : "incorrect",
           a, b, c, x1, x2, rootsCount,
           correctX1, correctX2, correctRootsCount);
}

//------------------------------------------------------------------------------------------
//! @brief Функция обработки аргументов командной строки.
//!
//! @param [in] argc количество аргументов командной строки.
//! @param [in] argv массив аргументов командной строки.
//!
//! @note в случае, если одним из элементов массива argv будет строка "--test"
//!       или "-t", то будет вызвана функция testProgram.
//------------------------------------------------------------------------------------------
void processCommandLineArguments(int argc, char *argv[])
{
    for (int i = 0; i < argc; i += 1)
    {
        if (!strcmp(argv[i], "--test") || !strcmp(argv[i], "-t"))
        {
            testProgram();
            break;
        }
    }
}

//------------------------------------------------------------------------------------------
//! @brief Функция тестирование программы на коректность работы.
//!
//! @note  функция testProgram вызывает тестирующие функции: testIsLessZero,
//!        testIsEqualZero, testSolveLinearEquation и testSolveQuadraticEquation,
//!        которые в свою очередь проверят на корректность работы соответствующие им
//!        функции: isLessZero, isEqualZero, solveLinearEquation и solveQuadraticEquation.
//------------------------------------------------------------------------------------------
void testProgram()
{
    testIsLessZeroAndIsEqualZero(-1.0f,    true,  false);
    testIsLessZeroAndIsEqualZero(-0.0011f, true,  false);
    testIsLessZeroAndIsEqualZero(-0.001f,  false, true);
    testIsLessZeroAndIsEqualZero( 0.0f,    false, true);
    testIsLessZeroAndIsEqualZero( 0.001f,  false, true);
    testIsLessZeroAndIsEqualZero( 0.0011f, false, false);
    testIsLessZeroAndIsEqualZero( 1.0f,    false, false);

    testSolveLinearEquation(0, 0,  0, INF_ROOTS);
    testSolveLinearEquation(0, 1,  0, 0);
    testSolveLinearEquation(1, 1, -1, 1);

    testSolveQuadraticEquation(1, 1,  1,  0, 0, 0);
    testSolveQuadraticEquation(0, 0,  0,  0, 0, INF_ROOTS);
    testSolveQuadraticEquation(1, 2,  1, -1, 0, 1);
    testSolveQuadraticEquation(1, 5, -6, -6, 1, 2);
}
