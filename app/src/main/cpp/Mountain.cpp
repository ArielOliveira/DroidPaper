//
// Created by ariel on 06/02/18.
//

#include "Mountain.h"
#include "GLBufferManager.h"
#include "logger.h"

const float color[] = {1.0f, 1.0f, 0.0f, 1.0};

Mountain::Mountain(int _windowSize, int _length, float _mountainRoughness, float _scrollSpeed, GLuint *ID):
        length(_length), stride((_length/3)*4),
        mountainRoughness(_mountainRoughness), scrollSpeed(_scrollSpeed), MOUNTAIN_ID(ID) {

    dirty = false;

    bufferSize = length*4;

    lastHeightMapped = new GLfloat[4];
    vertices = new GLfloat[bufferSize];
    translation = new float[16];

    translation[0] = 1.0f;
    translation[1] = 0.0f;
    translation[2] = 0.0f;
    translation[3] = 0.0f;

    translation[4] = 0.0f;
    translation[5] = 1.0f;
    translation[6] = 0.0f;
    translation[7] = 0.0f;

    translation[8] = 0.0f;
    translation[9] = 0.0f;
    translation[10] = 1.0f;
    translation[11] = 0.0f;

    translation[12] = 0.0f;
    translation[13] = 0.0f;
    translation[14] = 0.0f;
    translation[15] = 1.0f;

    verticesNumber = length*2;

    moved = 0;
    offset = 0;
    off = 3.0f;

    if (_windowSize) {
        shape(_windowSize, _length);
        seedVertice(_length);
        cache();

        delete vertices;
        vertices = new GLfloat[bufferSize/3];
    }

}

Mountain::Mountain() {}

Mountain::~Mountain() {
    delete vertices;
    delete lastHeightMapped;
    delete translation;
}

void Mountain::cache() {
    cacheBufferByID(vertices, bufferSize, MOUNTAIN_ID, GL_DYNAMIC_DRAW);
}

void Mountain::draw(GLint &uniform4) {
    if (moved <= -1.0f) {
        dirty = true;
        moved = 0;
    }

    glUniformMatrix4fv(uniform4, 1, GL_FALSE, translation);

    moved -= scrollSpeed;
    translation[3] -= scrollSpeed;
    glVertexAttribPointer(VERTEX_POSITION_INDX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_LINES, 0, verticesNumber);
}

void Mountain::bind() {glBindBuffer(GL_ARRAY_BUFFER, *MOUNTAIN_ID);}

void Mountain::update(int _windowSize) {
    shape(_windowSize, length/3, off);
    seedVertice(length/3);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * offset, sizeof(GLfloat) * stride, vertices);

    offset += stride;
    off += 1.0f;
    if (offset >= bufferSize) {
        offset = 0;
    }

    dirty = false;
}

void Mountain::seedVertice(int _length) {
    lastHeightMapped[0] = vertices[(_length*4)-4];
    lastHeightMapped[1] = vertices[(_length*4)-3];
    lastHeightMapped[2] = vertices[(_length*4)-2];
    lastHeightMapped[3] = vertices[(_length*4)-1];
}

void Mountain::shape(int _windowSize, int _length, float offScreen) {
    setBorders(_windowSize, _length, offScreen, vertices, NDC, mountainRoughness, lastHeightMapped);
}

void Mountain::setTranslationValueIndex(int index, float value) {translation[index] = value;}

float Mountain::getTranslationValueIndex(int index) {return translation[index];}

bool Mountain::isDirty() {return dirty;}



