//
// Created by ariel on 06/02/18.
//

#include "Mountain.h"
#include "GLBufferManager.h"
#include "logger.h"

Mountain::Mountain(unsigned int _length, float _mountainRoughness, float _scale, GLuint *ID):
        length(_length), lastHeightMapped(-2), stride((_length/3)*4),
        mountainRoughness(_mountainRoughness), scale(_scale), MOUNTAIN_ID(ID) {

    bufferSize = length*4;

    heightMap = new float[length];
    vertices = new GLfloat[bufferSize];

    LOGI("Mountain(%i)", _length);

    shape(length);
    cache();

    delete vertices;
    delete heightMap;

    vertices = new GLfloat[stride];
    heightMap = new GLfloat[length/3];
}

Mountain::~Mountain() {
    if (heightMap)
        delete heightMap;

    if (vertices)
        delete vertices;
}

void Mountain::cache() {
    cacheBufferByID(vertices, bufferSize, MOUNTAIN_ID, GL_DYNAMIC_DRAW);
}

void Mountain::draw() {
    GLuint offset = 0;

    glVertexAttribPointer(VERTEX_POSITION_INDX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, length*2);
}

void Mountain::bind() {glBindBuffer(GL_ARRAY_BUFFER, *MOUNTAIN_ID);}

void Mountain::update() {
    glBufferSubData(*MOUNTAIN_ID, offset, sizeof(vertices) * stride, vertices);
    offset += stride;
    if (offset >= length*2)
        offset = 0;
}

void Mountain::shape(int _length, float offScreen) {
    setBorders(_length, heightMap, 1.0f, mountainRoughness, scale, lastHeightMapped);
    LOGI("SetBorders(%i, heightMap, 1.0f, %f, %f, %f)", _length, mountainRoughness, scale, lastHeightMapped);
    lastHeightMapped = heightMap[_length-1];

    int index = 0;

    for (int i = 0; i < bufferSize; i += 4) {
        vertices[i] = (((float) (index - 0) / (length / 2) - 1) + offScreen);
        vertices[i + 1] = heightMap[index];
        vertices[i + 2] = (((float) (index - 0) / (length / 2) - 1) + offScreen);
        vertices[i + 3] = -1.0f;
        index++;
    }
}

float Mountain::getLast() {return lastHeightMapped;}


