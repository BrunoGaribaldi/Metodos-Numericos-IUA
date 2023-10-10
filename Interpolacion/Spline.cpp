//spline cubica

#include <iostream>
#include <math.h> 
#define FILAS 20
#define COLUMNAS 20
using namespace std;


void buildMatrix (double m[FILAS][2] , double a[FILAS][FILAS] , double b[FILAS] , int filas);

void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);


void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);


void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);

double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);	

void interpolacion (double m[FILAS][2], double x[FILAS], int filas);
	
	
	
int main(int argc, char *argv[]) {
	double m[4][2] = {{3,2.5},{4.5,1},{7,2.5},{9,0.5}}; 
	int filas = 4; //poner aca la cantidad de filas de m. acordate que la cantidad de intervalos es filas-1
	double a[FILAS][FILAS] = {{0}}; 
	double b[FILAS] = {0};
	//aca ingresa m
	printf("(X\t;\tY)\n\n");
	for(int i = 0 ; i < filas ; i++){ //FILAS aca ponelos a mano, segun la cantidad de puntos
		printf("(%lf\t;\t%lf)",m[i][0] , m[i][1]);
		printf("\n");
	}
	buildMatrix(m,a,b,filas);
	double* x = (double*)malloc((4*(filas-1)) * sizeof(double));
	triangulacion(a, b, x, 4*(filas-1));
	interpolacion(m,x,filas);
	return 0;
}

void buildMatrix (double m[FILAS][2] , double a[FILAS][FILAS] , double b[FILAS] , int filas){
	//construccion de las primeras 2n filas.
	int n = filas - 1; //esto es intervalos
	
	//construccion de las primeras 2n filas
	for (int k = 0 ; k < n ; k++){
		
		for(int j = 0 ; j < 4 ; j++){
			a[2*k][4*k + j] = pow(m[k][0] , 3 - j);
			a[2*k + 1][4*k + j] = pow(m[k+1][0] , 3 - j);
		}
		
		b[2*k] = m[k][1];
		b[2*k + 1] = m[k + 1][1];
	}
	
	//construccion de las derivadas primeras
	int k = 0; //hasta n-2
	for(int i = (2 * n) ; i <= ((3 * n) - 2) ; i++){ //filas
		
		for(int j = 0 ; j <= 2 ; ++j){
			a[i][4*k + j] = (3 - j) * pow(m[k+1][0] , 2 - j);
			a[i][4*(k+1) + j] = -(3 - j) * pow(m[k+1][0] , (2 - j));
			
		}
		k++;
		if(k > (n-2)){
			break;
		}
		b[i] = 0;
	}
	
	//construccion de las derivadas segundas
	k = 0; //hasta n-2
	for(int i = 3*n - 1 ; i <= 4*n -3 ; i++){
		
		a[i][4*k] = 6 * m[k+1][0];
		a[i][4*k + 1] = 2;
		a[i][4*(k+1)] = -6 * m[k+1][0];
		a[i][4*(k+1)+1] = -2; 

		k++;
		if(k > (n-2)){
			break;
		}
		b[i] = 0;
	}
	
	a[4*n - 2][0] = 3 * m[0][0];
	a[4*n - 2][1] = 1;
	a[4*n - 1][4*n - 4] = 3 * m[n][0];
	a[4*n - 1][4*n - 3] = 1;
	b[4*n - 2] = 0;
	b[4*n - 1] = 0;
	
	printf("\n");
	for(int i = 0 ; i < 4*n ; i++){
		for(int j = 0 ; j < 4*n ; j++){
			printf("\t%lf",a[i][j]);
		}
		printf("\t%lf\n",b[i]);
	}
	
}
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
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
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
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
	for (int i = 0; i < (filas/4); ++i) {
		printf("a%d = %lf\n", i , x[4*i]);
		printf("b%d = %lf\n", i , x[4*i + 1]);
		printf("c%d = %lf\n", i , x[4*i + 2]);
		printf("d%d = %lf\n", i , x[4*i + 3]);
	}
}
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i){
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
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
double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
	double norma = 1;
	for(int i = 0; i < filas ; i++){
		norma = norma * a[i][i];
	}
	return norma;
}
	
void interpolacion (double m[FILAS][2], double z[FILAS] ,int fila){
	double x;//Coeficiente a interpolar
	printf("Ingrese el valor a interpolar\n");
	scanf("%lf", &x);
	int intervalo;
	double resultado = 0; 
	if (x >= m[0][0] && x <= m[fila - 1][0]){
		
		for (int i = 0; i < fila; i++) {
			
			if(x >= m[i][0] && x < m[i+1][0]){
				resultado = z[4*i]*pow(x,3) + z[4*i+1]*pow(x,2) + z[4*i+2]*x + z[4*i+3];
				intervalo = i;
				break;
			}
		}
		printf("\nEl valor a interpolar se encuentra en el intervalo %d" , intervalo);
		printf("\nEl valor interpolado para %lf es: %lf", x, resultado);
		
	}else{
		printf("\nEl valor a interpolar no se encuentra en el rango de datos\n");
	}
}
