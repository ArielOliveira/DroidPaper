#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vectorSorter.h"

#define AVG2(a,b) ((a + b) / 2)

int _windowSize;
int totalWidth;
int offScreen;

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
    vector[(middle*4)-4] = (((float) (middle - 0) / (_windowSize / 2) - 1.0f) + offScreen);
    vector[(middle*4)-3] = AVG2(vector[(left*4)-3], vector[(right*4)-3]);
    vector[(middle*4)-3] += (randomizeFloat(1.0) * scale * 2) - scale;
    vector[(middle*4)-2] = (((float) (middle - 0) / (_windowSize / 2) - 1.0f) + offScreen);
    vector[(middle*4)-1] = -1.0f;
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

void setBorders(int windowSize, int width, int offScreen, float *vector, float height, float roughness, float scale, float seed) {
    totalWidth = width;
    _windowSize = windowSize;

    // X,Y X,Y
    vector[(width*4)-4] = (((float) (width - 0) / (windowSize / 2) - 1.0f) + offScreen);
    vector[(width*4)-3] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;
    vector[(width*4)-2] = (((float) (width - 0) / (windowSize / 2) - 1.0f) + offScreen);
    vector[(width*4)-1] = -1.0f;

    vector[0] = -1.0f + offScreen;
    if (seed == -2) vector[1] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;
    else vector[1] = seed;

    vector[2] = -1.0f + offScreen;
    vector[3] = -1.0f;

    scale *= roughness;
    setDisplacement(width-1, 0, width / 2, vector, scale);

    scale *= roughness;
    makeMountain(width / 2, 0, vector, roughness, scale);

    scale *= roughness;
    makeMountain(width-1, width / 2, vector, roughness, scale);
}
