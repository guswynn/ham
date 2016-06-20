#include <stdio.h>
#include <string.h>
#include <stdint.h>



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
  
  unsigned int val1;
  unsigned int val2;

  sscanf(argv[1], "%u", &val1);
  sscanf(argv[2], "%u", &val2);
  

  unsigned char count = ham((unsigned char) val1, (unsigned char) val2);
  
  printf("count:%u\n", (unsigned int) count);


  char* test = "asdfasdf";
  char* test2 = "bsdfasdf";

  int i;
  int sum = 0;
  for (i = 0; i < sizeof(test); i++){
    sum += ham((unsigned char)test[i], (unsigned char)test2[i]);
  }
  printf("sum:%u", (unsigned int) sum);

}

