//
// Created by ariel on 02/02/18.
//

#ifndef DROIDPAPER2_GLRENDERER_H
#define DROIDPAPER2_GLRENDERER_H

#include <pthread.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <android/native_window.h>

#include "EGLSurfaceManager.h"
#include "shaderLinker.h"
#include "shaderLib.h"

class GLRenderer {
    private:
        EGLSurfaceManager *surfaceManager;

        pthread_t threadId;
        pthread_mutex_t mutex;

        GLuint gProgram;
        GLint gTranslation;

        ANativeWindow *window;

        const GLuint VERTEX_POSITION_INDX;

        bool draw;

        enum RenderThreadMessage {
            MSG_NONE = 0,
            MSG_WINDOW_SET,
            MSG_RENDER_LOOP_EXIT
        };

        enum RenderThreadMessage msg;

        void destroy();
        void renderLoop();
        void drawFrame();

        bool setupGraphics();
        bool surfaceAcquired;

        static void* threadStartCallback(void *thread);

    public:
        GLRenderer();
        virtual ~GLRenderer();

        void start();
        void stop();
        void setWindow(ANativeWindow *window);

};

#endif //DROIDPAPER2_GLRENDERER_H
