#include "method.h"
#include "function.h"

static __m256d k1[3];
static __m256d k2[3];
static __m256d k3[3];
static __m256d k4[3];

static __m256d vh;
static __m256d vh2;
static __m256d vh6;
static __m256d vc2;

static int pstat = 0;
static short order[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
static const char* format;

inline static void add(__m256d* res,const __m256d a[3], const __m256d b[3])
{
    res[0] = _mm256_add_pd(a[0],b[0]);
    res[1] = _mm256_add_pd(a[1],b[1]);
    res[2] = _mm256_add_pd(a[2],b[2]);
}

inline static void multiply(__m256d* res, const __m256d a[3], __m256d k)
{
    res[0] = _mm256_mul_pd(a[0],k);
    res[1] = _mm256_mul_pd(a[1],k);
    res[2] = _mm256_mul_pd(a[2],k);
}

inline static void makefunction(__m256d* res, const __m256d v[3])
{
    V(res,0) = FUNCTION_0(v);
    V(res,1) = FUNCTION_1(v);
    V(res,2) = FUNCTION_2(v);
    V(res,3) = FUNCTION_3(v);
    V(res,4) = FUNCTION_4(v);
    V(res,5) = FUNCTION_5(v);
    V(res,6) = FUNCTION_6(v);
    V(res,7) = FUNCTION_7(v);
    V(res,8) = FUNCTION_8(v);
    V(res,9) = FUNCTION_9(v);
    V(res,10) = FUNCTION_10(v);
    V(res,11) = FUNCTION_11(v);
}

inline static void prestep(__m256d* target)
{
    FUNCTION_PRE(target);
}

inline static void poststep(__m256d* target)
{
    FUNCTION_POST(target);
}

inline static void makestep(__m256d* res, const __m256d p[3])
{
    makefunction(k1,p);
    multiply(res,k1, vh2);
    add(res,res,p);
    makefunction(k2,res);
    multiply(res,k2, vh2);
    add(res,res,p);
    makefunction(k3,res);
    multiply(res,k3, vh);
    add(res,res,p);
    makefunction(k4,res);

    multiply(k2, k2, vc2);
    multiply(k3, k3, vc2);
    add(res,k1,k4);
    add(res,res,k2);
    add(res,res,k3);
    multiply(res,res,vh6);
    add(res,res,p);
}

inline static void print(const __m256d v[3], int number)
{
    printf(format,
        VR(order[0]),VR(order[1]),VR(order[2]),VR(order[3]),
        VR(order[4]),VR(order[5]),VR(order[6]),VR(order[7]),
        VR(order[8]),VR(order[9]),VR(order[10]),VR(order[11]));
}

inline static void write(FILE* fp, const __m256d v[3], int number)
{
    fprintf(fp,format,
        VR(order[0]),VR(order[1]),VR(order[2]),VR(order[3]),
        VR(order[4]),VR(order[5]),VR(order[6]),VR(order[7]),
        VR(order[8]),VR(order[9]),VR(order[10]),VR(order[11]));
}

void* progress()
{
    do
    {
        fflush(stdout);
        int n = pstat;
        printf("[");
        while(n--) printf("%%");
        n = 40 - pstat;
        while(n--) printf(" ");
        printf("] %d %%", (int)(pstat / 0.4));
        printf("\r");
    } 
    while(pstat < 40);

    pthread_exit(NULL);
}

void calculate(double hsize, unsigned int line, unsigned int steps, unsigned int offset, FILE* fp, unsigned short mask)
{
    //////////////////////////////////////////////////////////////
    //                      Output format                       //
    //////////////////////////////////////////////////////////////

    int argsnum = 0;
    int osi = -1;
    while(++osi < 12) argsnum += (mask >> osi & 1);

    switch (argsnum)
    {
        case 0: format = FORMAT_MASK_0; break;
        case 1: format = FORMAT_MASK_1; break;
        case 2: format = FORMAT_MASK_2; break;
        case 3: format = FORMAT_MASK_3; break;
        case 4: format = FORMAT_MASK_4; break;
        case 5: format = FORMAT_MASK_5; break;
        case 6: format = FORMAT_MASK_6; break;
        case 7: format = FORMAT_MASK_7; break;
        case 8: format = FORMAT_MASK_8; break;
        case 9: format = FORMAT_MASK_9; break;
        case 10: format = FORMAT_MASK_10; break;
        case 11: format = FORMAT_MASK_11; break;
        case 12: format = FORMAT_MASK_12; break;    
        default: format = FORMAT_MASK_0; break;
    }

    int odi = 0;
    while(--osi > -1) if(mask >> osi & 1) { order[odi] = 11 - osi; odi++; };

    //////////////////////////////////////////////////////////////
    //                 __m256d constants                        //
    //////////////////////////////////////////////////////////////

    vh = _mm256_set1_pd(hsize);
    vh2 = _mm256_set1_pd(hsize / 2);
    vh6 = _mm256_set1_pd(hsize / 6);
    vc2 = _mm256_set1_pd(2.0);

    //////////////////////////////////////////////////////////////
    //                 Generators settings                      //
    //////////////////////////////////////////////////////////////

    SET_POISSON_PARAM(mconsts.fin);
    SET_RAYLEIGHT_PARAM(mconsts.b0);
    setpparam(hsize);

    //////////////////////////////////////////////////////////////
    //                 Initial prarmeters                       //
    //////////////////////////////////////////////////////////////

    double initial[12] = { 0.0,0.0,0,0,0,0,0,0,0,0,0,0 };

    __m256d b2[3] = { _mm256_loadu_pd(initial), _mm256_loadu_pd(initial + 4), _mm256_loadu_pd(initial + 8) };
    __m256d b1[3];

    __m256d* active = b2;
    __m256d* passive = b1;
    __m256d* tmp;

    int n = 0;
    unsigned int total = line * steps + offset;

    //////////////////////////////////////////////////////////////
    //                          METHOD                          //
    //////////////////////////////////////////////////////////////

    int ii = offset + 1;
    while(--ii)
    {
        tmp = passive;
        passive = active;
        active = tmp;

        // passive --- ( +h ) ----> active
        prestep(passive);
        makestep(active,passive);
        poststep(active);

        ++n;
        pstat = (int)(40.0 * n / total);        
    }

    

    ++steps;
    while(--steps)
    {
        int ii = line + 1;
        while(--ii)
        {
            tmp = passive;
            passive = active;
            active = tmp;

            // passive --- ( +h ) ----> active
            prestep(passive);
            makestep(active,passive);
            poststep(active);
            ++n;
        }

        /* [ pregress bar ] *************/
        pstat = (int)(40.0 * n / total);
        
        /* [ output ] ******************/
        write(fp,active,n);
        //print(active,n);
    }
}
