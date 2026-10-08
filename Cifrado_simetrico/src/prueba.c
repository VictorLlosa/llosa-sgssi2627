#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main( int argc,char *argv[]){
  if(argc != 3){
    printf("uso: ./cifrado desplazamiento \"mensaje\"");
    exit(0);
  }

  char *mensajeCifrado = argv[2];
  int desplazamiento = atoi(argv[1]);

  for (int j = 0; j < strlen(mensajeCifrado); j++){

    if((mensajeCifrado[j] >64 && mensajeCifrado[j] < 91) ||
      (mensajeCifrado[j] > 96 && mensajeCifrado[j] < 123)) { //si no es una letra se salta
      
      mensajeCifrado[j] = mensajeCifrado[j] + desplazamiento;

      if(mensajeCifrado[j] == 91){
        mensajeCifrado[j] = 65;
      }

      if(mensajeCifrado[j] == 123){
        mensajeCifrado[j] = 97;
      }
    }
  }

  printf("%s", mensajeCifrado);

  exit(1);


}
