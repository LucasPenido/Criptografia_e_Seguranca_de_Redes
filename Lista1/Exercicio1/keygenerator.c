#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int left[28];
    int right[28];
}roundKey;

typedef struct{
    int key[48];
}chaveFinalRound;

typedef struct {
    int key[48];
}chaveRound;

int * parityDrop(int vetor[]){

	int i=0;
	int *vetor2=malloc(sizeof(int)*56);

	printf("\n====Vetor : ");
	for(i=0;i<64;i++){
		printf("%d",vetor[i]);
	}

    int matriz[56]  = {
        vetor[56],vetor[48],vetor[40],vetor[32],vetor[24],vetor[16],vetor[ 8],
        vetor[ 0],vetor[57],vetor[49],vetor[41],vetor[33],vetor[25],vetor[17],
        vetor[9], vetor[ 1],vetor[58],vetor[50],vetor[42],vetor[34],vetor[26],
        vetor[18],vetor[10],vetor[ 2],vetor[59],vetor[51],vetor[43],vetor[35],
        vetor[62],vetor[54],vetor[46],vetor[38],vetor[30],vetor[22],vetor[14],
        vetor[ 6],vetor[61],vetor[53],vetor[45],vetor[37],vetor[29],vetor[21],
        vetor[13],vetor[ 5],vetor[60],vetor[52],vetor[44],vetor[36],vetor[28],
        vetor[20],vetor[12],vetor[ 4],vetor[27],vetor[19],vetor[11],vetor[ 3]};

    printf("\nVetor parity drop: ");
    for(i = 0 ; i< 56 ; i++){
        vetor2[i] = matriz[i];
        printf("%d",vetor2[i]);
    }


   return vetor2;
}

int * compressionBox(int vetorLeft[],int vetorRight[]){
	int *vetor=malloc(sizeof(int)*56);
	int *vetor2=malloc(sizeof(int)*48);
	int j=0,i=0;


	for(i=0;i<56;i++){
		vetor[i]=0;
	}


	for(i=0;i<28;i++){
		vetor[i]=vetorLeft[i];
	}

	for(i=28;i<56;i++){
		vetor[i]=vetorRight[j];
		j++;
	}

	printf("\n\tVetor:          ");
	for(i=0;i<56;i++){
		printf("%d",vetor[i]);
	}

    int matriz[48]  = {
	        vetor[13],vetor[16],vetor[10],vetor[23],vetor[ 0],vetor[4],
	        vetor[ 2],vetor[27],vetor[14],vetor[ 5],vetor[20],vetor[9],
	        vetor[22],vetor[18],vetor[11],vetor[ 3],vetor[25],vetor[ 7],
	        vetor[15],vetor[ 6],vetor[26],vetor[19],vetor[12],vetor[ 1],
	        vetor[40],vetor[51],vetor[30],vetor[36],vetor[46],vetor[54],
	        vetor[29],vetor[39],vetor[50],vetor[44],vetor[32],vetor[47],
	        vetor[43],vetor[48],vetor[38],vetor[55],vetor[33],vetor[52],
	        vetor[45],vetor[41],vetor[49],vetor[35],vetor[28],vetor[31]};

	printf("\n\tChave de Round :");
	for(i=0;i<48;i++){
		vetor2[i]=matriz[i];
	}

	for(i=0;i<48;i++){
		printf("%d",matriz[i]);
	}
	return vetor2;
}

int * shiftTwo(int vetor[]){
	//int vetor[28]={0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,0,0,1,0,1,1,0} ;//= malloc(sizeof(int)*56);
	int *vetorAux=malloc(sizeof(int)*28);
	int i=0,aux=0;

		for(i=0;i<26;i++){
			vetorAux[i]=vetor[i+2];
		}

		vetorAux[26] = vetor[0];
		vetorAux[27] = vetor[1];


	printf("\n\tAntes Shift Two:");
	for(i = 0 ; i< 28 ; i++){
        printf("%d",vetor[i]);
    }

	printf("\n\tShift Two      :");
	for(i = 0 ; i< 28 ; i++){
        printf("%d",vetorAux[i]);
    }

    return vetorAux;

}

int * shiftOne(int vetor[]){

	//int vetor[28]={0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,0,0,1,0,1,1,0} ;//= malloc(sizeof(int)*56);
	int *vetorAux=malloc(sizeof(int)*28);
	int i=0,aux=0;

		for(i=0;i<27;i++){
			vetorAux[i]=vetor[i+1];
		}

		vetorAux[27] = vetor[0];


	printf("\n\tAntes Shift One:");
	for(i = 0 ; i< 28 ; i++){
        printf("%d",vetor[i]);
    }

	printf("\n\tShift One      :");
	for(i = 0 ; i< 28 ; i++){
        printf("%d",vetorAux[i]);
    }


    return vetorAux;
}


void generateSubKeys(chaveRound * chaveround){

		FILE *arqChave;
		int varArqInt=0;
		int varArq;
		//int chavePrincipal[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
		int chavePrincipal[64];
		int contChave=0;
		int chavesDeRounds[17];
		roundKey roundKey[17];
		int j,i,k;
		chaveFinalRound chaveFinalRound[17];


	      arqChave = fopen ("chaveBits.txt", "r");
	      if (arqChave == NULL) {
	          printf ("Houve um erro ao abrir o arquivo de entrada.\n");
                exit(1);
	      }else{
	          printf ("Arquivo de entrada reconhecido com sucesso.\n");
	      }

	       while((varArq = fgetc(arqChave)) != EOF){
	       		varArqInt = varArq-48;
	       		printf("%d",varArqInt );
	       		chavePrincipal[contChave] = varArqInt;
	       		contChave++;
	       }
	       fclose(arqChave);
	       printf("Chave principal:");
		for(j=0;j<64;j++){
			printf("%d",chavePrincipal[j]);

		}

		//printf("\nCHEGOU 1\n");
	//PARITY DROP -> ROUND 0
		//FAZ A PRIMEIRA PERMUTAÇÃO PARA CRIAR A CHAVE CIFRADA DE 56 BITS
		int *parityDropKey = parityDrop(chavePrincipal);
		j=0;


	    printf("\nVetor que chega do parityDrop: ");
	    for(i = 0 ; i< 56 ; i++){

	        printf("%d",parityDropKey[i]);
	    }
		//SEPARA A CHAVE CIFRADA EM DOIS LADOS
			for(i=0;i<28;i++){
				roundKey[0].left[i] = parityDropKey[i];
			}

			for(i=28;i<56;i++){
				roundKey[0].right[j] = parityDropKey[i];
				j++;
			}

		int *roundKeyLeft;
		int *roundKeyRight;
		int *roundKeyFinal;

		//Um shift é dado em cada lado
		for(j=1;j<17;j++){

			printf("\n==============Round %d=========================\n",j);

			if(j==1 || j==2 || j==9 || j==16){
				printf("\nLeft:  ");
				 roundKeyLeft= shiftOne(roundKey[j-1].left);
				 printf("\nRight : ");
				 roundKeyRight= shiftOne(roundKey[j-1].right);
			}else{
				printf("\nLeft:  ");
				 roundKeyLeft= shiftTwo(roundKey[j-1].left);
				 	 printf("\nRight : ");
				 roundKeyRight= shiftTwo(roundKey[j-1].right);
			}

			for( i=0;i<28;i++){
				roundKey[j].left[i] = roundKeyLeft[i];
			}
			for( i=0;i<28;i++){
				roundKey[j].right[i] = roundKeyRight[i];
			}

			printf("\n\nRound key %d left  : ",j);
			for( i=0;i<28;i++){
				printf("%d",roundKey[j].left[i]);
			}

			printf("\nRound key %d right : ",j);
			for( i=0;i<28;i++){
				printf("%d",roundKey[j].right[i]);
			}

			printf("\n");

			int caractere[4]={0,0,0,0};
			int cont=0;
			int resultado=0;
			roundKeyFinal = compressionBox(roundKey[j].left,roundKey[j].right);
      for( i =0 ; i<48;i++){
          chaveround[j].key[i] = roundKeyFinal[i];
      }

		}

		free(roundKeyLeft);
		free(roundKeyRight);
		//Os dois lados são colocados no compression Box e a chave é gerada
			//chavesDeRounds[1]= compressionBox(roundKey[1].left,roundKey[1].right);

	}
