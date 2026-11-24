#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>

#define THRESHOLD_LOW     2.2
#define THRESHOLD_HIGH    4.2
#define COEF_A            5.0
#define SHIFT_B           3.2
#define SCALE_C           2.0
#define OFFSET_D          50.0
#define SCALE_E           4.0
#define OFFSET_F          60.0

#define X_MIN             1.2
#define X_MAX_LOG         2.2
#define X_VALID_LOW       1.0
#define X_VALID_HIGH      6.0

#define STATE_LOW         0
#define STATE_NORMAL      1
#define STATE_HIGH        2

#define Q_LIMIT           50.0


int    read_x(double *x);          
double calc_q(double x);
int    get_state(double q);
void   print_result(double x, double q, int state);

int main(void)
{
    double x;
    double q;
    int    state;

    setlocale(LC_ALL, "Russian");

    printf("Программа расчёта показателя Q по давлению в реакторе.\n");
    printf("Давление задаётся в барах, допустимый диапазон: %.1f - %.1f бар.\n",
           X_VALID_LOW, X_VALID_HIGH);

    if (read_x(&x) != 0) {          /* вся работа с пользователем — здесь */
        printf("Расчёт невозможен: введите число из диапазона %.1f - %.1f бар.\n",
               X_MIN, X_VALID_HIGH);
        printf("Нажмите Enter для выхода...");
        getchar();
        getchar();
        return 1;
    }

    q     = calc_q(x);
    state = get_state(q);
    print_result(x, q, state);

    return 0;
}


int read_x(double *x)
{
    printf("Введите x (бар): ");

    if (scanf("%lf", x) != 1) {
        printf("Ошибка: ожидалось число.\n");
        return -1;
    }

    /* корректный диапазон для логарифма: x >= 1.2 */
    if (*x < X_MIN) {
        printf("Ошибка: x = %.2f меньше %.1f — подкоренное выражение "
               "и аргумент логарифма должны быть неотрицательны, "
               "Q не определён.\n", *x, X_MIN);
        return -1;
    }

    if (*x < X_VALID_LOW || *x > X_VALID_HIGH) {
        printf("Предупреждение: x = %.2f вне диапазона %.1f - %.1f бар.\n",
               *x, X_VALID_LOW, X_VALID_HIGH);
    }

    return 0;
}

double calc_q(double x)
{
    if (x < THRESHOLD_LOW) {
        return COEF_A * sqrt(x - X_MIN) + 5.0;
    } else if (x <= THRESHOLD_HIGH) {
        return SCALE_C * (x - SHIFT_B) + OFFSET_D;
    } else {
        return SCALE_E * log(x - X_MAX_LOG) + OFFSET_F;
    }
}

int get_state(double q)
{
    if (q < Q_LIMIT) {
        return STATE_LOW;
    } else if (q <= Q_LIMIT + 20.0) {
        return STATE_NORMAL;
    } else {
        return STATE_HIGH;
    }
}

void print_result(double x, double q, int state)
{
    const char *name;

    switch (state) {
    case STATE_LOW:    name = "низкий";   break;
    case STATE_NORMAL: name = "норма";    break;
    case STATE_HIGH:   name = "высокий";  break;
    default:           name = "неизвестно"; break;
    }

    printf("\nX = %.2f бар\n", x);
    printf("Q = %.4f\n", q);
    printf("Состояние процесса: %s\n", name);
}
