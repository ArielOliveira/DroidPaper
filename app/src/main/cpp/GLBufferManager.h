//
// Created by ariel on 06/02/18.
//

#ifndef DROIDPAPER2_GLBUFFERMANAGER_H
#define DROIDPAPER2_GLBUFFERMANAGER_H

#include <GLES2/gl2.h>

const float NDC = 1.0f;

const GLuint VERTEX_POSITION_INDX = 0;
const GLuint VERTEX_COLOR_INDX = 1;
const GLuint VERTEX_POSITION_SIZE = 2;

void cacheBufferByID(GLfloat *bufferData, int bufferSize, GLuint *id, GLenum hint);
void cacheIndiceByID(GLushort *indicesData, int indicesNumber, GLuint *id, GLenum hint);

#endif //DROIDPAPER2_GLBUFFERMANAGER_H
