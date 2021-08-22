//-------------------------------------------------------------------------------------------
//! @brief Высисление корней квадратного уравенения.
//!
//! @avtor Костя Вихлянцев (https://github.com/vihlancevk/quadratic-equation-solver)
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
float readCoefficient(char coefficientDesignation);
void outputAnswer(float x1, float x2, int rootsCount);
int isLessZero(float number);
int isEqualZero(float number);
void solveLinearEquation(float a, float c, float *x, int *rootsCount);
void solveQuadraticEquation(float a, float b, float c, float *x1, float *x2, int *rootsCount);

int main()
{
    float a = 0, b = 0, c = 0;

    char const coefficientsDesignation[3] = {'a', 'b', 'c'};

    printf("Enter coefficients in quadratic equation in format a*x^2 + b*x + c = 0\n");

    a = readCoefficient(coefficientsDesignation[0]);
    b = readCoefficient(coefficientsDesignation[1]);
    c = readCoefficient(coefficientsDesignation[2]);

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
//! @return введённое с консоли число.
//-------------------------------------------------------------------------------------------
float readCoefficient(char coefficientDesignation)
{
    float number = 0;

    printf("%c: ", coefficientDesignation);
    int isCorrectInput = scanf("%f", &number);

    while (isCorrectInput == 0 || getchar() != '\n')
    {
        clearInputBuffer();

        printf("Please, enter the correct value for the coefficient\n");
        printf("%c: ", coefficientDesignation);
        isCorrectInput = scanf("%f", &number);
    }

    return number;
}

//-------------------------------------------------------------------------------------------
//! Вывод решения квадратного уравнения на экран консоли.
//!
//! @param [in] x1 первый корень уравнения.
//! @param [in] x2 второй корень уравнения.
//! @param [in] rootsCount количество корней уравнения.
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
//! Сравнения введённого с консоли числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @return 1 - если число меньше нуля;
//!         0 - если число больше или равно нулю.
//-------------------------------------------------------------------------------------------
int isLessZero(float number)
{
    return number < 0 - PRECISION;
}

//-------------------------------------------------------------------------------------------
//! Сравнения введённого с консоли числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @return 1 - если число равно нулю;
//!         0 - если число меньше или больше нуля.
//-------------------------------------------------------------------------------------------
int isEqualZero(float number)
{
    return number >= 0 - PRECISION && number <= 0 + PRECISION;
}

//-------------------------------------------------------------------------------------------
//! Вычисление корней линейного уравнения.
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
//! @param [in] c коэффициент квадратного уравнения (своюодный член).
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
