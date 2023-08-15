#include <stdio.h>
#include <math.h>

double funcion(double x);

void regulaFalsi();

int main() {

    regulaFalsi();

    return 0;
}

double funcion(double x) {

    return log(x) + exp(sin(x)) - x;

}

void regulaFalsi() {

    double a, b, tolerancia, c, error;
    int contador = 0;

    printf("Ingrese el límite inferior del intervalo: ");
    scanf("%lf", &a);
    printf("Ingrese el límite superior del intervalo: ");
    scanf("%lf", &b);
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

        if (funcion(a) * funcion(b) < 0.0) {
            do {
                contador++;

                c = (a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a));
               

                if (funcion(a) * funcion(c) > 0) {
                    a = c;
                } else if (funcion(a) * funcion(c) < 0) {
                    b = c;
                } else {
                    break;
                }

                error = (b - a) / 2;

            } while (error > tolerancia);

            printf("\nResultado de la raíz: %.10lf", c);
            printf("\nError estimado: %.10lf", error);
            printf("\nCantidad de iteraciones: %d\n", contador);
            
        } else {
            printf("\nNo hay raíz o hay un número par de ellas\n");
        }
    
}