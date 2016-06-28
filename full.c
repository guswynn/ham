#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned char ham(unsigned char c1, unsigned char c2){
  unsigned char dist = 0;
  unsigned char diff = c1 ^ c2;
  /* count the ones */
  for (dist = 0; diff; dist++){
    diff &= (diff-1);
  }
  return dist;
}
/*
int main(int argc, char **argv){

  int fd = open("compact", O_RDONLY);
  struct stat sb;
  
  if(fstat(fd, &sb) == -1){
    printf("stat problem");
  }


  size_t len = sb.st_size;

  char *addr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);

  int min = 161;
  int count = 0;
  int i,j;
  for (i = 0; i < len; i+=20) {
      for (j = i; j < len; j+=20) {
        int k;
        int h = 0;
        count++;
        for(k = 0; k < 20; k++){
          h += ham(addr[i+k], addr[j+k]);
        }
        if (h < min && h != 0){
          min = h;
        }
    }
    printf("%d\n", count/100000);
    if ((count % 100000000 == 0) && count !=0){
        break;
      }
  }
  printf("MIN:%d\n", min);
}
*/






void *DoWork(void *args){
  printf("ID: %lu, CPU: %d\n", pthread_self(), sched_getcpu()); 
  /* vals, [min, index1, index2] */
  int *saved = (int *) args;
  int offset = saved[0];
  printf("offset:%d\n\n", offset);
  int fd = open("compact", O_RDONLY);
  struct stat sb;
  
  if(fstat(fd, &sb) == -1){
    printf("stat problem");
  }


  size_t len = sb.st_size;

  char *addr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);

  saved[0] = 161;
  int count = 0;
  int i,j;
  for (i = (20*offset); i < len; i+=(20*offset)) {
      for (j = i+20; j < len; j+=20) {
        int k;
        int h = 0;
        count++;
        for(k = 0; k < 20; k++){
          h += ham(addr[i+k], addr[j+k]);
        }
        if (h < saved[0] && h != 0){
          saved[0] = h;
          saved[1] = i;
          saved[2] = j;
        }
    }
    if ((count > 1000000)){
        printf("%d\n", count/1000000);
        break;
    }
    if ((count > 100000000)){
        printf("%d\n", count/100000);
        break;
    }
  }
  munmap(addr, len);

  return 0;
}
  
/* I know there are 4 threads i'm going to make, so twelve values: */
int vals[12];
  

int main(int argc, char **argv){
  vals[0] = 0;
  vals[3] = 1;
  vals[6] = 2;
  vals[9] = 3;

  int num_cpu = sysconf(_SC_NPROCESSORS_ONLN);
  printf("num of processors: %d\n", num_cpu);

  pthread_t threads[num_cpu];
  pthread_attr_t attr;
  cpu_set_t cpus;
  pthread_attr_init(&attr);
  int i; 
  for (i = 0; i < num_cpu; i++) {
    CPU_ZERO(&cpus);
    CPU_SET(i, &cpus);
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpus);
    pthread_create(&threads[i], &attr, DoWork, (void *) (vals+(i*3)));
  }

  for (i = 0; i < num_cpu; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("min1:%d, min2:%d, min3:%d, min4:%d\n", vals[0], vals[3], vals[6], vals[9]);
  return 0;
}








