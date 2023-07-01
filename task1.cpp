#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// 第一关怎么写都能过，只要结果是对的就能过

void matrix_multiply(int A[], int B[], int C[], int dim) {
  // ======= Write your code below =======
  // 使用OpenMP指令并行化计算过程
  #pragma omp parallel for
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      int sum = 0;
      for (int k = 0; k < dim; k++) {
        sum += A[i * dim + k] * B[k *dim + j];
      }
      C[i * dim + j] = sum;
    }
  }
  // ======= Write your code above =======
}

int main() {
  int dim;

  scanf("%d", &dim);

  int *A = (int *)malloc(dim * dim * sizeof(int));
  int *B = (int *)malloc(dim * dim * sizeof(int));
  int *C = (int *)malloc(dim * dim * sizeof(int));

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      scanf("%d", &A[i * dim + j]);
    }
  }

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      scanf("%d", &B[i * dim + j]);
    }
  }

  // 进行矩阵乘法
  matrix_multiply(A, B, C, dim);

  // 打印结果矩阵 C
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%d ", C[i * dim + j]);
    }
    printf("\n");
  }

  free(A);
  free(B);
  free(C);

  return 0;
}
