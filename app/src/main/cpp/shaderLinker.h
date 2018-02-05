//
// Created by ariel on 04/02/18.
//

#ifndef DROIDPAPER2_SHADERLINKER_H
#define DROIDPAPER2_SHADERLINKER_H


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "logger.h"

GLuint init(const char* vShaderStr, const char* fShaderStr);
GLuint loadShader(const char *shaderSrc, GLenum type);

#endif //DROIDPAPER2_SHADERLINKER_H
