#include "engine/Renderer.h"

#include "engine/Log.h"
#include "engine/Window.h"

#include <array>
#include <cmath>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace engine {

namespace {

template <typename T>
bool LoadProc(T& out, const char* name) {
    out = reinterpret_cast<T>(glfwGetProcAddress(name));
    if (!out) {
        LogError(std::string("Failed to load OpenGL function: ") + name);
        return false;
    }
    return true;
}

using GLCreateShader = GLuint (*)(GLenum);
using GLShaderSource = void (*)(GLuint, GLsizei, const GLchar* const*, const GLint*);
using GLCompileShader = void (*)(GLuint);
using GLGetShaderiv = void (*)(GLuint, GLenum, GLint*);
using GLGetShaderInfoLog = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);
using GLDeleteShader = void (*)(GLuint);
using GLCreateProgram = GLuint (*)(void);
using GLAttachShader = void (*)(GLuint, GLuint);
using GLLinkProgram = void (*)(GLuint);
using GLGetProgramiv = void (*)(GLuint, GLenum, GLint*);
using GLGetProgramInfoLog = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);
using GLDeleteProgram = void (*)(GLuint);
using GLUseProgram = void (*)(GLuint);
using GLGetUniformLocation = GLint (*)(GLuint, const GLchar*);
using GLUniform1f = void (*)(GLint, GLfloat);
using GLUniform2f = void (*)(GLint, GLfloat, GLfloat);
using GLGenVertexArrays = void (*)(GLsizei, GLuint*);
using GLBindVertexArray = void (*)(GLuint);
using GLGenBuffers = void (*)(GLsizei, GLuint*);
using GLBindBuffer = void (*)(GLenum, GLuint);
using GLBufferData = void (*)(GLenum, GLsizeiptr, const void*, GLenum);
using GLVertexAttribPointer = void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
using GLEnableVertexAttribArray = void (*)(GLuint);
using GLDeleteVertexArrays = void (*)(GLsizei, const GLuint*);
using GLDeleteBuffers = void (*)(GLsizei, const GLuint*);
using GLDrawArrays = void (*)(GLenum, GLint, GLsizei);

GLCreateShader glCreateShaderPtr = nullptr;
GLShaderSource glShaderSourcePtr = nullptr;
GLCompileShader glCompileShaderPtr = nullptr;
GLGetShaderiv glGetShaderivPtr = nullptr;
GLGetShaderInfoLog glGetShaderInfoLogPtr = nullptr;
GLDeleteShader glDeleteShaderPtr = nullptr;
GLCreateProgram glCreateProgramPtr = nullptr;
GLAttachShader glAttachShaderPtr = nullptr;
GLLinkProgram glLinkProgramPtr = nullptr;
GLGetProgramiv glGetProgramivPtr = nullptr;
GLGetProgramInfoLog glGetProgramInfoLogPtr = nullptr;
GLDeleteProgram glDeleteProgramPtr = nullptr;
GLUseProgram glUseProgramPtr = nullptr;
GLGetUniformLocation glGetUniformLocationPtr = nullptr;
GLUniform1f glUniform1fPtr = nullptr;
GLUniform2f glUniform2fPtr = nullptr;
GLGenVertexArrays glGenVertexArraysPtr = nullptr;
GLBindVertexArray glBindVertexArrayPtr = nullptr;
GLGenBuffers glGenBuffersPtr = nullptr;
GLBindBuffer glBindBufferPtr = nullptr;
GLBufferData glBufferDataPtr = nullptr;
GLVertexAttribPointer glVertexAttribPointerPtr = nullptr;
GLEnableVertexAttribArray glEnableVertexAttribArrayPtr = nullptr;
GLDeleteVertexArrays glDeleteVertexArraysPtr = nullptr;
GLDeleteBuffers glDeleteBuffersPtr = nullptr;
GLDrawArrays glDrawArraysPtr = nullptr;

bool LoadOpenGLProcedures() {
    return LoadProc(glCreateShaderPtr, "glCreateShader") &&
           LoadProc(glShaderSourcePtr, "glShaderSource") &&
           LoadProc(glCompileShaderPtr, "glCompileShader") &&
           LoadProc(glGetShaderivPtr, "glGetShaderiv") &&
           LoadProc(glGetShaderInfoLogPtr, "glGetShaderInfoLog") &&
           LoadProc(glDeleteShaderPtr, "glDeleteShader") &&
           LoadProc(glCreateProgramPtr, "glCreateProgram") &&
           LoadProc(glAttachShaderPtr, "glAttachShader") &&
           LoadProc(glLinkProgramPtr, "glLinkProgram") &&
           LoadProc(glGetProgramivPtr, "glGetProgramiv") &&
           LoadProc(glGetProgramInfoLogPtr, "glGetProgramInfoLog") &&
           LoadProc(glDeleteProgramPtr, "glDeleteProgram") &&
           LoadProc(glUseProgramPtr, "glUseProgram") &&
           LoadProc(glGetUniformLocationPtr, "glGetUniformLocation") &&
           LoadProc(glUniform1fPtr, "glUniform1f") &&
           LoadProc(glUniform2fPtr, "glUniform2f") &&
           LoadProc(glGenVertexArraysPtr, "glGenVertexArrays") &&
           LoadProc(glBindVertexArrayPtr, "glBindVertexArray") &&
           LoadProc(glGenBuffersPtr, "glGenBuffers") &&
           LoadProc(glBindBufferPtr, "glBindBuffer") &&
           LoadProc(glBufferDataPtr, "glBufferData") &&
           LoadProc(glVertexAttribPointerPtr, "glVertexAttribPointer") &&
           LoadProc(glEnableVertexAttribArrayPtr, "glEnableVertexAttribArray") &&
           LoadProc(glDeleteVertexArraysPtr, "glDeleteVertexArrays") &&
           LoadProc(glDeleteBuffersPtr, "glDeleteBuffers") &&
           LoadProc(glDrawArraysPtr, "glDrawArrays");
}

bool CompileShader(GLuint shader, const char* source) {
    glShaderSourcePtr(shader, 1, &source, nullptr);
    glCompileShaderPtr(shader);

    GLint success = 0;
    glGetShaderivPtr(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar log[512];
        glGetShaderInfoLogPtr(shader, sizeof(log), nullptr, log);
        LogError(std::string("Shader compilation failed: ") + log);
        return false;
    }
    return true;
}

GLuint CreateShaderProgram(const char* vsSource, const char* fsSource) {
    const GLuint vertexShader = glCreateShaderPtr(GL_VERTEX_SHADER);
    if (!CompileShader(vertexShader, vsSource)) {
        glDeleteShaderPtr(vertexShader);
        return 0;
    }

    const GLuint fragmentShader = glCreateShaderPtr(GL_FRAGMENT_SHADER);
    if (!CompileShader(fragmentShader, fsSource)) {
        glDeleteShaderPtr(vertexShader);
        glDeleteShaderPtr(fragmentShader);
        return 0;
    }

    const GLuint program = glCreateProgramPtr();
    glAttachShaderPtr(program, vertexShader);
    glAttachShaderPtr(program, fragmentShader);
    glLinkProgramPtr(program);

    GLint success = 0;
    glGetProgramivPtr(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar log[512];
        glGetProgramInfoLogPtr(program, sizeof(log), nullptr, log);
        LogError(std::string("Program link failed: ") + log);
        glDeleteProgramPtr(program);
        glDeleteShaderPtr(vertexShader);
        glDeleteShaderPtr(fragmentShader);
        return 0;
    }

    glDeleteShaderPtr(vertexShader);
    glDeleteShaderPtr(fragmentShader);
    return program;
}

}  // namespace

Renderer::Renderer()
    : m_initialized(false),
      m_vao(0),
      m_vbo(0),
      m_program(0),
      m_timeUniform(-1),
      m_offsetUniform(-1) {}

bool Renderer::Initialize(Window& window) {
    glfwMakeContextCurrent(window.GetNativeHandle());

    if (!LoadOpenGLProcedures()) {
        return false;
    }

    const char* vertexSrc = R"(#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uOffset;

void main()
{
    gl_Position = vec4(aPos + uOffset, 0.0, 1.0);
}
)";

    const char* fragmentSrc = R"(#version 330 core
out vec4 FragColor;

uniform float uTime;

void main()
{
    float green = 0.5 + 0.5 * sin(uTime);
    FragColor = vec4(0.2, green, 0.9 - green * 0.5, 1.0);
}
)";

    m_program = CreateShaderProgram(vertexSrc, fragmentSrc);
    if (m_program == 0) {
        return false;
    }

    glUseProgramPtr(m_program);
    m_timeUniform = glGetUniformLocationPtr(m_program, "uTime");
    m_offsetUniform = glGetUniformLocationPtr(m_program, "uOffset");

    std::array<float, 6> vertices = {
        -0.1f, -0.1f,
         0.1f, -0.1f,
         0.0f,  0.15f};

    glGenVertexArraysPtr(1, &m_vao);
    glBindVertexArrayPtr(m_vao);

    glGenBuffersPtr(1, &m_vbo);
    glBindBufferPtr(GL_ARRAY_BUFFER, m_vbo);
    glBufferDataPtr(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointerPtr(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArrayPtr(0);

    glViewport(0, 0, window.GetWidth(), window.GetHeight());
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    m_initialized = true;
    LogInfo("Renderer initialized");
    return true;
}

void Renderer::BeginFrame() {
    if (!m_initialized) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(float totalTime, float offsetX, float offsetY) {
    if (!m_initialized) {
        return;
    }

    glUseProgramPtr(m_program);
    if (m_timeUniform >= 0) {
        glUniform1fPtr(m_timeUniform, totalTime);
    }
    if (m_offsetUniform >= 0) {
        glUniform2fPtr(m_offsetUniform, offsetX, offsetY);
    }

    glBindVertexArrayPtr(m_vao);
    glDrawArraysPtr(GL_TRIANGLES, 0, 3);
}

void Renderer::EndFrame() {
    // Placeholder for future draw submission / buffer management.
}

void Renderer::Shutdown() {
    if (!m_initialized) {
        return;
    }

    if (m_vbo) {
        glDeleteBuffersPtr(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_vao) {
        glDeleteVertexArraysPtr(1, &m_vao);
        m_vao = 0;
    }
    if (m_program) {
        glDeleteProgramPtr(m_program);
        m_program = 0;
    }

    m_initialized = false;
    LogInfo("Renderer shutdown");
}

}  // namespace engine
