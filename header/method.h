
#ifndef __METHOD_H__
#define __METHOD_H__

#define DEFAULT_OUTPUT_NAME "./res.csv"
#define DEFAULT_INPUT_NAME "./consts.bin"
#define DEFAULT_MASK 0x0FFF
#define DEFAULT_STEP 0.01
#define DEFAULT_OFFSET 0
#define DEFAULT_LINE 25
#define DEFAULT_LENGTH 40000

#define FORMAT_MASK_0 ""
#define FORMAT_MASK_1 "%.4f\n"
#define FORMAT_MASK_2 "%.4f, %.4f\n"
#define FORMAT_MASK_3 "%.4f, %.4f, %.4f\n"
#define FORMAT_MASK_4 "%.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_5 "%.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_6 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_7 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_8 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_9 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_10 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_11 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"
#define FORMAT_MASK_12 "%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n"

#include <stdio.h>
#include <immintrin.h>
#include <pthread.h>

void calculate(double h, unsigned int line, unsigned int steps, unsigned int offset, FILE* fp, unsigned short mask);
void* progress();

#endif
