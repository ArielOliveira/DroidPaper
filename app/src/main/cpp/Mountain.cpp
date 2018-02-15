//
// Created by ariel on 06/02/18.
//

#include "Mountain.h"
#include "GLBufferManager.h"
#include "logger.h"

Mountain::Mountain(unsigned int _windowSize, unsigned int _length, float _mountainRoughness, float _scrollSpeed, float _maxHeight, GLint *_translationShader, GLuint *ID):
        windowSize(_windowSize), length(_length), stride((_length/3)*4),
        mountainRoughness(_mountainRoughness), scrollSpeed(_scrollSpeed),  maxHeight(_maxHeight),
        scale(_maxHeight/4), translationShader(_translationShader), MOUNTAIN_ID(ID) {

    bufferSize = length*4;
    offset = 0;
    verticesNumber = length*2;
    vertices = new GLfloat[bufferSize];
    lastHeightMapped = 0;

    moved = 0;

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

    off = 3.0f;

    //initRand();
    shape(length);
    lastHeightMapped = new GLfloat[4];
    seedVertice(length);

    cache();

    delete vertices;
    vertices = new GLfloat[stride];
    scale /= 3;

}

Mountain::~Mountain() {
    delete vertices;
    delete lastHeightMapped;
    delete translation;
}

void Mountain::cache() {
    cacheBufferByID(vertices, bufferSize, MOUNTAIN_ID, GL_DYNAMIC_DRAW);
}

void Mountain::draw() {
    if (moved <= -1.0f) {
        update();
        moved = 0;
    }

    glUniformMatrix4fv(*translationShader, 1, GL_FALSE, translation);

    moved -= scrollSpeed;
    bind();
    translation[3] -= scrollSpeed;
    glVertexAttribPointer(VERTEX_POSITION_INDX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, verticesNumber);
}

void Mountain::bind() {glBindBuffer(GL_ARRAY_BUFFER, *MOUNTAIN_ID);}

void Mountain::update() {
    unsigned int updateSize = length/3;
    shape(updateSize, off);
    seedVertice(updateSize);
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * offset, sizeof(GLfloat) * stride, vertices);

    offset += stride;
    off += 1.0f;
    if (offset >= bufferSize) {
        offset = 0;
    }
}

void Mountain::seedVertice(unsigned int _length) {
    lastHeightMapped[0] = vertices[(_length*4)-4];
    lastHeightMapped[1] = vertices[(_length*4)-3];
    lastHeightMapped[2] = vertices[(_length*4)-2];
    lastHeightMapped[3] = vertices[(_length*4)-1];
}

void Mountain::shape(unsigned int _length, float offScreen) {
    setBorders(windowSize, _length, offScreen, vertices, maxHeight, mountainRoughness, scale, lastHeightMapped);
}

void Mountain::setTranslationValueIndex(int index, float value) {translation[index] = value;}


