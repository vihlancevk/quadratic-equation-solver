#include <assert.h>
#include <math.h>
#include"equationSolution.h"

const float PRECISION = 0.001f;

//------------------------------------------------------------------------------------------
//! @brief Сравнения числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @note сравнение числа происходит при помощи константы PRECISION = 0.001f,
//!       таким образом, если число попадает в интервал от минус бесконечности
//!       до 0 - PRECISION,
//!       то оно меньше нуля.
//!
//! @return меньше ли нуля число.
//------------------------------------------------------------------------------------------
bool isLessZero(float number)
{
    assert(isfinite(number));

    return number < 0 - PRECISION;
}

//------------------------------------------------------------------------------------------
//! @brief Сравнения числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @note сравнение числа происходит при помощи константы PRECISION = 0.001f,
//!       таким образом, если число попадает в интервал от 0 - PRECISION
//!       до 0 + PRECISION,
//!       то оно равно нулю.
//!
//! @return является ли число нулём.
//------------------------------------------------------------------------------------------
bool isEqualZero(float number)
{
    assert(isfinite(number));

    return number >= 0 - PRECISION && number <= 0 + PRECISION;
}

//------------------------------------------------------------------------------------------
//! @brief Вычисление корней линейного уравнения вида ax + b = 0.
//!
//! @param [in] a линейный коэффициент линейного уравнения.
//! @param [in] b коэффициент линейного уравнения (свободный член).
//! @param [out] x корень линейного уравнения.
//!
//! @return количество корней линейного уравнения.
//------------------------------------------------------------------------------------------
int solveLinearEquation(float a, float b, float *x)
{
    assert(isfinite(a));
    assert(isfinite(b));

    assert(x != nullptr);

    int rootsCount = 0;

    if (!isEqualZero(a) && !isEqualZero(b))
    {
        *x = -b/a;
        rootsCount = 1;
    }
    else if (!isEqualZero(a) && isEqualZero(b))
    {
        *x = 0;
        rootsCount = 1;
    }
    else if (isEqualZero(a) && !isEqualZero(b))
    {
        rootsCount = 0;
    }
    else
    {
        rootsCount = INF_ROOTS;
    }

    return rootsCount;
}

//------------------------------------------------------------------------------------------
//! @brief Вычисление корней квадратного уравнения.
//!
//! @param [in] a коэффициент квадратного уравнения (старший коэффициент).
//! @param [in] b коэффициент квадратного уравнения (коэффициент при x).
//! @param [in] c коэффициент квадратного уравнения (свободный член).
//! @param [out] x1 корень квадратного уравнения.
//! @param [out] x2 корень квадратного уравнения.
//!
//! @return количество корней уравнения квадратного уравнения.
//------------------------------------------------------------------------------------------
int solveQuadraticEquation(float a, float b, float c, float *x1, float *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert((x1 - x2) != 0);

    int rootsCount = 0;

    *x1 = 0;
    *x2 = 0;

    if (!isEqualZero(a))
    {
        float D = b*b - 4*a*c;
        float multiplier = 1/(a*2);

        if (isLessZero(D))
        {
            rootsCount = 0;
        }
        else if (isEqualZero(D))
        {
            *x1 = -b*multiplier;
            rootsCount = 1;
        }
        else
        {
            float sqrtD = sqrtf(D);
            *x1 = (-b - sqrtD)*multiplier;
            *x2 = (-b + sqrtD)*multiplier;
            rootsCount = 2;
        }
    }
    else
    {
        rootsCount = solveLinearEquation(b, c, x1);
    }

    return rootsCount;
}
