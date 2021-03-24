
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <immintrin.h>
#include "generator.h"
#include "constant.h"
#include "pulsegen.h"

#define V(vector,number) vector[number / 4][number % 4] 
#define VR(number) v[number / 4][number % 4]

#define USE_SHORTCASTS
#ifdef USE_SHORTCASTS

    ////////////////////_______VECTOR_______///////////////
    //     [ t, X, Yg, Iepscs, Yd, V, n, m, h, ipre ]    //
    //     [ 0, 1,  2,      3,  4, 5, 6, 7, 8,    9 ]    //
    ///////////////////////////////////////////////////////

    #define VAR_T VR(0)
    #define VAR_X VR(1)
    #define VAR_Yg VR(2)
    #define VAR_Iepscs VR(3)
    #define VAR_Yd VR(4)
    #define VAR_V VR(5)
    #define VAR_n VR(6)
    #define VAR_m VR(7)
    #define VAR_h VR(8)
    #define VAR_A mconsts.A
    #define VAR_Ipre mconsts.ipre
    
    #define LOC_Ipre 9

#endif

#define CALC_FUNC(number) inline double FUNCTION_##number(const __m256d v[3])
#define SERV_FUNC(number) inline void FUNCTION_##number(__m256d v[3])

///////////////////////////////////////////////////////
//                   service functions               //
///////////////////////////////////////////////////////

SERV_FUNC(PRE)
{
    // triggers rayleight b0 param changing
    SET_RAYLEIGHT_PARAM(mconsts.b0 * (1 + mconsts.gammad * VAR_Yd));
    VAR_A = playrayleight();
    // trigers ipre generator
    VAR_Ipre = getipre(VAR_T);
    
}
SERV_FUNC(POST)
{
    VR(LOC_Ipre) = VAR_Ipre;
    VR(10) = VAR_A;
}


///////////////////////////////////////////////////////
//                   other functions                 //
///////////////////////////////////////////////////////

CALC_FUNC(Iion)
{   
    // Ina + Ik + Il
    return
        mconsts.gna * pow(VAR_m,3) * VAR_h * (VAR_V - mconsts.ENa) 
        + mconsts.gk * pow(VAR_n,4) * (VAR_V - mconsts.Ek) 
        + mconsts.gl * (VAR_V - mconsts.El);
}

inline double H(double x)
{
    return (1 + (x > 0) - (x < 0)) / 2;
}

///////////////////////////////////////////////////////
//                   main functions                  //
///////////////////////////////////////////////////////

CALC_FUNC(0) 
{ 
    return 1; 
}
CALC_FUNC(1) // DXDT
{
    return -mconsts.ax * (VAR_X - mconsts.k0 * (1 + mconsts.gammag * VAR_Yg) * H(VAR_Ipre - 0.5));
}
CALC_FUNC(2) // DYgDT
{
    return -mconsts.ag * (VAR_Yg - pow(1 + exp(-(VAR_X-mconsts.thg)/mconsts.kg),-1));
}
CALC_FUNC(3) // DIepscsDT
{
    return -mconsts.ai * (VAR_Iepscs + VAR_A * H(VAR_Ipre - 0.5));
}
CALC_FUNC(4) // DYdDT
{
    return -mconsts.ad * (VAR_Yd - pow(1 + exp(-(VAR_X-mconsts.thd)/mconsts.kd),-1));
}
CALC_FUNC(5) //DVDT
{
    return (1/mconsts.C) * (mconsts.Ith - FUNCTION_Iion(v) - VAR_Iepscs * pow(1 + exp(-(VAR_X - mconsts.thx)/mconsts.kx),-1));
}
CALC_FUNC(6) // DNiDT
{ 
    return
        ((0.01 * (VAR_V + 55)) / (1 - exp(0.1 * (-55 - VAR_V)))) * (1 - VAR_n)
        - 0.125 * exp((-VAR_V - 65) / 80) * VAR_n;
}
CALC_FUNC(7) // DMiDT 
{  
    return
        ((0.1 * (VAR_V + 40)) / (1 - exp(0.1 * (-40 - VAR_V)))) * (1 - VAR_m)
        - 4 * exp((-VAR_V - 65)/ 18) * VAR_m;
}
CALC_FUNC(8)  // DHiDT
{ 
    return  
        (0.07 * exp(0.05 * (-VAR_V - 65))) * (1 - VAR_h)
        - pow(1 + exp(0.1*(-35-VAR_V)),-1) * VAR_h;

}
CALC_FUNC(9) { return 0; }
CALC_FUNC(10) { return 0; }
CALC_FUNC(11) { return 0; }

#endif
