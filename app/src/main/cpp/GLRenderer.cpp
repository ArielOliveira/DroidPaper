//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

#include "geometryTestObjects.h"

float squareColors[] = {0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,};

GLRenderer::GLRenderer(): msg(MSG_NONE), draw(false) {
    surfaceManager = new EGLSurfaceManager();
    surfaceAcquired = surfaceManager->hasSurface();
    pthread_mutex_init(&mutex, 0);

    vboIds = new GLuint[3];
}

GLRenderer::~GLRenderer() {
    pthread_mutex_destroy(&mutex);

    glDeleteBuffers(3, vboIds);
}

void GLRenderer::start() {
    pthread_create(&threadId, 0, threadStartCallback, this);
}

void GLRenderer::pause() {
    pthread_mutex_lock(&mutex);
    msg = MSG_RENDER_LOOP_PAUSE;
    pthread_mutex_unlock(&mutex);
}

void GLRenderer::stop() {
    pthread_mutex_lock(&mutex);
    msg = MSG_RENDER_LOOP_EXIT;
    pthread_mutex_unlock(&mutex);

    pthread_join(threadId, 0);
}

bool GLRenderer::setupGraphics() {
    gProgram = init(vShaderStr, fShaderStr);
    if (!gProgram) {
        LOGE("Could not create program. %i", gProgram);
        return false;
    }

    glBindAttribLocation(gProgram, VERTEX_POSITION_INDX, "vPosition");
    checkGlError("glBindAttribLocation");
    LOGI("glBindAttribLocation(\"vPosition\") = %d\n",
         VERTEX_POSITION_INDX);

    gColor = glGetUniformLocation(gProgram, "uniformColor");
    gTranslation = glGetUniformLocation(gProgram, "myTranslation");

    glViewport(0, 0, surfaceManager->getWidth(), surfaceManager->getHeight());
    checkGlError("glViewport");

    return true;
}

void GLRenderer::setWindow(ANativeWindow *window) {
    pthread_mutex_lock(&mutex);
    msg = MSG_WINDOW_SET;
    this->window = window;
    pthread_mutex_unlock(&mutex);

}

void GLRenderer::destroy() {
    surfaceAcquired = false;
    delete surfaceManager;
    surfaceManager = 0;

    mountains.clear();

    glDeleteBuffers(2, vboIds);
}

void GLRenderer::drawFrame() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glUniform4f(gColor, color[0]-0.015f, color[1]-0.015f, color[2]-0.015f, color[3]);
    mountains[0]->bind();
    mountains[0]->draw(gTranslation);
    if (mountains[0]->isDirty()) {
        mountains[0]->update(surfaceManager->getWidth());
    }

    glUniform4f(gColor, color[0]+0.045f, color[1]+0.045f, color[2]+0.045f, color[3]);
    mountains[2]->bind();
    mountains[2]->draw(gTranslation);
    if (mountains[2]->isDirty()) {
        mountains[2]->update(surfaceManager->getWidth());
    }

    glUniform4f(gColor, color[0]+0.015f, color[1]+0.015f, color[2]+0.015f, color[3]);
    mountains[1]->bind();
    mountains[1]->draw(gTranslation);
    if (mountains[1]->isDirty()) {
        mountains[1]->update(surfaceManager->getWidth());
    }

    surfaceManager->swapBuffers();

}

void GLRenderer::initialize() {
    EGLSurfaceManager *_surfaceDummy = surfaceManager;
    surfaceManager = new EGLSurfaceManager(window);
    delete _surfaceDummy;
    surfaceAcquired = surfaceManager->hasSurface();

    setupGraphics();

    glGenBuffers(3, vboIds);
    int width = surfaceManager->getWidth();
    int height = surfaceManager->getHeight();
    mountains = {new Mountain(width, width+(width/2), 0.4f, 0.005f, &vboIds[0]),
                 new Mountain(width, width+(width/2), 0.7f, 0.00125f, &vboIds[1]),
                 new Mountain(width, width+(width/2), 0.6f, 0.0025f, &vboIds[2])};

    mountains[2]->setTranslationValueIndex(7, -0.60f);
    mountains[0]->setTranslationValueIndex(7, -0.90f);


    glEnable(GL_DEPTH_TEST);
    glEnableVertexAttribArray(VERTEX_POSITION_INDX);
}

void GLRenderer::renderLoop() {
    draw = true;
    while(draw) {
        pthread_mutex_lock(&mutex);
        switch(msg) {
            case MSG_WINDOW_SET:
                initialize();
                break;
            case MSG_RENDER_LOOP_EXIT:
                draw = false;
                destroy();
                break;
            case MSG_RENDER_LOOP_PAUSE:
                break;
            default:
                break;
        }
        msg = MSG_NONE;
        if (surfaceAcquired) {
            drawFrame();
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* GLRenderer::threadStartCallback(void *thread) {
    GLRenderer *renderer = (GLRenderer*)thread;
    renderer->renderLoop();
    pthread_exit(0);
}