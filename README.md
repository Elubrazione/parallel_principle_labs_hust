# HUST-2023春 并行编程与实践

## [任务一](./task1.cpp) 使用OpenMP进行并行矩阵乘法
出现链接错误`undefined reference to 'omp_get_wtime'`是因为没有链接OpenMP库，在编译命令中添加-fopenmp选项即可，命令如下。
```bash
# 添加选项
g++ -fopenmp task1.cpp -o task1

# 命令行
cd "e:\Codefield\parallel_principle_labs_hust\task1\" ;
if ($?) { g++ -fopenmp task1.cpp -o task1 } ; if ($?) { .\task1 }
```
## [任务二](./task2.cpp) 使用Pthreads实现并行文本搜索