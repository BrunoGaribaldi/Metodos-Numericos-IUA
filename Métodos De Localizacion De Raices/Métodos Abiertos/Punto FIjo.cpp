#include <stdio.h>
#include <math.h>


double g(double);

void PuntoFijo();


int main()
{
    PuntoFijo();
    return 0;
}

double g(double x)
{ // funcion g
    return exp(-x);
}

void PuntoFijo()
{
    // acordate que tenes que inicializarlo donde quieras, va a funcionar igual. Te puede llevar +- iteraciones pero es lo mismo

    double xViejo; // es el punto de partida digamos
    double xNuevo;
    int contador = 0;
    double error = 0;
    double tolerancia;
    printf("Ingrese la tolerancia\n"); 
    scanf("%lf", &tolerancia);
    printf("Ingrese el punto inicial\n"); 
    scanf("%lf", &xViejo);
    do
    {

        contador++;

        if (fabs((g(xViejo + 0.01) - g(xViejo)) / 0.01) >= 1) // Derivada >= 1
        { 

            printf("\n\nNo cumple con el criterio de convergencia. El metodo diverge (|g'(x)|>1)");
            break;
        }
        else
        {

            xNuevo = g(xViejo);
            error = fabs(xNuevo - xViejo);
            xViejo = xNuevo;
        }

    } while (error > tolerancia);

    printf("\n\n\nEl punto fijo de g(x), es decir la raiz de f es: %.10lf", xNuevo);
    printf("\nEl valor del error en la raiz es de: %.10lf", error);
    printf("\nLa resolucion del proble tomó %d iteraciones", contador);
}