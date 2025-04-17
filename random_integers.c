#include <time.h>
#include <stdlib.h>
#include <limits.h>

void initiate_randomness(void)
{
    time_t t = time(NULL);
    srand((unsigned int)(t % (time_t)UINT_MAX));
}

int generate_random_number(void)
{
#ifndef INITIATED_RANDOMNESS
    initiate_randomness();
#define INITIATED_RANDOMNESS
#endif
    int r = rand();
    return r;
}

int generateLimitedRandomNumber(int limit)
{
    int divisor = RAND_MAX / (limit + 1);
    int number = 0;
    do
    {
        number = rand() / divisor;
    } while (number > limit);
    return number;
}
