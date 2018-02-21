//
// Created by ariel on 19/02/18.
//

#ifndef DROIDPAPER2_RANDUTILS_H
#define DROIDPAPER2_RANDUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randomizeFloat(float max) {
    float randomN;
    randomN = ((float)rand()/(float)(RAND_MAX) * max);
    return randomN;
}

void initRand() {
    srand(time(NULL));
}

#endif //DROIDPAPER2_RANDUTILS_H
