#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

unsigned char ham(unsigned char c1, unsigned char c2){
  unsigned char dist = 0;
  unsigned char diff = c1 ^ c2;
  //count the ones
  for (dist = 0; diff; dist++){
    diff &= (diff-1);
  }
  return dist;
}

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






