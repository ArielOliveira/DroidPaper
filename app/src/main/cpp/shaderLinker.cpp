//
// Created by ariel on 20/11/17.
//

#include "stdlib.h"
#include "shaderLinker.h"

GLuint loadShader(const char *shaderSrc, GLenum type) {
     GLuint shader = glCreateShader(type);

    if (shader) {
        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);

        GLint compiled = 0;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            GLint infoLen = 0;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen > 1) {
                char *infoLog = new char[infoLen];

                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                LOGE("Could not compile shader %d:\n%s\n", type, infoLog);
                free(infoLog);

            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint init(const char* vShaderStr, const char* fShaderStr) {
    GLuint vertexShader = loadShader(vShaderStr, GL_VERTEX_SHADER);

    if (!vertexShader)
        return 0;

    GLuint fragmentShader = loadShader(fShaderStr, GL_FRAGMENT_SHADER);

    if (!fragmentShader)
        return 0;

    GLuint programObject = glCreateProgram();

    if (programObject) {
        glAttachShader(programObject, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(programObject, fragmentShader);
        checkGlError("glAttachShader");

        glLinkProgram(programObject);

        GLint linked = GL_FALSE;

        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
        if (linked != GL_TRUE) {
            GLint infoLen = 0;

            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen) {
                char *infoLog = new char[infoLen];
                if (infoLog) {
                    glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                    LOGE("Could not link program:\n%s\n", infoLog);
                    free(infoLog);
                }
            }
            glDeleteProgram(programObject);
            programObject = 0;
        }
    }
    return programObject;
}

