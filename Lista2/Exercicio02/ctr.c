#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des/des.c"

void * convertMessageInBits(char *message ,int *aux1){
  int j=0;

    for(int i=0;i<16;i++){
      switch(message[i]){
             case '0':
                 //binary = 0000;
                 aux1[j] = 0;
                 aux1[j+1] = 0;
                 aux1[j+2] = 0;
                 aux1[j+3] = 0;
                 break;
             case '1':
                 //binary = 0001;
                 aux1[j] = 0;
                 aux1[j+1] = 0;
                 aux1[j+2] = 0;
                 aux1[j+3] = 1;
                 break;
             case '2':
                 //binary = 0010;
                 aux1[j] = 0;
                 aux1[j+1] = 0;
                 aux1[j+2] = 1;
                 aux1[j+3] = 0;
                 break;
             case '3':
                 //binary = 0011;
                 aux1[j] = 0;
                 aux1[j+1] = 0;
                 aux1[j+2] = 1;
                 aux1[j+3] = 1;
                 break;
             case '4':
                 //binary = 0100;
                 aux1[j] = 0;
                 aux1[j+1] = 1;
                 aux1[j+2] = 0;
                 aux1[j+3] = 0;
                 break;
             case '5':
                 //binary = 0101;
                 aux1[j] = 0;
                 aux1[j+1] = 1;
                 aux1[j+2] = 0;
                 aux1[j+3] = 1;
                 break;
             case '6':
                 //binary = 0110;
                 aux1[j] = 0;
                 aux1[j+1] = 1;
                 aux1[j+2] = 1;
                 aux1[j+3] = 0;
                 break;
             case '7':
                 //binary = 0111;
                 aux1[j] = 0;
                 aux1[j+1] = 1;
                 aux1[j+2] = 1;
                 aux1[j+3] = 1;
                 break;
             case '8':
                 //binary = 1000;
                 aux1[j] = 1;
                 aux1[j+1] = 0;
                 aux1[j+2] = 0;
                 aux1[j+3] = 0;
                 break;
             case '9':
                 //binary = 1001;
                 aux1[j] = 1;
                 aux1[j+1] = 0;
                 aux1[j+2] = 0;
                 aux1[j+3] = 1;
                 break;
             case 'a':
                 //binary = 1010;
                 aux1[j] = 1;
                 aux1[j+1] = 0;
                 aux1[j+2] = 1;
                 aux1[j+3] = 0;
                 break;
             case 'b':
                 //binary = 1011;
                 aux1[j] = 1;
                 aux1[j+1] = 0;
                 aux1[j+2] = 1;
                 aux1[j+3] = 1;
                 break;
             case 'c':
                 //binary = 1100;
                 aux1[j] = 1;
                 aux1[j+1] = 1;
                 aux1[j+2] = 0;
                 aux1[j+3] = 0;
                 break;
             case 'd':
                 //binary = 1101;
                 aux1[j] = 1;
                 aux1[j+1] = 1;
                 aux1[j+2] = 0;
                 aux1[j+3] = 1;
                 break;
             case 'e':
                 //binary = 1110;
                 aux1[j] = 1;
                 aux1[j+1] = 1;
                 aux1[j+2] = 1;
                 aux1[j+3] = 0;
                 break;
             case 'f':
                 //binary = 1111;
                 aux1[j] = 1;
                 aux1[j+1] = 1;
                 aux1[j+2] = 1;
                 aux1[j+3] = 1;
                 break;
         }
         j= j+4;
    }
}

void xorFunction(int *counterCriptedBits,int *messageBits,int *xorResult){
  for(int i=0;i<64;i++){
        xorResult[i] = counterCriptedBits[i]^messageBits[i];
    }
}

char convertBinToHex(int *vetor){
    char hexValue;
    int decimalValue=0 ;
    int vetorAux[4];
    int i;

    vetorAux[3] = vetor[3] * 1;
    vetorAux[2] = vetor[2] * 2;
    vetorAux[1] = vetor[1] * 4;
    vetorAux[0] = vetor[0] * 8;

    for(i = 0 ; i<4 ; i++){
        decimalValue += vetorAux[i];
    }

    switch(decimalValue){
        case 0:
            hexValue = '0';
            break;
        case 1:
            hexValue = '1';
            break;
        case 2:
            hexValue = '2';
            break;
        case 3:
            hexValue = '3';
            break;
        case 4:
            hexValue = '4';
            break;
        case 5:
            hexValue = '5';
            break;
        case 6:
            hexValue = '6';
            break;
        case 7:
            hexValue = '7';
            break;
        case 8:
            hexValue = '8';
            break;
        case 9:
            hexValue = '9';
            break;
        case 10:
            hexValue = 'a';
            break;
        case 11:
            hexValue = 'b';
            break;
        case 12:
            hexValue = 'c';
            break;
        case 13:
            hexValue = 'd';
            break;
        case 14:
            hexValue = 'e';
            break;
        case 15:
            hexValue = 'f';
            break;
        default:
            break;
    }

    return hexValue;
}

int main(){

    int opcao=0,messageSize=0;
    int counterCriptedBits[64],messageBits[64],xorResult[64];
    int messageCounter=0,roundCounter=0;
    char roundCounterMessage[64];
    char key[16];
    FILE *keyFile ;

    while(1){
        printf("\n\n==== MENU ====\n");

        printf("1 - Criptografa mensagem \n");
        printf("2 - Descriptografa mensagem \n");
        printf("3 - Sair \n");

        printf("Digite a opcao: ");
        scanf("%d",&opcao);
        switch(opcao){

            case 1:
                printf("Insira o tamanho(em bits) da mensagem hexadecimal a ser inserida(64/128/192/256/320/384/.../576): ");
                scanf("%d",&messageSize);

                char *message = malloc((messageSize/4)*sizeof(char));
                printf("Insira a mensagem : ");
                scanf("%s",message);

                printf("Insira a chave: ");
                scanf("%s",key);
                keyFile = fopen ("entradaChave.txt", "w");
                fprintf(keyFile,"%s",key);
                fclose(keyFile);

                printf("\nMensagem criptografada: " );
                for(roundCounter = 0; roundCounter < messageSize/64; roundCounter++ ){

                    snprintf (roundCounterMessage,64, "000000000000000%d",roundCounter+1);
                    FILE *counterToCrip = fopen ("entradaMensagem.txt", "w");
                    fprintf(counterToCrip,"%s",roundCounterMessage);
                    fclose(counterToCrip);

                    criptografa(counterCriptedBits);

                    char *messageAux = malloc(16*sizeof(char));
                    for(int i=0;i<16;i++){
                      messageAux[i] = message[messageCounter];
                      messageCounter++;
                    }

                    convertMessageInBits(messageAux,messageBits);

                    xorFunction(counterCriptedBits,messageBits,xorResult);

                    int vetorAuxMensagem[4];
                    int cont=0;
                    for(int i=0;i<64;i++){
                      vetorAuxMensagem[cont] = xorResult[i];
                      cont++;
                      if(cont%4==0){
                        printf("%c",convertBinToHex(vetorAuxMensagem));
                        cont =0;
                      }
                    }

                }
                messageCounter = 0;
                remove("entradaChave.txt");
                remove("entradaMensagem.txt");
                break;

            case 2:
                printf("Insira o tamanho(em bits) da mensagem hexadecimal a ser inserida(64/128/192/256/320/384/.../576): ");
                scanf("%d",&messageSize);

                char *messageCyper = malloc((messageSize/4)*sizeof(char));
                printf("Insira a mensagem a ser descriptografada : ");
                scanf("%s",messageCyper);

                printf("Insira a chave: ");
                scanf("%s",key);
                keyFile = fopen ("entradaChave.txt", "w");
                fprintf(keyFile,"%s",key);
                fclose(keyFile);

                printf("\nMensagem descriptografada: " );
                for(roundCounter = 0; roundCounter < messageSize/64; roundCounter++ ){

                    snprintf (roundCounterMessage,64, "000000000000000%d",roundCounter+1);

                    FILE *counterToCrip2 = fopen ("entradaMensagem.txt", "w");
                    fprintf(counterToCrip2,"%s",roundCounterMessage);
                    fclose(counterToCrip2);

                    criptografa(counterCriptedBits);

                    char *messageCypherAux = malloc(16*sizeof(char));
                    for(int i=0;i<16;i++){
                      messageCypherAux[i] = messageCyper[messageCounter];
                      messageCounter++;
                    }
                    convertMessageInBits(messageCypherAux,messageBits);

                    xorFunction(counterCriptedBits,messageBits,xorResult);

                    int vetorAuxMensagem2[4];
                    int cont2=0;
                    for(int i=0;i<64;i++){
                      vetorAuxMensagem2[cont2] = xorResult[i];
                      cont2++;
                      if(cont2%4==0){
                        printf("%c",convertBinToHex(vetorAuxMensagem2));
                        cont2 =0;
                      }
                    }

                }
                messageCounter = 0;
                remove("entradaChave.txt");
                remove("entradaMensagem.txt");
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
