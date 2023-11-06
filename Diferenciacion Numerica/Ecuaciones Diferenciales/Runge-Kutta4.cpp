#include <iostream>
#include <math.h>
using namespace std;

double f(double x ,double y){//la forma que resuelve este metodo es ecuaciones de la forma: dy/dx = f(x,y) y necesitamos y(x0)= y0
	return x*sqrt(y);		 // por ejemplo : dy/dx + 2xy = 0, donde tu f(xy) es -2xy
}
	
int main(int argc, char *argv[]) {
	double a,b,h,k1,k2,k3,k4;
	int n;
	printf("\nIngresar intervalo [a,b]\n a:");
	scanf("%lf",&a);
	printf("\nIngresar intervalo [a,b]\n b:");
	scanf("%lf",&b);
	printf("\nIngresar la cantidad de puntos:");//TAMBIEN PUEDE SER INGRESAR DIRECTAMENTE H. H = (B-A)/CANT.PUNTOS
	scanf("%d",&n);
	h = (b-a)/n;
	printf("\nh=%lf",h);
	double *x = (double *)malloc((n+1) * sizeof(double)); //con n+1 porq por ejemplo si tengo a y b y tengo 5 puntos, voy a necesitar el a,1,2,3,4,b
	double *y = (double *)malloc((n+1) * sizeof(double));
	printf("\nIngresar el dato inicial y(x0)\ny0:");
	scanf("%lf",&y[0]);
	x[0] = a;
	printf("x0=%lf",x[0]);
	printf("y0=%lf",y[0]);
	
	for(int i = 0 ; i < n ; i++){
		
		x[i+1] = x[i] + h;
		
		
		k1 = f(x[i],y[i]);
		
		k2 = f(x[i] + h/2 , y[i]+ (h/2)*k1);
		
		k3 = f(x[i] + h/2 , y[i]+ (h/2)*k2);
		
		k4 = f(x[i] + h , y[i] + k3 * h);
		
		y[i+1] = y[i] + (h/6)*(k1+2*k2+2*k3+k4);
		
		printf("\nX%d = %lf\nY%d = %lf",i+1, x[i+1],i+1, y[i+1]);
	}
	return 0;
}

