//
// Created by ariel on 02/02/18.
//

#ifndef DROIDPAPER2_LOGGER_H
#define DROIDPAPER2_LOGGER_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <android/log.h>

#define LOG_TAG "libgl2jni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //DROIDPAPER2_LOGGER_H
