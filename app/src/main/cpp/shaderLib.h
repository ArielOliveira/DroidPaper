//
// Created by ariel on 20/11/17.
//

#ifndef DROIDPAPER2_SHADERLIB_H
#define DROIDPAPER2_SHADERLIB_H

const char vShaderStr[] =
        "uniform mat4 myTranslation;                            \n"
        "attribute vec4 vPosition;                              \n"
        "attribute vec4 vColor;                                 \n"
        "varying vec4 out_color;                                \n"
                "void main()                                    \n"
                "{                                              \n"
                "   out_color = vColor;                         \n"
                "   gl_Position = vPosition * myTranslation;    \n"
                "}                                              \n";

const char fShaderStr[] =
        "precision mediump float;                               \n"
        "varying vec4 out_color;                                \n"
        "uniform vec4 ambient_color;                            \n"
                "void main()                                    \n"
                "{                                              \n"
                "   gl_FragColor = out_color * ambient_color;   \n"
                "}                                              \n";

#endif //DROIDPAPER2_SHADERLIB_H
