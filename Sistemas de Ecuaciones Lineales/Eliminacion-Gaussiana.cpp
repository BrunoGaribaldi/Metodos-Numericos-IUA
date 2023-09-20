#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Función para contar las filas en el archivo
int contarFilas(FILE* fp);

// Función para leer la matriz desde el archivo
void leerMatriz(FILE* fp, double**& matriz, int filas, int& columnas);

// Función para crear y usar la matriz 'a'
void crearMatrizA(double**& a, double** matriz, int filas, int columnas);

// Función para crear y usar el arreglo 'b'
void crearMatrizB(double*& b, double** matriz, int filas, int columnas);

// Función para triangular matriz
void triangulacion(double** a, double* b, double* x, int filas);

//Funcion para retrostutituir matriz
void retrostutitucion(double** a, double* b, double* x, int filas);

//
void pivot(double** a, double* b, int filas, int i);

//verifica que en la diagonal no hayan ceros.
double determinante(double** a, double* b, double* x, int filas);

int main(int argc, char* argv[]) {
	
	FILE* fp;
	fp = fopen("data.txt", "r");
	
	if (fp == NULL) {
		puts("No se puede abrir el archivo");
		return 1;
	}
	
	// Contar filas en el archivo
	int filas = contarFilas(fp);
	printf("Numero de filas de la matriz leida = %d\n", filas);
	
	// Cerramos y reabrimos el archivo para resetear el puntero
	fclose(fp);
	fp = fopen("data.txt", "r");
	
	int columnas;
	double** matriz = NULL; //matriz es la del txt
	
	// Leer la matriz desde el archivo, guardandola en matriz.
	leerMatriz(fp, matriz, filas, columnas);
	fclose(fp);
	
	// Imprimir la matriz leída
	printf("\nMatriz leida: \n");
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			printf("%lf ", matriz[i][j]);
		}
		printf("\n");
	}
	
	// Crear e imprimir la matriz 'a'
	double** a = NULL;
	crearMatrizA(a, matriz, filas, columnas);
	
	// Crear e imprimir la matriz 'b'
	double* b = NULL;
	crearMatrizB(b, matriz, filas, columnas);
	
	// Llamar a la función eliminacionGaussiana --> la llamo triangulacion
	double* x = (double*)malloc(filas * sizeof(double));
	triangulacion(a, b, x, filas);
	
	// Liberar la memoria de  matriz (total)
	for (int i = 0; i < filas; i++) {
		free(matriz[i]);
	}
	free(matriz);
	
	// Liberar la memoria de 'a', 'b' y 'xnuevo'
	for (int i = 0; i < filas; i++) {
		free(a[i]);
	}
	free(a);
	free(b);
	free(x);
	
	return 0;
}

int contarFilas(FILE* fp) {
	int filas = 0;
	char c;
	
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			filas++;
		}
	}
	
	return filas;
}

void leerMatriz(FILE* fp, double**& matriz, int filas, int& columnas) {
	char c;
	
	matriz = (double**)malloc(filas * sizeof(double*));
	for (int i = 0; i < filas; i++) {
		matriz[i] = (double*)malloc(100 * sizeof(double)); // Asumiendo un máximo de 100 columnas
	}
	
	int i, j;
	for (i = 0; i < filas; i++) {
		j = 0;
		do {
			fscanf(fp, "%lf", &(matriz[i][j]));
			j++;
		} while ((c = fgetc(fp)) != '\n');
	}
	
	columnas = j;
	printf("\nNumero de columnas de la matriz leida = %d",columnas);
}

void crearMatrizA(double**& a, double** matriz, int filas, int columnas) {
	int num1 = filas;
	int num2 = columnas - 1;
	
	a = (double**)malloc(num1 * sizeof(double*));
	
	for (int i = 0; i < num1; i++) {
		a[i] = (double*)malloc(num2 * sizeof(double));
	}
	
	// Inicialización y uso del arreglo 'a'
	printf("\nMatriz A: \n");
	for (int i = 0; i < num1; i++) {
		for (int j = 0; j < num2; j++) {
			a[i][j] = matriz[i][j];
			printf("%lf ", a[i][j]);
		}
		printf("\n");
	}
}

void crearMatrizB(double*& b, double** matriz, int filas, int columnas) {
	int size = filas;
	
	b = (double*)malloc(size * sizeof(double));
	
	// Inicialización y uso del arreglo 'b'
	printf("\nArreglo B: \n");
	for (int i = 0; i < size; i++) {
		b[i] = matriz[i][columnas - 1];
		printf("%lf ", b[i]);
	}
	printf("\n");
}

void triangulacion(double** a, double* b, double* x, int filas) {
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
void pivot (double** a, double* b, int filas, int i) {
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

void retrostutitucion(double** a, double* b, double* x, int filas) {
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
	printf("Conjunto solucion: \n");
	for (int i = 0; i < filas; ++i) {
		printf("x%d = %lf\n", i + 1, x[i]);
	}
}

double determinante(double** a, double* b, double* x, int filas) {
	double norma = 1;
	for(int i = 0; i < filas ; i++){
		norma = norma * a[i][i];
	}
	return norma;
}
