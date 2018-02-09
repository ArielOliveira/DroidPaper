//
// Created by ariel on 06/02/18.
//

#ifndef DROIDPAPER2_MOUNTAIN_H
#define DROIDPAPER2_MOUNTAIN_H

#include <GLES2/gl2.h>
#include "vectorSorter.h"

class Mountain {
    private:
        GLfloat *vertices;

        unsigned int bufferSize;
        unsigned int length;

        float *heightMap;
        float scale;
        float mountainRoughness;
        float lastHeightMapped;

        GLintptr offset;

        const int stride;

        //GLenum DRAW_HINT;

        GLuint *MOUNTAIN_ID;

        void cache();
    public:

        Mountain(unsigned int _length, float _mountainRoughness, float _scale, GLuint *_ID);
        Mountain();
        ~Mountain();

        void shape(int _length, float offScreen = 0.0f);
        void bind();
        void update();
        void draw();

        float getLast();
};


#endif //DROIDPAPER2_MOUNTAIN_H
