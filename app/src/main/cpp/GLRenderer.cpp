//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

#include "geometryTestObjects.h"

float squareColors[] = {0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,};

GLuint vboIds[3];

GLRenderer::GLRenderer(): msg(MSG_NONE), draw(false), gProgram(0), gTranslation(0) {
    surfaceManager = new EGLSurfaceManager();
    surfaceAcquired = surfaceManager->hasSurface();
    pthread_mutex_init(&mutex, 0);
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

void GLRenderer::initVBOs() {
    glGenBuffers(2, vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, square, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6, indices, GL_STATIC_DRAW);
}

void GLRenderer::drawFrame() {
    GLuint offset = 0;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glUniform4f(gColor, color[0]+0.075f, color[1]+0.075f, color[2]+0.075f, color[3]);
    mountains[0]->draw();

    glUniform4f(gColor, color[0], color[1], color[2], color[3]);
    mountains[1]->draw();

    glUniform4f(gColor, color[0]+0.150f, color[1]+0.150f, color[2]+0.150f, color[3]+0.150f);
    mountains[2]->draw();



    surfaceManager->swapBuffers();
}

void GLRenderer::initialize() {
    EGLSurfaceManager *_surfaceDummy = surfaceManager;
    surfaceManager = new EGLSurfaceManager(window);
    delete _surfaceDummy;
    surfaceAcquired = surfaceManager->hasSurface();

    setupGraphics();


    glGenBuffers(3, vboIds);
    unsigned int width = (unsigned)surfaceManager->getWidth();
    mountains = {new Mountain(width, width+(width/2), 0.5f, 0.005f, 1.0f, &gTranslation, &vboIds[0]),
                 new Mountain(width, width+(width/2), 0.6f, 0.0025f, 1.0f, &gTranslation, &vboIds[1]),
                 new Mountain(width, width+(width/2), 0.7f, 0.00125f, 1.0f, &gTranslation, &vboIds[2])};

    mountains[0]->setTranslationValueIndex(7, -0.70f);
    mountains[1]->setTranslationValueIndex(7, -0.10f);

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