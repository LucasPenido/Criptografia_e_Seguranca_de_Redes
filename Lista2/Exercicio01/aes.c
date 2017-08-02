#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

typedef struct{
    char byte1;
    char byte2;
    int  bits1[4];
    int  bits2[4];
    int  bitsHexa[8];
    int  byteInt1;
    int  byteInt2;
}Infos;

typedef struct{
  int mult1[8];
  int mult2[8];
  int mult4[8];
  int mult8[8];
  int resultado[8];
  int resultadoFinal[8];
}ResultMult;

typedef struct{
    char *w[4];
}temp;

typedef struct{
    char *w[4];
}word;

typedef struct{
    int key[128];
}roundKey;

int convertHexForDecimal(char character){

  switch (character) {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'A':
      return 10;
    case 'B':
      return 11;
    case 'C':
      return 12;
    case 'D':
      return 13;
    case 'E':
      return 14;
    case 'F':
      return 15;
    case 'O':
      return 0;
  }
}

char * InverseS_box(int row , int column){
  char * InverseSbox[16][16] =   {
                 /* 0 *//* 1 *//* 2 *//* 3 *//* 4 *//* 5 *//* 6 *//* 7 *//* 8 *//* 9 *//* A *//* B *//* C *//* D *//* E *//* F */
          /* 0 */ "52" , "09" , "6A" , "D5" , "30" , "36" , "A5" , "38" , "BF" , "40" , "A3" , "9E" , "81" , "F3" , "D7" , "FB" ,
          /* 1 */ "7C" , "E3" , "39" , "82" , "9B" , "2F" , "FF" , "87" , "34" , "8E" , "43" , "44" , "C4" , "DE" , "E9" , "CB" ,
          /* 2 */ "54" , "7B" , "94" , "32" , "A6" , "C2" , "23" , "3D" , "EE" , "4C" , "95" , "0B" , "42" , "FA" , "C3" , "4E" ,
          /* 3 */ "08" , "2E" , "A1" , "66" , "28" , "D9" , "24" , "B2" , "76" , "5B" , "A2" , "49" , "6D" , "8B" , "D1" , "25" ,
          /* 4 */ "72" , "F8" , "F6" , "64" , "86" , "68" , "98" , "16" , "D4" , "A4" , "5C" , "CC" , "5D" , "65" , "B6" , "92" ,
          /* 5 */ "6C" , "70" , "48" , "50" , "FD" , "ED" , "B9" , "DA" , "5E" , "15" , "46" , "57" , "A7" , "8D" , "9D" , "84" ,
          /* 6 */ "90" , "D8" , "AB" , "00" , "8C" , "BC" , "D3" , "0A" , "F7" , "E4" , "58" , "05" , "B8" , "B3" , "45" , "06" ,
          /* 7 */ "D0" , "2C" , "1E" , "8F" , "CA" , "3F" , "OF" , "02" , "C1" , "AF" , "BD" , "03" , "01" , "13" , "8A" , "6B" ,
          /* 8 */ "3A" , "91" , "11" , "41" , "4F" , "67" , "DC" , "EA" , "97" , "F2" , "CF" , "CE" , "F0" , "B4" , "E6" , "73" ,
          /* 9 */ "96" , "AC" , "74" , "22" , "E7" , "AD" , "35" , "85" , "E2" , "F9" , "37" , "E8" , "1C" , "75" , "DF" , "6E" ,
          /* A */ "47" , "F1" , "1A" , "71" , "1D" , "29" , "C5" , "89" , "6F" , "B7" , "62" , "0E" , "AA" , "18" , "BE" , "1B" ,
          /* B */ "FC" , "56" , "3E" , "4B" , "C6" , "D2" , "79" , "20" , "9A" , "DB" , "C0" , "FE" , "78" , "CD" , "5A" , "F4" ,
          /* C */ "1F" , "DD" , "A8" , "33" , "88" , "07" , "C7" , "31" , "B1" , "12" , "10" , "59" , "27" , "80" , "EC" , "5F" ,
          /* D */ "60" , "51" , "7F" , "A9" , "19" , "B5" , "4A" , "0D" , "2D" , "E5" , "7A" , "9F" , "93" , "C9 ", "9C" , "EF" ,
          /* E */ "A0" , "E0" , "3B" , "4D" , "AE" , "2A" , "F5" , "B0" , "C8" , "EB" , "BB" , "3C" , "83" , "53" , "99" , "61" ,
          /* F */ "17" , "2B" , "04" , "7E" , "BA" , "77" , "D6" , "26" , "E1" , "69" , "14" , "63" , "55" , "21" , "0C" , "7D" ,
      };
      return InverseSbox[row][column];
}

char * S_box(int row , int column){

    char * matrix[16][16] ={"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76",
                            "CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0",
                            "B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15",
                            "04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75",
                            "09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84",
                            "53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF",
                            "D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8",
                            "51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2",
                            "CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73",
                            "60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB",
                            "E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79",
                            "E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08",
                            "BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A",
                            "70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E",
                            "E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF",
                            "8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"};

    return matrix[row][column];
}

void passForBite(Infos* vetor){

  int i,j,k=0;
  int bitShift=0;
  int value1 = 0;
  int value2 = 0;
  int vetorAux1[4];
  int vetorAux2[4];


  for(j=0;j<16;j++){
    k=0;
    for(i = 3 ; i>= 0 ; i--){
        value1 = convertHexForDecimal(vetor[j].byte1);
        bitShift = value1 >> i;
        if(bitShift & 1){
            vetorAux1[k] = 1;
        }
        else{
        	vetorAux1[k] = 0;
        }
        k++;
    }

    k=0;
    for(i = 3 ; i>= 0 ; i--){
        value2 = convertHexForDecimal(vetor[j].byte2);
        bitShift = value2 >> i;
        if(bitShift & 1){
            vetorAux2[k] = 1;
        }
        else{
        	vetorAux2[k] = 0;
        }
        k++;
    }

    for(i=0;i<4;i++){
    //  vetor[j].bits = malloc(sizeof())
      vetor[j].bits1[i] = vetorAux1[i];
      vetor[j].bits2[i] = vetorAux2[i];
    }
  }
}

void fillHexBits(Infos* vetor){
  int i,j;
  for(i=0 ; i<16; i++){
    for(j = 0 ; j<4;j++){
      vetor[i].bitsHexa[j] = vetor[i].bits1[j];
    }
    for( j = 0 ; j<4; j++){
      vetor[i].bitsHexa[j+4] = vetor[i].bits2[j];
    }
  }
}

void addition(int * vetor , int * vetor2,int * vetorResult){
    int xorValue,i;
    for(i = 0 ; i<8;i++){
      xorValue = vetor[i]^vetor2[i];
      vetorResult[i] = xorValue;
    }
}

void multiplicationGF(int * vetor, int *v ,int *vetorResult){
  int i,j;
  int irredutivePolinome[8] = {0,0,0,1,1,0,1,1};
  int vetorAux[8];

  //Exeuta a operação de multiplicação com 2
  if(v[7]==0){
    if(vetor[0]==0){
        for ( i = 0; i < 8; i++) {
          if(i!=7){
            vetorResult[i] = vetor[i+1];
          }else{
            vetorResult[i] = 0;
          }
        }
      }else{
          for (i = 0; i < 8; i++){
            if(i!=7){
              vetorAux[i] = vetor[i+1];
            }else{
              vetorAux[i] = 0;
            }
          }
          addition(vetorAux,irredutivePolinome,vetorResult);
        }
      //Executa a operação de multiplicação sobre 3
      }else{
        if(vetor[0]==0){
            for ( i = 0; i < 8; i++) {
              if(i!=7){
                vetorResult[i] = vetor[i+1];
              }else{
                vetorResult[i] = 0;
              }
            }
          }else{
              for ( i = 0; i < 8; i++){
                if(i!=7){
                  vetorAux[i] = vetor[i+1];
                }else{
                  vetorAux[i] = 0;
                }
              }
              addition(vetorAux,irredutivePolinome,vetorResult);
          }
          addition(vetor,vetorResult,vetorResult);
      }
}

int findDecimalNumber(int * vetor){
    int decimalValue=0 ;
    int i;
        vetor[3] = vetor[3] * 1;
        vetor[2] = vetor[2] * 10;
        vetor[1] = vetor[1] * 100;
        vetor[0] = vetor[0] * 1000;
        for(i = 0 ; i<4 ; i++){
            decimalValue += vetor[i];
        }
    return decimalValue;
}

char convertBinaryNumberInInteger(int * vetor){
    int decimalNumber;
    decimalNumber = findDecimalNumber(vetor);

    switch(decimalNumber){
        case 0:
            return '0';
        case 1:
            return '1';
        case 10:
            return '2';
        case 11:
            return '3';
        case 100:
            return '4';
        case 101:
            return '5';
        case 110:
            return '6';
        case 111:
            return '7';
        case 1000:
            return '8';
        case 1001:
            return '9';
        case 1010:
            return 'A';
        case 1011:
            return 'B';
        case 1100:
            return 'C';
        case 1101:
            return 'D';
        case 1110:
            return 'E';
        case 1111:
            return 'F';
    }
}

void mixColumnTransformation(Infos* vetor, Infos * result){
    int i;
    int vetorAux1[8];
    int vetorAux2[8];
    int vetorAux3[8];
    int vetorAux4[8];
    int vetor2[8] = {0,0,0,0,0,0,1,0};
    int vetor3[8] = {0,0,0,0,0,0,1,1};
    int j,k;
    int transitionVector1[4];
    int transitionVector2[4];
      i=0;
      k = 0;
      // forma a primeira linha da matriz do mixColumnTransformation
      for(i = 0 ; i<4 ;i++){
        multiplicationGF(vetor[i].bitsHexa,vetor2,vetorAux1);
        multiplicationGF(vetor[i+4].bitsHexa,vetor3,vetorAux2);
        addition(vetorAux1,vetorAux2,vetorAux3);
        addition(vetorAux3,vetor[i+8].bitsHexa,vetorAux4);
        addition(vetor[i+12].bitsHexa,vetorAux4,result[k].bitsHexa);
        for(j=0; j <4;j++){
          transitionVector1[j] = result[k].bitsHexa[j];
        }
        for(j=4; j <8;j++){
          transitionVector2[j-4] = result[k].bitsHexa[j];
        }
        result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
        result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
        k++;
      }
      //Produz a segunda linha do mixColumnTransformation
      for(i = 0 ; i<4 ; i++){
        multiplicationGF(vetor[4+i].bitsHexa,vetor2,vetorAux1);
        multiplicationGF(vetor[8+i].bitsHexa,vetor3,vetorAux2);
        addition(vetorAux1,vetorAux2,vetorAux3);
        addition(vetorAux3,vetor[i].bitsHexa,vetorAux4);
        addition(vetorAux4,vetor[12+i].bitsHexa,result[k].bitsHexa);
        for(j=0; j <4;j++){
          transitionVector1[j] = result[k].bitsHexa[j];
        }
        for(j=4; j <8;j++){
          transitionVector2[j-4] = result[k].bitsHexa[j];
        }
        result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
        result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
        k++;
      }
      //Produz a terceira linha do mix column
      for(i =0 ; i<4 ; i++){
        multiplicationGF(vetor[i+8].bitsHexa,vetor2,vetorAux1);
        multiplicationGF(vetor[i+12].bitsHexa,vetor3,vetorAux2);
        addition(vetorAux1,vetorAux2,vetorAux3);
        addition(vetor[i+4].bitsHexa,vetorAux3,vetorAux4);
        addition(vetor[i].bitsHexa,vetorAux4,result[k].bitsHexa);
        for(j=0; j <4;j++){
          transitionVector1[j] = result[k].bitsHexa[j];
        }
        for(j=4; j <8;j++){
          transitionVector2[j-4] = result[k].bitsHexa[j];
        }
        result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
        result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
        k++;
      }
      //produz a quarta linha do mixColumnTransformation
      for(i =0 ; i<4 ; i++){
        multiplicationGF(vetor[i].bitsHexa,vetor3,vetorAux1);
        multiplicationGF(vetor[i+12].bitsHexa,vetor2,vetorAux2);
        addition(vetorAux1,vetorAux2,vetorAux3);
        addition(vetor[i+4].bitsHexa,vetorAux3,vetorAux4);
        addition(vetor[i+8].bitsHexa,vetorAux4,result[k].bitsHexa);
        for(j=0; j <4;j++){
          transitionVector1[j] = result[k].bitsHexa[j];
        }
        for(j=4; j <8;j++){
          transitionVector2[j-4] = result[k].bitsHexa[j];
        }
        result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
        result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
        k++;
      }
}

int findDecimalNumber2(int *vetor){
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

    return decimalValue;
}

char  convertBinToHex(int intValue){
    char hexValue;

    switch(intValue){
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
            hexValue = 'A';
            break;
        case 11:
            hexValue = 'B';
            break;
        case 12:
            hexValue = 'C';
            break;
        case 13:
            hexValue = 'D';
            break;
        case 14:
            hexValue = 'E';
            break;
        case 15:
            hexValue = 'F';
            break;
        default:
            break;
    }

    return hexValue;
}

void convertHexToBinary(char word,int *aux1){

    switch(word){
        case '0':
            //binary = 0000;
            aux1[0] = 0;
            aux1[1] = 0;
            aux1[2] = 0;
            aux1[3] = 0;
            break;
        case '1':
            //binary = 0001;
            aux1[0] = 0;
            aux1[1] = 0;
            aux1[2] = 0;
            aux1[3] = 1;
            break;
        case '2':
            //binary = 0010;
            aux1[0] = 0;
            aux1[1] = 0;
            aux1[2] = 1;
            aux1[3] = 0;
            break;
        case '3':
            //binary = 0011;
            aux1[0] = 0;
            aux1[1] = 0;
            aux1[2] = 1;
            aux1[3] = 1;
            break;
        case '4':
            //binary = 0100;
            aux1[0] = 0;
            aux1[1] = 1;
            aux1[2] = 0;
            aux1[3] = 0;
            break;
        case '5':
            //binary = 0101;
            aux1[0] = 0;
            aux1[1] = 1;
            aux1[2] = 0;
            aux1[3] = 1;
            break;
        case '6':
            //binary = 0110;
            aux1[0] = 0;
            aux1[1] = 1;
            aux1[2] = 1;
            aux1[3] = 0;
            break;
        case '7':
            //binary = 0111;
            aux1[0] = 0;
            aux1[1] = 1;
            aux1[2] = 1;
            aux1[3] = 1;
            break;
        case '8':
            //binary = 1000;
            aux1[0] = 1;
            aux1[1] = 0;
            aux1[2] = 0;
            aux1[3] = 0;
            break;
        case '9':
            //binary = 1001;
            aux1[0] = 1;
            aux1[1] = 0;
            aux1[2] = 0;
            aux1[3] = 1;
            break;
        case 'A':
            //binary = 1010;
            aux1[0] = 1;
            aux1[1] = 0;
            aux1[2] = 1;
            aux1[3] = 0;
            break;
        case 'B':
            //binary = 1011;
            aux1[0] = 1;
            aux1[1] = 0;
            aux1[2] = 1;
            aux1[3] = 1;
            break;
        case 'C':
            //binary = 1100;
            aux1[0] = 1;
            aux1[1] = 1;
            aux1[2] = 0;
            aux1[3] = 0;
            break;
        case 'D':
            //binary = 1101;
            aux1[0] = 1;
            aux1[1] = 1;
            aux1[2] = 0;
            aux1[3] = 1;
            break;
        case 'E':
            //binary = 1110;
            aux1[0] = 1;
            aux1[1] = 1;
            aux1[2] = 1;
            aux1[3] = 0;
            break;
        case 'F':
            //binary = 1111;
            aux1[0] = 1;
            aux1[1] = 1;
            aux1[2] = 1;
            aux1[3] = 1;
            break;
    }
}

char * xorFunction(char *word1,char *word2){
    int aux1[4];
    int aux2[4];
    int aux[8];
    char *auxChar = malloc(sizeof(char)*2);
    int numBin1[4],numBin2[4],numBin3[4],numBin4[4];
    int i=0;

    convertHexToBinary(word1[0],numBin1);
    convertHexToBinary(word1[1],numBin2);
    convertHexToBinary(word2[0],numBin3);
    convertHexToBinary(word2[1],numBin4);

    for(i=0;i<4;i++){

        aux1[i] = numBin1[i]^numBin3[i];
    }

    for( i=0;i<4;i++){
        aux2[i] = numBin2[i]^numBin4[i];
    }
    auxChar[0] = convertBinToHex(findDecimalNumber2(aux1));
    auxChar[1] = convertBinToHex(findDecimalNumber2(aux2));

    return auxChar;
}

void xor(int * vetor1 , int * vetor2 , int *result){
  int i;
  for(i = 127 ; i>=0 ; i--){
    result[i] = vetor1[i]^vetor2[i];
  }
}

int converHexToDec(char letter){

    switch(letter){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
    }

}

char * getSBoxValue(char *word){

    int line = converHexToDec(word[0]);
    int collum = converHexToDec(word[1]);

    char * sbox[16][16] =   {
               /* 0 *//* 1 *//* 2 *//* 3 *//* 4 *//* 5 *//* 6 *//* 7 *//* 8 *//* 9 *//* A *//* B *//* C *//* D *//* E *//* F */
        /* 0 */ "63" , "7C" , "77" , "7B" , "F2" , "6B" , "6F" , "C5" , "30" , "01" , "67" , "2B" , "FE" , "D7" , "AB" , "76" ,
        /* 1 */ "CA" , "82" , "C9" , "7D" , "FA" , "59" , "47" , "F0" , "AD" , "D4" , "A2" , "AF" , "9C" , "A4" , "72" , "C0" ,
        /* 2 */ "B7" , "FD" , "93" , "26" , "36" , "3F" , "F7" , "CC" , "34" , "A5" , "E5" , "F1" , "71" , "D8" , "31" , "15" ,
        /* 3 */ "04" , "C7" , "23" , "C3" , "18" , "96" , "05" , "9A" , "07" , "12" , "80" , "E2" , "EB" , "27" , "B2" , "75" ,
        /* 4 */ "09" , "83" , "2C" , "1A" , "1B" , "6E" , "5A" , "A0" , "52" , "3B" , "D6" , "B3" , "29" , "E3" , "2F" , "84" ,
        /* 5 */ "53" , "D1" , "00" , "ED" , "20" , "FC" , "B1" , "5B" , "6A" , "CB" , "BE" , "39" , "4A" , "4C" , "58" , "CF" ,
        /* 6 */ "D0" , "EF" , "AA" , "FB" , "43" , "4D" , "33" , "85" , "45" , "F9" , "02" , "7F" , "50" , "3C" , "9F" , "A8" ,
        /* 7 */ "51" , "A3" , "40" , "8F" , "92" , "9D" , "38" , "F5" , "BC" , "B6" , "DA" , "21" , "10" , "FF" , "F3" , "D2" ,
        /* 8 */ "CD" , "0C" , "13" , "EC" , "5F" , "97" , "44" , "17" , "C4" , "A7" , "7E" , "3D" , "64" , "5D" , "19" , "73" ,
        /* 9 */ "60" , "81" , "4F" , "DC" , "22" , "2A" , "90" , "88" , "46" , "EE" , "B8" , "14" , "DE" , "5E" , "0B" , "DB" ,
        /* A */ "E0" , "32" , "3A" , "0A" , "49" , "06" , "24" , "5C" , "C2" , "D3" , "AC" , "62" , "91" , "95" , "E4" , "79" ,
        /* B */ "E7" , "C8" , "37" , "6D" , "8D" , "D5" , "4E" , "A9" , "6C" , "56" , "F4" , "EA" , "65" , "7A" , "AE" , "08" ,
        /* C */ "BA" , "78" , "25" , "2E" , "1C" , "A6" , "B4" , "C6" , "E8" , "DD" , "74" , "1F" , "4B" , "BD" , "8B" , "8A" ,
        /* D */ "70" , "3E" , "B5" , "66" , "48" , "03" , "F6" , "0E" , "61" , "35" , "57" , "B9" , "86" , "C1 ", "1D" , "9E" ,
        /* E */ "E1" , "F8" , "98" , "11" , "69" , "D9" , "8E" , "94" , "9B" , "1E" , "87" , "E9" , "CE" , "55" , "28" , "DF" ,
        /* F */ "8C" , "A1" , "89" , "0D" , "BF" , "E6" , "42" , "68" , "41" , "99" , "2D" , "0F" , "B0" , "54" , "BB" , "16" ,
    };

    return sbox[line][collum];
}

char * RCon(int opcao){
    switch(opcao){
        case 1:
            return "01";

        case 2:
            return "02";

        case 3:
            return "04";

        case 4:
            return "08";

        case 5:
            return "10";

        case 6:
            return "20";

        case 7:
            return "40";

        case 8:
            return "80";

        case 9:
            return "1B";

        case 10:
            return "36";

        case 11:
            return "6C";

        case 12:
            return "D8";

        case 13:
            return "AB";

        case 14:
            return "4D";

        case 15:
            return "9A";
    }

}

int * convertWordLetterInBinary(char *word){
  int * aux = malloc(sizeof(int)*8);
  int aux1[4],aux2[4];
  int i;
  convertHexToBinary(word[0],aux1);
  convertHexToBinary(word[1],aux2);

  for(i=0;i<4;i++){
    aux[i] = aux1[i];
    aux[i+4] = aux2[i];
  }

  return aux;
}

int *convertWordInBinary(word word1,word word2,word word3,word word4){
  int * aux = malloc(sizeof(int)*8);
  int * roundKeyAux = malloc(sizeof(int)*128);
  //int roundKeyAux[128];
  int k=0;
  int j;

      aux = convertWordLetterInBinary(word1.w[0]);
      for(j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word2.w[0]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word3.w[0]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word4.w[0]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }


      aux = convertWordLetterInBinary(word1.w[1]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word2.w[1]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word3.w[1]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word4.w[1]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }


      aux = convertWordLetterInBinary(word1.w[2]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word2.w[2]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word3.w[2]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word4.w[2]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }


      aux = convertWordLetterInBinary(word1.w[3]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word2.w[3]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word3.w[3]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }
      aux = convertWordLetterInBinary(word4.w[3]);
      for( j=0;j<8;j++){
        roundKeyAux[k] = aux[j];
        k++;
      }


  free(aux);
  return roundKeyAux;
}

void  generateRoundKeys(roundKey *roundKey){
    char keyInserted[32];
    char keyAux0[2],keyAux1[2],keyAux2[2],keyAux3[2],keyAux4[2],keyAux5[2],keyAux6[2],keyAux7[2],keyAux8[2];
    char keyAux9[2],keyAux10[2],keyAux11[2],keyAux12[2],keyAux13[2],keyAux14[2],keyAux15[2];

    printf("Insira a chave: " );
    scanf("%s",keyInserted);

    snprintf (keyAux0,3, "%c%c" ,keyInserted[0] ,keyInserted[1]);
    snprintf (keyAux1,3, "%c%c" ,keyInserted[2] ,keyInserted[3]);
    snprintf (keyAux2,3, "%c%c" ,keyInserted[4] ,keyInserted[5]);
    snprintf (keyAux3,3, "%c%c" ,keyInserted[6] ,keyInserted[7]);
    snprintf (keyAux4,3, "%c%c" ,keyInserted[8] ,keyInserted[9]);
    snprintf (keyAux5,3, "%c%c" ,keyInserted[10 ],keyInserted[11]);
    snprintf (keyAux6,3, "%c%c" ,keyInserted[12] ,keyInserted[13]);
    snprintf (keyAux7,3, "%c%c" ,keyInserted[14] ,keyInserted[15]);
    snprintf (keyAux8,3, "%c%c" ,keyInserted[16] ,keyInserted[17]);
    snprintf (keyAux9,3, "%c%c" ,keyInserted[18] ,keyInserted[19]);
    snprintf (keyAux10,3, "%c%c",keyInserted[20],keyInserted[21]);
    snprintf (keyAux11,3, "%c%c",keyInserted[22],keyInserted[23]);
    snprintf (keyAux12,3, "%c%c",keyInserted[24],keyInserted[25]);
    snprintf (keyAux13,3, "%c%c",keyInserted[26],keyInserted[27]);
    snprintf (keyAux14,3, "%c%c",keyInserted[28],keyInserted[29]);
    snprintf (keyAux15,3, "%c%c",keyInserted[30],keyInserted[31]);


    //char *key[16] = {"0F","15","71","C9","47","D9","E8","59","0C","B7","AD","D6","AF","7F","67","98"};
    char *key[16] = {keyAux0,keyAux1,keyAux2,keyAux3,keyAux4,keyAux5,keyAux6,keyAux7,keyAux8,keyAux9,keyAux10,keyAux11,keyAux12,keyAux13,keyAux14,keyAux15};
    temp temp;
    char *aux;
    word word[44];
    int i=0 , j;
    int roundCounter=0;

    //First round
    for(i=0;i<4;i++){
        word[i].w[0] = key[4*i];
        word[i].w[1] = key[4*i+1];
        word[i].w[2] = key[4*i+2];
        word[i].w[3] = key[4*i+3];
    }

    roundCounter++;


    for (i = 4; i < 44; i++){

        temp.w[0] = word[i-1].w[0];
        temp.w[1] = word[i-1].w[1];
        temp.w[2] = word[i-1].w[2];
        temp.w[3] = word[i-1].w[3];


        if(i%4 == 0){
            //Rot word
            aux        = temp.w[0];
            temp.w[0] = temp.w[1];
            temp.w[1] = temp.w[2];
            temp.w[2] = temp.w[3];
            temp.w[3] = aux;

            // Subword S-box e XOR com RCJ
            temp.w[0] = xorFunction (getSBoxValue(temp.w[0]),RCon(roundCounter));
            temp.w[1] = xorFunction (getSBoxValue(temp.w[1]),"00");
            temp.w[2] = xorFunction (getSBoxValue(temp.w[2]),"00");
            temp.w[3] = xorFunction (getSBoxValue(temp.w[3]),"00");

            roundCounter++;
        }

        word[i].w[0] = xorFunction(word[i - 4].w[0],temp.w[0]);
        word[i].w[1] = xorFunction(word[i - 4].w[1],temp.w[1]);
        word[i].w[2] = xorFunction(word[i - 4].w[2],temp.w[2]);
        word[i].w[3] = xorFunction(word[i - 4].w[3],temp.w[3]);

    }

      int *roundKeyBinary[11];

      //Round 0 key
      roundKeyBinary[0] = convertWordInBinary(word[0],word[1],word[2],word[3]);
      //Round 1 key
      roundKeyBinary[1] = convertWordInBinary(word[4],word[5],word[6],word[7]);
      //Round 2 key
      roundKeyBinary[2] = convertWordInBinary(word[8],word[9],word[10],word[11]);
      //Round 3 key
      roundKeyBinary[3] = convertWordInBinary(word[12],word[13],word[14],word[15]);
      //Round 4 key
      roundKeyBinary[4] = convertWordInBinary(word[16],word[17],word[18],word[19]);
      //Round 5 key
      roundKeyBinary[5] = convertWordInBinary(word[20],word[21],word[22],word[23]);
      //Round 6 key
      roundKeyBinary[6] = convertWordInBinary(word[24],word[25],word[26],word[27]);
      //Round 7 key
      roundKeyBinary[7] = convertWordInBinary(word[28],word[29],word[30],word[31]);
      //Round 8 key
      roundKeyBinary[8] = convertWordInBinary(word[32],word[33],word[34],word[35]);
      //Round 9 key
      roundKeyBinary[9] = convertWordInBinary(word[36],word[37],word[38],word[39]);
      //Round 10 key
      roundKeyBinary[10] = convertWordInBinary(word[40],word[41],word[42],word[43]);

      //Transfer to struct
        for( i=0;i<11;i++){
          for( j=0;j<128;j++){
              roundKey[i].key[j]=roundKeyBinary[i][j];
          }
        }
    }

void multiplicationGF2(int * vetor,int *vetorResult){
      int i,j;
      int irredutivePolinome[8] = {0,0,0,1,1,0,1,1};
      int vetorAux[8];

      //Exeuta a operação de multiplicação com 2
        if(vetor[0]==0){
            for ( i = 0; i < 8; i++) {
              if(i!=7){
                vetorResult[i] = vetor[i+1];
              }else{
                vetorResult[i] = 0;
              }
            }
          }else{
              for (i = 0; i < 8; i++){
                if(i!=7){
                  vetorAux[i] = vetor[i+1];
                }else{
                  vetorAux[i] = 0;
                }
              }
              addition(vetorAux,irredutivePolinome,vetorResult);
        }
}

void multiTesteD(ResultMult * mult, int * vetor, int *saida){
      int i;
      multiplicationGF2(vetor,mult->mult2);
      multiplicationGF2(mult->mult2,mult->mult4);
      multiplicationGF2(mult->mult4,mult->mult8);
      addition(vetor,mult->mult4,mult->resultado);
      addition(mult->mult8,mult->resultado,mult->resultadoFinal);
      for(i = 0 ; i<8 ; i++){
        saida[i] = mult->resultadoFinal[i];
      }
}

void multiTesteE(ResultMult * mult, int * vetor,int * saida){
      int i;
      multiplicationGF2(vetor,mult->mult2);
      multiplicationGF2(mult->mult2,mult->mult4);
      multiplicationGF2(mult->mult4,mult->mult8);
      addition(mult->mult2,mult->mult4,mult->resultado);
      addition(mult->mult8,mult->resultado,mult->resultadoFinal);
      for(i = 0 ; i<8 ; i++){
        saida[i] = mult->resultadoFinal[i];
      }
}

void multiTesteB(ResultMult * mult, int * vetor,int * saida){
      int i = 0;
      multiplicationGF2(vetor,mult->mult2);
      multiplicationGF2(mult->mult2,mult->mult4);
      multiplicationGF2(mult->mult4,mult->mult8);
      addition(vetor,mult->mult2,mult->resultado);
      addition(mult->mult8,mult->resultado,mult->resultadoFinal);
      for(i = 0 ; i<8 ; i++){
        saida[i] = mult->resultadoFinal[i];
      }
}

void multiTeste9(ResultMult * mult, int * vetor, int * saida){
      int i;
      multiplicationGF2(vetor,mult->mult2);
      multiplicationGF2(mult->mult2,mult->mult4);
      multiplicationGF2(mult->mult4,mult->mult8);
      addition(mult->mult8,vetor,mult->resultadoFinal);
      for(i = 0 ; i<8 ; i++){
        saida[i] = mult->resultadoFinal[i];
      }
}

void inverseMixColumn(Infos * vetor, Infos * result){
  ResultMult mult;
  int aux1[8];
  int aux2[8];
  int aux3[8];
  int aux4[8];
  int aux5[8];
  int aux6[8];
  int k=0,i,j;
  int transitionVector1[4];
  int transitionVector2[4];
  //formando a primeira linha inversa
  for(i = 0 ; i< 4 ; i++){
    multiTesteE(&mult,vetor[i].bitsHexa,aux1);
    multiTesteB(&mult,vetor[i+4].bitsHexa,aux2);
    addition(aux1,aux2,aux3);
    multiTesteD(&mult,vetor[i+8].bitsHexa,aux4);
    addition(aux3,aux4,aux5);
    multiTeste9(&mult,vetor[i+12].bitsHexa,aux6);
    addition(aux5,aux6,result[k].bitsHexa);
    for(j=0; j <4;j++){
      transitionVector1[j] = result[k].bitsHexa[j];
    }
    for(j=4; j <8;j++){
      transitionVector2[j-4] = result[k].bitsHexa[j];
    }
    result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
    result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
    k++;
  }
  //formando a segunda linha inversa
  for(i = 0 ; i< 4 ; i++){
    multiTeste9(&mult,vetor[i].bitsHexa,aux1);
    multiTesteE(&mult,vetor[i+4].bitsHexa,aux2);
    addition(aux1,aux2,aux3);
    multiTesteB(&mult,vetor[i+8].bitsHexa,aux4);
    addition(aux3,aux4,aux5);
    multiTesteD(&mult,vetor[i+12].bitsHexa,aux6);
    addition(aux5,aux6,result[k].bitsHexa);
    for(j=0; j <4;j++){
      transitionVector1[j] = result[k].bitsHexa[j];
    }
    for(j=4; j <8;j++){
      transitionVector2[j-4] = result[k].bitsHexa[j];
    }
    result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
    result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);

    k++;
  }
  //formando a terceira linha inversa
  for(i = 0 ; i< 4 ; i++){
    multiTesteD(&mult,vetor[i].bitsHexa,aux1);

    multiTeste9(&mult,vetor[i+4].bitsHexa,aux2);
    addition(aux1,aux2,aux3);
    multiTesteE(&mult,vetor[i+8].bitsHexa,aux4);
    addition(aux3,aux4,aux5);
    multiTesteB(&mult,vetor[i+12].bitsHexa,aux6);
    addition(aux5,aux6,result[k].bitsHexa);
    for(j=0; j <4;j++){
      transitionVector1[j] = result[k].bitsHexa[j];
    }
    for(j=4; j <8;j++){
      transitionVector2[j-4] = result[k].bitsHexa[j];
    }
    result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
    result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
    k++;
  }
  //formando quarta linha
  for(i = 0 ; i< 4 ; i++){
    multiTesteB(&mult,vetor[i].bitsHexa,aux1);
    multiTesteD(&mult,vetor[i+4].bitsHexa,aux2);
    addition(aux1,aux2,aux3);
    multiTeste9(&mult,vetor[i+8].bitsHexa,aux4);
    addition(aux3,aux4,aux5);
    multiTesteE(&mult,vetor[i+12].bitsHexa,aux6);
    addition(aux5,aux6,result[k].bitsHexa);
    for(j=0; j <4;j++){
      transitionVector1[j] = result[k].bitsHexa[j];
    }
    for(j=4; j <8;j++){
      transitionVector2[j-4] = result[k].bitsHexa[j];
    }
    result[k].byte1 = convertBinaryNumberInInteger(transitionVector1);
    result[k].byte2 = convertBinaryNumberInInteger(transitionVector2);
    k++;
  }
}

void encryptMessage(){
  int i , j ,k;
  int column=0 , row =0;
  char  * aux;
  Infos vetor[16];
  Infos r[16]  ;
  Infos resultsForInverse[16];
  int bitsAux1[4],bits2Aux2[4],firstAndLastRound[128],auxT1[4],auxT2[4];
  int bitsForXor[128] , results[128] ;
  roundKey roundKey[11];
  int auxInt1 , auxInt2;
  int op;
  Infos mixInverso[16];
  char * matrixAux [4][4];
  char * auxForByte;
  int l=0,c=0;
  char auxMatrix0[2],auxMatrix1[2],auxMatrix2[2],auxMatrix3[2],auxMatrix4[2],auxMatrix5[2],auxMatrix6[2],auxMatrix7[2],auxMatrix8[2];
  char auxMatrix9[2],auxMatrix10[2],auxMatrix11[2],auxMatrix12[2],auxMatrix13[2],auxMatrix14[2],auxMatrix15[2];

  generateRoundKeys(roundKey);

  char mensagem[32];
  printf("Insira a mensagem: " );
  scanf("%s", mensagem);

  snprintf (auxMatrix0,3, "%c%c",mensagem[0],mensagem[1]);
  snprintf (auxMatrix1,3, "%c%c",mensagem[2],mensagem[3]);
  snprintf (auxMatrix2,3, "%c%c",mensagem[4],mensagem[5]);
  snprintf (auxMatrix3,3, "%c%c",mensagem[6],mensagem[7]);
  snprintf (auxMatrix4,3, "%c%c",mensagem[8],mensagem[9]);
  snprintf (auxMatrix5,3, "%c%c",mensagem[10],mensagem[11]);
  snprintf (auxMatrix6,3, "%c%c",mensagem[12],mensagem[13]);
  snprintf (auxMatrix7,3, "%c%c",mensagem[14],mensagem[15]);
  snprintf (auxMatrix8,3, "%c%c",mensagem[16],mensagem[17]);
  snprintf (auxMatrix9,3, "%c%c",mensagem[18],mensagem[19]);
  snprintf (auxMatrix10,3, "%c%c",mensagem[20],mensagem[21]);
  snprintf (auxMatrix11,3, "%c%c",mensagem[22],mensagem[23]);
  snprintf (auxMatrix12,3, "%c%c",mensagem[24],mensagem[25]);
  snprintf (auxMatrix13,3, "%c%c",mensagem[26],mensagem[27]);
  snprintf (auxMatrix14,3, "%c%c",mensagem[28],mensagem[29]);
  snprintf (auxMatrix15,3, "%c%c",mensagem[30],mensagem[31]);

  char * matrix[4][4] = { auxMatrix0 , auxMatrix4 , auxMatrix8  , auxMatrix12,
                          auxMatrix1 , auxMatrix5 , auxMatrix9  , auxMatrix13,
                          auxMatrix2 , auxMatrix6 , auxMatrix10 , auxMatrix14,
                          auxMatrix3 , auxMatrix7 , auxMatrix11 , auxMatrix15};


  while (c<11) {

      if(c == 0 ){
        for( i = 0 ; i< 4 ; i++){
          for(j = 0 ; j < 4 ; j++){
            aux = malloc(sizeof(char)*2);
            aux = matrix[i][j];
            convertHexToBinary(aux[0],auxT1);
            convertHexToBinary(aux[1],auxT2);
            for(k = 0 ; k<4 ; k++){
              firstAndLastRound[l] = auxT1[k];
              l++;
            }
            for(k = 0 ; k<4 ; k++){
              firstAndLastRound[l] = auxT2[k];
              l++;
            }
          }
        }
        xor(firstAndLastRound,roundKey[c].key,results);

        l = 0;
        //armazena os bytes para um proximo round
        for(i = 0 ; i <16 ; i++){
          for(j = 0 ; j <4 ; j++){
            r[i].bits1[j] = results[l];
            l++;
          }
          for(j = 0 ; j <4 ; j++){
            r[i].bits2[j] = results[l];
            l++;
          }
          r[i].byte1 = convertBinaryNumberInInteger(r[i].bits1);
          r[i].byte2 = convertBinaryNumberInInteger(r[i].bits2);

        }

        l=0;
        for(i = 0 ; i < 4 ; i++){
          for(j=0;j<4;j++){
            auxForByte = malloc(sizeof(char)*2);
            auxForByte[0] = r[l].byte1;
            auxForByte[1] = r[l].byte2;
            matrix[i][j] = auxForByte;
            l++;
          }
        }
        l=0;
      }else{

          // prepara a matriz de entrada para fazer o shiftRows
          k = 0;
          for(i = 0 ; i < 4 ; i++){
            for(j = 0 ; j < 4; j++){
                aux = (char*) malloc(sizeof(char)*2);
                aux = matrix[i][j];
                row = convertHexForDecimal(aux[0]);
                column = convertHexForDecimal(aux[1]);
                vetor[k].byteInt1 = row;
                vetor[k].byteInt2 = column;
                matrixAux[i][j] = S_box(row,column);
                k++;
            }
          }
          // Aplica shiftRows transformation
          char * matrixShiftRows[4][4] = {
                   matrixAux[0][0],matrixAux[0][1],matrixAux[0][2],matrixAux[0][3],
                   matrixAux[1][1],matrixAux[1][2],matrixAux[1][3],matrixAux[1][0],
                   matrixAux[2][2],matrixAux[2][3],matrixAux[2][0],matrixAux[2][1],
                   matrixAux[3][3],matrixAux[3][0],matrixAux[3][1],matrixAux[3][2]};
          k = 0;
          //Preenche as informações dos bytes

          for(i = 0 ; i < 4 ; i++){
            for(j = 0 ; j < 4 ; j++){
              aux = (char*)malloc(sizeof(char)*2);
              aux = matrixShiftRows[i][j];
              vetor[k].byte1 = aux[0];
              vetor[k].byte2 = aux[1];
              k++;
              }
          }
          j=0;
          passForBite(vetor);
          fillHexBits(vetor);
          // executa operações sobre o mix column
            if(c<10){
              mixColumnTransformation(vetor,r);
            }else{
              k=0;
              for(i = 0 ; i<16; i++){
                for( j = 0 ; j< 8 ; j++){
                  bitsForXor[k] = vetor[i].bitsHexa[j];
                  k++;
                }
              }
            }

          k=0;
          // prepara o vetor  para poder fazer o xor com a chave do round
          if(c!=10){
            for(i = 0 ; i<16; i++){
              for( j = 0 ; j< 8 ; j++){
                bitsForXor[k] = r[i].bitsHexa[j];
                k++;
              }
            }
          }
          //executa o xor com a chave do round
          xor(bitsForXor,roundKey[c].key,results);

          l = 0;
          //armazena os bytes para um proximo round
          for(i = 0 ; i <16 ; i++){
            for(j = 0 ; j <4 ; j++){
              r[i].bits1[j] = results[l];
              l++;
            }
            for(j = 0 ; j <4 ; j++){
              r[i].bits2[j] = results[l];
              l++;
            }
            r[i].byte1 = convertBinaryNumberInInteger(r[i].bits1);
            r[i].byte2 = convertBinaryNumberInInteger(r[i].bits2);
          }
          l=0;
          // transfere os dados para a matriz de entrada do round
          for(i = 0 ; i < 4 ; i++){
            for(j=0;j<4;j++){
              auxForByte = malloc(sizeof(char)*2);
              auxForByte[0] = r[l].byte1;
              auxForByte[1] = r[l].byte2;
              matrix[i][j] = auxForByte;
              l++;
            }
          }
      }
      c++;
  }
  printf("Seu texto cifrado e : \n");
  for(i = 0 ; i <4 ; i++){
    printf("%c",r[i].byte1);
    printf("%c",r[i].byte2);

    printf("%c",r[i+4].byte1);
    printf("%c",r[i+4].byte2);

    printf("%c",r[i+8].byte1);
    printf("%c",r[i+8].byte2);

    printf("%c",r[i+12].byte1);
    printf("%c",r[i+12].byte2);

  }
}

void convertMessageInBits(char *word,int *vetor,int counter){
    int *aux = malloc(sizeof(int)*8);
    int i=0;

    aux = convertWordLetterInBinary(word);
    for(i=0;i<8;i++){
      vetor[counter] = aux[i];
      counter++;
    }
    free(aux);

}

void decryptMessage() {
  int i , j ,k;
  int column=0 , row =0;
  char  * aux;
  Infos vetor[16];
  Infos resultsForInverse[16];
  int bitsForXor[128] , results[128] ;
  roundKey roundKey[11];
  Infos mixInverso[16];
  char auxMatrix0[2],auxMatrix1[2],auxMatrix2[2],auxMatrix3[2],auxMatrix4[2],auxMatrix5[2],auxMatrix6[2],auxMatrix7[2],auxMatrix8[2];
  char auxMatrix9[2],auxMatrix10[2],auxMatrix11[2],auxMatrix12[2],auxMatrix13[2],auxMatrix14[2],auxMatrix15[2];
  char * matrixAux [4][4];
  char * auxForByte;
  int l=0,c=0;

  generateRoundKeys(roundKey);

  char mensagem[32];
  printf("Insira a mensagem: " );
  scanf("%s", mensagem);

  snprintf (auxMatrix0,3, "%c%c",mensagem[0],mensagem[1]);
  snprintf (auxMatrix1,3, "%c%c",mensagem[2],mensagem[3]);
  snprintf (auxMatrix2,3, "%c%c",mensagem[4],mensagem[5]);
  snprintf (auxMatrix3,3, "%c%c",mensagem[6],mensagem[7]);
  snprintf (auxMatrix4,3, "%c%c",mensagem[8],mensagem[9]);
  snprintf (auxMatrix5,3, "%c%c",mensagem[10],mensagem[11]);
  snprintf (auxMatrix6,3, "%c%c",mensagem[12],mensagem[13]);
  snprintf (auxMatrix7,3, "%c%c",mensagem[14],mensagem[15]);
  snprintf (auxMatrix8,3, "%c%c",mensagem[16],mensagem[17]);
  snprintf (auxMatrix9,3, "%c%c",mensagem[18],mensagem[19]);
  snprintf (auxMatrix10,3, "%c%c",mensagem[20],mensagem[21]);
  snprintf (auxMatrix11,3, "%c%c",mensagem[22],mensagem[23]);
  snprintf (auxMatrix12,3, "%c%c",mensagem[24],mensagem[25]);
  snprintf (auxMatrix13,3, "%c%c",mensagem[26],mensagem[27]);
  snprintf (auxMatrix14,3, "%c%c",mensagem[28],mensagem[29]);
  snprintf (auxMatrix15,3, "%c%c",mensagem[30],mensagem[31]);

  char * matrix[4][4] = { auxMatrix0 , auxMatrix4 , auxMatrix8  , auxMatrix12,
                          auxMatrix1 , auxMatrix5 , auxMatrix9  , auxMatrix13,
                          auxMatrix2 , auxMatrix6 , auxMatrix10 , auxMatrix14,
                          auxMatrix3 , auxMatrix7 , auxMatrix11 , auxMatrix15};

  c = 10;
  k = 0;
  int vetorMessageBits[128];
  int counterMessageBits=0;

  for(i=0;i<4;i++){
      for(j=0;j<4;j++){
        convertMessageInBits(matrix[i][j],vetorMessageBits,counterMessageBits);
        counterMessageBits = counterMessageBits+8;
      }
  }

  while(c>=0){
    if(c == 10){

      xor(vetorMessageBits,roundKey[c].key,results);
              for(i=0;i<128;i++){

      }
      c--;
    }else{
        k=0;
        for(i = 0 ; i < 16 ; i++){
          for(j = 0 ; j <8 ; j++){
            vetor[i].bitsHexa[j] = results[k];
            k++;
          }
        }

        for(j = 0 ; j< 16 ; j++){
          for(i=0 ; i< 4 ; i++){
            vetor[j].bits1[i] = vetor[j].bitsHexa[i];
            vetor[j].bits2[i] = vetor[j].bitsHexa[i+4];

          }

            vetor[j].byte1 = convertBinaryNumberInInteger(vetor[j].bits1);
            vetor[j].byte2 = convertBinaryNumberInInteger(vetor[j].bits2);

        }

        k=0;
        for(i=0 ; i<4;i++){
          for(j =0 ; j< 4 ; j++){
            aux = malloc(sizeof(char)*2);
            aux[0] = vetor[k].byte1;
            aux[1] = vetor[k].byte2;

            matrixAux[i][j] = aux;

            k++;
          }
        }

        char*matrixInverseShiftRows[4][4] = {matrixAux[0][0],matrixAux[0][1],matrixAux[0][2],matrixAux[0][3],
                                             matrixAux[1][3],matrixAux[1][0],matrixAux[1][1],matrixAux[1][2],
                                             matrixAux[2][2],matrixAux[2][3],matrixAux[2][0],matrixAux[2][1],
                                             matrixAux[3][1],matrixAux[3][2],matrixAux[3][3],matrixAux[3][0]};


        k = 0;
        //executa o Inverse S Box;

        for(i = 0 ; i < 4 ; i++){
          for(j = 0 ; j < 4; j++){
              aux = (char*) malloc(sizeof(char)*2);
              aux = matrixInverseShiftRows[i][j];
              vetor[k].byte1 = aux[0];
              vetor[k].byte2 = aux[1];

              row = convertHexForDecimal(aux[0]);
              column = convertHexForDecimal(aux[1]);


              vetor[k].byteInt1 = row;
              vetor[k].byteInt2 = column;
              matrixAux[i][j] = InverseS_box(row,column);

              k++;
          }
        }
        //armazena os dados obtidos do inverse sub bytes
        k=0;
        for(i = 0 ; i< 4 ; i ++){
          for(j = 0 ; j<4 ; j++){
            aux = (char*) malloc(sizeof(char)*2);
            aux = matrixAux[i][j];
            vetor[k].byte1 = aux[0];
            vetor[k].byte2 = aux[1];
            k++;
          }
        }

        // transforma os bytes em bits
        passForBite(vetor);
        fillHexBits(vetor);
        k=0;
        // prepara os bits para fazer o xor com a chave do round
        for(j = 0 ; j< 16 ; j++){
          for(i=0 ; i< 8 ; i++){
          bitsForXor[k] = vetor[j].bitsHexa[i] ;
          k++;
          }
        }
          // executa o xor com a chave do round
          xor(bitsForXor,roundKey[c].key,results);
          k=0;
          for(i = 0 ; i < 16 ; i ++){
            for(j = 0 ; j< 8 ; j++){
              vetor[i].bitsHexa[j] = results[k];
              k++;
            }
          }

          k=0;
          if(c!=0){
            // executa o mixColumnTransformation Inverso
            inverseMixColumn(vetor,resultsForInverse);
            for(i = 0 ; i<16 ; i++){
              for( j = 0 ; j< 8 ; j++){
                results[k] = resultsForInverse[i].bitsHexa[j];
                k++;
              }
            }

          }else{
            k=0;
            for(i = 0 ; i<16 ; i++){
              for( j = 0 ; j< 8 ; j++){
                results[k] = vetor[i].bitsHexa[j];
                k++;
              }
            }

          }

        c--;
    }
  }

  int vetBits[4];
  char resultWord[32];
  int counter=0;
  int counterWord=0;

  for( i = 0 ; i< 128 ; i++){
    vetBits[counter]= results[i];
    counter++;
    if(counter==4){
      resultWord[counterWord] = convertBinaryNumberInInteger(vetBits);
      counterWord++;
      counter=0;
    }
  }

  printf("\n" );
  printf("Sua mensagem decifrada e: " );
  for(i=0;i<8;i=i+2){
    printf("%c",resultWord[i]);
    printf("%c",resultWord[i+1]);
    printf("%c",resultWord[i+8]);
    printf("%c",resultWord[i+9]);
    printf("%c",resultWord[i+16]);
    printf("%c",resultWord[i+17]);
    printf("%c",resultWord[i+24]);
    printf("%c",resultWord[i+25]);
  }
  printf("\n" );


}

int main() {
  int op=0;

  while (1) {
    printf("\n====== MENU ======\n");
    printf("1 Criptografa Mensagem\n" );
    printf("2 Descriptografa Mensagem\n" );
    printf("3 Sair\n" );
    printf("\n Opcao: " );
    scanf("%d",&op);

    switch (op) {
      case 1:
        encryptMessage();
        break;
      case 2:
        decryptMessage();
        break;
      case 3:
        return 0;
      default:
        printf("Insira uma opcao Valida" );
        break;
    }
  }

    return 0;
}
