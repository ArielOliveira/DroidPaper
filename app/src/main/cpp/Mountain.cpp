//
// Created by ariel on 06/02/18.
//

#include "Mountain.h"
#include "GLBufferManager.h"
#include "logger.h"

float off = 0;

Mountain::Mountain(unsigned int _windowSize, unsigned int _length, float _mountainRoughness, float _scale, GLuint *ID):
        windowSize(_windowSize), length(_length), lastHeightMapped(-2), stride((_length/3)*4),
        mountainRoughness(_mountainRoughness), scale(_scale), MOUNTAIN_ID(ID) {

    bufferSize = length*4;
    offset = 0;
    verticesNumber = length*2;
    vertices = new GLfloat[bufferSize];

    shape(length);
    cache();

    delete vertices;
    vertices = new GLfloat[stride];
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
    glVertexAttribPointer(VERTEX_POSITION_INDX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, verticesNumber);
}

void Mountain::bind() {glBindBuffer(GL_ARRAY_BUFFER, *MOUNTAIN_ID);}

void Mountain::update() {
    shape(length/3, off);
    LOGI("First pair of vertices %f %f %f %f", vertices[0], vertices[1], vertices[2], vertices[3]);
    LOGI("Middle pair of vertices %f %f %f %f", vertices[(stride/2)-4], vertices[(stride/2)-3], vertices[(stride/2)-2], vertices[(stride/2)-1]);
    LOGI("Last pair of vertices %f %f %f %f", vertices[stride-4], vertices[stride-3], vertices[stride-2], vertices[stride-1]);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * offset, sizeof(GLfloat) * stride, vertices);

    offset += stride;
    off += 1.0f;
    if (offset >= bufferSize) {
        off = 0;
        offset = 0;
    }
}

void Mountain::shape(int _length, float offScreen) {
    setBorders(windowSize, _length, offScreen, vertices, 1.0f, mountainRoughness, scale, lastHeightMapped);
    lastHeightMapped = vertices[bufferSize-3];

}

float Mountain::getLast() {return lastHeightMapped;}


