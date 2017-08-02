#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void pseudoRandomGeneratorAlgorithm(unsigned char state[],int sizeGenerate){
  int i=0,j=0,aux=0,k=0;
  unsigned char character;
  FILE *outF = fopen("saida.dat","w");

   for (k=0; k < sizeGenerate; k++)  {
      i = (i + 1) % 256;
      j = (j + state[i]) % 256;
      aux = state[i];
      state[i] = state[j];
      state[j] = aux;

      character = state[(state[i] + state[j]) % 256];
      fputc(character, outF);
   }
    fclose(outF);
}

void keySchedulingAlgorithm(unsigned char state[], unsigned char key[], int keyLen){
  int i=0,j=0,aux=0;

  // Init the state
  for (i=0; i < 256; i++){
    state[i] = i;
  }

   for (i=0; i < 256; ++i) {
      j = (j + state[i] + key[i % keyLen]) % 256;
      aux = state[i];
      state[i] = state[j];
      state[j] = aux;
   }
}


int main(){
  unsigned char key[256];
  unsigned char state[256];
  int sizeGenerate=0;
  int i=0;

  printf("Insira a chave:\n" );
  scanf("%s",key);

  keySchedulingAlgorithm(state,key,strlen(key));

  printf("Insira o numero de bytes a serem gerados: " );
  scanf("%d",&sizeGenerate);

  pseudoRandomGeneratorAlgorithm(state,sizeGenerate);

  printf("Saida gerada no arquivo 'saida.dat' \n");

 return 0;
}
