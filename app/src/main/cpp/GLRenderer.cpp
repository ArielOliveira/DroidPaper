//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

GLfloat square[] = {-0.5f, -0.5f,
                    -0.5f, 0.5f,
                    0.5f,  0.5f,
                    0.5f, -0.5f,};


GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
                                      0.5f, -0.5f,};

GLushort triangleIndex[] = {0, 1, 2,};

GLushort indices[] = {0, 1, 2, 3, 0, 2,};

float myTranslation1[] = {1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f,};

GLRenderer::GLRenderer(): msg(MSG_NONE), draw(false), gProgram(0), gTranslation(0), VERTEX_POSITION_INDX(0) {
    surfaceManager = new EGLSurfaceManager();
    surfaceAcquired = surfaceManager->hasSurface();
    pthread_mutex_init(&mutex, 0);
}

GLRenderer::~GLRenderer() {
    destroy();
}

void GLRenderer::start() {
    LOGI("Starting Thread");
    pthread_create(&threadId, 0, threadStartCallback, this);

}

void GLRenderer::stop() {
    pthread_mutex_lock(&mutex);
    msg = MSG_RENDER_LOOP_EXIT;
    pthread_mutex_unlock(&mutex);

    pthread_join(threadId, 0);
}

bool GLRenderer::setupGraphics() {
    LOGI("setupGraphics(%d, %d)", surfaceManager->getWidth(), surfaceManager->getHeight());

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
    delete surfaceManager;
    surfaceManager = 0;
}

void GLRenderer::drawFrame() {
    GLuint offset = 0;

    GLuint vboIds[2];

    GLfloat *squarePointer = square;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glGenBuffers(2, vboIds);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, squarePointer, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 6, indices, GL_DYNAMIC_DRAW);

    glUniformMatrix4fv(gTranslation, 1, GL_FALSE, myTranslation1);
    glEnableVertexAttribArray(VERTEX_POSITION_INDX);
    glVertexAttribPointer(VERTEX_POSITION_INDX, 2, GL_FLOAT, GL_FALSE, 0, (const void*)offset);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glDeleteBuffers(2, vboIds);

    /*
    glUniformMatrix4fv(gTranslation, 1, GL_FALSE, myTranslation1);
    glVertexAttribPointer(VERTEX_POSITION_INDX, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(VERTEX_POSITION_INDX);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
    */

    surfaceManager->swapBuffers();
}

void GLRenderer::renderLoop() {
    draw = true;
    LOGI("Drawing Enabled");
    while(draw) {
        pthread_mutex_lock(&mutex);
        switch(msg) {
            case MSG_WINDOW_SET:
                if (surfaceManager) {
                    delete surfaceManager;
                    surfaceManager = 0;
                }
                LOGI("Setting window");
                surfaceManager = new EGLSurfaceManager(window);
                surfaceAcquired = surfaceManager->hasSurface();
                setupGraphics();
                break;
            case MSG_RENDER_LOOP_EXIT:
                draw = false;
                surfaceAcquired = false;
                destroy();
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
    LOGI("Drawing Disabled");
}

void* GLRenderer::threadStartCallback(void *thread) {
    GLRenderer *renderer = (GLRenderer*)thread;
    renderer->renderLoop();
    pthread_exit(0);
}