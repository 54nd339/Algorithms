// Strassen’s algorithm for matrix multiplication
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nextPowerOf2(n) (int)pow(2, ceil(log2(n)))

int **allocateMatrix(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)malloc(n * sizeof(int));
    return matrix;
}
void add(int **A, int **B, int **C, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}
void sub(int **A, int **B, int **C, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    }
}

void Strassen(int **A, int **B, int **C, int n) {
    //base case
    if(n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    
    //divide A and B into 4 submatrices
    int **A11 = allocateMatrix(n/2);
    int **A12 = allocateMatrix(n/2);
    int **A21 = allocateMatrix(n/2);
    int **A22 = allocateMatrix(n/2);
    int **B11 = allocateMatrix(n/2);
    int **B12 = allocateMatrix(n/2);
    int **B21 = allocateMatrix(n/2);
    int **B22 = allocateMatrix(n/2);
    for(int i = 0; i < n/2; i++) {
        for(int j = 0; j < n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + n/2];
            A21[i][j] = A[i + n/2][j];
            A22[i][j] = A[i + n/2][j + n/2];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + n/2];
            B21[i][j] = B[i + n/2][j];
            B22[i][j] = B[i + n/2][j + n/2];
        }
    }
    
    // M1 = (A11 + A22)(B11 + B22)
    int **M1 = allocateMatrix(n/2);
    int **A11_A22 = allocateMatrix(n/2);
    int **B11_B22 = allocateMatrix(n/2);
    add(A11, A22, A11_A22, n/2);
    add(B11, B22, B11_B22, n/2);
    Strassen(A11_A22, B11_B22, M1, n/2);

    // M2 = (A21 + A22)B11
    int **M2 = allocateMatrix(n/2);
    int **A21_A22 = allocateMatrix(n/2);
    add(A21, A22, A21_A22, n/2);
    Strassen(A21_A22, B11, M2, n/2);

    // M3 = A11(B12 - B22)
    int **M3 = allocateMatrix(n/2);
    int **B12_B22 = allocateMatrix(n/2);
    sub(B12, B22, B12_B22, n/2);
    Strassen(A11, B12_B22, M3, n/2);

    // M4 = A22(B21 - B11)
    int **M4 = allocateMatrix(n/2);
    int **B21_B11 = allocateMatrix(n/2);
    sub(B21, B11, B21_B11, n/2);
    Strassen(A22, B21_B11, M4, n/2);

    // M5 = (A11 + A12)B22
    int **M5 = allocateMatrix(n/2);
    int **A11_A12 = allocateMatrix(n/2);
    add(A11, A12, A11_A12, n/2);
    Strassen(A11_A12, B22, M5, n/2);

    // M6 = (A21 - A11)(B11 + B12)
    int **M6 = allocateMatrix(n/2);
    int **A21_A11 = allocateMatrix(n/2);
    int **B11_B12 = allocateMatrix(n/2);
    sub(A21, A11, A21_A11, n/2);
    add(B11, B12, B11_B12, n/2);
    Strassen(A21_A11, B11_B12, M6, n/2);

    // M7 = (A12 - A22)(B21 + B22)
    int **M7 = allocateMatrix(n/2);
    int **A12_A22 = allocateMatrix(n/2);
    int **B21_B22 = allocateMatrix(n/2);
    sub(A12, A22, A12_A22, n/2);
    add(B21, B22, B21_B22, n/2);
    Strassen(A12_A22, B21_B22, M7, n/2);

    // C11 = M1 + M4 - M5 + M7
    int **C11 = allocateMatrix(n/2);
    int **M1_M4 = allocateMatrix(n/2);
    int **M5_M7 = allocateMatrix(n/2);
    add(M1, M4, M1_M4, n/2);
    sub(M5, M7, M5_M7, n/2);
    add(M1_M4, M5_M7, C11, n/2);

    // C12 = M3 + M5
    int **C12 = allocateMatrix(n/2);
    add(M3, M5, C12, n/2);

    // C21 = M2 + M4
    int **C21 = allocateMatrix(n/2);
    add(M2, M4, C21, n/2);

    // C22 = M1 - M2 + M3 + M6
    int **C22 = allocateMatrix(n/2);
    int **M1_M2 = allocateMatrix(n/2);
    int **M3_M6 = allocateMatrix(n/2);
    sub(M1, M2, M1_M2, n/2);
    add(M3, M6, M3_M6, n/2);
    add(M1_M2, M3_M6, C22, n/2);

    // C = [C11 C12]
    //     [C21 C22]
    for(int i = 0; i < n/2; i++) {
        for(int j = 0; j < n/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + n/2] = C12[i][j];
            C[i + n/2][j] = C21[i][j];
            C[i + n/2][j + n/2] = C22[i][j];
        }
    }
}
void Multiply(int **A, int **B, int **C, int n) {
    if(n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    Strassen(A, B, C, n);
}

int main() {
    printf("Enter the size of the matrix: ");
    int n; scanf("%d", &n);
    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);
    printf("Enter the elements of the first matrix: ");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter the elements of the second matrix: ");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    Multiply(A, B, C, n);
    printf("The product of the two matrices is: \n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}