#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	//Armar la matriz aumentada
	// p es el grado del polinomio +1 (porq arranca en cero)
	//n es el arreglo que contiene los puntos (xi,yi)
	//filas es basicamente la cantridad de (xi,yi) que tenes
	//como resultado tengo b y m
	
	for (int i = 0 ; i < p ; i++){
		double sumxy = 0; 
		for (int j = 0 ; j < filas ; j++){
			sumxy = sumxy + pow(n[j][0],i)*n[j][1];
		}
		b[i] = sumxy;
		for(int j = 0; j<p ; j++){
			double sumx = 0;
			for(int k = 0; k < filas ; k++){
				sumx = sumx + pow(n[k][0],i+j);
			}
			m[i][j] = sumx;
		}
	}
	
	return 0;
}
