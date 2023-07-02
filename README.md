# HUST-2023春 并行编程与实践

## [任务一](./task1/task1.cpp) 使用OpenMP进行并行矩阵乘法

### BUGS
出现链接错误`undefined reference to 'omp_get_wtime'`是因为没有链接OpenMP库，在编译命令中添加-fopenmp选项即可，命令如下。
```bash
# 添加选项
g++ -fopenmp task1.cpp -o task1

# 命令行
cd "e:\Codefield\parallel_principle_labs_hust\task1\" ;
if ($?) { g++ -fopenmp task1.cpp -o task1 } ; if ($?) { .\task1 }
```

### LOGS
#### Step 1
不使用任何优化的情况下，`dim=1000`的情况下计算两个矩阵乘法所花费的时间如下：

![step1](./task1/src/1.png)

#### Step 2
加上 `#pragma omp parallel for` 指令来并行化矩阵乘法，它会让编译器将接下来的for循环并行化执行，其中每个线程将负责处理不同的迭代。而OpenMP会自动根据可用的线程数进行任务划分和分配。花费的时间如下：

![step2](./task1/src/2.png)


## [任务二](./task2.cpp) 使用Pthreads实现并行文本搜索