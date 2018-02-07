//
// Created by ariel on 06/02/18.
//

#include "GLBufferManager.h"

void cacheBufferByID(GLfloat *verticesData, GLuint verticesNumber, GLuint id, GLenum hint) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesNumber, verticesData, hint);
}

void updateBufferByID() {}