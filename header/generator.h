
#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <math.h>
#include <stdlib.h>

double genparamb;
double genparaml;

//////////////////////////////////////////////////////////////
//                      Destributions                       //
//////////////////////////////////////////////////////////////

double poisson(int k) 
{
    int ii = k + 1;
    int fact = 1.0;
    while(--ii) fact *= ii;

    return (pow(genparaml,k) / fact) * exp(-genparaml);
}
inline double rayleight(double x) 
{
    return (2 * x) / (genparamb * genparamb) * exp(-((x*x)/(genparamb*genparamb))); 
}

//////////////////////////////////////////////////////////////
//                      Generators                          //
//////////////////////////////////////////////////////////////

double playpoisson() 
{ 
    int k = 0;

    double left = 0;
    double right = left + poisson(k);

    double x = rand() * 1.0 / RAND_MAX;
    while(left < x)
    {
        ++k;
        left = right;
        right = left + poisson(k);
    }

    return k-1;
}
inline double playrayleight() 
{
    return sqrt(-genparamb*genparamb * log(1 - rand() * 1.0 / RAND_MAX)); 
}

//////////////////////////////////////////////////////////////
//                      Settters                            //
//////////////////////////////////////////////////////////////

#define SET_RAYLEIGHT_PARAM(param) genparamb = param
#define SET_POISSON_PARAM(param) genparaml = param

#endif /* __GENERATOR_H__ */
