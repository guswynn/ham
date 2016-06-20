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
  char line[50]; //will only be commits, 40 hex characters
  hashes = fopen("hashes.txt", "r");
  while (fgets(line, 100, hashes) != NULL){
    int count;
    unsigned char val[20];
    printf("%s, Vals: ", line);
    for (count = 0; count < 20; count++){
      sscanf(line + 2*count, "%02x", &val[count]);
      printf("%u ", (unsigned int) val[count]);
     }
  }
}

