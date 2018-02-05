//
// Created by ariel on 03/02/18.
//

#include "EGLSurfaceManager.h"

EGLSurfaceManager::EGLSurfaceManager(ANativeWindow *window) {
    const EGLint windowAttribList[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    const EGLint surfaceAttribList[] = {
            EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
            EGL_NONE
    };

    const EGLint contextAttribList[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    EGLConfig config;
    EGLint numConfigs;
    EGLint format;

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOGE("eglGetDisplay() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    if (!eglInitialize(display, 0, 0)) {
        LOGE("eglInitialize() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    if (!eglChooseConfig(display, windowAttribList, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }
/*
    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOGE("eglGetConfigAttrib() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }
*/
    //ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, window, surfaceAttribList))) {
        LOGE("eglCreateWindowSurface() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    if (!(context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribList))) {
        LOGE("eglCreateContext() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    if (!eglMakeCurrent(display, surface, surface, context)) {
        LOGE("eglMakeCurrent() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOGE("eglQuerySurface() returned error %d", eglGetError());
        hasSurfaceV = false;
        return;
    }

    hasSurfaceV = true;
}

EGLSurfaceManager::EGLSurfaceManager() {
    display = EGL_NO_DISPLAY;
    surface = EGL_NO_SURFACE;
    context = EGL_NO_CONTEXT;

    width = 0;
    height = 0;

    hasSurfaceV = false;
}

EGLSurfaceManager::~EGLSurfaceManager() {
    if (hasSurfaceV) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(display, context);
        eglDestroySurface(display, surface);
        eglTerminate(display);
    }

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}

EGLDisplay EGLSurfaceManager::getDisplay() {return display;}

EGLSurface EGLSurfaceManager::getSurface() {return surface;}

EGLContext EGLSurfaceManager::getContext() {return context;}

EGLint EGLSurfaceManager::getWidth() {return width;}

EGLint EGLSurfaceManager::getHeight() {return height;}

bool EGLSurfaceManager::hasSurface() {return hasSurfaceV;}

void EGLSurfaceManager::swapBuffers() {
     eglSwapBuffers(display, surface);
}

