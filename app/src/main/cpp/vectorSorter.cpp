#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vectorSorter.h"

#define AVG2(a,b) ((a + b) / 2)

void makeMountain(int right, int left, float *vector, float roughness, float scale);

float randomizeFloat(float max) {
    float randomN;
    randomN = ((float)rand()/(float)(RAND_MAX) * max);
    return randomN-1.0;
}

void setVector(float *vector, int size) {
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++) {
        vector[i] = 0;
    }
}

void setDisplacement(int right, int left, int middle, float *vector, float scale) {

    vector[middle] = AVG2(vector[left], vector[right]);
    vector[middle] += (randomizeFloat(1.0) * scale * 2) - scale;

}

void makeMountain(int right, int left, float *vector, float roughness, float scale) {
    if (right - left > 1 && right > 1) {
        int middle = AVG2(right, left);
        setDisplacement(right, left, middle, vector, scale);

        scale *= roughness;
        makeMountain(right, middle, vector, roughness, scale);

        scale *= roughness;
        makeMountain(middle, left, vector, roughness, scale);
    }
}

void setBorders(int width, float *vector, float height, float roughness, float scale, float seed) {
    vector[width-1] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;

    if (seed == -2) vector[0] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;
    else vector[0] = seed;

    scale *= roughness;
    setDisplacement(width-1, 0, width / 2, vector, scale);

    scale *= roughness;
    makeMountain(width / 2, 0, vector, roughness, scale);

    scale *= roughness;
    makeMountain(width-1, width / 2, vector, roughness, scale);
}
