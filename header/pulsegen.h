
#ifndef __PULSEGEN_H__
#define __PULSEGEN_H__

#include "generator.h"

struct pulseparams {

    double step;
    double tj;
    double tau;

} pparams = { 0.01, 0.0, 1.0 };

inline void setpparam(double s)
{
    pparams.step = s;
}

inline double getipre(double t)
{
    // generate
    if(t > pparams.tj + pparams.tau)
    {
        pparams.tj += (pparams.tau + playpoisson());
    }
    //produce
    if(t >= pparams.tj && t <= pparams.tj + pparams.tau)
    {
        return 1;
    }
    return 0;

}


#endif
