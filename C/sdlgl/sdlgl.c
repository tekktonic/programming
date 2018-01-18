#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <GL/glew.h>
#include <assert.h>
#include "dlib.h"

int main(void)
{
    SDL_Window *win;
    SDL_GLContext ctx;
    GLuint progID = 0;
    GLuint vertex2dLoc = -1;
    GLuint vbo = 0; // the vertex buffer object
    GLuint ibo = 0; // the index buffer object.
    
    GLfloat square[] = { -1.0f, -1.0f, 0.0f,
                       -1.0f, 1.0f, 0.0f,
                       1.0f, 1.0f, 0.0f,
                       1.0f, -1.0f, 0.0f};
    


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    win = SDL_CreateWindow("GL", 0, 0, 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    ctx = SDL_GL_CreateContext(win);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    assert(glewError == GLEW_OK);

    SDL_GL_SetSwapInterval(1); // vsync

    progID = glCreateProgram();

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

    char *vertShaderSource = slurp("vert.glsl");
    glShaderSource(vertShader, 1, vertShaderSource, NULL);

    glCompileShader(vertShader);
    free(vertShaderSource);

    GLint vertShaderCompiled = GL_False;
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertShaderCompiled);

    glAttachShader(progID, vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    chdar *fragShaderSource = slurp("frag.glsl");

    glShaderSource(fragShader, 1, fragShaderSource, NULL);

    glCompileShader(fragShader);
    free(fragShaderSource);

    glAttachShader(progID, fragShader);

    glLinkProgram(progID);

    vertex2dLoc = glGetAttribLocation(progID, "LVertexPos2D");

    glClearColor(0.f, 0.f, 0.f, 1.f);

    GLuint indexData[] = {0, 1, 2, 3};

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), square, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    GLBufferDATA(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    
}
