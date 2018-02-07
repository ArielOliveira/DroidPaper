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
        unsigned int length;

        float *heightMap;
        float scale;
        float mountainRoughness;
        float lastHeightMapped;

        const GLenum DRAW_HINT;
        const GLuint *MOUNTAIN_ID;

    public:
        Mountain(unsigned int _length, float _mountainRoughness, float _scale);
        Mountain();
        ~Mountain();

        bool shapeMountain();
        void bindMountain();

        float getLast();

};


#endif //DROIDPAPER2_MOUNTAIN_H
