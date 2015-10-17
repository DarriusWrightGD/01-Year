//
// Created by Darrius on 10/11/2015.
//

//#include "rendering_wright_esengine_nativec_NativeLib.h"
#include "NativeLib.h"

NativeLib lib;

GLfloat triangleVertices[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
GLfloat triangleColors[] = {0.7f, 0.1f, 0.4f, 0.1f, 0.8f, 0.4f, 0.0f, 1.0f, 0.3f};

GLuint programId;
GLint positionAttributeHandle;
GLint colorAttributeHandle;

static const char vertexShader[] =
        "#version 300 es                                          \n"
                "in vec4        vertexPosition;                           \n"
                "in vec4        vertexColor;                              \n"
                "out vec4       color;                            \n"
                "void main() {                                            \n"
                "  gl_Position   = vertexPosition;         \n"
                "  color = vertexColor;                           \n"
                "}\n";

static const char fragmentShader[] =
        "#version 300 es            \n"
                "precision mediump float;   \n"
                "in vec4 color;     \n"
                "out vec4 fragColor;        \n"
                "void main() {              \n"
                "  fragColor = color;\n"
                "}";

void NativeLib::printGLString(const char *name, GLenum s) {
    LOGI("GL %s = %s\n", name, (const char *) glGetString((s)));
}

void NativeLib::checkGLError(const char *operation) {
    for (GLuint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", operation, error);
    }
}


GLuint NativeLib::loadAndCompileShader(GLenum shaderType, const char *sourceCode) {
    GLuint shader = glCreateShader(shaderType);

    if (shader) {
        glShaderSource(shader, 1, &sourceCode, NULL);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint NativeLib::linkShader(GLuint vertShaderId, GLuint fragShaderId) {
    if (!vertShaderId || !fragShaderId) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertShaderId);
        glAttachShader(program, fragShaderId);

        glLinkProgram(program);

        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("could not link program : \n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint NativeLib::createProgramExec(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShaderId = loadAndCompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShaderId = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    return linkShader(vertexShaderId, fragmentShaderId);
}


void NativeLib::printOpenGLESInfo() {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
    printGLString("GL Shading Language", GL_SHADING_LANGUAGE_VERSION);
}


JNIEXPORT void JNICALL Java_rendering_wright_esengine_nativec_NativeLib_Init
(JNIEnv * env, jclass, jstring path)
{
    setenv("FILESYSTEM", env->GetStringUTFChars(path, NULL), 1);
    lib.initGL();
}

JNIEXPORT void JNICALL Java_rendering_wright_esengine_nativec_NativeLib_Resize
(JNIEnv * env, jclass, jint width, jint height)
{
    lib.resizeGL(width, height);
}

JNIEXPORT void JNICALL Java_rendering_wright_esengine_nativec_NativeLib_Update
(JNIEnv *, jclass)
{
    lib.updateGL();
}

void NativeLib::initGL() {
    printOpenGLESInfo();
    programId = createProgramExec(vertexShader, fragmentShader);
    if (!programId) {
        LOGE("Could not create program.");
        return;
    }
    checkGLError("GraphicsInit");
}

void NativeLib::resizeGL(jint width, jint height ) {
    glViewport(0, 0, width, height);
}

void NativeLib::updateGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.4, 0.7, 0.1, 1.0f);
    glUseProgram(programId);

    //  positionAttributeHandle = glGetAttribLocation(programId, "vertexPosition");
    //  colorAttributeHandle = glGetAttribLocation(programId, "vertexColor");

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, triangleVertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, triangleColors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}




