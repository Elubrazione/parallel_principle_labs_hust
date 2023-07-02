#include <omp.h>
#include <bits/stdc++.h>

int block_size = 32;

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


void matrix_multiply_block(int A[], int B[], int C[], int dim) {

  // 使用OpenMP指令并行化计算过程
  #pragma omp parallel for collapse(2)
  for (int i = 0; i < dim; i += block_size) {
    for (int j = 0; j < dim; j += block_size) {
      for (int k = 0; k < dim; k += block_size) {
        // 计算当前块的起始和结束索引
        int i_end = i + block_size < dim ? i + block_size : dim;
        int j_end = j + block_size < dim ? j + block_size : dim;
        int k_end = k + block_size < dim ? k + block_size : dim;

        // 在当前块内进行矩阵乘法计算
        for (int ii = i; ii < i_end; ++ii) {
          #pragma omp simd
          for (int jj = j; jj < j_end; ++jj) {
            for (int kk = k; kk < k_end; ++kk) {
              C[ii * dim + jj] += A[ii * dim + kk] * B[kk * dim + jj];
            }
          }
        }
      }
    }
  }
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
  for (int i = 0; i < 10; i++)
    matrix_multiply_block(A, B, C, dim);
  // matrix_multiply(A, B, C, dim);
  double end_time = omp_get_wtime();

  // 保存结果
  // std::cout << "Origin Mode" << std::endl;
  // std::cout << "Using OpenMp (#pragma omp parallel for)" << std::endl;
  std::cout << "Using OpenMp and Blocks With SIMD" << std::endl;
  saveMatrixToFile(C, dim, filenameC);
  std::cout << "Execution time: " << end_time - start_time << " s" << std::endl;

  free(A);
  free(B);
  free(C);

  return 0;
}
