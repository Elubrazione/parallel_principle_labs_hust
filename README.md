# HUST-2023春 并行编程与实践

## [任务一](./task1/task1.cpp) 使用OpenMP进行并行矩阵乘法

### TASK
- 你的程序应该能够接受两个矩阵作为输入，并计算它们的乘积。
- 使用OpenMP将矩阵乘法操作并行化，以加快计算速度。
- 考虑如何将矩阵数据进行划分和分配给不同的线程，以实现并行计算。
- 考虑如何处理并行区域的同步，以避免竞态条件和数据一致性问题。
- 考虑如何利用OpenMP的并行循环和矩阵计算指令，以进一步提高并行效率。

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
不使用任何优化的情况下，`dim=1000`的情况下计算两个矩阵乘法所花费的时间如下（这里为了放大观察，此后都将矩阵乘法执行10次）：

![step1](./task1/src/1.png)

#### Step 2
加上 `#pragma omp parallel for` 指令来并行化矩阵乘法，它会让编译器将接下来的for循环并行化执行，其中每个线程将负责处理不同的迭代。而OpenMP会自动根据可用的线程数进行任务划分和分配。花费的时间如下：

![step2](./task1/src/2.png)

#### Step 3
使用块划分的方法将矩阵划分为更小的块，块大小为32，并使用OpenMP的并行指令 `#pragma omp parallel for collapse(2)` 将计算任务分配给多个线程。花费的时间如下：

![step3](./task1/src/3.png)

#### Step 4
在块内的第二层循环内部使用 `#pragma omp simd` 指令来实现向量化并行计算。这个指令将循环内的迭代向量化，以利用SIMD指令集并行计算。

![step4](./task1/src/4.png)

## [任务二](./task2/task2.cpp) 使用Pthreads实现并行文本搜索

### TASK
- 你需要实现一个函数，该函数接受一个目标字符串和一个包含多个文本文件的文件夹路径。
- 程序应该并行地搜索每个文本文件，查找包含目标字符串的行，并将匹配的行打印出来。
- 每个线程应该处理一个文件，你需要合理地分配文件给不同的线程。
- 确保你的程序是线程安全的，并正确处理多个线程之间的同步问题。

### LOGS
