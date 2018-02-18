//
// Created by ariel on 02/02/18.
//

#ifndef DROIDPAPER2_GLRENDERER_H
#define DROIDPAPER2_GLRENDERER_H

#include <pthread.h>
#include <android/native_window.h>

#include <vector>
using std::vector;

#include "EGLSurfaceManager.h"
#include "GLBufferManager.h"
#include "shaderLinker.h"
#include "shaderLib.h"
#include "matrixUtils.h"
#include "Mountain.h"

class GLRenderer {
    private:
        EGLSurfaceManager *surfaceManager;

        pthread_t threadId;
        pthread_mutex_t mutex;

        ANativeWindow *window;

        vector<Mountain*> mountains;

        GLuint gProgram;
        GLint gTranslation;
        GLint gColor;

        GLuint *vboIds;

        bool draw;

        enum RenderThreadMessage {
            MSG_NONE = 0,
            MSG_WINDOW_SET,
            MSG_RENDER_LOOP_PAUSE,
            MSG_RENDER_LOOP_RESUME,
            MSG_RENDER_LOOP_EXIT
        };

        enum RenderThreadMessage msg;

        void initialize();
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
        void resume();
        void pause();
        void stop();
        void setWindow(ANativeWindow *window);

};

#endif //DROIDPAPER2_GLRENDERER_H
