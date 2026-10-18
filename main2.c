#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <locale.h>
#include <math.h>
double q(double x) {
    if (x < 2.2) {
        return 5.0 * sqrt(x - 2.2 + 1.0) + 5.0;
    }
    else if ( x <= 4.2) {
        return 2.0 * (x - 3.2) + 50.0;
    }
    else   {
        return 4.0 * log(x - 4.2 + 2.0) + 60.0;
    }
}


int main(void) {
    setlocale(LC_ALL, "Russian");
    double x;
    printf("введите x (бар): ");
    if (scanf("%lf", &x) != 1){
        printf("q(%.2f) = %.4f\n", x, q(x));
        return 1;
    }
    
    printf("q(%.2f) = %.4f\n", x, q(x));
    return 0;
}

