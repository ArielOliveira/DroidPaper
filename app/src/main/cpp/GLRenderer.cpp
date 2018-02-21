//
// Created by ariel on 02/02/18.
//

#include "GLRenderer.h"

#include "geometryTestObjects.h"

float mountainColors[] = {0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,
                        0.545, 0.271, 0.075, 1.0f,};

GLRenderer::GLRenderer(): msg(MSG_NONE), draw(false) {
    surfaceManager = new EGLSurfaceManager();
    surfaceAcquired = surfaceManager->hasSurface();
    pthread_mutex_init(&mutex, 0);

    initRand();

    vboIds = new GLuint[6];
}

GLRenderer::~GLRenderer() {
    pthread_mutex_destroy(&mutex);
    destroy();
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

    glBindAttribLocation(gProgram, VERTEX_COLOR_INDX, "vColor");
    checkGlError("glBindAttribLocation");
    LOGI("glBindAttribLocation(\"vColor\") = %d\n",
         VERTEX_COLOR_INDX);

    gTranslation = glGetUniformLocation(gProgram, "myTranslation");

    gAmbient = glGetUniformLocation(gProgram, "ambient_color");
    if (gAmbient < 0)
        LOGI("Error gAmbient");

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

    glDeleteBuffers(6, vboIds);
}

void GLRenderer::drawFrame() {
    static bool eita;
    static float ambient;
    if (!eita) {
        ambient += 0.001f;
        if (ambient >= 1.0f)
            eita = true;
    } else {
        ambient -= 0.001f;
        if (ambient <= 0.0f)
            eita = false;
    }





    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glUniform4f(gAmbient, ambientColor[0]+ambient, ambientColor[1]+ambient, ambientColor[2]+ambient, ambientColor[3]+ambient);

    glVertexAttrib4f(VERTEX_COLOR_INDX, color[0], color[1], color[2], color[3]);
    mountains[0]->bind();
    mountains[0]->draw(gTranslation);
    if (mountains[0]->isDirty()) {
        mountains[0]->update(surfaceManager->getWidth());
    }

    glVertexAttrib4f(VERTEX_COLOR_INDX, color[0]+0.045f, color[1]+0.045f, color[2]+0.045f, color[3]);
    mountains[2]->bind();
    mountains[2]->draw(gTranslation);
    if (mountains[2]->isDirty()) {
        mountains[2]->update(surfaceManager->getWidth());
    }
    glVertexAttrib4f(VERTEX_COLOR_INDX, color[0]+0.015f, color[1]+0.015f, color[2]+0.015f, color[3]);
    mountains[1]->bind();
    mountains[1]->draw(gTranslation);
    if (mountains[1]->isDirty()) {
        mountains[1]->update(surfaceManager->getWidth());
    }

    glEnableVertexAttribArray(VERTEX_COLOR_INDX);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[2]);
    glVertexAttribPointer(VERTEX_COLOR_INDX, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glUniformMatrix4fv(gTranslation, 1, GL_FALSE, myTranslation1);
    glVertexAttribPointer(VERTEX_POSITION_INDX, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(VERTEX_COLOR_INDX);

    surfaceManager->swapBuffers();

}

void GLRenderer::initialize() {
    EGLSurfaceManager *_surfaceDummy = surfaceManager;
    surfaceManager = new EGLSurfaceManager(window);
    delete _surfaceDummy;
    surfaceAcquired = surfaceManager->hasSurface();

    setupGraphics();

    glGenBuffers(6, vboIds);


    cacheBufferByID(sky, 8, &vboIds[0], GL_STATIC_DRAW);
    cacheIndiceByID(indices, 6, &vboIds[1], GL_STATIC_DRAW);

    cacheBufferByID(skyColor, 16, &vboIds[2], GL_STATIC_DRAW);

    int width = surfaceManager->getWidth();

    mountains = {new Mountain(width, width+(width/2), 0.4f, 0.005f, &vboIds[3]),
                 new Mountain(width, width+(width/2), 0.7f, 0.00125f, &vboIds[4]),
                 new Mountain(width, width+(width/2), 0.6f, 0.0025f, &vboIds[5])};


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