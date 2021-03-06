//
// Created by ariel on 02/02/18.
//

#include "logger.h"


void printGLString(const char *name, GLenum s) {
    const char *v = (const char*) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void checkGlError(const char* op) {
    for (int error = glGetError(); error; error = glGetError()) {
        LOGI("after %s () glError (0x%x)\n", op, error);
    }
}


