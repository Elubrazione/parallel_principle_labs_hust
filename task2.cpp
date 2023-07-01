#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>

#define MAX_LINE_LENGTH 256

typedef struct {
  const char* filename;
  const char* target_string;
} ThreadData;

void* search_file(void* arg) {
  ThreadData* data = (ThreadData*)arg;
  char line[MAX_LINE_LENGTH];

  FILE* file = fopen(data->filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    pthread_exit(NULL);
  }

  int line_number = 1;
  // ======= Write your code below =======
  // 执行文本搜索
  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    if (strstr(line, data->target_string) != NULL)
      printf("%s:%d: %s", data->filename, line_number, line);
    line_number++;
  
  // 文件关闭&线程退出
  fclose(file);
  pthread_exit(NULL);
  // ======= write your code above =======
}

void search_files(const char* folder_path, const char* target_string) {
  DIR* directory;
  struct dirent* entry;

  directory = opendir(folder_path);
  if (directory == NULL) {
    perror("Error opening directory");
    return;
  }
  // ======= Write your code below =======
  pthread_t threads[256];
  ThreadData thread_data[256];
  int num_threads = 0;

  // 执行搜索任务
  while ((entry = readdir(directory)) != NULL) {
    // 为每个线程分配任务
    if (entry->d_type == DT_REG) {
      char file_path[MAX_LINE_LENGTH];
      snprintf(file_path, sizeof(file_path), "%s/%s", folder_path, entry->d_name);

      thread_data[num_threads].filename = strdup(file_path);
      thread_data[num_threads].target_string = target_string;

      pthread_create(&threads[num_threads], NULL, search_file, &thread_data[num_threads]);
      num_threads++;
    }
  }
  closedir(directory);

  // 线程同步
  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
    free((void*)thread_data[i].filename);
  }
  // ======= write your code above =======
}

int main() {
  char folder_path[256] = "/data/workspace/myshixun/texts";
  char target_string[256];

  scanf("%s", target_string);

  search_files(folder_path, target_string);

  return 0;
}
