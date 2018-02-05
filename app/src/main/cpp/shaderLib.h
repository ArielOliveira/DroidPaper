//
// Created by ariel on 20/11/17.
//

#ifndef DROIDPAPER2_SHADERLIB_H
#define DROIDPAPER2_SHADERLIB_H

const char vShaderStr[] =
        "attribute vec4 vPosition;              \n"
        "uniform mat4 myTranslation;            \n"
                "void main()                    \n"
                "{                              \n"
                "   gl_Position = vPosition * myTranslation;    \n"
                "}                              \n";

const char fShaderStr[] =
        "precision mediump float;                       \n"
                "void main()                                    \n"
                "{                                              \n"
                "   gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);    \n"
                "}                                              \n";

#endif //DROIDPAPER2_SHADERLIB_H
