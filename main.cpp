//-------------------------------------------------------------------------------------------
//! @brief Высисление корней квадратного уравенения.
//!
//! @author Костя Вихлянцев (https://github.com/vihlancevk/quadratic-equation-solver)
//! @file main.cpp
//! @date 22.08.2021
//!
//! @copyright Copyright (c) 2021
//-------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

const int INF_ROOTS = 3;
const float PRECISION = 0.001f;

void clearInputBuffer();
float readCoefficient(char coefficientSymbol);
void outputAnswer(float x1, float x2, int rootsCount);
bool isLessZero(float number);
bool isEqualZero(float number);
void solveLinearEquation(float a, float c, float *x, int *rootsCount);
void solveQuadraticEquation(float a, float b, float c, float *x1, float *x2, int *rootsCount);

int main()
{
    float a = 0, b = 0, c = 0;

    printf("Enter coefficients in quadratic equation in format a*x^2 + b*x + c = 0\n");

    a = readCoefficient('a');
    b = readCoefficient('b');
    c = readCoefficient('c');

    int rootsCount = 0;
    float x1 = 0, x2 = 0;

    solveQuadraticEquation(a, b, c, &x1, &x2, &rootsCount);

    outputAnswer(x1, x2, rootsCount);

    return 0;
}

//-------------------------------------------------------------------------------------------
//! Очистка ввода с консоли.
//-------------------------------------------------------------------------------------------
void clearInputBuffer()
{
    while (getchar() != '\n');
}

//-------------------------------------------------------------------------------------------
//! Считывание с консоли введённого коэффициента квадратного уравнения.
//!
//! @param [in] coefficientDesignation буквенное обозначение вводимого коэффициента.
//!
//! @note пользователь поочередно вводит коэффициенты a, b и с соответсвенно квадратного уравнения вида a*x^2 + b*x + c = 0;
//!       после ввода одного из коэфиициентов ему необходимо нажать Enter, чтобы перейти к вводу другого или закончить его,
//!       если он ввел коэффициент c.
//!
//! @return введённое с консоли число.
//-------------------------------------------------------------------------------------------
float readCoefficient(char coefficientSymbol)
{
    float number = 0;

    printf("%c: ", coefficientSymbol);
    int isCorrectInput = scanf("%f", &number);

    while (isCorrectInput == 0 || getchar() != '\n')
    {
        clearInputBuffer();

        printf("Please, enter the correct value for the coefficient\n");
        printf("%c: ", coefficientSymbol);
        isCorrectInput = scanf("%f", &number);
    }

    return number;
}

//-------------------------------------------------------------------------------------------
//! Вывод решения квадратного уравнения на консоль.
//!
//! @param [in] x1 первый корень уравнения.
//! @param [in] x2 второй корень уравнения.
//! @param [in] rootsCount количество корней уравнения.
//!
//! @note в консоле польхователь увидит один из возможных вариантов вывода:
//!       1) No valid roots - это значит, что у квадратного уравнения нет действительных корней;
//!       2) The quadratic equation has only one root: x1 - это значит, что квадратное уравнение имеет только один корень x1,
//!       где x1 - вещественное число;
//!       3) The quadratic equation has two roots:
//!       x1 and x2 - это значит, что квадратное уравнение имеет два корня: x1 и x2, где x1 и x2 - вещественные числа;
//!       4) Infinitely many roots - это значит, что квадратное уравнение имеет бесконечно много корней.
//!
//! @warning в случае, если в ходе выполнения программы на вход данной функции придёт параметр rootCount с недопустимым
//!          для него значение (допустимые значения: 0, 1, 2, INF_ROOTS (=3)), то на консаль будет выведенно сообщение об ошибке:
//!          Wrong parameter value rootsCount.
//-------------------------------------------------------------------------------------------
void outputAnswer(float x1, float x2, int rootsCount)
{
    switch (rootsCount)
    {
        case 0:
        {
            printf("No valid roots");
            break;
        }
        case 1:
        {
            printf("The quadratic equation has only one root:\n%.3f", x1);
            break;
        }
        case 2:
        {
            printf("The quadratic equation has two roots:\n%.3f and %.3f", x1, x2);
            break;
        }
        case INF_ROOTS:
        {
            printf("Infinitely many roots");
            break;
        }
        default:
        {
            printf("Wrong parameter value rootsCount");
        }
    }
}

//-------------------------------------------------------------------------------------------
//! Сравнения числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @note сравнение числа происходит при помощи константы PRECISION = 0.001f,
//!       таким образом, если число попадает в интервал от минус бесконечности до 0 - PRECISION,
//!       то оно меньше нуля.
//!
//! @return true или false.
//-------------------------------------------------------------------------------------------
bool isLessZero(float number)
{
    return number < 0 - PRECISION;
}

//-------------------------------------------------------------------------------------------
//! Сравнения числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @note сравнение числа происходит при помощи константы PRECISION = 0.001f,
//!       таким образом, если число попадает в интервал от 0 - PRECISION до 0 + PRECISION,
//!       то оно равно нулю.
//!
//! @return true или false.
//-------------------------------------------------------------------------------------------
bool isEqualZero(float number)
{
    return number >= 0 - PRECISION && number <= 0 + PRECISION;
}

//-------------------------------------------------------------------------------------------
//! Вычисление корней линейного уравнения вида ax + c = 0.
//!
//! @param [in] a линейный коэффициент линейного уравнения.
//! @param [in] c коэффициент линейного уравнения (свободный член).
//! @param [out] x корень линейного уравнения.
//! @param [out] rootsCount количество корней линейного уравнения.
//-------------------------------------------------------------------------------------------
void solveLinearEquation(float a, float c, float *x, int *rootsCount)
{
    if (!isEqualZero(a) && !isEqualZero(c))
    {
        *x = -c/a;
        *rootsCount = 1;
    }
    else if (!isEqualZero(a) && isEqualZero(c))
    {
        *x = 0;
        *rootsCount = 1;
    }
    else if (isEqualZero(a) && !isEqualZero(c))
    {
        *rootsCount = 0;
    }
    else
    {
        *rootsCount = INF_ROOTS;
    }
}

//-------------------------------------------------------------------------------------------
//! Вычисление корней квадратного уравнения.
//!
//! @param [in] a коэффициент квадратного уравнения (старший коэффициент).
//! @param [in] b коэффициент квадратного уравнения (коэффициент при x).
//! @param [in] c коэффициент квадратного уравнения (свободный член).
//! @param [out] x1 корень квадратного уравнения.
//! @param [out] x2 корень квадратного уравнения.
//! @param [out] rootsCount количество корней квадратного уравнения.
//-------------------------------------------------------------------------------------------
void solveQuadraticEquation(float a, float b, float c, float *x1, float *x2, int *rootsCount)
{
    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(rootsCount != nullptr);

    *x1 = 0;
    *x2 = 0;

    if (!isEqualZero(a))
    {
        float D = b*b - 4*a*c;
        float multiplier = 1/(a*2);

        if (isLessZero(D))
        {
            *rootsCount = 0;
        }
        else if (isEqualZero(D))
        {
            *x1 = -b*multiplier;
            *rootsCount = 1;
        }
        else
        {
            float sqrtD = sqrtf(D);
            *x1 = (-b - sqrtD)*multiplier;
            *x2 = (-b + sqrtD)*multiplier;
            *rootsCount = 2;
        }
    }
    else
    {
        solveLinearEquation(b, c, x1, rootsCount);
    }
}
