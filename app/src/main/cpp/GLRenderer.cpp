//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

#include "geometryTestObjects.h"

float myTranslation1[] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f,};

GLuint vboIds[2];

GLRenderer::GLRenderer(): msg(MSG_NONE), draw(false), gProgram(0), gTranslation(0) {
    surfaceManager = new EGLSurfaceManager();
    surfaceAcquired = surfaceManager->hasSurface();
    pthread_mutex_init(&mutex, 0);
}

GLRenderer::~GLRenderer() {
    pthread_mutex_destroy(&mutex);

    glDeleteBuffers(2, vboIds);
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

    delete mountain;
    mountain = 0;

    glDeleteBuffers(2, vboIds);
}

void GLRenderer::initVBOs() {
    glGenBuffers(2, vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, square, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6, indices, GL_DYNAMIC_DRAW);
}

void GLRenderer::drawFrame() {
    GLuint offset = 0;

    static float degrees;
    degrees -= 0.005f;
    if (degrees <= -1.0f) {
        mountain->update();
        degrees = 0;
    }


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glUniformMatrix4fv(gTranslation, 1, GL_FALSE, myTranslation1);
    glEnableVertexAttribArray(VERTEX_POSITION_INDX);
    //glVertexAttribPointer(VERTEX_POSITION_INDX, 2, GL_FLOAT, GL_FALSE, 0, (const void*)offset);
    mountain->draw();
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    myTranslation1[3] -= 0.005f;

    //rotateY(degrees, myTranslation1);
    //rotateX(degrees, myTranslation1);
    //rotateZ(degrees, myTranslation1);

    surfaceManager->swapBuffers();
}

void GLRenderer::initialize() {
    EGLSurfaceManager *_surfaceDummy = surfaceManager;
    surfaceManager = new EGLSurfaceManager(window);
    delete _surfaceDummy;
    surfaceAcquired = surfaceManager->hasSurface();

    setupGraphics();
    glGenBuffers(2, vboIds);
    int width = surfaceManager->getWidth();
    mountain = new Mountain(width, width+(width/2), 0.5f, (1.0f/4.0f), &vboIds[0]);
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