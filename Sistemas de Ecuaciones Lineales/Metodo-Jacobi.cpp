#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Funci�n para contar las filas en el archivo
int contarFilas(FILE* fp);

// Funci�n para leer la matriz desde el archivo
void leerMatriz(FILE* fp, double**& matriz, int filas, int& columnas);

// Funci�n para crear y usar la matriz 'a'
void crearMatrizA(double**& a, double** matriz, int filas, int columnas);

// Funci�n para crear y usar el arreglo 'b'
void crearArregloB(double*& b, double** matriz, int filas, int columnas);

// Funci�n para realizar el m�todo de Jacobi
void jacobi(double** a, double* b, double* xnuevo, int filas);


int main(int argc, char* argv[]) {
	
	
	FILE* fp;
	fp = fopen("data.txt", "r");
	
	if (fp == NULL) {
		puts("No se puede abrir el archivo");
		return 1;
	}
	
	// Contar filas en el archivo
	int filas = contarFilas(fp);
	printf("numero de filas = %i\n", filas);
	
	// Cerramos y reabrimos el archivo para resetear el puntero
	fclose(fp);
	fp = fopen("data.txt", "r");
	
	int columnas;
	double** matriz = NULL; //matriz es la del txt
	
	// Leer la matriz desde el archivo, guardandola en matriz.
	leerMatriz(fp, matriz, filas, columnas);
	fclose(fp);
	
	// Imprimir la matriz le�da
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
	
	// Crear e imprimir el arreglo 'b'
	double* b = NULL;
	crearArregloB(b, matriz, filas, columnas);
	
	// Llamar a la funci�n Jacobi
	double* xnuevo = (double*)malloc(filas * sizeof(double));
	jacobi(a, b, xnuevo, filas);
	
	// Liberar la memoria de  matriz
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
	free(xnuevo);
	
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
		matriz[i] = (double*)malloc(100 * sizeof(double)); // Asumiendo un m�ximo de 100 columnas
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
}

void crearMatrizA(double**& a, double** matriz, int filas, int columnas) {
	int num1 = filas;
	int num2 = columnas - 1;
	
	a = (double**)malloc(num1 * sizeof(double*));
	
	for (int i = 0; i < num1; i++) {
		a[i] = (double*)malloc(num2 * sizeof(double));
	}
	
	// Inicializaci�n y uso del arreglo 'a'
	printf("\nMatriz A: \n");
	for (int i = 0; i < num1; i++) {
		for (int j = 0; j < num2; j++) {
			a[i][j] = matriz[i][j];
			printf("%lf ", a[i][j]);
		}
		printf("\n");
	}
}

void crearArregloB(double*& b, double** matriz, int filas, int columnas) {
	int size = filas;
	
	b = (double*)malloc(size * sizeof(double));
	
	// Inicializaci�n y uso del arreglo 'b'
	printf("\nArreglo B: \n");
	for (int i = 0; i < size; i++) {
		b[i] = matriz[i][columnas - 1];
		printf("%lf ", b[i]);
	}
	printf("\n");
}

void jacobi(double** a, double* b, double* xnuevo, int filas) {
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if (xViejo == NULL) {
		perror("Error al asignar memoria para los arreglos");
		return;
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xnuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
	double suma;
	printf("\nIngrese la tolerancia\n");
	scanf("%lf", &tolerancia);
	
	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			for (int j = 0; j < filas; j++) {
				if (j != i)
					suma += a[i][j] * xViejo[j];
			}
			xnuevo[i] = (b[i] - suma) / a[i][i];
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xnuevo[i] - xViejo[i]) * (xnuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignaci�n del vector viejo para la pr�xima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xnuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	printf("\n El resultado es: \nxnuevo = [\t");
	for (int i = 0; i < filas; i++) {
		printf("%lf\t", xnuevo[i]);
	}
	
	printf("]\n La cantidad de iteraciones fueron: %d \n El error es de %lf", iteraciones, error);
	
	free(xViejo);
}
