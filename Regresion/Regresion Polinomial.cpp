#include <iostream>
#include <stdio.h>
#include <math.h>
#define FILAS 20
using namespace std;

void armadoMatriz (double m[FILAS][2], double a[FILAS][FILAS], double b[FILAS], int gradoP, int filas);
void error (double x[FILAS], double m[FILAS][2], int gradoP, int filas);

void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);

int main(int argc, char *argv[]) {
	double m[FILAS][2];
	m[0][0] =1 ;
	m[0][1] =1 ;
	m[1][0] =2 ;
	m[1][1] =2 ;
	m[2][0] =3 ;
	m[2][1] =4 ;
	m[3][0] =5 ;
	m[3][1] =6 ;
	double a[FILAS][FILAS];
	double b[FILAS];
	int filas = 4 , gradoP; 
	printf("\nDatos leidos del archivo: \n\t    X\t\t|\t    Y\n");
	for(int i = 0; i < filas ; i++){
		printf("\t%lf\t\t%lf\n",m[i][0],m[i][1]);
	}
	printf("\nIngrese el grado del polinomio\n");
	scanf("%d", &gradoP);
	gradoP = gradoP + 1;
	if(filas < gradoP){
		printf("\nADVERTENCIA datos insuficientes para el grado del polinomio");
		exit(1);
	}
	armadoMatriz(m,a,b,gradoP,filas);
	printf("\nMatriz:\n");
	for(int i = 0; i < filas ; i++){
		for(int j = 0; j < filas ; j++){
			printf("\t%lf",a[i][j]);
		}
		printf("\t%lf\n",b[i]);
	}
	double* x = (double*)malloc(FILAS * sizeof(double));
	triangulacion(a, b, x, filas);
	error(x,m,gradoP,filas);
	return 0;
}
void armadoMatriz (double m[FILAS][2], double a[FILAS][FILAS], double b[FILAS], int gradoP, int filas){
	for (int i = 0; i < gradoP; i++) {
		double sumxy = 0;
		for (int j = 0; j < filas; j++) {
			sumxy = sumxy + pow(m[j][0], i) * m[j][1];
		}
		b[i] = sumxy;
		for (int j = 0; j < gradoP; ++j) {
			double sumx = 0;
			for (int k = 0; k < filas; ++k) {
				sumx = sumx + pow(m[k][0], i + j);
			}
			a[i][j] = sumx;
		}
	}
}
void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
	for (int i = 0 ; i < (filas - 1) ; i++){
		pivot(a, b, filas , i);
		for (int j = i + 1; j < filas; j++) {
			double factor = -a[j][i] / a[i][i];
			for (int k = 0; k < filas; ++k) {
				a[j][k] = a[i][k] * factor + a[j][k];
			}
			b[j] = b[i] * factor + b[j];
		}
	}
	
	double norma = determinante(a,b,x,filas);
	if(norma == 0.0){
		printf("\n\nmatriz singular");
	}else{
		retrostutitucion(a, b, x, filas);
	}
}
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
	double value = 0;
	value = b[filas - 1] / a[filas - 1][filas - 1];
	x[filas - 1] = value;
	for (int i = filas - 2; i >= 0; --i) {
		double sum = 0;
		for (int j = i + 1; j < filas; ++j) {
			sum = sum + a[i][j] * x[j];
		}
		value = (b[i] - sum) / a[i][i];
		x[i] = value;
	}
	printf("\n\n\n\nConjunto solución de las asubn: \n");
	for (int i = 0; i < filas; ++i) {
		printf("a%d = %lf\n", i , x[i]);
	}
	
	printf("\n\n");
	printf("Polinomio Interpolador: \n");
	int pow = 0;
	for (int i = 0; i <= filas - 1; i++) {
		if (pow == 0)
			printf("%lf", x[i]);
		else {
			if (x[i] >= 0)
				printf(" + %lf.x^%d ", x[i], pow);
			else
				printf(" %lf.x^%d", x[i], pow);
		}
		pow++;
	}
}
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i){
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					printf("Se realizo pivoteo\n");
					double swap = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = swap;
				}
				double swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
	}
}
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas){
	double norma = 1;
	for(int i = 0; i < filas ; i++){
		norma = norma * a[i][i];
	}
	return norma;
}
void error (double x[FILAS], double m[FILAS][2], int gradoP, int filas){
	double yb = 0;
	double e = 0;
	double ecm;
	double st = 0;
	double r;
	for (int i = 0; i < filas; i++) {
		double sum = 0;
		for (int j = 0; j < gradoP; j++) {
			sum = sum + x[j]*pow(m[i][0], j);
		}
		e = e + pow(m[i][1]-sum, 2);
		yb = yb + m[i][1];
	}
	yb = yb/(filas+1);
	for (int i = 0; i < filas; i++) {
		st = st + pow(m[i][1]-yb, 2);
	}
	r = sqrt(fabs(e-st)/st);
	ecm = sqrt(e/filas);
	printf("\nEl error es de: %lf\n", e);
	printf("El error cuadratico medio es de: %lf\n", ecm);
	printf("st: %lf\n", st);
	printf("El coeficiente de correlacion es: %lf\n", r);
}
