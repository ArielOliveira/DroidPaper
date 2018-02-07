#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "logger.h"
#include "GLRenderer.h"

static ANativeWindow *window = 0;
static GLRenderer *renderer = 0;


extern "C" {
    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnStart(JNIEnv *env, jobject thisObj) {
        LOGI("OnStart()");
        renderer = new GLRenderer();
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnResume(JNIEnv *env, jobject thisObj) {
        LOGI("OnResume()");
        renderer->start();
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnPause(JNIEnv *env, jobject thisObj) {
        LOGI("OnPause()");
        renderer->stop();
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnStop(JNIEnv *env, jobject thisObj) {
        LOGI("OnStop()");
        delete renderer;
        renderer = 0;
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceCreated(JNIEnv *env, jobject thisObj) {

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceChanged(JNIEnv *env, jobject thisObj, jobject surface, jboolean running) {
        if (surface != 0) {
            window = ANativeWindow_fromSurface(env, surface);
            if (running) {
                renderer->setWindow(window);
                LOGI("Got Window &p", window);
            }
        } else {
            ANativeWindow_release(window);
        }
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeResumeCurrent(JNIEnv *env, jobject thisObj) {
        LOGI("Destroying surface");

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativePauseCurrent(JNIEnv *env, jobject thisObj) {
        LOGI("Destroying surface");

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceDestroyed(JNIEnv *env, jobject thisObj) {
        LOGI("Destroying surface");

    }
}
