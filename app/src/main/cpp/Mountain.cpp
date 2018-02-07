//
// Created by ariel on 06/02/18.
//

#include "Mountain.h"

Mountain::Mountain(unsigned int _length, float _mountainRoughness, float _scale): DRAW_HINT(GL_DYNAMIC_DRAW),
                                                                                  length(_length),
                                                                                  mountainRoughness(_mountainRoughness),
                                                                                  scale(_scale) {
    heightMap = new float[length];

    vertices = new GLfloat[length*2];

}

Mountain::Mountain(): DRAW_HINT(GL_DYNAMIC_DRAW) {}

Mountain::~Mountain() {
    if (heightMap)
        delete heightMap;

    if (vertices)
        delete vertices;

    glDeleteBuffers(1, MOUNTAIN_ID);
}

void Mountain::bindMountain() {glBindBuffer(1, *MOUNTAIN_ID);}

bool Mountain::shapeMountain() {
    if (vertices) {
        setBorders(length, heightMap, 1.0f, mountainRoughness, scale);

        lastHeightMapped = heightMap[length-1];

        int index = 0;

        for (int i = 0; i < length*2; i += 4) {
            vertices[i] = (float)(index-0)/(length/2)-1;
            vertices[i+1] = heightMap[index];
            vertices[i+2] = (float)(index - 0)/(length/2)-1;
            vertices[i+3] = -1.0f;
            index++;
        }
        return true;
    }
    return false;
}

float Mountain::getLast() {return lastHeightMapped;}


