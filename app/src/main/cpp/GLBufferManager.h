//
// Created by ariel on 06/02/18.
//

#ifndef DROIDPAPER2_GLBUFFERMANAGER_H
#define DROIDPAPER2_GLBUFFERMANAGER_H

#include <GLES2/gl2.h>
void cacheBufferByID(GLfloat *verticesData, GLuint verticesNumber, GLuint id, GLenum hint);
void updateBufferByID();
void bindBuffer(GLuint *id);


#endif //DROIDPAPER2_GLBUFFERMANAGER_H
