#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int somaGF(int a, int b){
	int resultado = 0;

	resultado = a^b;

	printf("Resultado soma: %d\n",resultado );
	return resultado;

}

int subGF(int a, int b){
	int resultado = 0;

	resultado = a^b;

	printf("Resultado subtracao: %d\n",resultado );
	return resultado;

}

int multiGF(unsigned  a, unsigned  b) {
   unsigned aa = a, bb = b, r = 0, t;
   while (aa != 0) {
      if ((aa & 1) != 0){
         r = r ^ bb;
      }

      t = bb & 0x80;
      bb = bb << 1;
      if (t != 0){
         bb = bb ^ 0x1b;
      }

      aa = aa >> 1;
   }
   printf("Resultado : %d\n",r );
   return r;
}


int main(){
	int a,b;
	int opcao;

	printf("Insira o primeiro valor:");
		scanf("%d",&a);
	printf("Insira o segundo valor :");
		scanf("%d",&b);


	printf("==== MENU ====\n");
	printf("Opcoes: 1-Soma 2- Mult 3-Sub\n");

	printf("Insira a opcao: ");
		scanf("%d",&opcao);

	switch(opcao){
		case 1:
			somaGF(a,b);
			break;

		case 2:
			multiGF(a,b);
			break;
		case 3:
			subGF(a,b);
			break;

	}
	return 0;
}
