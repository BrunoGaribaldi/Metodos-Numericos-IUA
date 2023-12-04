#include <iostream>
#include <math.h>
using namespace std;

double f1(double y2){//la forma que resuelve este metodo es ecuaciones de la forma: dy/dx = f(x,y) y necesitamos y(x0)= y0
	return y2;		 // por ejemplo : dy/dx + 2xy = 0, donde tu f(xy) es -2xy
}
	double f2(double x ,double y1){//la forma que resuelve este metodo es ecuaciones de la forma: dy/dx = f(x,y) y necesitamos y(x0)= y0
		return -y1+4*cos(x);		 // por ejemplo : dy/dx + 2xy = 0, donde tu f(xy) es -2xy
	}
	
	int main(int argc, char *argv[]) {
		double a,b,h,k11,k21,k31,k41,k12,k22,k32,k42;
		int n = 200;
		h = 0.01;

		double *x = (double *)malloc((n+1) * sizeof(double)); //con n+1 porq por ejemplo si tengo a y b y tengo 5 puntos, voy a necesitar el a,1,2,3,4,b
		double *y1 = (double *)malloc((n+1) * sizeof(double));
		double *y2 = (double *)malloc((n+1) * sizeof(double));
		x[0] = 0;
		y1[0] = 0;
		y2[0] =0 ;

		
		for(int i = 0 ; i < n ; i++){
			
			x[i+1] = x[i] + h;
			
			
			k11 = f1(y2[i]);
			k12 = f2(x[i],y1[i]);
			
			k21 = f1( y2[i]+ (h/2)*k12);
			k22 = f2(x[i] + h/2 , y1[i]+ (h/2)*k11);
			
			k31 = f1( y2[i]+ (h/2)*k22);
			k32 = f2(x[i] + h/2 , y1[i]+ (h/2)*k21);
			
			k41 = f1(y2[i] + k32 * h);
			k42 = f2(x[i] + h , y1[i] + k31 * h);
			
			y1[i+1] = y1[i] + (h/6)*(k11+2*k21+2*k31+k41);
			y2[i+1] = y2[i] + (h/6)*(k12+2*k22+2*k32+k42);
			
			printf("\n(%lf,%lf)", x[i+1], y1[i+1]);
		}
		return 0;
	}
