#include <stdio.h>

int main() {
	FILE *archivo;
	archivo = fopen("data.txt", "w"); // Abre el archivo en modo escritura ("w")
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return 1;
	}
	
	fprintf(archivo, "x\ty\n"); // Escribe encabezados de columna
	
	char respuesta;
	do {
		double x, y;
		
		printf("Ingrese el valor de x: ");
		scanf("%lf", &x);
		
		printf("Ingrese el valor de y: ");
		scanf("%lf", &y);
		
		fprintf(archivo, "%.2lf\t%.2lf\n", x, y); // Escribe los valores en el archivo
		
		printf("¿Desea ingresar otro par de valores? (s/n): ");
		scanf(" %c", &respuesta);
		
	} while (respuesta == 's' || respuesta == 'S');
	
	fclose(archivo); // Cierra el archivo
	
	printf("Datos escritos en el archivo 'data.txt'.\n");
	
	return 0;
}
