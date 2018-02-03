#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "logger.h"

ANativeWindow *window = 0;

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnStart(JNIEnv *env, jobject thisObj) {

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnResume(JNIEnv *env, jobject thisObj) {

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeOnPause(JNIEnv *env, jobject thisObj) {

    }


    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceCreated(JNIEnv *env, jobject thisObj) {

    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceChanged(JNIEnv *env, jobject thisObj, jobject surface) {
        if (surface != 0) {
            window = ANativeWindow_fromSurface(env, surface);

        }
    }

    JNIEXPORT void JNICALL
    Java_com_adeveloper_droidpaper_NativeLibLoader_nativeSurfaceDestroyed(JNIEnv *env, jobject thisObj) {

    }
}
