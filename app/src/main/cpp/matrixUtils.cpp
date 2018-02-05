//
// Created by ariel on 04/02/18.
//

#include "matrixUtils.h"

void rotateX(float degrees, float *matrix4x4) {
    //matrix4x4[5] = cos(degrees);
    matrix4x4[6] = sin(degrees) * (-1.0f);
    matrix4x4[9] = sin(degrees);
    //matrix4x4[10] = cos(degrees);
}

void rotateY(float degrees, float *matrix4x4) {
    matrix4x4[0] = cos(degrees);
    //matrix4x4[2] = sin(degrees);
    //matrix4x4[8] = sin(degrees) * (-1.0f);
    matrix4x4[10] = cos(degrees);
}

void rotateZ(float degrees, float *matrix4x4) {
    matrix4x4[0] = cos(degrees);
    matrix4x4[1] = sin(degrees) * (-1.0f);
    matrix4x4[4] = sin(degrees);
    matrix4x4[5] = cos(degrees);
}