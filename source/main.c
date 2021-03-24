#include "method.h"
#include <time.h>
#include "constant.h"

const int optionsize = 2;
const char* OPTIONS[] = { "Output file", "Input consts file" };

int main(int argc, char** argv)
{
    FILE* file;
    const char* filename;
    if(argc > 1) filename = argv[1];
    else filename = DEFAULT_OUTPUT_NAME;
    file = fopen(filename,"w");

    FILE* input;
    const char* inputname;
    if(argc > 2) inputname = argv[2];
    else inputname = DEFAULT_INPUT_NAME;
    input = fopen(inputname,"r");

    printf("\n[ ---------------{ %s }--------------- ]\n\n","PROC");

    if(argc > 1)
    {
        printf("__ARGS____________________________________\n");
        int ii = 0;
        while(++ii < argc && ii < optionsize + 1) printf("\n%s = %s",OPTIONS[ii - 1],argv[ii]);
    }

    loadconsts(input);
    testconsts();

    printf("\n__________________________________________\n\n");

    pthread_t id;
    pthread_create(&id, NULL, progress, NULL);
    clock_t start = clock();
    calculate(0.01,25,10000,file,0x0FFF);
    clock_t end = clock();
    pthread_join(id, NULL);
    clock_t close = clock();

    double time = ((double)(end - start)/CLOCKS_PER_SEC);
    double waited = ((double)(close - end)/CLOCKS_PER_SEC);
    printf("\n\n__STATS___________________________________\n");
    printf("\nTime: %.4f seconds",time);
    printf("\nOutput: %s",filename);
    printf("\n__________________________________________");

    fclose(file);
    fclose(input);

    printf("\n\n");
    return 0;
}
