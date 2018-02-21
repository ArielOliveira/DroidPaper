//
// Created by ariel on 06/02/18.
//

#ifndef DROIDPAPER2_GEOMETRYTESTOBJECTS_H
#define DROIDPAPER2_GEOMETRYTESTOBJECTS_H

#include <GLES2/gl2.h>

float myTranslation1[] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f,};

float myTranslation2[] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f,};

float myTranslation3[] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f,};

float sky[] = {-1.0f, -1.0f,
               -1.0f,  1.0f,
                1.0f,  1.0f,
                1.0f, -1.0f,};

float skyColor[] = {0.022, 0.080, 0.080, 1.0f,
                    0.000, 0.749, 1.000, 1.0f,
                    0.000, 0.749, 1.000, 1.0f,
                    0.022, 0.080, 0.080, 1.0f,};

float ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f};

float color[] = {0.545, 0.271, 0.075, 1.0f,};

GLfloat cube[] = { -0.5f,  0.5f, -0.5f,
                   -0.5f,  0.5f, -0.5f,
                   0.5f, -0.5f, -0.5f,
                   0.5f, -0.5f, -0.5f,

                   0.5f, -0.5f, -1.0f,
                   0.5f,  0.5f, -1.0f,
                   -0.5f,  0.5f, -1.0f,
                   -0.5f, -0.5f, -1.0f,};

GLfloat square[] = {-0.5f, -0.5f,
                    -0.5f,  0.5f,
                     0.5f,  0.5f,
                     0.5f, -0.5f,};

GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
                                0.5f, -0.5f,};


GLushort triangleIndex[] = {0, 1, 2,};

GLushort cubeIndices[] = {0, 1, 2,  0, 2, 3,
                          0, 3, 4,  0, 4, 6,
                          0, 5, 6,  0, 6, 1,
                          7, 6, 1,  7, 1, 2,
                          7, 4, 5,  7, 5, 6,
                          7, 2, 3,  7, 3, 4,};

GLushort indices[] = {2, 1, 0, 2, 0, 3,};

#endif //DROIDPAPER2_GEOMETRYTESTOBJECTS_H
