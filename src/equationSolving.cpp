#include <assert.h>
#include <math.h>
#include "../include/equationSolving.h"

const double PRECISION = 0.001f;

//===========================================================================================
//! @brief Вычисление корней квадратного уравнения.
//!
//! @param [in] a коэффициент квадратного уравнения (старший коэффициент).
//! @param [in] b коэффициент квадратного уравнения (коэффициент при x).
//! @param [in] c коэффициент квадратного уравнения (свободный член).
//! @param [out] x1 корень квадратного уравнения.
//! @param [out] x2 корень квадратного уравнения.
//!
//! @note Корни квадратного уравнения зануляются при работе функции,
//!       даже если их нет.
//!
//! @return Количество корней уравнения квадратного уравнения.
//------------------------------------------------------------------------------------------
int solveQuadraticEquation(double a, double b, double c, double *x1, double *x2)
{
    #ifdef DEBUG
        assert(isfinite(a));
        assert(isfinite(b));
        assert(isfinite(c));

        assert(x1 != nullptr);
        assert(x2 != nullptr);
        assert(x1 != x2);
    #endif

    int rootsCount = 0;

    *x1 = 0;
    *x2 = 0;

    if (compareZero(a) == 0)
        return solveLinearEquation(b, c, x1);

    if(compareZero(c) == 0)
    {
        rootsCount = solveLinearEquation(a, b, x1);
        *x2 = 0;
        if(rootsCount == INF_ROOTS)
        {
            return rootsCount;
        }
        else
        {
            return (rootsCount + 1);
        }
    }

    double D = b*b - 4*a*c;
    double multiplier = 1/(a*2);

    if (compareZero(D) < 0)
    {
        rootsCount = 0;
    }
    else if (compareZero(D) == 0)
    {
        *x1 = -b*multiplier;
        rootsCount = 1;
    }
    else
    {
        double sqrtD = sqrt(D);
        *x1 = (-b - sqrtD)*multiplier;
        *x2 = (-b + sqrtD)*multiplier;
        rootsCount = 2;
    }

    return rootsCount;
}

//===========================================================================================
//! @brief Вычисление корней линейного уравнения вида ax + b = 0.
//!
//! @param [in] a линейный коэффициент линейного уравнения.
//! @param [in] b коэффициент линейного уравнения (свободный член).
//! @param [out] x корень линейного уравнения.
//!
//! @return Количество корней линейного уравнения.
//------------------------------------------------------------------------------------------
int solveLinearEquation(double a, double b, double *x)
{
    #ifdef DEBUG
        assert(isfinite(a));
        assert(isfinite(b));

        assert(x != nullptr);
    #endif

    int rootsCount = 0;

    if (compareZero(a) != 0 && compareZero(b) != 0)
    {
        *x = -b/a;
        rootsCount = 1;
    }
    else if (compareZero(a) != 0 && compareZero(b) == 0)
    {
        *x = 0;
        rootsCount = 1;
    }
    else if (compareZero(a) == 0 && compareZero(b) != 0)
    {
        rootsCount = 0;
    }
    else
    {
        rootsCount = INF_ROOTS;
    }

    return rootsCount;
}

//==========================================================================================
//! @brief Сравнения числа с нулём.
//!
//! @param [in] number число, которое нужно сравнить с нулём.
//!
//! @return Функция возвращает:
//!         1)  1, если число number больше нуля;
//!         2)  0, если число number равно нулю;
//!         3) -1, если число number меньше нуля.
//------------------------------------------------------------------------------------------
int compareZero(double number)
{
    if (number > 0 + PRECISION)
    {
        return 1;
    }
    else if (0 - PRECISION <= number && number <= 0 + PRECISION)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
