#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>



unsigned char ham(unsigned char c1, unsigned char c2){
  unsigned char dist = 0;
  unsigned char diff = c1 ^ c2;
  //count the ones
  for (dist = 0; diff; dist++){
    diff &= (diff-1);
  }
  return dist;
}

int calc_diff(char *l1, char *l2){
    int count;
    unsigned int val1;
    unsigned int val2;
    int sum = 0;
    for (count = 0; count < 20; count++){
      sscanf(l1 + 2*count, "%02x", &val1);
      sscanf(l2 + 2*count, "%02x", &val2);
      sum += ham(val1, val2);
    }
   return sum;
  }





int main(int argc, char **argv){
  /*
  char* test = "cd4e49485429ef53d3f91e9ec8c3c85a094405da";
  unsigned char val[20];
  int count;
  for (count = 0; count < 20; count++){
    sscanf(test + 2*count, "%02x", &val[count]);
    printf("NEW VAL:%u\n", (unsigned int) val[count]);
    printf("hex check:%02x\n\n", val[count]);
   }
*/


  FILE *hashes;
  FILE *hashes2;
  char line[50]; //will only be commits, 40 hex characters
  char line2[50]; //will only be commits, 40 hex characters
  hashes = fopen("hashes.txt", "r");
  hashes2 = fopen("hashes2.txt", "r");
  int sum = 0;
  int count = 0;
  int min = 161;
  char min1[50];
  char min2[50];
  char *a1 = malloc(50);
  char *a2 = malloc(50);
  while (fgets(line, 100, hashes) != NULL){
    while (fgets(line2, 100, hashes2)!= NULL){
      //printf("%s\n", line);
      //printf("%s\n", line2);
      memcpy(a1, line, 50);
      memcpy(a2, line2, 50);
      int val = calc_diff(a1, a2);
      printf("val:%d\n", val);
      sum += val;
      count = val == 0 ? count : count + 1;
      if (val < min && val != 0){
        min = val;
        memcpy(min1, a1, 50);
        memcpy(min2, a2, 50);
      }
    }
  }
  printf("MIN:%d\n", min);
  printf("ONE:%s, TWO:%s\n", min1, min2);
  printf("AVG:%f\n", (float) sum / (float) count);
}






