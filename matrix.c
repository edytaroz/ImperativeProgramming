#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n) {
	for(int i = 0; i < n; ++i) {
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n) {
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

void print_mat_ind(double A[][SIZE], int m, int n, const int indices[]);

// 5.1
// Calculate matrix product, AB = A X B
// A[m][p], B[p][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n)
{
    double tmp = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < p; k++)
            {
                tmp += (A[i][k]*B[k][j]);
            }
            AB[i][j] = tmp;
            tmp = 0;
        }
    }
}

// Calculate matrix - vector product
void mat_vec_product(double A[][SIZE], const double b[], double Ab[], int m, int n);

void backward_substit(double A[][SIZE], double x[], int n);

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n);

// 5.2
// Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n)
{
    double tmp = 0;
    double wyznacznik = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i][i] == 0)
        {
            return NAN;
        }
        wyznacznik *= A[i][i];
        for (int j = i + 1; j < n; j++)
        {
            if (A[j][i] != 0)
            {
                tmp = A[j][i]/A[i][i];
                tmp *= (-1);
                for (int k = i ; k < n; k++)
                {
                    A[j][k] += (tmp*A[i][k]);
                }
            }
        }
    }
    wyznacznik *= A[n-1][n-1];
    return wyznacznik;
}

// 5.3
// Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps)
{
    double wyznacznik = 1, znak = 0;
    int index[n];
    int swap;
    double wsp;
    double B[n];
    for (int i = 0; i < n; i++)
    {
        B[i] = b[i];
    }

    for(int i = 0; i < n; i++){
        index[i] = i;
    }

    for(int k = 0; k < n; k++){
        for(int w = n-1; w > k; w--){
            if(A[index[w]][k] > A[index[w-1]][k]){
                swap = index[w-1];
                index[w-1] = index[w];
                index[w] = swap;
                znak++;
            }
        }
        if(fabs(A[index[k]][k]) < eps){
            wyznacznik = 0;
        }
        for(int w = k+1; w < n; w++){
            wsp = A[index[w]][k]/A[index[k]][k];
            A[index[w]][k] = 0;
            for(int j = k+1; j < n; j++){
                A[index[w]][j] = A[index[w]][j] - A[index[k]][j] * wsp;
            }
            B[index[w]] = B[index[w]] - B[index[k]]* wsp;
        }
        wyznacznik = wyznacznik*A[index[k]][k];
    }
    for(int w = n-1; w >=0; w--){
        for(int i = n-1; i>w; i--){
            B[index[w]] -= x[i]*A[index[w]][i];
        }
        x[w]=B[index[w]]/A[index[w]][w];
    }
    return wyznacznik * pow(-1,znak);
    /*
    double tmp = 0;
    double maks = A[0][0];
    for (int i = 0; i < n; i++)
    {
        x[i] = b[i];
    }
    int rem = 0;
    double det = 1;
    for (int i = 0; i < n - 1; i++)
    {
        maks = A[i][i];
        for (int j = i; j < n; j++)
        {
            if (fabs(A[j][i]) > fabs(maks))
            {
                maks = A[j][i];
                rem = j;
            }
        }
        if (maks != A[i][i])
        {
            det *= (-1);
        }
        if (maks < eps)
        {
            return 0;
        }
        double t = 0;
        double p = 0;
        det *= maks;
        for (int j = i; j < n; j++)
        {
            t = A[i][j];
            p = A[rem][j];
            A[i][j] = p;
            A[rem][j] = t;
        }
        t = x[rem];
        x[rem] = x[i];
        x[i] = t;
        tmp = 0;
        for (int j = i + 1; j < n; ++j) {
            if (A[i][i] != 0)
            {
                tmp = A[j][i] / A[i][i];
                tmp *= (-1);
                for (int k = i; k < n; ++k) {
                    A[j][k] += (tmp * A[i][k]);
                }
                x[j] += (tmp * x[i]);
            }
        }
    }
    det *= A[n-1][n-1];
    if (det != 0 && b != NULL && x != NULL)
    {
        tmp = 0;
        for (int i = n - 1; i > -1; i--)
        {
            for (int k = i + 1; k < n; k++)
            {
                tmp = A[i][k]/A[k][k];
                x[i] -= (A[i][k] * x[k]);
                A[i][k] -= tmp * A[k][k];
            }
            x[i] /= A[i][i];
        }
        return det;
    }
     */
}

// 5.4
// Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.

double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps)
{
    double tmp = 0;
    double maks = A[0][0];
    int rem = 0;
    double det = 1;
    double t[n][2*n];
    for (int i = 0; i< n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            t[i][j] = A[i][j];
            t[i][j+n] = 0;
        }
        t[i][i+n] = 1;
    }
    for (int i = 0; i < n - 1; i++)
    {
        det *= t[i][i];
        if (t[i][i] != 1)
        {
            int j = i + 1;
            while (t[j][i] == 0 && j < n)
            {
                j += 1;
            }
            tmp = (-1) * (t[i][i] - 1) / t[j][i];
            for (int k = i; k < 2*n; k++){
                t[i][k] += tmp * t[j][k];
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            tmp = t[j][i] / t[i][i];
            tmp *= (-1);
            for (int k = i; k < 2*n; k++)
            {
                t[j][k] += (tmp * t[i][k]);
            }
        }
    }
    det = t[n-1][n-1];
    tmp = t[n-1][n-1];
    for (int i = n - 1; i < 2*n; i++)
    {
        t[n-1][i] /= tmp;
    }
    for (int i = 0; i < n-1; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            tmp = (-1) * t[i][k]/t[k][k];
            for (int j = i + 1; j < 2*n; j++)
            {
                t[i][j] += tmp*t[k][j];
            }
        }
    }
    /*
    for (int i = 0; i < n - 1; i++)
    {

        maks = A[i][i];
        for (int j = i; j < n; j++)
        {
            if (fabs(t[j][i]) > fabs(maks))
            {
                maks = t[j][i];
                rem = j;
            }
        }
        if (maks < eps)
        {
            return 0;
        }
        double temp = 0;
        for (int j = i; j < n; j++)
        {
            temp = t[i][j];
            t[i][j] = t[rem][j];
            t[rem][j] = temp;
        }

        det *= t[i][i];
        if (t[i][i] != 1)
        {
            int j = i + 1;
            while (t[j][i] == 0 && j < n)
            {
                j += 1;
            }
            tmp = (-1) * (t[i][i] - 1) / t[j][i];
            for (int k = i; k < 2*n; k++){
                t[i][k] += tmp * t[j][k];
            }
        }
        for (int j = i + 1; j < n; j++)
        {
            tmp = t[j][i] / t[i][i];
            tmp *= (-1);
            for (int k = i; k < 2*n; k++)
            {
                t[j][k] += (tmp * t[i][k]);
            }
        }
    }
    det *= t[n-1][n-1];
    tmp = t[n-1][n-1];
    for (int i = n - 1; i < 2*n; i++)
    {
        t[n-1][i] /= tmp;
    }
    for (int i = 0; i < n-1; i++)
    {
        for (int k = i + 1; k < n; k++)
        {
            tmp = (-1) * t[i][k]/t[k][k];
            for (int j = i + 1; j < 2*n; j++)
            {
                t[i][j] += tmp*t[k][j];
            }
        }
    }
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = t[i][j+n];
        }
    }
    return det;
}

int main(void) {

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if(det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A,n,n);
			printf("%.4f\n",matrix_inv(A, B, n, eps));
			print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}
