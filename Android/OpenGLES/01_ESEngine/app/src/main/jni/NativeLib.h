//
// Created by Darrius on 10/11/2015.
//
#ifndef ESENGINE_NATIVELIB_H
#define ESENGINE_NATIVELIB_H
#include <jni.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define LOG_TAG "NativeLib.h"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class NativeLib {
public:
    void initGL();
    void resizeGL(jint width, jint height);
    void updateGL();
    static void checkGLError(const char *operation);
    static void printGLString(const char *name, GLenum s);
private:
    GLuint loadAndCompileShader(GLenum shaderType, const char *sourceCode);
    GLuint createProgramExec(const char *vertexSource, const char *fragmentSource);
    GLuint linkShader(GLuint vertShaderId, GLuint fragShaderId);
    void printOpenGLESInfo();
};


#endif //ESENGINE_NATIVELIB_H
