//
// Created by ariel on 03/02/18.
//

#ifndef DROIDPAPER2_EGLSURFACEMANAGER_H
#define DROIDPAPER2_EGLSURFACEMANAGER_H

#include <EGL/egl.h>
#include <android/native_window.h>

#include "logger.h"

class EGLSurfaceManager {
    private:
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
        EGLint width;
        EGLint height;

        bool hasSurfaceV;

    public:
        EGLSurfaceManager(ANativeWindow *window);
        EGLSurfaceManager();
        ~EGLSurfaceManager();

        EGLDisplay getDisplay();
        EGLSurface getSurface();
        EGLContext getContext();

        EGLint getWidth();
        EGLint getHeight();

        bool hasSurface();

        void swapBuffers();
};


#endif //DROIDPAPER2_EGLSURFACE_H
