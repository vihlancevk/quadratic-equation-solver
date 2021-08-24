#include <stdio.h>
#include <assert.h>
#include <math.h>
#include"userInteraction.h"
#include"equationSolution.h"

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
