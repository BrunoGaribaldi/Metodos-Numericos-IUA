#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Función para contar las filas en el archivo
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

// Función para leer la matriz desde el archivo
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
}

// Función para crear y usar la matriz 'a'
void crearYUsarMatrizA(double**& a, double** matriz, int filas, int columnas) {
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

// Función para crear y usar el arreglo 'b'
void crearYUsarArregloB(double*& b, double** matriz, int filas, int columnas) {
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
	double** matriz = NULL;
	
	// Leer la matriz desde el archivo
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
	
	// Crear y usar la matriz 'a'
	double** a = NULL;
	crearYUsarMatrizA(a, matriz, filas, columnas);
	
	// Crear y usar el arreglo 'b'
	double* b = NULL;
	crearYUsarArregloB(b, matriz, filas, columnas);
	
	// Liberar la memoria de la matriz
	for (int i = 0; i < filas; i++) {
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}

