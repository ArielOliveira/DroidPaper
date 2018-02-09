//
// Created by ariel on 06/02/18.
//

#include "GLBufferManager.h"

void cacheBufferByID(GLfloat *bufferData, int bufferSize, GLuint *id, GLenum hint) {
    glBindBuffer(GL_ARRAY_BUFFER, *id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * bufferSize, bufferData, hint);
}

void cacheIndiceByID(GLushort *indicesData, int indicesNumber, GLuint *id, GLenum hint) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesNumber, indicesData, hint);
}

void updateBufferByID() {}