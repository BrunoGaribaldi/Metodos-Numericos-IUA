#include <stdio.h>
#include <math.h>

#define MAXCOL 2
#define MAXCOLM 100
#define MAXROW 100

void readTxtI(double[MAXROW][MAXCOL], int *);

void printMatrixI(double[MAXROW][MAXCOL], int);

void buildMatrix(double [MAXROW][MAXCOL], double [MAXROW][MAXCOLM], double [MAXROW], int, int);

void error (double [MAXROW], double [MAXROW][MAXCOL], int, int);

void triangulation(double [MAXROW][MAXCOLM], double [MAXROW], int, int);

void retrosustitucion(double [MAXROW][MAXCOLM], double [MAXROW], double [MAXROW], int, int);

void pivot(double [MAXROW][MAXCOLM], double [MAXROW], int, int, int);

void polynomial (double [MAXROW], int);


void printMatrix(double [MAXROW][MAXCOLM], double [MAXROW], int, int);

int main(int argc, char *argv[]) {
    int rows, p;
    double nodes[MAXROW][MAXCOL];
    double m[MAXROW][MAXCOLM];
    double b[MAXROW];
    double x[MAXROW];

    printf("Ingrese el grado del polinomio\n");
    scanf("%d", &p);
    p = p+1; //Correccion por no consideracion del termino a0
    readTxtI(nodes, &rows);
    printMatrixI(nodes, rows);
    buildMatrix(nodes, m, b, rows, p);
    printf("----------- MATRIZ AMPLIADA -----------\n");
    printMatrix(m, b, p, p);
    printf("---------------------------------------\n");
    printf("----------- MATRIZ REDUCIDA -----------\n");
    triangulation(m, b, p, p);
    printf("---------------------------------------\n");
    retrosustitucion(m, b, x, p, p);
    error(x, nodes, p, rows);
    polynomial(x, p);

    return 0;
}

void readTxtI(double m[MAXROW][MAXCOL], int *rows) {
    FILE *readPtr;
    int j, i, n;
    float k;
    readPtr = fopen("data.txt", "r");
    fscanf(readPtr, "%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < MAXCOL; j++) {
            fscanf(readPtr, "%f", &k);
            m[i][j] = k;
        }
    }
    fclose(readPtr);
    *rows = n;
}

void printMatrixI(double m[MAXROW][MAXCOL], int rows) {
    printf("------ NODOS ------\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAXCOL; j++) {
            printf(" %lf ", m[i][j]);
        }
        printf("\n");
    }
    printf("-------------------\n");
}

void printMatrix(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lf ", m[i][j]);
        }
        printf("%lf", b[i]);
        printf("\n");
    }
}

void buildMatrix(double n[MAXROW][MAXCOL], double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int p) {

    for (int i = 0; i < p; ++i) {
        double sumxy = 0;
        for (int j = 0; j < rows; ++j) {
            sumxy = sumxy + pow(n[j][0], i) * n[j][1];
        }
        b[i] = sumxy;
        for (int j = 0; j < p; ++j) {
            double sumx = 0;
            for (int k = 0; k < rows; ++k) {
                sumx = sumx + pow(n[k][0], i + j);
            }
            m[i][j] = sumx;
        }
    }

}

void error (double a[MAXROW], double n[MAXROW][MAXCOL], int p, int rows){
    double yb = 0;
    double e = 0;
    double ecm;
    double st = 0;
    double r;
    for (int i = 0; i < rows; ++i) {
        double sum = 0;
        for (int j = 0; j < p; ++j) {
            sum = sum + a[j]*pow(n[i][0], j);
        }
        e = e + pow(n[i][1]-sum, 2);
        yb = yb + n[i][1];
    }
    yb = yb/(rows+1);
    for (int i = 0; i < rows; ++i) {
        st = st + pow(n[i][1]-yb, 2);
    }
    r = sqrt(fabs(e-st)/st);
    ecm = sqrt(e/rows);
    printf("El error es de: %lf\n", e);
    printf("El error cuadratico medio es de: %lf\n", ecm);
    printf("st: %lf\n", st);
    printf("El coeficiente de correlacion es: %lf\n", r);
}

void triangulation(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows - 1; ++i) {
        pivot(m, b, rows, columns, i);
        for (int j = i + 1; j < rows; ++j) {
            double factor = -m[j][i] / m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    printMatrix(m, b, rows, columns);
}

void pivot(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns, int i) {
    double tolerance = pow(10, -3);
    if (fabs(m[i][i]) < tolerance) {
        for (int j = i + 1; j < rows; ++j) {
            if (fabs(m[j][i]) > fabs(m[i][i])) {
                for (int k = i; k < columns; ++k) {
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
                double swap = b[i];
                b[i] = b[j];
                b[j] = swap;
            }
        }
    }
}

void retrosustitucion(double m[MAXROW][MAXCOLM], double b[MAXROW], double x[MAXROW], int rows, int columns) {
    double value;
    value = b[rows - 1] / m[rows - 1][columns - 1];
    x[rows - 1] = value;
    for (int i = rows - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    printf("Conjunto solucion: \n");
    for (int i = 0; i < rows; ++i) {
        printf("x%d = %lf\n", i, x[i]);
    }
}

void polynomial (double x[MAXROW], int p){
    printf("Polinomio: \n");
    int pow = 0;
    for (int i = 0; i <= p - 1; i++) {
        if (pow == 0)
            printf("%lf", x[i]);
        else {
            if (x[i] >= 0)
                printf(" + %E.x^%d ", x[i], pow);
            else
                printf(" %E.x^%d", x[i], pow);
        }
        pow++;
    }
}


