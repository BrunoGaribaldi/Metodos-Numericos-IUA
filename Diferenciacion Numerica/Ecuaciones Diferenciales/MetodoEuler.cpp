#include <iostream>
#include <math.h>
using namespace std;

double f(double x ,double y){//la forma que resuelve este metodo es ecuaciones de la forma: dy/dx = f(x,y) y necesitamos y(x0)= y0
	return (-2*x*y);		 // por ejemplo : dy/dx + 2xy = 0, donde tu f(xy) es -2xy
}
int main(int argc, char *argv[]) {
	double a,b,h;
	int n;
	printf("\nIngresar intervalo [a,b]\n a:");
	scanf("%lf",&a);
	printf("\nIngresar intervalo [a,b]\n b:");
	scanf("%lf",&b);
	printf("\nIngresar la cantidad de puntos:");//TAMBIEN PUEDE SER INGRESAR DIRECTAMENTE H. H = (B-A)/CANT.PUNTOS
	scanf("%d",&n);
	h = (b-a)/n;
	double *x = (double *)malloc((n+1) * sizeof(double)); //con n+1 porq por ejemplo si tengo a y b y tengo 5 puntos, voy a necesitar el a,1,2,3,4,b
	double *y = (double *)malloc((n+1) * sizeof(double));
	printf("\nIngresar x0 e y0\nx0:");
	scanf("%lf",&x[0]);
	printf("ny0:");
	scanf("%lf",&y[0]);
	
	for(int i = 0 ; i < n ; i++){ //menor a n porq cuando llegue a n-1, el for calcula el n+1
		x[i+1] =  x[i]+ h;
		y[i+1] = y[i] + h*f(x[i],y[i]);
		printf("\nX%d = %lf\nY%d = %lf",i+1, x[i+1],i+1, y[i+1]);
	}
	return 0;
}

