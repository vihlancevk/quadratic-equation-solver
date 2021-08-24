//------------------------------------------------------------------------------------------
//! @brief Вычисление корней квадратного уравнения.
//!
//! @author Костя Вихлянцев (https://github.com/vihlancevk/quadratic-equation-solver)
//! @file main.cpp
//! @date 22.08.2021
//!
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

const int INF_ROOTS = -1;
const float PRECISION = 0.001f;

void processCommandLineArguments(int argc, char *argv[]);
void testProgram();
void clearInputBuffer();
float readCoefficient(char coefficientSymbol);
void outputAnswer(float x1, float x2, int rootsCount);
bool isLessZero(float number);
bool isEqualZero(float number);
void testIsLessZeroAndIsEqualZero(float number, bool correctIsLessZero, bool correctIsEqualZero);
int solveLinearEquation(float a, float b, float *x);
void testSolveLinearEquation(float a, float b, float correctX, int correctRootsCount);
int solveQuadraticEquation(float a, float b, float c, float *x1, float *x2);
void testSolveQuadraticEquation(float a, float b, float c, float correctX1,
                                float correctX2, int correctRootsCount);

int main(int argc, char *argv[])
{
    processCommandLineArguments(argc, argv);

    float a = 0, b = 0, c = 0;

    printf("Enter coefficients in quadratic equation in format a*x^2 + b*x + c = 0\n");

    a = readCoefficient('a');
    b = readCoefficient('b');
    c = readCoefficient('c');

    int rootsCount = 0;
    float x1 = 0, x2 = 0;

    rootsCount = solveQuadraticEquation(a, b, c, &x1, &x2);

    outputAnswer(x1, x2, rootsCount);

    return 0;
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
    testIsLessZeroAndIsEqualZero(0.0f,     false, true);
    testIsLessZeroAndIsEqualZero(0.001f,   false, true);
    testIsLessZeroAndIsEqualZero(0.0011f,  false, false);
    testIsLessZeroAndIsEqualZero(1.0f,     false, false);

    testSolveLinearEquation(0, 0,  0, INF_ROOTS);
    testSolveLinearEquation(0, 1,  0, 0);
    testSolveLinearEquation(1, 1, -1, 1);

    testSolveQuadraticEquation(1, 1,  1,  0, 0, 0);
    testSolveQuadraticEquation(0, 0,  0,  0, 0, INF_ROOTS);
    testSolveQuadraticEquation(1, 2,  1, -1, 0, 1);
    testSolveQuadraticEquation(1, 5, -6, -6, 1, 2);
}

//------------------------------------------------------------------------------------------
//! @brief Очистка ввода с консоли.
//------------------------------------------------------------------------------------------
void clearInputBuffer()
{
    while (getchar() != '\n');
}

//------------------------------------------------------------------------------------------
//! @brief Считывание с консоли введённого коэффициента квадратного уравнения.
//!
//! @param [in] coefficientSymbol буквенное обозначение вводимого коэффициента.
//!
//! @note пользователь вводит значение коэффициента,
//!       который обозначается символом coefficientSymbol;
//!       чтобы закончить ввод числа необходимо нажать Enter.
//!
//! @return введённое с консоли число.
//------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------
//! @brief Вывод решения квадратного уравнения на консоль.
//!
//! @param [in] x1 первый корень уравнения.
//! @param [in] x2 второй корень уравнения.
//! @param [in] rootsCount количество корней уравнения.
//!
//! @note в консоле пользователь увидит один из возможных вариантов вывода:
//!       1) No valid roots - это значит,
//!       что у квадратного уравнения нет действительных корней;
//!       2) The quadratic equation has only one root: x1 - это значит,
//!       что квадратное уравнение имеет только один корень x1,
//!       где x1 - вещественное число;
//!       3) The quadratic equation has two roots:
//!       x1 and x2 - это значит, что квадратное уравнение имеет два корня:
//!       x1 и x2, где x1 и x2 - вещественные числа;
//!       4) Infinitely many roots - это значит,
//!       что квадратное уравнение имеет бесконечно много корней.
//!
//! @warning в случае, если в ходе выполнения программы на вход данной функции
//!          придёт параметр rootsCount с недопустимым
//!          для него значением (допустимые значения: 0, 1, 2, INF_ROOTS (=-1)),
//!          то в консоль будет выведенно сообщение об ошибке:
//!          Wrong parameter value rootsCount.
//------------------------------------------------------------------------------------------
void outputAnswer(float x1, float x2, int rootsCount)
{
    assert(isfinite(x1));
    assert(isfinite(x2));

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
