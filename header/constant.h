
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <stdio.h>

// 4 + 4 + 3 + 2 + 3 + 3 + 1 + 3 = 23

struct cstorage {

    double ax;
    double ag;
    double ai;
    double ad;

    double k0;
    double kg;
    double kx;
    double kd;

    double thg;
    double thx;
    double thd;

    double gammag;
    double gammad;

    double gna;
    double gk;
    double gl;

    double ENa;
    double Ek;
    double El;

    double Ith;

    double fin;
    double b0;
    double C;

    // inner
    double A;
    double ipre;

} mconsts;

void loadconsts(FILE* file);
void testconsts();

#endif /* __CONSTANTS_H__ */
