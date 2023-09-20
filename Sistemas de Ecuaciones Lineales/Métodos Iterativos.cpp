#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define FILAS 20
#define COLUMNAS 20

using namespace std;

void fileReader (double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA (double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB (double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

void jacobi (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
void gaussSeidel (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
void relajacion (double a[FILAS][COLUMNAS] , double b[FILAS], int filas);
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas);


int main(int argc, char* argv[])
{
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 0, columnas = 0;
	fileReader(m, &filas, &columnas);
	matrizA(a,m,filas, columnas);
	matrizB(b,m,filas, columnas);
	
	int scanner;
	printf("Seleccione:\n 1 --> Jacobi \n 2 --> Gauss Seidel \n 3 --> Gauss Seidel con Relajacion\n");
	scanf("%d",&scanner);
	switch(scanner){
		case 1:
			jacobi(a,b,filas);
			break;
			
		case 2: 
			gaussSeidel(a,b,filas);
			break;
		case 3: 
			relajacion(a,b,filas);
			break;
			
		default: 
			printf("\n Se seleccionó mal la opcion");
	}
	

}
void fileReader (double m[FILAS][COLUMNAS],int* filas, int* columnas){
	
	
	FILE *fp;
	char c;
	fp = fopen("data.txt","r");
	if ( fp == NULL )
	{
		printf("No se puede abrir el archivo");
	}
	int fila=0;
	int columna;
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
	columna = j;
	*columnas = columna;
	*filas = fila;
	
}
void matrizA (double a[FILAS][COLUMNAS],double m[FILAS][COLUMNAS], int filas, int columnas){
	for(int i = 0 ; i < filas ; i++){
		for (int j = 0 ; j < columnas - 1 ; j++){
			a[i][j] = m[i][j];
		}
	}
}
	
void matrizB (double b[FILAS],double m[FILAS][COLUMNAS], int filas, int columnas){

	for(int i = 0 ; i < filas ; i++){
		b[i] = m[i][columnas - 1];
	}
	
}
	
void jacobi(double a[FILAS][COLUMNAS] , double b[FILAS] , int filas){
	printf("\n\n***Ha seleccionado método de jacobi***\n\n");
	
	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
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
			xNuevo[i] = (b[i] - suma) / a[i][i];
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignación del vector viejo para la próxima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	printf("\n El resultado es: \nxnuevo = [\t");
	for (int i = 0; i < filas; i++) {
		printf("%lf\t", xNuevo[i]);
	}
	
	printf("]\n La cantidad de iteraciones fueron: %d \n El error es de %lf", iteraciones, error);
}
void gaussSeidel (double a[FILAS][COLUMNAS] , double b[FILAS], int filas){
	printf("\n\n***Ha seleccionado método de Gauss Seidel***\n\n");
	
	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
	printf("\nIngrese la tolerancia\n");
	scanf("%lf", &tolerancia);
	
	do {
		iteraciones++;
		for (int i = 0; i < filas; i++) {
			suma = 0;
			if(i == 0){
				for(int j = 1 ; j < filas ; j++){
					suma+= a[i][j] * xNuevo[j];
				}
				xNuevo[i] = (b[i] - suma)/a[i][i]; 
			}else{
				for(int j = 0 ; j < i  ; j++){
					suma += a[i][j] * xNuevo[j];
				}
				
				for(int j = i+1 ; j < filas ; j++){
					suma+= a[i][j] * xViejo[j]; 
				}
				
				xNuevo[i] = (b[i] - suma)/a[i][i];
			}
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignación del vector viejo para la próxima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	printf("\n El resultado es: \nxnuevo = [\t");
	for (int i = 0; i < filas; i++) {
		printf("%lf\t", xNuevo[i]);
	}
	
	printf("]\n La cantidad de iteraciones fueron: %d \n El error es de %lf", iteraciones, error);
}
	
void relajacion (double a[FILAS][COLUMNAS] , double b[FILAS], int filas){
	printf("\n\n***Ha seleccionado método de Gauss Seidel con Coeficiente de Relajacion***\n\n");
	bool check = diagonalmenteDominante(a,filas);
	if(!check)
		exit(0);
	
	double suma = 0; 
	double* xNuevo = (double*)malloc(filas * sizeof(double));
	double* xViejo = (double*)malloc(filas * sizeof(double));
	
	if(xNuevo == NULL || xViejo == NULL){
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for (int i = 0; i < filas; i++) {
		xViejo[i] = 0.0;
		xNuevo[i] = xViejo[i];
	}
	
	double error;
	double tolerancia;
	int iteraciones = 0;
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
					suma+= a[i][j] * xNuevo[j];
				}
				xNuevo[i] = (b[i] - suma)/a[i][i];
				xNuevo[i] = factor_relajacion * xNuevo[i] + (1-factor_relajacion) * xViejo[i]; 
			}else{
				for(int j = 0 ; j < i  ; j++){
					suma += a[i][j] * xNuevo[j];
				}
				
				for(int j = i+1 ; j < filas ; j++){
					suma+= a[i][j] * xViejo[j]; 
				}
				
				xNuevo[i] = (b[i] - suma)/a[i][i];
				xNuevo[i] = factor_relajacion * xNuevo[i] + (1-factor_relajacion) * xViejo[i]; 
			}
		}
		
		// Manejo del error
		suma = 0;
		for (int i = 0; i < filas; i++) {
			suma += (xNuevo[i] - xViejo[i]) * (xNuevo[i] - xViejo[i]);
		}
		error = sqrt(suma);
		
		// Reasignación del vector viejo para la próxima pasada.
		for (int i = 0; i < filas; i++) {
			xViejo[i] = xNuevo[i];
		}
	} while (error > tolerancia && iteraciones < 10000);
	
	printf("\n El resultado es: \nxnuevo = [\t");
	for (int i = 0; i < filas; i++) {
		printf("%lf\t", xNuevo[i]);
	}
	
	printf("]\n La cantidad de iteraciones fueron: %d \n El error es de %lf", iteraciones, error);

}
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas){
	double suma = 0; 
	int counter = 0;
	for(int i = 0; i < filas ; i++){
		suma = 0; 
		counter++;
		for(int j = 0 ; j < filas ; j++){
			if(j!=i){
				suma+= fabs(a[i][j]);
			}
		}
		
		if(fabs(a[i][i]) < suma)
			printf("\nLa matriz no es diagonalmente dominante. Fila: %d",counter);
		
		if(a[i][i] == 0){
			printf("\nCeros en la diagonal");
			return false;
		}
	}
	return true;
}
