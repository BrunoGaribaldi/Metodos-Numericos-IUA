#include <iostream>
#include <math.h>
#define FILAS 20
using namespace std;


void fileReader (double m[FILAS][2], int* filas);


void lagrange (double m[FILAS][2], int fila);	
void polinomica (double [FILAS][2], int fila);


void triangulacion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void retrostutitucion(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][FILAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][FILAS], double b[FILAS], double x[FILAS], int filas);


double func (double x){
	
	return x + 2/x;
}

	
int main(int argc, char *argv[]) {
	double m[FILAS][2];
	int filas; 
	fileReader(m,&filas);
	int seleccion;
	printf("\ncantidad de filas %d\n",filas);
	printf("\nPuntos guardados: ");
	printf("(X ; Y)\n\n");
	for(int i = 0; i < filas ; i++){
		printf("(%lf ; %lf)",m[i][0],m[i][1]);
		printf("\n");
	}
	printf("\nIngrese:\n 1 --> Lagrange\n 2 --> Polinomica\n");
	scanf("%d",&seleccion);
	switch (seleccion){
	case 1: 
		lagrange(m, filas);
		break;
	case 2: 
		polinomica(m, filas);
		break;
	default: 
		printf("\nSe seleccionó mal la opcion");
		break;
	}
	return 0;
}


void fileReader (double m[FILAS][2],int* filas){
	
	
	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	
	if ( fp == NULL )
	{
		printf("No se puede abrir el archivo");
	}
	int fila=0;
	while((c = fgetc(fp)) != EOF)
	{
		if(c == '\n'){
			fila++;
		}
	}
	
	fclose(fp);
	fp = fopen("data.txt","r");
	
	int i, j;
	for(i = 0; i < fila; i++) {
		j = 0;
		do {
			fscanf(fp, "%lf", &(m[i][j]));
			j++;
		} while((c = fgetc(fp)) != '\n');
	}
	
	*filas = fila;
	
}
	
void lagrange (double m[FILAS][2], int fila){
	double x;//Coeficiente a interpolar
	double e;
	printf("Recuerde haber definido la funcion previamente\n");
	printf("Ingrese el valor a interpolar\n");
	scanf("%lf", &x);
	
	double sum = 0; 
	for (int i = 0; i < fila; i++) {
		double producto = 1;
		for (int j = 0; j < fila; j++) {
			if (j != i) {
				producto *= ((x - m[i][0]) / (m[j][0] - m[i][0]));
			}
		}
		sum += m[i][1] * producto;
	}
	e = fabs(func(x) - sum);
	printf("El valor interpolado para %lf es: %lf, con un error de %lf", x, sum, e);
}

void polinomica (double m[FILAS][2], int fila){
	double a[FILAS][FILAS]; 
	double b[FILAS];
	
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < fila +1 ; j++) {
			a[i][j] = pow(m[i][0], j);
		}
		b[i] = m[i][1];
	}
	printf("\nMatriz a\n");
	for (int i = 0; i < fila; i++) {
		for (int j = 0; j < fila; j++) {
			printf("%lf",a[i][j]);
			printf("\t");
		}
		printf("\n");
	}
	printf("\nMatriz b\n");
	for (int i = 0; i < fila; i++) {
		printf("%lf",b[i]);
		printf("\t");
	}
	
	double* x = (double*)malloc(fila * sizeof(double));
	triangulacion(a, b, x, fila);
	
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
