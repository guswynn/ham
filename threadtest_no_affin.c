#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

void *DoWork(void *args){
  printf("ID: %lu, CPU: %d\n", pthread_self(), sched_getcpu()); 
  while(1);
  return 0;
}
  
  

int main(int argc, char **argv){


  int num_cpu = sysconf(_SC_NPROCESSORS_ONLN);
  printf("num of processors: %d\n", num_cpu);

  pthread_t threads[num_cpu];
   
  for (int i = 0; i < num_cpu; i++) {
    pthread_create(&threads[i], NULL, DoWork, NULL);
  }

  for (int i = 0; i < num_cpu; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}








