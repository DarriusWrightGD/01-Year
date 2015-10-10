//
// Created by Darrius on 10/10/2015.
//

#ifndef _00_HELLOTRIANGLE_NATIVELIB_H_H
#define _00_HELLOTRIANGLE_NATIVELIB_H_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define LOG_TAG "NativeLib.h"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


GLuint loadAndCompileShader(GLenum shaderType, const char *sourceCode);

GLuint createProgramExec(const char *vertexSource, const char *fragmentSource);

void Init();

void Resize(jint width, jint height);

void Update();

#endif //00_HELLOTRIANGLE_NATIVELIB_H_H
