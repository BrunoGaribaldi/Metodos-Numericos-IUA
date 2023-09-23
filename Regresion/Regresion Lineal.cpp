#include <iostream>
#include <math.h>
#define ROWS 20
#define FILAS 2
using namespace std;


void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);


void regresionLineal(double m[ROWS][2] , int filas);

int main(int argc, char *argv[]) {
	double m[ROWS][2];
	m[0][0] = -1;
	m[0][1] = 10;
	m[1][0] = 0;
	m[1][1] = 9;
	m[2][0] = 1;
	m[2][1] = 7;
	m[3][0] = 2;
	m[3][1] = 5;
	m[4][0] = 3;
	m[4][1] = 4;
	m[5][0] = 4;
	m[5][1] = 3;
	m[6][0] = 5;
	m[6][1] = 0;
	m[7][0] = 6;
	m[7][1] = -1;
	int filas = 8; 
	printf("\n--> Regresion Lineal\n");
	
	regresionLineal(m , filas);

	return 0;
	
}
void regresionLineal(double m[ROWS][2], int filas){
	double a[2][2] = {{0}};
	double b[2] = {0};
	double yProm = 0, r = 0, Sr = 0, St = 0, sum = 0; 
	a[1][1] = filas;
	for(int i = 0 ; i < filas ; i++){
		a[0][0]+= pow(m[i][0],2);
		a[0][1]+= m[i][0];
		a[1][0]+= m [i][0];
		b[0]+= m[i][0] * m[i][1];
		b[1] += m[i][1]; 
	}
	
	printf("\nMatriz:\n");
	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < 2 ; j++){
			printf("\t%lf",a[i][j]);
		}
		printf("\t%lf",b[i]);
		printf("\n");
	}
	
	double* x = (double*)malloc(2 * sizeof(double));
	triangulacion(a, b, x, 2);
	
	printf("\n\n\n\nConjunto solución: \n");
	for (int i = 0; i < 2; ++i) {
		printf("\nX%d = %lf\n" ,i, x[i]);
	}
 	
	for(int i = 0; i < filas ; i++){
		yProm+= m[i][1];
		
	}
	yProm = yProm/filas; //check
	for(int i = 0; i < filas ; i++){
		St+= pow((m[i][1] - yProm) , 2);
		
	}
	
	for(int i = 0; i<filas ; i++){
		sum+= pow((m[i][1] - (x[0]*m[i][0]+x[1])) , 2);
	}
	
	Sr = sqrt(sum/filas);//check
	printf("%lf",Sr);
	
	r = (St - sum)/St;//check
	
	printf("\n%lf",r);
	
}
void triangulacion(double a[2][2], double b[2], double x[ROWS], int filas){
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
		
void retrostutitucion(double a[2][2], double b[2], double x[ROWS], int filas){
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
	
}
			
void pivot(double a[2][2], double b[2], int filas, int i){
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
				
double determinante(double a[2][2], double b[2], double x[ROWS], int filas){
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
