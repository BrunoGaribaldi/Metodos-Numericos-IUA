#include <iostream>
#include <math.h>
#define FILAS 9
using namespace std;

double f(double x){
	return x;
}
	int length (double a[] , int tamanio);
	
	int main(int argc, char *argv[]) {
		double a[FILAS][2] = {{0,1},{0.25,1.384},{0.5,1.849},{0.75,2.417},{1,3.118},{1.25,3.99},{1.5,5.082},{1.75,6.45},{2,8.189}};
		double deriv[FILAS][2] = {{0}};
		double h = 0.25;
		deriv[0][1] = (-a[2][1]+4*a[1][1]-3*a[0][1])/(2*0.25);//hacia adelante
		deriv[8][1] = (3*a[8][1] - 4*a[7][1] + a[6][1])/(2*0.25); //hacia atras
		for(int i = 0 ; i < 9 ; i++){
			deriv[i][0] = a[i][0];
		}
		for(int i = 1 ; i < 8 ; i++){
			deriv[i][1] = (a[i+1][1] - a[i-1][1])/(2*h); 
		}
		for(int i = 0 ; i < 9 ; i++){
			printf("\n(%lf,%lf)",deriv[i][0],deriv[i][1]);
		}
		return 0;
	}
