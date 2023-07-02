#include <omp.h>
#include <bits/stdc++.h>

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


void generateRandomMatrix(int *matrix, int dim) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, 100);

  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      matrix[i * dim + j] = dis(gen);
    }
  }
}


void saveMatrixToFile(const int *matrix, int dim, const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    for (int i = 0; i < dim; ++i) {
      for (int j = 0; j < dim; ++j) {
        file << matrix[i * dim + j] << " ";
      }
      file << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Unable to open file: " << filename << std::endl;
  }
}


int main() {
  int dim = 1000;

  std::string filenameA = "./matrixA.txt";
  std::string filenameB = "./matrixB.txt";
  std::string filenameC = "./matrixC.txt";

  int *A = (int *)malloc(dim * dim * sizeof(int));
  int *B = (int *)malloc(dim * dim * sizeof(int));
  int *C = (int *)malloc(dim * dim * sizeof(int));

  generateRandomMatrix(A, dim);
  generateRandomMatrix(B, dim);

  saveMatrixToFile(A, dim, filenameA);
  saveMatrixToFile(B, dim, filenameB);

  // 进行矩阵乘法
  double start_time = omp_get_wtime();
  matrix_multiply(A, B, C, dim);
  double end_time = omp_get_wtime();

  // 保存结果
  saveMatrixToFile(C, dim, filenameC);
  std::cout << "Execution time: " << end_time - start_time << " s" << std::endl;

  free(A);
  free(B);
  free(C);

  return 0;
}
