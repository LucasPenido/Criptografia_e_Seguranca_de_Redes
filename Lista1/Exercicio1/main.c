#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lembrar de incluir o outro arquivo
#include "keygenerator.c"


typedef struct{
    int esquerda[32];
    int direita[32];
}mensagem;


void geraArquivoChaveBits(){
      FILE *arqChave,*arqChaveBits;
      int bitShift=0,valor=0;
      int i=0,j,a=0 ,b=0,k= 0;
      int varArq=0;
      int cont=0;
      int vetor[4];

      remove("chaveBits.txt");
      arqChave = fopen ("entradaChave.txt", "r");
      arqChaveBits = fopen("chaveBits.txt", "w");

      if (arqChave == NULL) {
          printf ("Houve um erro ao abrir o arquivo de entrada.\n");
          exit(1);
      }else{
          printf ("Arquivo de entrada reconhecido com sucesso.\n");
      }

     while((varArq = fgetc(arqChave)) != EOF){

          if(varArq!='0'|| varArq!= '1'|| varArq!= '2'|| varArq!= '3'|| varArq!= '4'|| varArq!= '5'|| varArq!= '6'|| varArq!= '7'|| varArq!= '8'|| varArq!= '9'){
            if(varArq=='a'){
              printf("\nEntrou no A");
                varArq=10;
            }else if(varArq=='b'){
               varArq=11;
               printf("\nEntrou no B");
            }else if(varArq=='c'){
              varArq=12;
              printf("\nEntrou no C");
            }else if(varArq=='d'){
              varArq=13;
              printf("\nEntrou no D");
            }else if(varArq=='e'){
              varArq=14;
              printf("\nEntrou no E");
            }else if(varArq=='f'){
              varArq=15;
              printf("\nEntrou no F");
            }

          }else{

            varArq = varArq - 48;
          }

          for(i = 3 ; i>= 0 ; i--){
              bitShift = varArq >> i;
              if(bitShift & 1) {
                  vetor[k] = 1;
              } else {
                  vetor[k] = 0;
              }
              k++;
          }

          k=0;

          //PEGA O VALOR TRANSFORMADO E SALVA NO ARQUIVO DE SAIDA
          for(i=0;i<4;i++){
              fprintf(arqChaveBits,"%d",vetor[i]);
          }

     }
    fclose(arqChave);
    fclose(arqChaveBits);
}

int * initialPermutation(int vetor[]){
    int i;
    int *vetor2=malloc(sizeof(int)*64);

    printf("Vetor que chega no ini: \n");
    for(i = 0 ; i< 64 ; i++){
        printf("%d",vetor[i]);
    }


    int matriz[64]  = {
        vetor[57] , vetor[49] , vetor[41] , vetor[33] , vetor[25] , vetor[17] , vetor[9] , vetor[1],
        vetor[59] , vetor[51] , vetor[43] , vetor[35] , vetor[27] , vetor[19] , vetor[11] , vetor[3],
        vetor[61] , vetor[53] , vetor[45] , vetor[37] , vetor[29] , vetor[21] , vetor[13] , vetor[5],
        vetor[63] , vetor[55] , vetor[47] , vetor[39] , vetor[31] , vetor[23] , vetor[15] , vetor[7],
        vetor[56] , vetor[48] , vetor[40] , vetor[32] , vetor[24] , vetor[16] , vetor[8]  , vetor[0],
        vetor[58] , vetor[50] , vetor[42] , vetor[34] , vetor[26] , vetor[18] , vetor[10] , vetor[2],
        vetor[60] , vetor[52] , vetor[44] , vetor[36] , vetor[28] , vetor[20] , vetor[12] , vetor[4],
        vetor[62] , vetor[54] , vetor[46] , vetor[38] , vetor[30] , vetor[22] , vetor[14], vetor[6]

    };

    for(i = 0 ; i< 64 ; i++){
        vetor2[i] = matriz[i];
    }

    return vetor2;
}

void ExpansionPermutationE(int vetor[], int * vetor2){
    int i;
    int matriz[48] =
    {
        vetor[31], vetor[0],  vetor[1],  vetor[2],  vetor[3],  vetor[4],
        vetor[3],  vetor[4],  vetor[5],  vetor[6],  vetor[7],  vetor[8],
        vetor[7],  vetor[8],  vetor[9],  vetor[10], vetor[11], vetor[12],
        vetor[11], vetor[12], vetor[13], vetor[14], vetor[15], vetor[16],
        vetor[15], vetor[16], vetor[17], vetor[18], vetor[19], vetor[20],
        vetor[19], vetor[20], vetor[21], vetor[22], vetor[23], vetor[24],
        vetor[23], vetor[24], vetor[25], vetor[26], vetor[27], vetor[28],
        vetor[27], vetor[28], vetor[29], vetor[30], vetor[31], vetor[0]
    };
    for(i = 0 ; i< 48 ; i++){
        vetor2[i] = matriz[i];
    }
}

int * xorVetores(int vetor[],int vetor2[]){
    int *vetorXor = malloc(sizeof(int)*48);
    int i=0;

    for(i=0;i<48;i++){
        if(vetor[i]==0 && vetor2[i]==0){
            vetorXor[i] = 0;
        }else if(vetor[i]== 1 && vetor2[i]==0){
            vetorXor[i] = 1;
        }else if(vetor[i]==0 && vetor2[i]==1){
            vetorXor[i] = 1;
        }else{
            vetorXor[i] = 0;
        }

    }


    return vetorXor;
}

int convertTwoBinaryNumberInInteger(int num1 , int num2){

    if(num1 == 0 && num2 == 0){
        return 1;
    }else if(num1 == 0 && num2 == 1){
        return 2;
    }else if(num1 == 1 && num2 == 0){
        return 3;
    }else if(num1 == 1 && num2 == 1){
        return 4;
    }
}

int findDecimalNumber(int * vetor, int opcao){
    int decimalValue=0 ;
    int i;
    if(opcao == 1){
        vetor[3] = vetor[3] * 1;
        vetor[2] = vetor[2] * 10;
        vetor[1] = vetor[1] * 100;
        vetor[0] = vetor[0] * 1000;

        for(i = 0 ; i<4 ; i++){
            decimalValue += vetor[i];


        }
    }
    if(opcao == 2){
        vetor[4] = vetor[4] * 1;
        vetor[3] = vetor[3] * 10;
        vetor[2] = vetor[2] * 100;
        vetor[1] = vetor[1] * 1000;

        for(i = 1 ; i<5 ; i++){
            decimalValue += vetor[i];


        }

    }

    return decimalValue;
}

int convertBinaryNumberInInteger(int vetor[],int opcao){

    int decimalNumber;

    decimalNumber = findDecimalNumber(vetor,opcao);

    switch(decimalNumber){
        case 0:
            return 0;
        case 1:
            return 1;
        case 10:
            return 2;
        case 11:
            return 3;
        case 100:
            return 4;
        case 101:
            return 5;
        case 110:
            return 6;
        case 111:
            return 7;
        case 1000:
            return 8;
        case 1001:
            return 9;
        case 1010:
            return 10;
        case 1011:
            return 11;
        case 1100:
            return 12;
        case 1101:
            return 13;
        case 1110:
            return 14;
        case 1111:
            return 15;
    }
}

int * convertIntegerNumberInBinary(int num){
    int *vetor = malloc(sizeof(int)*4);
    int i;
    switch(num){
        case 0:
            vetor[0] = 0;
            vetor[1] = 0;
            vetor[2] = 0;
            vetor[3] = 0;
            break;
        case 1:
            vetor[0] = 0;
            vetor[1] = 0;
            vetor[2] = 0;
            vetor[3] = 1;
            break;
        case 2:
            vetor[0] = 0;
            vetor[1] = 0;
            vetor[2] = 1;
            vetor[3] = 0;
            break;
        case 3:
            vetor[0] = 0;
            vetor[1] = 0;
            vetor[2] = 1;
            vetor[3] = 1;
            break;
        case 4:
            vetor[0] = 0;
            vetor[1] = 1;
            vetor[2] = 0;
            vetor[3] = 0;
            break;
        case 5:
            vetor[0] = 0;
            vetor[1] = 1;
            vetor[2] = 0;
            vetor[3] = 1;
            break;
        case 6:
            vetor[0] = 0;
            vetor[1] = 1;
            vetor[2] = 1;
            vetor[3] = 0;
            break;
        case 7:
            vetor[0] = 0;
            vetor[1] = 1;
            vetor[2] = 1;
            vetor[3] = 1;
            break;
        case 8:
            vetor[0] = 1;
            vetor[1] = 0;
            vetor[2] = 0;
            vetor[3] = 0;
            break;
        case 9:
            vetor[0] = 1;
            vetor[1] = 0;
            vetor[2] = 0;
            vetor[3] = 1;
            break;
        case 10:
            vetor[0] = 1;
            vetor[1] = 0;
            vetor[2] = 1;
            vetor[3] = 0;
            break;
        case 11:
            vetor[0] = 1;
            vetor[1] = 0;
            vetor[2] = 1;
            vetor[3] = 1;
            break;
        case 12:
            vetor[0] = 1;
            vetor[1] = 1;
            vetor[2] = 0;
            vetor[3] = 0;
            break;
        case 13:
            vetor[0] = 1;
            vetor[1] = 1;
            vetor[2] = 0;
            vetor[3] = 1;
            break;
        case 14:
            vetor[0] = 1;
            vetor[1] = 1;
            vetor[2] = 1;
            vetor[3] = 0;
            break;
        case 15:
            vetor[0] = 1;
            vetor[1] = 1;
            vetor[2] = 1;
            vetor[3] = 1;
            break;
    }

    return vetor;
}

int S_box1(int row , int column){

    row = row - 1 ;

   int matriz[4][16] = { 14, 4 , 13, 1 , 2 , 15, 11, 8 , 3 , 10, 6 , 12 , 5 , 9 , 0 , 7,
                         0 , 15, 7 , 4 , 14, 2 , 13, 1 , 10, 6 , 12, 11 , 9 , 5 , 3 , 8,
                         4 , 1 ,14 , 8 , 13, 6 , 2 , 11, 15, 12, 9 ,  7 , 3 , 10, 5 , 0,
                        15 , 12, 8 , 2 , 4 , 9 ,1  , 7 ,  5, 11, 3 , 14 , 10,  0, 6 , 13
                    };
    return matriz[row][column];
}

int S_box2(int row , int column){

    row = row - 1 ;

   int matriz[4][16] = {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
                    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
                    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
                    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

    return matriz[row][column];
}

int S_box3(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
                        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
                        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
                        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

    return matriz[row][column];
}

int S_box4(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = {7, 13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
                        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
                        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
                        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
                        };
    return matriz[row][column];
}

int S_box5(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
                        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
                        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
                        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
                        };

    return matriz[row][column];
}

int S_box6(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = {12 ,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
                        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
                        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
                        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

    return matriz[row][column];
}

int S_box7(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = { 4,11, 2,14,15, 0, 8,13, 3,12, 9,  7, 5, 10, 6, 1,
                     13, 0,11, 7, 4, 9, 1,10,14, 3, 5, 12, 2, 15, 8, 6,
                      1, 4,11,13,12, 3, 7,14,10,15, 6,  8, 0,  5, 9, 2,
                      6,11,13, 8, 1, 4,10, 7, 9, 5, 0, 15,14,  2, 3, 12
                        };

    return matriz[row][column];
}

int S_box8(int row , int column){

    row = row - 1 ;

    int matriz[4][16] = {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
                        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
                        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
                        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
    return matriz[row][column];
}

int * permutationFunctionP(int vetor[]){
    int i;
    int *vetor2=malloc(sizeof(int)*32);
   int    matriz[32] =
    {
        vetor[15] , vetor[6]  , vetor[19] , vetor[20] , vetor[28] , vetor[11] , vetor[27] , vetor[16],
        vetor[0]  , vetor[14] , vetor[22] , vetor[25] , vetor[4]  , vetor[17] , vetor[30] , vetor[9],
        vetor[1]  , vetor[7]  , vetor[23] , vetor[13] , vetor[31] , vetor[26] , vetor[2]  , vetor[8],
        vetor[18] , vetor[12] , vetor[29] , vetor[5]  , vetor[21] , vetor[10] , vetor[3]  , vetor[24]

    };

    for(i = 0 ; i< 32 ; i++){
        vetor2[i] = matriz[i];
    }

    return vetor2;
}

int * xorVetoresFinal(int vetor[],int vetor2[]){
    int *vetorXor = malloc(sizeof(int)*32);
    int i=0;

    printf("\nVetor 1(Permutacao): ");
    for(i = 0 ; i< 32 ; i++){
        printf("%d",vetor[i]);
    }
    printf("\nVetor 2(mensagem Esquerda: ");
    for(i = 0 ; i< 32 ; i++){
        printf("%d",vetor2[i]);
    }

    for(i=0;i<32;i++){
        if(vetor[i]==0 && vetor2[i]==0){
            vetorXor[i] = 0;
        }else if(vetor[i]== 1 && vetor2[i]==0){
            vetorXor[i] = 1;
        }else if(vetor[i]==0 && vetor2[i]==1){
            vetorXor[i] = 1;
        }else{
            vetorXor[i] = 0;
        }

    }

    printf("\nResultado xor Final: ");
    for(i = 0 ; i< 32 ; i++){
        printf("%d",vetorXor[i]);
    }

    return vetorXor;
}

void inverseInitialPermutation(int * vetor , int *vetor2){
    int i;
    int matriz[64] = {
        vetor[39] , vetor[7] , vetor[47] , vetor[15] , vetor[55] , vetor[23] , vetor[63] , vetor[31],
        vetor[38] , vetor[6] , vetor[46] , vetor[14] , vetor[54] , vetor[22] , vetor[62] , vetor[30],
        vetor[37] , vetor[5] , vetor[45] , vetor[13] , vetor[53] , vetor[21] , vetor[61] , vetor[29],
        vetor[36] , vetor[4] , vetor[44] , vetor[12] , vetor[52] , vetor[20] , vetor[60] , vetor[28],
        vetor[35] , vetor[3] , vetor[43] , vetor[11] , vetor[51] , vetor[19] , vetor[59] , vetor[27],
        vetor[34] , vetor[2] , vetor[42] , vetor[10] , vetor[50] , vetor[18] , vetor[58] , vetor[26],
        vetor[33] , vetor[1] , vetor[41] , vetor[9]  , vetor[49] , vetor[17] , vetor[57] , vetor[25],
        vetor[32] , vetor[0] , vetor[40] , vetor[8]  , vetor[48] , vetor[16] , vetor[56] , vetor[24],
    };

    for(i = 0 ; i< 64 ; i++){
        vetor2[i] = matriz[i];
    }

    printf("Inverse Initial permutation : ");
    for(i = 0 ; i< 64 ; i++){
        printf("%d",vetor2[i]);
    }
    printf("\n");    
}

void convertBinaryNumberInHexa(int *vetor, char * saida){

    int decimalNumber;
    int vetorAux[4];
    int i , j,c=0;
    for(i = 0 ; i<64 ; i+=4)
    {

        for(j = 0; j<4; j++)
        {
            vetorAux[j] = vetor[i+j];
        }
        decimalNumber = findDecimalNumber(vetorAux,1);

        switch(decimalNumber)
        {
        case 0:
            saida[c] = '0';
            break;
        case 1:
            saida[c] = '1';
            break;
        case 10:
            saida[c] = '2';
            break;
        case 11:
            saida[c] = '3';
            break;
        case 100:
            saida[c] = '4';
            break;
        case 101:
            saida[c] = '5';
            break;
        case 110:
            saida[c] = '6';
            break;
        case 111:
            saida[c] = '7';
            break;
        case 1000:
            saida[c] = '8';
            break;
        case 1001:
            saida[c] = '9';
            break;
        case 1010:
            saida[c] = 'a';
            break;
        case 1011:
            saida[c] = 'b';
            break;
        case 1100:
            saida[c] = 'c';
            break;
        case 1101:
            saida[c] = 'd';
            break;
        case 1110:
            saida[c] = 'e';
            break;
        case 1111:
            saida[c] = 'f';
            break;
        }
        c++;


    }
}

void passaCaractereParaBitCriptografa(int valor ){
    int i=0,k=0;
    int bitShift=0;
    int vetor[4];
    int cont=0;

    FILE *arqSaida;
    arqSaida = fopen ("entradaMensagemBits.txt", "a+");

    if (arqSaida == NULL)
    {
        printf ("Houve um erro ao abrir o arquivo de saida.\n");
        exit(1);
    }
    else
    {
        printf ("Arquivo de saida criado com sucesso.\n");
    }


    for(i = 3 ; i>= 0 ; i--)
    {

        bitShift = valor >> i;
        if(bitShift & 1)
        {
            vetor[k] = 1;
        }
        else
        {
            vetor[k] = 0;
        }

        k++;
    }

    printf("Valor: %d -> \n",valor );
    for(i=0; i<4; i++)
    {
        printf("%d",vetor[i]);
    }
    printf("\n");

    for(i=0; i<4; i++)
    {
        fprintf(arqSaida,"%d",vetor[i]);
    }

    fclose (arqSaida);

}

void transformaMensagemEmBitCriptografa() {

      FILE *arqEntrada;
      int bitShift=0,valor=0;
      int i,j,a=0 ,b=0,k= 0;
      int matriz[2][2];
      int varArq=0;
      int *varArqBit;
      int cont=0;

      arqEntrada = fopen ("entradaMensagem.txt", "r");
      remove("entradaMensagemBits.txt");

      if (arqEntrada == NULL) {
          printf ("Houve um erro ao abrir o arquivo de entrada.\n");
          exit(1);
      }else{
          printf ("Arquivo de entrada reconhecido com sucesso.\n");
      }
     while((varArq = fgetc(arqEntrada)) != EOF){

          if(varArq!='0'|| varArq!= '1'|| varArq!= '2'|| varArq!= '3'|| varArq!= '4'|| varArq!= '5'|| varArq!= '6'|| varArq!= '7'|| varArq!= '8'|| varArq!= '9'){
            if(varArq=='a'){
               varArq=10;
            }else if(varArq=='b'){
               varArq=11;
            }else if(varArq=='c'){
              varArq=12;
            }else if(varArq=='d'){
              varArq=13;
            }else if(varArq=='e'){
              varArq=14;
            }else if(varArq=='f'){
              varArq=15;
            }
          }else{
            varArq = varArq - 48;
          }

          passaCaractereParaBitCriptografa(varArq);
     }
    fclose (arqEntrada);
}

void passaCaractereParaBitDescriptografa(int valor ){
    int i=0,k=0;
    int bitShift=0;
    int vetor[4];
    int cont=0;

    FILE *arqSaida;
    arqSaida = fopen ("entradaCifradaBits.txt", "a+");

    if (arqSaida == NULL)
    {
        printf ("Houve um erro ao abrir o arquivo de saida.\n");
        exit(1);
    }
    else
    {
        printf ("Arquivo de saida criado com sucesso.\n");
    }


    for(i = 3 ; i>= 0 ; i--)
    {

        bitShift = valor >> i;
        if(bitShift & 1)
        {
            vetor[k] = 1;
        }
        else
        {
            vetor[k] = 0;
        }

        k++;
    }

    printf("Valor: %d -> \n",valor );
    for(i=0; i<4; i++)
    {
        printf("%d",vetor[i]);
    }
    printf("\n");

    for(i=0; i<4; i++)
    {
        fprintf(arqSaida,"%d",vetor[i]);
    }

    fclose (arqSaida);

}

void transformaMensagemEmBitDescriptografa() {

      FILE *arqEntrada;
      int bitShift=0,valor=0;
      int i,j,a=0 ,b=0,k= 0;
      int matriz[2][2];
      int varArq=0;
      int *varArqBit;
      int cont=0;

      arqEntrada = fopen ("saidaCifrada.txt", "r");
      remove("entradaCifradaBits.txt");

      if (arqEntrada == NULL) {
          printf ("Houve um erro ao abrir o arquivo de entrada.\n");
          exit(1);
      }else{
          printf ("Arquivo de entrada reconhecido com sucesso.\n");
      }
     while((varArq = fgetc(arqEntrada)) != EOF){

          if(varArq!='0'|| varArq!= '1'|| varArq!= '2'|| varArq!= '3'|| varArq!= '4'|| varArq!= '5'|| varArq!= '6'|| varArq!= '7'|| varArq!= '8'|| varArq!= '9'){
            if(varArq=='a'){
               varArq=10;
            }else if(varArq=='b'){
               varArq=11;
            }else if(varArq=='c'){
              varArq=12;
            }else if(varArq=='d'){
              varArq=13;
            }else if(varArq=='e'){
              varArq=14;
            }else if(varArq=='f'){
              varArq=15;
            }
          }else{
            varArq = varArq - 48;
          }

          passaCaractereParaBitDescriptografa(varArq);
     }
    fclose (arqEntrada);
}

int criptografa(){
    int contadorRound=0;
    int i=0,o,k,j;
    FILE *arqMensagemBits;
    int mensagemBitsArquivo[64];
    int varArq,varArqInt;
    int contBitsLidos=0;
    chaveRound chaveround[17];
    mensagem mensagem[17];

    remove("saidaCifrada.txt");
    remove("entradaMensagemBits.txt");


    //pegar os arquivos com a mensagem do usuário e a transforma em bits
        transformaMensagemEmBitCriptografa();
    //pega  o arquivo com a chave e a transforma em bits
        geraArquivoChaveBits();
    //gera sub keys
        generateSubKeys(chaveround);


    for( o=1;o<17;o++){
            printf("\n\tChave de Round %d :",o);
            for( k=0;k<48;k++){
                //printf("%d",roundKeyFinal[j]);
            printf("%d",chaveround[o].key[k]);
            }

    }
    //PEGA A O BLOCO DA MENSAGEM EM EM BITS E COLOCA EM UM ARQUIVO
        arqMensagemBits = fopen ("entradaMensagemBits.txt", "r");

        if (arqMensagemBits == NULL) {
            printf ("Houve um erro ao abrir o arquivo de entrada.\n");
            return 1;
        }else{
            printf ("Arquivo de entrada reconhecido com sucesso.\n");
        }

        while((varArq = fgetc(arqMensagemBits)) != EOF){
            varArqInt = varArq-48;
            mensagemBitsArquivo[contBitsLidos] = varArqInt;
            contBitsLidos++;

            if(contBitsLidos==64){

                   printf("\nMensagem lida em bits:\n");
                   for(i=0;i<64;i++){
                    printf("%d",mensagemBitsArquivo[i]);
                   }

                //INITIAL PERMUTATION
                int * bitsMensagem ;
                bitsMensagem = initialPermutation(mensagemBitsArquivo);

                printf("\n=====================initialPermutation:================================\n");
                for(i=0;i<64;i++){
                    printf("%d",bitsMensagem[i]);
                }
                printf("\n");


                j=0;

                for(i=0;i<32;i++){
                    mensagem[0].esquerda[i] = bitsMensagem[i];
                }
                for(i=32;i<64;i++){
                    mensagem[0].direita[j] = bitsMensagem[i];
                    j++;
                }


                printf("\nMensagem Esquerda 0:\n");
                for(i=0;i<32;i++){
                    printf("%d",mensagem[0].esquerda[i]);
                }
                printf("\nMensagem direita: 0\n");
                for(i=0;i<32;i++){
                    printf("%d",mensagem[0].direita[i]);
                }
                printf("\n");

                //ROUNDS 

                int  expasionPermutation[48];
                int * xorResult;
                int resultadoSBox=0;
                int valorDecLinha=0;
                int valorDecColuna=0;
                int vetorSBoxLinha[4];
                int vetorSBoxColuna[4];


                for(i=1;i<17;i++){
                
                    printf("======================== ROUND %d ==============================",i);
                        printf("\nMensagem Esquerda %d : ",i-1);
                        for(j=0;j<32;j++){
                            printf("%d",mensagem[i-1].esquerda[j]);
                        }
                        printf("\n");

                        printf("\nMensagem Direita %d : ",i-1);
                        for(j=0;j<32;j++){
                            printf("%d",mensagem[i-1].direita[j]);
                        }
                        printf("\n");

                        ExpansionPermutationE(mensagem[i-1].direita, expasionPermutation);

                        printf("\nExpasion permutation : ");
                        for(j=0;j<48;j++){
                            printf("%d",expasionPermutation[j]);
                        }
                        printf("\n");


                        //faz xor com as minhas chaves(sai 48)
                        
                        xorResult = xorVetores(expasionPermutation,chaveround[i].key);
                        printf("\nResultado Xor (ExpansionPermutation,chave): ");
                        for(j=0;j<48;j++){
                                printf("%d",xorResult[j]);
                        }
                        printf("\n");

                        //vao entrar nas s box, em cada uma 6 bits
                            //===== S BOX 1 =====
                                vetorSBoxColuna[0] = xorResult[1] ; vetorSBoxColuna[1] = xorResult[2] ; vetorSBoxColuna[2] = xorResult[3] ; vetorSBoxColuna[3] = xorResult[4] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[0],xorResult[5]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  =   S_box1(valorDecLinha,valorDecColuna);
                                int * vetSBox1 =   convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 2 =====
                                vetorSBoxColuna[0] = xorResult[7] ; vetorSBoxColuna[1] = xorResult[8] ; vetorSBoxColuna[2] = xorResult[9] ; vetorSBoxColuna[3] = xorResult[10] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[6],xorResult[11]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box2(valorDecLinha,valorDecColuna);
                                int * vetSBox2 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 3 =====
                                vetorSBoxColuna[0] = xorResult[13] ; vetorSBoxColuna[1] = xorResult[14] ; vetorSBoxColuna[2] = xorResult[15] ; vetorSBoxColuna[3] = xorResult[16] ;

                                valorDecLinha  =  convertTwoBinaryNumberInInteger(xorResult[12],xorResult[17]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box3(valorDecLinha,valorDecColuna);
                                int * vetSBox3 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 4 =====
                                vetorSBoxColuna[0] = xorResult[19] ; vetorSBoxColuna[1] = xorResult[20] ; vetorSBoxColuna[2] = xorResult[21] ; vetorSBoxColuna[3] = xorResult[22] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[18],xorResult[23]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box4(valorDecLinha,valorDecColuna);
                                int * vetSBox4 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 5 =====
                                vetorSBoxColuna[0] = xorResult[25] ; vetorSBoxColuna[1] = xorResult[26] ; vetorSBoxColuna[2] = xorResult[27] ; vetorSBoxColuna[3] = xorResult[28] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[24],xorResult[29]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box5(valorDecLinha,valorDecColuna);
                                int * vetSBox5 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 6 =====
                                vetorSBoxColuna[0] = xorResult[31] ; vetorSBoxColuna[1] = xorResult[32] ; vetorSBoxColuna[2] = xorResult[33] ; vetorSBoxColuna[3] = xorResult[34] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[30],xorResult[35]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box6(valorDecLinha,valorDecColuna);
                                int * vetSBox6 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 7 =====
                                vetorSBoxColuna[0] = xorResult[37] ; vetorSBoxColuna[1] = xorResult[38] ; vetorSBoxColuna[2] = xorResult[39] ; vetorSBoxColuna[3] = xorResult[40] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[36],xorResult[41]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box7(valorDecLinha,valorDecColuna);
                                int * vetSBox7 = convertIntegerNumberInBinary(resultadoSBox);

                            //===== S BOX 8 =====
                                vetorSBoxColuna[0] = xorResult[43] ; vetorSBoxColuna[1] = xorResult[44] ; vetorSBoxColuna[2] = xorResult[45] ; vetorSBoxColuna[3] = xorResult[46] ;

                                valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[42],xorResult[47]);
                                valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                resultadoSBox  = S_box8(valorDecLinha,valorDecColuna);
                                int * vetSBox8 = convertIntegerNumberInBinary(resultadoSBox);

                            //=====RESULTADO ====
                            printf("\nResultado Depois SBOX: ");
                            printf("%d%d%d%d ",vetSBox1[0],vetSBox1[1],vetSBox1[2],vetSBox1[3]);
                            printf("%d%d%d%d ",vetSBox2[0],vetSBox2[1],vetSBox2[2],vetSBox2[3]);
                            printf("%d%d%d%d ",vetSBox3[0],vetSBox3[1],vetSBox3[2],vetSBox3[3]);
                            printf("%d%d%d%d ",vetSBox4[0],vetSBox4[1],vetSBox4[2],vetSBox4[3]);
                            printf("%d%d%d%d ",vetSBox5[0],vetSBox5[1],vetSBox5[2],vetSBox5[3]);
                            printf("%d%d%d%d ",vetSBox6[0],vetSBox6[1],vetSBox6[2],vetSBox6[3]);
                            printf("%d%d%d%d ",vetSBox7[0],vetSBox7[1],vetSBox7[2],vetSBox7[3]);
                            printf("%d%d%d%d ",vetSBox8[0],vetSBox8[1],vetSBox8[2],vetSBox8[3]);

                            printf("\n");

                            //resultado 32 bits
                            int resultadoSBoxes[32] ={vetSBox1[0],vetSBox1[1],vetSBox1[2],vetSBox1[3],
                                                    vetSBox2[0],vetSBox2[1],vetSBox2[2],vetSBox2[3],
                                                    vetSBox3[0],vetSBox3[1],vetSBox3[2],vetSBox3[3],
                                                    vetSBox4[0],vetSBox4[1],vetSBox4[2],vetSBox4[3],
                                                    vetSBox5[0],vetSBox5[1],vetSBox5[2],vetSBox5[3],
                                                    vetSBox6[0],vetSBox6[1],vetSBox6[2],vetSBox6[3],
                                                    vetSBox7[0],vetSBox7[1],vetSBox7[2],vetSBox7[3],
                                                    vetSBox8[0],vetSBox8[1],vetSBox8[2],vetSBox8[3]
                                                    };

                        //entra na permutation
                        int *resultadoPermutacao = permutationFunctionP(resultadoSBoxes);

                        //resultado disso faz xor com lado esquerdo

                        printf("\nResultado permutacao: ");
                        for(j=0;j<32;j++){
                            printf("%d",resultadoPermutacao[j] );
                        }

                        printf("\nMensagem esquerda: ");
                        for(j=0;j<32;j++){
                            printf("%d",mensagem[i-1].esquerda[j]);
                        }
                        printf("\n");

                        int *xorFinal = xorVetoresFinal( resultadoPermutacao, mensagem[i-1].esquerda);

                        printf("\nXor Final: ");
                        for(j=0;j<32;j++){
                            printf("%d",xorFinal[j] );
                        }
                        printf("\n");

                        //lado direito(resultaod dessa operação) vira o esquerdo
                        for(j = 0 ; j<32; j++){
                            mensagem[i].esquerda[j] = mensagem[i-1].direita[j];
                        }   
                        for(j = 0 ; j<32; j++){
                            mensagem[i].direita[j] = xorFinal[j];
                        }

                        printf("\nResultado Final Round %d: \n",i);
                        printf("\tEsquerdo: ");
                        for(j = 0 ; j<32; j++){
                            printf("%d",mensagem[i].esquerda[j]);
                        }
                        printf("\n\tDireito: ");
                        for(j = 0 ; j<32; j++){
                            printf("%d",mensagem[i].direita[j]);
                        }
                        printf("\n================================================================\n");

                }
                        int vetorAux[64];
                        int vetorAux2[64];
                        
                        for(j=0;j<32;j++){
                            vetorAux[j] = mensagem[16].direita[j];
                        }
                        for(i=0,j=32;i<32,j<64;j++,i++){
                            vetorAux[j] = mensagem[16].esquerda[i];
                        }
                        
                        inverseInitialPermutation(vetorAux,vetorAux2);

                        printf("\n=========respostaFinal==============\n");
                        for(i=0;i<64;i++){
                            printf("%d",vetorAux2[i]);
                        }
                        printf("\n");
                        
                        FILE *saidaCifrada;

                        saidaCifrada = fopen ("saidaCifrada.txt", "a");

                        if (saidaCifrada == NULL) {
                            printf ("Houve um erro ao abrir o arquivo de entrada.\n");
                            return 1;
                        }else{
                            printf ("Arquivo de entrada reconhecido com sucesso.\n");
                        }

                        char saida[16];

                        convertBinaryNumberInHexa(vetorAux2,saida);

                        for(i=0;i<16;i++){
                            fprintf(saidaCifrada,"%c",saida[i]);
                        }

                        fclose(saidaCifrada);
                        contBitsLidos=0;
            }
        }
    fclose(arqMensagemBits);
    remove("entradaMensagemBits.txt");
    remove("chaveBits.txt");

    return 0;
}

int descriptografa(){
    int contadorRound=0;
    int i=0,o,k,j;
    FILE *arqMensagemBits;
    int mensagemBitsArquivo[64];
    int varArq,varArqInt;
    chaveRound chaveround[17];
    mensagem mensagem[17];
    int contBitsLidos=0;

    remove("textoDecifrado.txt");
    remove("entradaCifradaBits.txt");

    //pegar os arquivos com a mensagem do usuário e a transforma em bits
        transformaMensagemEmBitDescriptografa();
    //pega  o arquivo com a chave e a transforma em bits
        geraArquivoChaveBits();
    //gera sub keys
        generateSubKeys(chaveround);
    printf("\n=================HUEHEUHUEUEH=======================");

    for( o=1;o<17;o++){
            printf("\n\tChave de Round %d :",o);
            for( k=0;k<48;k++){
                //printf("%d",roundKeyFinal[j]);
            printf("%d",chaveround[o].key[k]);
            }

    }
    //PEGA A O BLOCO DA MENSAGEM EM EM BITS E COLOCA EM UM ARQUIVO
        arqMensagemBits = fopen ("entradaCifradaBits.txt", "r");

        if (arqMensagemBits == NULL) {
            printf ("Houve um erro ao abrir o arquivo de entrada.\n");
            return 1;
        }else{
            printf ("Arquivo de entrada reconhecido com sucesso.\n");
        }

       while((varArq = fgetc(arqMensagemBits)) != EOF){
            varArqInt = varArq-48;
            mensagemBitsArquivo[contBitsLidos] = varArqInt;
            contBitsLidos++;

                if(contBitsLidos==64){
                       printf("\nMensagem lida em bits:\n");
                       for(i=0;i<64;i++){
                        printf("%d",mensagemBitsArquivo[i]);
                       }

                    //INITIAL PERMUTATION
                    int * bitsMensagem ;
                    bitsMensagem = initialPermutation(mensagemBitsArquivo);

                    printf("\n=====================initialPermutation:================================\n");
                    for(i=0;i<64;i++){
                        printf("%d",bitsMensagem[i]);
                    }
                    printf("\n");


                    j=0;

                    for(i=0;i<32;i++){
                        mensagem[0].esquerda[i] = bitsMensagem[i];
                    }
                    for(i=32;i<64;i++){
                        mensagem[0].direita[j] = bitsMensagem[i];
                        j++;
                    }


                    printf("\nMensagem Esquerda 0:\n");
                    for(i=0;i<32;i++){
                        printf("%d",mensagem[0].esquerda[i]);
                    }
                    printf("\nMensagem direita: 0\n");
                    for(i=0;i<32;i++){
                        printf("%d",mensagem[0].direita[i]);
                    }
                    printf("\n");

                    //ROUNDS 

                    int  expasionPermutation[48];
                    int * xorResult;
                    int resultadoSBox=0;
                    int valorDecLinha=0;
                    int valorDecColuna=0;
                    int vetorSBoxLinha[4];
                    int vetorSBoxColuna[4];
                    int contChave=16;

                    for(i=1;i<17;i++){
                    
                        printf("======================== ROUND %d ==============================",i);
                            printf("\nMensagem Esquerda %d : ",i-1);
                            for(j=0;j<32;j++){
                                printf("%d",mensagem[i-1].esquerda[j]);
                            }
                            printf("\n");

                            printf("\nMensagem Direita %d : ",i-1);
                            for(j=0;j<32;j++){
                                printf("%d",mensagem[i-1].direita[j]);
                            }
                            printf("\n");

                            ExpansionPermutationE(mensagem[i-1].direita, expasionPermutation);

                            printf("\nExpasion permutation : ");
                            for(j=0;j<48;j++){
                                printf("%d",expasionPermutation[j]);
                            }
                            printf("\n");


                            //faz xor com as minhas chaves(sai 48)
                            
                            xorResult = xorVetores(expasionPermutation,chaveround[contChave].key);
                            printf("\nResultado Xor (ExpansionPermutation,chave): ");
                            for(j=0;j<48;j++){
                                    printf("%d",xorResult[j]);
                            }
                            printf("\n");

                            //vao entrar nas s box, em cada uma 6 bits
                                //===== S BOX 1 =====
                                    vetorSBoxColuna[0] = xorResult[1] ; vetorSBoxColuna[1] = xorResult[2] ; vetorSBoxColuna[2] = xorResult[3] ; vetorSBoxColuna[3] = xorResult[4] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[0],xorResult[5]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  =   S_box1(valorDecLinha,valorDecColuna);
                                    int * vetSBox1 =   convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 2 =====
                                    vetorSBoxColuna[0] = xorResult[7] ; vetorSBoxColuna[1] = xorResult[8] ; vetorSBoxColuna[2] = xorResult[9] ; vetorSBoxColuna[3] = xorResult[10] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[6],xorResult[11]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box2(valorDecLinha,valorDecColuna);
                                    int * vetSBox2 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 3 =====
                                    vetorSBoxColuna[0] = xorResult[13] ; vetorSBoxColuna[1] = xorResult[14] ; vetorSBoxColuna[2] = xorResult[15] ; vetorSBoxColuna[3] = xorResult[16] ;

                                    valorDecLinha  =  convertTwoBinaryNumberInInteger(xorResult[12],xorResult[17]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box3(valorDecLinha,valorDecColuna);
                                    int * vetSBox3 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 4 =====
                                    vetorSBoxColuna[0] = xorResult[19] ; vetorSBoxColuna[1] = xorResult[20] ; vetorSBoxColuna[2] = xorResult[21] ; vetorSBoxColuna[3] = xorResult[22] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[18],xorResult[23]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box4(valorDecLinha,valorDecColuna);
                                    int * vetSBox4 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 5 =====
                                    vetorSBoxColuna[0] = xorResult[25] ; vetorSBoxColuna[1] = xorResult[26] ; vetorSBoxColuna[2] = xorResult[27] ; vetorSBoxColuna[3] = xorResult[28] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[24],xorResult[29]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box5(valorDecLinha,valorDecColuna);
                                    int * vetSBox5 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 6 =====
                                    vetorSBoxColuna[0] = xorResult[31] ; vetorSBoxColuna[1] = xorResult[32] ; vetorSBoxColuna[2] = xorResult[33] ; vetorSBoxColuna[3] = xorResult[34] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[30],xorResult[35]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box6(valorDecLinha,valorDecColuna);
                                    int * vetSBox6 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 7 =====
                                    vetorSBoxColuna[0] = xorResult[37] ; vetorSBoxColuna[1] = xorResult[38] ; vetorSBoxColuna[2] = xorResult[39] ; vetorSBoxColuna[3] = xorResult[40] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[36],xorResult[41]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box7(valorDecLinha,valorDecColuna);
                                    int * vetSBox7 = convertIntegerNumberInBinary(resultadoSBox);

                                //===== S BOX 8 =====
                                    vetorSBoxColuna[0] = xorResult[43] ; vetorSBoxColuna[1] = xorResult[44] ; vetorSBoxColuna[2] = xorResult[45] ; vetorSBoxColuna[3] = xorResult[46] ;

                                    valorDecLinha  =   convertTwoBinaryNumberInInteger(xorResult[42],xorResult[47]);
                                    valorDecColuna =   convertBinaryNumberInInteger(vetorSBoxColuna,1);
                                    resultadoSBox  = S_box8(valorDecLinha,valorDecColuna);
                                    int * vetSBox8 = convertIntegerNumberInBinary(resultadoSBox);

                                //=====RESULTADO ====
                                printf("\nResultado Depois SBOX: ");
                                printf("%d%d%d%d ",vetSBox1[0],vetSBox1[1],vetSBox1[2],vetSBox1[3]);
                                printf("%d%d%d%d ",vetSBox2[0],vetSBox2[1],vetSBox2[2],vetSBox2[3]);
                                printf("%d%d%d%d ",vetSBox3[0],vetSBox3[1],vetSBox3[2],vetSBox3[3]);
                                printf("%d%d%d%d ",vetSBox4[0],vetSBox4[1],vetSBox4[2],vetSBox4[3]);
                                printf("%d%d%d%d ",vetSBox5[0],vetSBox5[1],vetSBox5[2],vetSBox5[3]);
                                printf("%d%d%d%d ",vetSBox6[0],vetSBox6[1],vetSBox6[2],vetSBox6[3]);
                                printf("%d%d%d%d ",vetSBox7[0],vetSBox7[1],vetSBox7[2],vetSBox7[3]);
                                printf("%d%d%d%d ",vetSBox8[0],vetSBox8[1],vetSBox8[2],vetSBox8[3]);

                                printf("\n");

                                //resultado 32 bits
                                int resultadoSBoxes[32] ={vetSBox1[0],vetSBox1[1],vetSBox1[2],vetSBox1[3],
                                                        vetSBox2[0],vetSBox2[1],vetSBox2[2],vetSBox2[3],
                                                        vetSBox3[0],vetSBox3[1],vetSBox3[2],vetSBox3[3],
                                                        vetSBox4[0],vetSBox4[1],vetSBox4[2],vetSBox4[3],
                                                        vetSBox5[0],vetSBox5[1],vetSBox5[2],vetSBox5[3],
                                                        vetSBox6[0],vetSBox6[1],vetSBox6[2],vetSBox6[3],
                                                        vetSBox7[0],vetSBox7[1],vetSBox7[2],vetSBox7[3],
                                                        vetSBox8[0],vetSBox8[1],vetSBox8[2],vetSBox8[3]
                                                        };

                            //entra na permutation
                            int *resultadoPermutacao = permutationFunctionP(resultadoSBoxes);

                            //resultado disso faz xor com lado esquerdo

                            printf("\nResultado permutacao: ");
                            for(j=0;j<32;j++){
                                printf("%d",resultadoPermutacao[j] );
                            }

                            printf("\nMensagem esquerda: ");
                            for(j=0;j<32;j++){
                                printf("%d",mensagem[i-1].esquerda[j]);
                            }
                            printf("\n");

                            int *xorFinal = xorVetoresFinal( resultadoPermutacao, mensagem[i-1].esquerda);

                            printf("\nXor Final: ");
                            for(j=0;j<32;j++){
                                printf("%d",xorFinal[j] );
                            }
                            printf("\n");

                            //lado direito(resultaod dessa operação) vira o esquerdo
                            for(j = 0 ; j<32; j++){
                                mensagem[i].esquerda[j] = mensagem[i-1].direita[j];
                            }   
                            for(j = 0 ; j<32; j++){
                                mensagem[i].direita[j] = xorFinal[j];
                            }

                            printf("\nResultado Final Round %d: \n",i);
                            printf("\tEsquerdo: ");
                            for(j = 0 ; j<32; j++){
                                printf("%d",mensagem[i].esquerda[j]);
                            }
                            printf("\n\tDireito: ");
                            for(j = 0 ; j<32; j++){
                                printf("%d",mensagem[i].direita[j]);
                            }
                            printf("\n================================================================\n");
                            contChave--;
                    }
                            int vetorAux[64];
                            int vetorAux2[64];
                            
                            for(j=0;j<32;j++){
                                vetorAux[j] = mensagem[16].direita[j];
                            }
                            for(i=0,j=32;i<32,j<64;j++,i++){
                                vetorAux[j] = mensagem[16].esquerda[i];
                            }
                            
                            inverseInitialPermutation(vetorAux,vetorAux2);

                            printf("\n=========respostaFinal==============\n");
                            for(i=0;i<64;i++){
                                printf("%d",vetorAux2[i]);
                            }
                            printf("\n");
                            
                            FILE *saidaDecifrada;

                            saidaDecifrada = fopen ("textoDecifrado.txt", "a");

                            if (saidaDecifrada == NULL) {
                                printf ("Houve um erro ao abrir o arquivo de entrada.\n");
                                return 1;
                            }else{
                                printf ("Arquivo de entrada reconhecido com sucesso.\n");
                            }

                            char saida[16];

                            convertBinaryNumberInHexa(vetorAux2,saida);

                            for(i=0;i<16;i++){
                                fprintf(saidaDecifrada,"%c",saida[i]);
                            }

                            fclose(saidaDecifrada);
                            contBitsLidos=0;
                }
            }
            fclose(arqMensagemBits);
            remove("entradaCifradaBits.txt");
              remove("chaveBits.txt");
    return 0;
}


int main(){

    int opcao=0;

    while(1){
        printf("==== MENU ====\n");

        printf("1 - Criptografa mensagem \n");
        printf("2 - Descriptografa mensagem \n");
        printf("3 - Sair \n");

        printf("Digite a opcao: ");
        scanf("%d",&opcao);
        switch(opcao){

            case 1:
                criptografa();
                break;

            case 2:
                descriptografa();
                break;

            case 3:
            return 0;
                break;

            default:
                printf("ERRO: INSIRA UMA OPCAO VALIDA !\n");
                break;
        }
    }
}
