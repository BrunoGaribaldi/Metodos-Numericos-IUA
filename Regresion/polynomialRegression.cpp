#include <iostream>
#include <cmath>
#include <iomanip>

#define MAXCOLUMNS 2
#define MAXCOLUMNS2 100
#define MAXROWS 100

using namespace std;

void printMatrix(double [MAXROWS][MAXCOLUMNS], int);
void assembleMatrix(double [MAXROWS][MAXCOLUMNS], double [MAXROWS][MAXCOLUMNS2], double [MAXROWS], int, int);
int gaussianElimination(double [MAXROWS][MAXCOLUMNS2], double [MAXROWS], double [MAXROWS], int);
void printPolynomial(double [MAXROWS], int);
void details(double [MAXROWS][MAXCOLUMNS], double [MAXROWS], int, int);

int main(void) {
	int rows = 6; // Cambiado a 6 ya que tienes 6 filas en los datos de ejemplo
	double matrix[MAXROWS][MAXCOLUMNS2];
	double b[MAXROWS];
	double x[MAXROWS];
	int flag = 1;
	int degree = 0;
	
	double nodes[6][2] = {{0.2 , -0.94}, {0.6 , -0.26},{1.3 , 2.35},{1.4 , 2.94},{1.8 , 5.45},{2.0 , 7.20}};
	
	cout << "---------------------------" << endl;
	cout << "METODO REGRESION POLINOMICA" << endl;
	cout << "---------------------------" << endl;
	
	printMatrix(nodes, rows);
	
	// Ingresar el grado del polinomio
	do {
		cout << endl;
		cout << "----------------------------" << endl;
		cout << "Ingresar grado del polinomio: " << endl;
		cout << "----------------------------" << endl;
		cin >> degree;
		
		if (rows < degree + 1) {
			cout << "La regresión no es posible para el polinomio deseado" << endl;
			flag = 1;
		} else {
			flag = 0;
		}
	} while (flag == 1);
	
	assembleMatrix(nodes, matrix, b, rows, degree);
	gaussianElimination(matrix, b, x, degree);
	printPolynomial(x, degree);
	details(nodes, x, rows, degree);
	
	return 0;
}

void printMatrix(double matrix[MAXROWS][MAXCOLUMNS], int rows) {
	cout << "LOS ELEMENTOS DE LA MATRIZ SON:" << endl;
	for (int indexA = 0; indexA < rows; indexA++) {
		for (int indexB = 0; indexB < MAXCOLUMNS; indexB++) {
			cout << matrix[indexA][indexB] << "\t";
		}
		cout << endl;
	}
}

void assembleMatrix(double nodes[MAXROWS][MAXCOLUMNS], double matrix[MAXROWS][MAXCOLUMNS2], double b[MAXROWS], int rows,
	int degree) {
	double sum;
	for (int indexA = 0; indexA <= degree; indexA++) {
		
		for (int indexB = 0; indexB <= degree; indexB++) {
			sum = 0;
			
			for (int indexC = 0; indexC < rows; indexC++) {
				sum = sum + pow(nodes[indexC][0], indexB + indexA);
			}
			
			matrix[indexA][indexB] = sum;
		}
		
		sum = 0;
		for (int indexB = 0; indexB < rows; indexB++) {
			sum = sum + (pow(nodes[indexB][0], indexA) * nodes[indexB][1]);
		}
		b[indexA] = sum;
	}
	
	// Imprimir matriz
	cout << endl << "Matriz de Vandermonde" << endl;
	for (int indexA = 0; indexA <= degree; indexA++) {
		for (int indexB = 0; indexB <= degree; indexB++) {
			cout << matrix[indexA][indexB] << " ";
		}
		cout << " ---> " << b[indexA];
		cout << endl;
	}
}
	
	int gaussianElimination(double matrix[MAXROWS][MAXCOLUMNS2], double b[MAXROWS], double x[MAXROWS], int rows) {
		// Eliminación gaussiana
		
		double aux;
		double factor;
		float e = pow(10, -3);
		
		// Triangulación superior
		for (int indexA = 0; indexA <= rows; indexA++) {
			
			// Pivoteo
			int swap = 0;
			if (fabs(matrix[indexA][indexA]) < e) {
				
				for (int indexB = indexA + 1; indexB <= rows - 1; indexB++) {
					
					if (fabs(matrix[indexB][indexA]) > fabs(matrix[indexA][indexA])) {
						
						for (int indexC = indexA; indexC <= rows - 1; indexC++) {
							aux = matrix[indexA][indexC];
							matrix[indexA][indexC] = matrix[indexB][indexC];
							matrix[indexB][indexC] = aux;
						}
						
						aux = b[indexA];
						b[indexA] = b[indexB];
						b[indexB] = aux;
						swap = 1;
						break;
					}
				}
				if (swap == 0) {
					cout << "Warning: sistema singular, no se puede resolver" << endl;
					return 1;
				} else {
					cout << "Pivoteo concretado " << endl;
				}
			}
			
			for (int indexB = indexA + 1; indexB <= rows; indexB++) {
				factor = (-matrix[indexB][indexA]) / (matrix[indexA][indexA]);
				
				for (int indexC = indexA; indexC <= rows; indexC++)
					matrix[indexB][indexC] = matrix[indexB][indexC] + factor * matrix[indexA][indexC];
					b[indexB] = b[indexB] + factor * b[indexA];
			}
		}
		
		// Imprime matriz triangular
		cout << endl << "La Matriz triangular superior quedo: " << endl;
		for (int indexA = 0; indexA <= rows; indexA++) {
			
			for (int indexB = 0; indexB <= rows; indexB++) {
				cout << matrix[indexA][indexB] << " ";
			}
			cout << b[indexA] << endl;
		}
		
		// Sustitución regresiva
		double suma;
		x[rows] = b[rows] / matrix[rows][rows];
		
		for (int indexA = rows - 1; indexA >= 0; indexA--) {
			suma = b[indexA];
			
			for (int indexB = indexA + 1; indexB <= rows; indexB++) {
				suma -= matrix[indexA][indexB] * x[indexB];
			}
			
			x[indexA] = (suma) / matrix[indexA][indexA];
		}
		
		cout << endl << "********Soluciones********" << endl;
		for (int index = 0; index <= rows; index++)
			cout << endl << "x" << index << "=" << x[index];
		cout << endl;
		
		return 0;
	}
	
	void printPolynomial(double x[MAXROWS], int degree) {
		
		cout << endl << endl;
		cout << "POLINOMIO" << endl;
		int exponente = 0;
		for (int index = 0; index <= degree; index++) {
			if (exponente == 0)
				cout << x[index];
			else {
				if (x[index] >= 0)
					cout << " + " << x[index] << " " << "X^" << exponente << " ";
				else
					cout << x[index] << " " << "X^" << exponente << " ";
			}
			exponente++;
		}
	}
	
	void details(double nodes[MAXROWS][MAXCOLUMNS], double x[MAXROWS], int rows, int degree) {
		
		cout << endl << endl << "--------" << endl;
		cout << "DETALLES" << endl;
		cout << "--------" << endl;
		double syx;    // Desviación estándar-(error estándar estimado)
		double sr;    // Error, residuo - (suma de los cuadrados de los residuos)
		double st;    // Error medio- (suma total de los cuadrados)
		double r2;    // Coeficiente de determinación
		double r;    // Coeficiente de correlación
		double ymedia;    // Media de y
		double sum;
		double ecm;
		
		// Cálculo de media de y
		ymedia = 0;
		for (int index = 0; index < rows; index++){
			ymedia = ymedia + nodes[index][1];
		}
			ymedia = ymedia / rows;
			
			// calculo suma total de los cuadrados
			st = 0;
			for (int index = 0; index < rows; index++)
				st = st + pow(nodes[index][1] - ymedia, 2);
			
			// Cálculo del error-residuo
			sr = 0;
			for (int indexA = 0; indexA < rows; indexA++) {
				sum = 0;
				for (int indexB = 0; indexB <= degree; indexB++) {
					sum = sum + (x[indexB] * pow(nodes[indexA][0], indexB));
				}
				sr = sr + pow((nodes[indexA][1] - sum), 2);
			}
			
			ecm = sqrt(sr/rows);
			
			// Cálculo del error estandar estimado (desviación estándar)
			syx = sqrt(sr / ((double) rows - (degree + 1)));
			
			// Cálculo del coeficiente de determinación
			r2 = fabs(st - sr) / st;
			
			// Cálculo del coeficiente de correlación
			r = sqrt(r2);
			
			// Impresión de los resultados
			cout << "Error/Residuo (suma de cuadrados de los residuos): " << sr << endl;
			cout << "Error cuadrático medio: " << ecm << endl;
			cout << "Desviación estándar (Error estándar estimado): " << syx << endl;
			cout << "Error medio (suma total de cuadrados): " << st << endl;
			cout << "Coeficiente de determinación: " << r2 << endl;
			cout << "Coeficiente de correlación: " << r << endl;
	}
	
