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

        float off;
        float mountainRoughness;
        float moved;
        float scrollSpeed;
        float *translation;

        int bufferSize;
        int length;
        int verticesNumber;

        int offset;
        int stride;

        bool dirty;

        GLuint *MOUNTAIN_ID;

        void seedVertice(int _length);
        void cache();
    public:

        Mountain(int _windowSize, int _length, float _mountainRoughness, float _scrollSpeed, GLuint *_ID);
        Mountain();
        ~Mountain();

        void setTranslationValueIndex(int index, float value);
        float getTranslationValueIndex(int index);

        void bind();
        void shape(int _windowSize, int _length, float offScreen = 0);
        void update(int _windowSize);
        void draw(GLint &uniform4);

        bool isDirty();

};


#endif //DROIDPAPER2_MOUNTAIN_H
