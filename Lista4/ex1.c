#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int eu(int a,int b, int c){

    return (a-b*c);

}

//encontra o mdc e o multplicativo inverso
int mdc(int num1, int num2 , int *ptrXmenosUm, int *ptrXzero){

    int quonciente ;
    if(num2==0){
        if(*ptrXmenosUm<0){
            *ptrXzero=*ptrXzero+*ptrXmenosUm;
        }
        return num1;
    }
    else{
        quonciente = num1/num2;
        quonciente = floor(quonciente);
        *ptrXmenosUm = eu(*ptrXmenosUm,quonciente,*ptrXzero);
        return mdc(num2,num1%num2,ptrXzero,ptrXmenosUm);
    }
}


int exponenciacao(int a, int b, int c){
int result ;
int i;
result =a;
  for( i = 1 ; i < b ; i++){
    result*=a;
    result = result % c;
  }
  return result;
}


int nValue(int num1, int num2){
  return num1*num2;
}
int eulerTotientFunction(int num1 , int num2){
  int p , q;
  p = num1-1;
  q = num2 -1;
  return nValue(p,q);
}


int rsaEncript(int n, int e, int plainText){
  int cipher;
  int expo;
  expo = exponenciacao(plainText,e,n);
  cipher = expo%n;
  return cipher;
}


void encrypt( char * path,int n, int e){
  FILE * arq;
  FILE *arqEncrypt;
  char caractare;
  int plainText[15];
  int cipherText[15];
  int i=0,j,aux;
  arq = fopen(path, "r");

  if(arq == NULL){
    printf("Houve um erro ao abrir o arquivo solicitado!\n");
  }else{

  }
  i=0;

  while((caractare = fgetc(arq)) !=EOF){
    aux = caractare;
    plainText[i] = aux;
    i++;
  }
  
  for(j = 0 ; j< 15; j++){
    cipherText[j] = rsaEncript(n,e,plainText[j]);
  }
  arqEncrypt = fopen("cipherText.txt", "w");

  if(arqEncrypt == NULL){
    printf("Houve um erro ao abrir o arquivo solicitado!\n");
  }else{
    int c;
     for(j = 0 ; j < 15 ; j++){
      printf("%d\n",cipherText[j] );
      c = cipherText[j];
      fprintf(arqEncrypt, "%d ",c);

    }
  }
  fclose(arqEncrypt);


  arqEncrypt = fopen("cipherText.txt", "r");
  if(arqEncrypt == NULL){
    printf("Houve um erro ao abrir o arquivo solicitado!\n");
  }
  i=0;
  int num;
  printf("Seu texto criptografado e :\n");
  while((fscanf(arqEncrypt,"%d",&num)) !=EOF){
      printf("%c",num);
  }
  fclose(arqEncrypt);
  fclose(arq);
}

void decription(char* path, int n, int d){
    FILE * arq;
    FILE *arqEncrypt;
    char caractare;
    int plainText[15];
    int cipherText[15];
    int i=0,j,aux;
    arqEncrypt = fopen(path, "r");
    if(arqEncrypt == NULL){
      printf("Houve um erro ao abrir o arquivo solicitado\n");
    }else{
      int num;
      while((fscanf(arqEncrypt,"%d",&num)) !=EOF){
          cipherText[i] = num;
          i++;
      }
      for(j = 0 ; j< 15 ; j++){
          plainText[j] = rsaEncript(n,d,cipherText[j]);
      }
      arq = fopen("arquivo.txt", "w");

      if(arq == NULL){
        printf("ouve um erro ao abrir o arquivo\n");
      }else{
        int c;
         for(j = 0 ; j < 15 ; j++){
          c = plainText[j];
          fprintf(arq, "%c",c);
        }
      }
    }
    fclose(arqEncrypt);
    fclose(arq);
}

int main() {

  int q ,p,e;
  int n,d;
  int valueMdc;
  int *ptrXmenosUm ,*ptrXzero;
  int saida,xMenosUm,xZero ;
  int j;//Find mdc and multiplicative inverse

  xMenosUm = 1;
  xZero = 0;
  ptrXmenosUm = &xMenosUm;
  ptrXzero = &xZero;

  int saidaText[15];
  char  path[30];
  printf("Digite o valor de p:");
  scanf("%d",&p);
  printf("Digite o valor de q:");
  scanf("%d",&q);
  printf("Digite o valor de e:");
  scanf("%d",&e);

  valueMdc = mdc(e,eulerTotientFunction(p,q),ptrXmenosUm,ptrXzero);
  n = nValue(p,q);
  d = *ptrXmenosUm;

  if(valueMdc == 1 && n>e ){
    int op;
    printf(">>>>>>>>>>>>>>>Menu<<<<<<<<<<<<<<<<<\n");
    printf("Digite 1 para criptografar\n");
    printf("Digite 2 para descriptografar\n");
    scanf("%d",&op);
      if(op == 1){
        printf("Digite o local do arquivo: ");
        scanf("%s",path);
        encrypt(path,n,e);
      }else{
          printf("Digite o local do arquivo: ");
          scanf("%s",path);
          decription(path,n,d);
      }
  }else{
    printf("Chave invalida!!\n");
  }

  return 0;
}
