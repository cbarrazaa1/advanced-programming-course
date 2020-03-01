/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 21/Feb/2020
*/
#include <stdio.h>
#define N 2

/*
  Data structure to simplify passing around 2D matrices.
*/
typedef struct {
  int data[N][N];
} matrix2d;

/*
  getMatrix
  Gets a matrix from user input.
  @param m Pointer to matrix where the result will be put in.
*/
void getMatrix(matrix2d* m) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &m->data[i][j]);
    }
  }
}

/*
  getUserInput
  Gets the user input needed for the program.
  @param m1 Pointer to first matrix to be filled.
  @param m2 Pointer to second matrix to be filled.
*/
void getUserInput(matrix2d* m1, matrix2d* m2) {
  printf("Enter matrix 1:\n");
  getMatrix(m1);

  printf("Enter matrix 2:\n");
  getMatrix(m2);
}

/*
  printMatrix
  Prints a 2D matrix.
  @param m Pointer to matrix to print to screen.
*/
void printMatrix(const matrix2d* m) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", m->data[i][j]);
    }
    printf("\n");
  }
}

/*
  initMatrix
  Initializes a 2D matrix to all zeroes.
  @param m Pointer to matrix to initialize.
*/
void initMatrix(matrix2d* m) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m->data[i][j] = 0;
    }
  }
}

/*
  addMatrices
  Adds two matrices.
  @param m1 Pointer to first matrix to add.
  @param m2 Pointer to second matrix to add.
  @return Matrix where the sum result is stored.
*/
matrix2d addMatrices(const matrix2d* m1, const matrix2d* m2) {
  matrix2d m3;
  initMatrix(&m3);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m3.data[i][j] = m1->data[i][j] + m2->data[i][j];
    }
  }

  return m3;
}

/*
  subtractMatrices
  Subtracts two matrices.
  @param m1 Pointer to first matrix to subtract.
  @param m2 Pointer to second matrix to subtract.
  @return Matrix where the difference result is stored.
*/
matrix2d subtractMatrices(const matrix2d* m1, const matrix2d* m2) {
  matrix2d m3;
  initMatrix(&m3);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      m3.data[i][j] = m1->data[i][j] - m2->data[i][j];
    }
  }

  return m3;
}

/*
  multMatrices
  Multiplies two matrices.
  @param m1 Pointer to first matrix to multiply.
  @param m2 Pointer to second matrix to multiply.
  @return Matrix where the multiplication result is stored.
*/
matrix2d multMatrices(const matrix2d* m1, const matrix2d* m2) {
  matrix2d m3;
  initMatrix(&m3);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        m3.data[i][j] += m1->data[i][k] * m1->data[k][j];
      }
    }
  }

  return m3;
}

/*
  printOutput
  Prints the required results of the program.
  @param m1 Pointer to first matrix to use for results.
  @param m2 Pointer to second matrix to use for results.
*/
void printOutput(const matrix2d* m1, const matrix2d* m2) {
  matrix2d result;

  // print initial matrices
  printf("Matrix 1:\n");
  printMatrix(m1);

  printf("Matrix 2:\n");
  printMatrix(m2);

  // add matrices
  result = addMatrices(m1, m2);
  printf("Matrix 1 + Matrix 2:\n");
  printMatrix(&result);

  // subtract matrices
  result = subtractMatrices(m1, m2);
  printf("Matrix 1 - Matrix 2:\n");
  printMatrix(&result);

  // multiply matrices
  result = multMatrices(m1, m2);
  printf("Matrix 1 * Matrix 2:\n");
  printMatrix(&result);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  matrix2d m1, m2;

  getUserInput(&m1, &m2);
  printOutput(&m1, &m2);
  return 0;
}