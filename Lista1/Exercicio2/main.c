#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int eu(int a,int b, int c)
{

    return (a-b*c);

}

int mdc(int num1, int num2 , int *ptrXmenosUm, int *ptrXzero)
{

    int quonciente ;
    if(num2==0)
    {

        if(*ptrXmenosUm<0)
        {
            *ptrXzero=*ptrXzero+*ptrXmenosUm;
        }
        return num1;

    }
    else
    {
        quonciente = num1/num2;
        quonciente = floor(quonciente);
        *ptrXmenosUm = eu(*ptrXmenosUm,quonciente,*ptrXzero);
        return mdc(num2,num1%num2,ptrXzero,ptrXmenosUm);
    }
}


int main()
{

    int num1 ,num2,xMenosUm,xZero;
    int *ptrXmenosUm ,*ptrXzero;
    int saida;
    xMenosUm = 1;
    xZero = 0;
    ptrXmenosUm = &xMenosUm;
    ptrXzero = &xZero;

    printf("Digite os valores desejados para encontrar o inverso multiplicativo\n");
    scanf("%d",&num1);
    scanf("%d",&num2);

    saida = mdc(num1,num2,ptrXmenosUm,ptrXzero);

    if(saida != 1)
    {
        printf("Não existe inverso multiplicativo");
    }
    else
    {
        printf("o inverso multiplicativo de %d modulos %d é = %d\n",num1,num2,*ptrXmenosUm);
    }
    return 0;
}

