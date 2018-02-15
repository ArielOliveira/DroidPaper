//
// Created by ariel on 20/11/17.
//

#ifndef DROIDPAPER2_SHADERLIB_H
#define DROIDPAPER2_SHADERLIB_H

const char vShaderStr[] =
        "attribute vec4 vPosition;                              \n"
        "uniform mat4 myTranslation;                            \n"
                "void main()                                    \n"
                "{                                              \n"
                "   gl_Position = vPosition * myTranslation;    \n"
                "}                                              \n";

const char fShaderStr[] =
        "precision mediump float;                               \n"
        "uniform lowp vec4 uniformColor;                             \n"
                "void main()                                    \n"
                "{                                              \n"
                "   gl_FragColor = uniformColor;                \n"
                "}                                              \n";

#endif //DROIDPAPER2_SHADERLIB_H
