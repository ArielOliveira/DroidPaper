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
        GLfloat *lastHeightMapped;

        float scale;
        float maxHeight;
        float off;
        float moved;
        float scrollSpeed;
        float mountainRoughness;
        float *translation;

        GLint *translationShader;

        unsigned int windowSize;
        unsigned int bufferSize;
        unsigned int length;
        unsigned int verticesNumber;

        unsigned int offset;
        unsigned int stride;

        GLuint *MOUNTAIN_ID;

        void seedVertice(unsigned int _length);
        void cache();
    public:

        Mountain(unsigned int _windowSize, unsigned int _length,
                 float _mountainRoughness, float _scrollSpeed, float _maxHeight,
                 GLint *_translationShader, GLuint *_ID);
        Mountain();
        ~Mountain();

        void setTranslationValueIndex(int index, float value);
        float getTranslationValueIndex(int index);

        void shape(unsigned int _length, float offScreen = 0);
        void bind();
        void update();
        void draw();

};


#endif //DROIDPAPER2_MOUNTAIN_H
