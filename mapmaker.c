#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>




int main(int argc, char **argv){

  FILE *hashes;
  FILE *wb;
  char line[50]; //will only be commits, 40 hex characters
  hashes = fopen("hashes.txt", "r");
  wb = fopen("compact", "wb");
  while (fgets(line, 50, hashes) != NULL){
    int count;
    unsigned int val;
    for (count = 0; count < 20; count++){
      sscanf(line + 2*count, "%02x", &val);
      unsigned char c = (unsigned char) val;
//      write(wb,&c,1);
      fputc(c, wb);
     }
  }
  fclose(hashes);
  fclose(wb);
}






