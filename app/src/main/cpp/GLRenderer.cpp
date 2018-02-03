//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

GLRenderer::GLRenderer(): display(0), surface(0), context(0),
                          width(0), height(0) {

}

GLRenderer::~GLRenderer() {
    destroy();
}

void GLRenderer::destroy() {}