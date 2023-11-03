//metodo para calcular derivadas
#include <iostream>
#include <math.h>
/*#define FILAS 20*/
using namespace std;

double f(double x){
	return x;
}
int length (double a[] , int tamanio);

int main(int argc, char *argv[]) {
	double a[4] = {1,2,3,4};
	int cantidadIntervalos = length(a,sizeof(a) / sizeof(a[0])) - 1;
	
	return 0;
}
int length (double a[] , int tamanio){
	if (tamanio == 0) {
		return 0;
	} else {
		return 1 + length(a + 1, tamanio - 1);
	}
}
