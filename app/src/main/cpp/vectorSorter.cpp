#include "vectorSorter.h"
#include "randUtils.h"
#include "logger.h"

#define AVG2(a,b) ((a + b) / 2)

int _windowSize;
GLfloat _offScreen;

void makeMountain(int right, int left, GLfloat *vector, float roughness, float scale);

void setDisplacement(int right, int left, int middle, GLfloat *vector, float scale) {
    if (left == 0 || left == 1)
        left++;

    int problem = middle;
    //if (middle == 1)
       //problem++;

    vector[(problem*4)-4] = (((float) (middle) / (_windowSize / 2) - 1) + _offScreen);
    vector[(problem*4)-3] = AVG2(vector[(left*4)-3], vector[(right*4)-3]);
    vector[(problem*4)-3] += (randomizeFloat(2.0) * scale * 2) - scale;
    vector[(problem*4)-2] = (((float) (middle) / (_windowSize / 2) - 1) + _offScreen);
    vector[(problem*4)-1] = -1.0f;
}

void makeMountain(int right, int left, GLfloat *vector, float roughness, float scale) {
    if (right - left > 1 && right > 1) {
        int middle = AVG2(right, left);
        setDisplacement(right, left, middle, vector, scale);

        scale *= roughness;
        makeMountain(right, middle, vector, roughness, scale);

        scale *= roughness;
        makeMountain(middle, left, vector, roughness, scale);
    }
}

void setBorders(int windowSize, int width, GLfloat offScreen, float *vector, float height, float roughness, GLfloat *seed) {
    _windowSize = windowSize;
    _offScreen = offScreen;

    float scale = height / 8;

    vector[(width*4)-4] = (((float) width / (windowSize / 2) - 1) + offScreen);
    vector[(width*4)-3] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;
    vector[(width*4)-3] = vector[(width*4)-3] / (height / 2) - 1;
    vector[(width*4)-2] = (((float) width / (windowSize / 2) - 1) + offScreen);
    vector[(width*4)-1] = -1.0f;

    if (seed) {
        vector[0] = seed[0];
        vector[1] = seed[1];
        vector[2] = seed[2];
        vector[3] = seed[3];
    } else {
        vector[0] = (((float) 0 / (windowSize / 2) - 1) + offScreen);
        vector[1] = height / 2 + (randomizeFloat(2.0) * scale * 2) - scale;
        vector[2] = (((float) 0 / (windowSize / 2) - 1) + offScreen);
        vector[3] = -1.0f;
    }


    scale *= roughness;
    setDisplacement(width, 0, width/2, vector, scale);

    scale *= roughness;
    makeMountain(width/2, 0, vector, roughness, scale);

    scale *= roughness;
    makeMountain(width, width/2, vector, roughness, scale);
}
