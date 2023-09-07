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
void crearArregloB(double*& b, double** matriz, int filas, int columnas);

// Función para realizar el método de Jacobi
void gauss_seidel(double** a, double* b, double* xnuevo, int filas);


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
	
	// Crear e imprimir el arreglo 'b'
	double* b = NULL;
	crearArregloB(b, matriz, filas, columnas);
	
	// Llamar a la función gauss_seidel
	double* xnuevo = (double*)malloc(filas * sizeof(double));
	gauss_seidel(a, b, xnuevo, filas);
	
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

void crearArregloB(double*& b, double** matriz, int filas, int columnas) {
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

void gauss_seidel(double** a, double* b, double* xnuevo, int filas) {
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
	float factor_relajacion;
	
	printf("\nIngrese la tolerancia\n");
	scanf("%lf", &tolerancia);
	
	printf("\nIngrese el factor relajacion\n");
	scanf("%f", &factor_relajacion);
	
	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			if(i == 0){
				for(int j = 1 ; j < filas ; j++){
					suma+= a[i][j] * xnuevo[j];
				}
				xnuevo[i] = (b[i] - suma)/a[i][i]; 
				xnuevo[i] = factor_relajacion * xnuevo[i] + (1-factor_relajacion) * xViejo[i]; 
			}else{
				for(int j = 0 ; j < i ; j++){
					suma += a[i][j] * xnuevo[j];
				}
				
				for(int j = i+1 ; j < filas ; j++){
					suma+= a[i][j] * xViejo[j]; 
				}
				xnuevo[i] = (b[i] - suma)/a[i][i];
				xnuevo[i] = factor_relajacion * xnuevo[i] + (1-factor_relajacion) * xViejo[i]; 
			}
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xnuevo[i] - xViejo[i]) * (xnuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignación del vector viejo para la próxima pasada.
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
