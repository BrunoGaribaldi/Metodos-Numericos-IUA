#include <iostream>
#include <math.h>
using namespace std;

double f(double x){ //ingresar la funcion
	return 2*x*x*x;
}

int main(int argc, char *argv[]) {
	int cantidad_puntos;
	double a,b;
	double integral;
	double c0,c1,c2,c3,c4,c5,x0,x1,x2,x3,x4,x5;
	printf("\nIngresar a\n");
	scanf("%lf",&a);
	printf("\nIngresar b\n");
	scanf("%lf",&b);
	printf("\nIngresar la cantidad de puntos\n");
	scanf("%d",&cantidad_puntos);
	
	switch(cantidad_puntos){
	case 2:
		c0 = 1;
		c1 = 1; 
		x0 = - 0.577350269;
		x1 = 0.577350269;
		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2));
		break;
	case 3: 
		c0 = 0.5555556;
		x0 = - 0.774596669; 
		c1 = 0.8888889; 
		x1 = 0.0;
		c2 = 0.5555556; 
		x2 = 0.774596669;
		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2) + c2 * f(((b-a)/2)*x2 + (b+a)/2));
		break; 
	case 4: 
		c0 = 0.3478548;
		x0 = - 0.861136312;
		c1 = 0.6521452; 
		x1 = - 0.339981044;
		c2 = 0.6521452;
		x2 = 0.339981044;
		c3 = 0.3478548; 
		x3 = 0.861136312;		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2) + c2 * f(((b-a)/2)*x2 + (b+a)/2) + c3 * f(((b-a)/2)*x3 + (b+a)/2));	
		break;
	case 5: 
		c0 = 0.2369269;
		x0 = - 0.906179846; 
		c1 = 0.4786287;
		x1 = - 0.538469310;
		c2 = 0.5688889;
		x2 = 0.0;
		c3 = 0.4786287;
		x3 = 0.538469310;
		c4 = 0.2369269;
		x4 = 0.906179846;		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2) + c2 * f(((b-a)/2)*x2 + (b+a)/2) + c3 * f(((b-a)/2)*x3 + (b+a)/2) + c4 * f(((b-a)/2)*x4 + (b+a)/2));		
		break;
	case 6: 
		c0 = 0.1713245;
		x0 = - 0.932469514;
		c1 = 0.3607616;
		x1 = - 0.661209386;
		c2 = 0.4679139;
		x2 = - 0.238619186;
		c3 = 0.4679139;
		x3 = 0.238619186;
		c4 = 0.3607616;
		x4 = 0.661209386;
		c5 = 0.1713245;
		x5 = 0.932469514;
		integral = ((b-a)/2) * (c0 * f(((b-a)/2) * x0 + (b+a)/2) + c1 * f(((b-a)/2)*x1 + (b+a)/2) + c2 * f(((b-a)/2)*x2 + (b+a)/2) + c3 * f(((b-a)/2)*x3 + (b+a)/2) + c4 * f(((b-a)/2)*x4 + (b+a)/2) + c5 * f(((b-a)/2)*x5 + (b+a)/2));		
		break;
	default:
		printf("\nLa cantidad de puntos debe estar entre 2 y 6");
		break;
	}
	
	printf("\nEl valor de la integral entre a=%lf y b=%lf es de: I=%lf",a,b,integral);
	return 0;
}

