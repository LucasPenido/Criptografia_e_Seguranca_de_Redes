#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//efetua a exponenciacao
long long int exep(int a, int b , int c){
int i;
long long int saida;
saida =a;
  for( i = 1 ; i<b; i++){
    saida*=a;
    saida = saida % c;
  }
  return saida;
}
// encontra o valor de k e q
int find_k_q(int *k , int *q ,int n ){
  int i ,j;
  int valueTest,condition;
  valueTest = (n - 1);
  for (i = 0 ; i < n ; i++){
    for( j = 1 ; j< n ; j+=2){
        condition = pow(2,i)*j;
        if(valueTest == condition){
          *k = i;
          *q = j;
          return 1;
      }
    }
  }
  return 0;
}
// gerador de numero pseudo aleatorio
int linearCongruentialGenerator(int m , int seed){
  int value;
  int randonNumber;
  value = 16807*seed+17;
  randonNumber = value % m;
  if(randonNumber == m){
    randonNumber = randonNumber - 1;
  //apenas evita que o numero seja 0
  }else if(randonNumber == 0){
    randonNumber = 17;
  }
  return randonNumber;
}

//teste de miller rabin
int test(int a ,int n){
  int value,*k,*q, valueK=0 , valueQ=0, i,t,x;
  long long int aux;
  k = &valueK;
  q = &valueQ;
  t = find_k_q(k,q,n);
  aux = exep(a,*q, n);
  x = aux % n;
  if(x == 1 || x == (n-1)){
    return 1;
  }
  for(i = 0 ; i <=*k-1; i++){
    aux = exep(x,2,n);
    x =  aux % n;
    if(x == 1){
      return -1;
    }
    if(x == (n-1)){
      return 1;
    }
  }
  return -1;
}

int main(){
  int aux , i,seed;
  double prime = 1,probility;
  int qtd, number;
  printf("Digite o valor para conferir se e primo: ");
  scanf("%d",&number);
  printf("Digite a quantidade de testes desejados: ");
  scanf("%d",&qtd);

  i = 0;
  while(i!=qtd){
    if( i == 0){
      seed = linearCongruentialGenerator(number,7);
      //printf("seed ==%d\n",seed );
    }else{
      seed = linearCongruentialGenerator(number,seed);
      //printf("seed ==%d\n",seed );
    }
    aux = test(seed,number);
    if(aux == 1){
      prime = prime * 0.25;
      //printf("%lf\n",prime );
    }else{
      prime = -1;
      break;
    }
    i++;
  }
  if(prime == -1){
    printf("Numero Composto!\n");
  }else{
    probility = 100 - prime;
    printf("Numero com probabilidade de ser primo = %lf%% \n",probility);
  }
  return 0;
}
