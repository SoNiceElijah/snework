
#include "constant.h"

void loadconsts(FILE* file) 
{
    double numbers[23];
    size_t result = fread(numbers,8,23,file);

    mconsts.ax      = numbers[ 0];
    mconsts.ag      = numbers[ 1];
    mconsts.ai      = numbers[ 2];
    mconsts.ad      = numbers[ 3];

    mconsts.k0      = numbers[ 4];
    mconsts.kg      = numbers[ 5];
    mconsts.kx      = numbers[ 6];
    mconsts.kd      = numbers[ 7];

    mconsts.thg     = numbers[ 8];
    mconsts.thx     = numbers[ 9];
    mconsts.thd     = numbers[10];

    mconsts.gammag  = numbers[11];
    mconsts.gammad  = numbers[12];

    mconsts.gna     = numbers[13];
    mconsts.gk      = numbers[14];
    mconsts.gl      = numbers[15];

    mconsts.ENa     = numbers[16];
    mconsts.Ek      = numbers[17];
    mconsts.El      = numbers[18];

    mconsts.Ith     = numbers[19];

    mconsts.fin     = numbers[20];
    mconsts.b0      = numbers[21];
    mconsts.C       = numbers[22];
}

void testconsts()
{
    printf("\n\n__CONSTS__________________________________\n");

    printf("\nax \t= %.4f\n",mconsts.ax);
    printf("ag \t= %.4f\n",mconsts.ag); 
    printf("ai \t= %.4f\n",mconsts.ai); 
    printf("ad \t= %.4f\n",mconsts.ad); 
 
    printf("\nk0 \t= %.4f\n",mconsts.k0); 
    printf("kg \t= %.4f\n",mconsts.kg); 
    printf("kx \t= %.4f\n",mconsts.kx); 
    printf("kd \t= %.4f\n",mconsts.kd); 
 
    printf("\nthg \t= %.4f\n",mconsts.thg); 
    printf("thx \t= %.4f\n",mconsts.thx); 
    printf("thd \t= %.4f\n",mconsts.thd); 
 
    printf("\ngammag \t= %.4f\n",mconsts.gammag); 
    printf("gammad \t= %.4f\n",mconsts.gammad); 
 
    printf("\ngna \t= %.4f\n",mconsts.gna); 
    printf("gk \t= %.4f\n",mconsts.gk); 
    printf("gl \t= %.4f\n",mconsts.gl); 
 
    printf("\nENa \t= %.4f\n",mconsts.ENa); 
    printf("Ek \t= %.4f\n",mconsts.Ek); 
    printf("El \t= %.4f\n",mconsts.El); 
 
    printf("\nIth \t= %.4f\n",mconsts.Ith); 
 
    printf("\nfin \t= %.4f\n",mconsts.fin); 
    printf("b0 \t= %.4f\n",mconsts.b0); 
    printf("C \t= %.4f\n",mconsts.C); 
}
