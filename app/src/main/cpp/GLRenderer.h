//
// Created by ariel on 02/02/18.
//

#ifndef DROIDPAPER2_GLRENDERER_H
#define DROIDPAPER2_GLRENDERER_H

#include <pthread.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/native_window.h>

class GLRenderer {
    public:
        GLRenderer();
        virtual ~GLRenderer();

        void start();
        void stop();
        void setWindow(ANativeWindow *window);
    private:
        pthread_t threadId;
        pthread_mutex_t mutex;

        ANativeWindow *window;

        EGLDisplay display;
        EGLSurface  surface;
        EGLContext context;

        int width;
        int height;

        bool setupEGL();
        void destroy();

        void drawFrame();

};

#endif //DROIDPAPER2_GLRENDERER_H
