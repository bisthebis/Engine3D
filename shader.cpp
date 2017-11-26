/*
MIT License

Copyright (c) 2017 Boris Martin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "shader.h"
#include <glad/glad.h>
#include <stdexcept>
#include <fstream>
#include <sstream>

std::string readFile(const std::string &path) {
    std::ifstream file;
    file.open(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::unique_ptr<Shader> makeShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath) {
    return std::make_unique<Shader>(readFile(vertexPath), readFile(fragmentPath));
}

std::unique_ptr<Shader> makeShaderFromSource(const std::string &vertexSource, const std::string &fragmentSource) {
    return std::make_unique<Shader>(vertexSource, fragmentSource);
}

Shader::Shader(const std::string &vertex, const std::string &frag)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar *vertexCStr = vertex.data();
    glShaderSource(vertexShader, 1, &vertexCStr, nullptr);
    glCompileShader(vertexShader);

    {
        int success;
        char infolog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infolog);
            std::string errorLog = std::string("Error compiling vertex shader : ") + infolog;
            throw std::runtime_error(errorLog);
        }
    }

    const GLchar *fragmentCStr = frag.data();
    glShaderSource(fragmentShader, 1, &fragmentCStr, nullptr);
    glCompileShader(fragmentShader);

    {
        int success;
        char infolog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infolog);
            std::string errorLog = std::string("Error compiling fragment shader : ") + infolog;
            throw std::runtime_error(errorLog);
        }
    }

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    {
        int success;
        char infolog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infolog);
            std::string errorLog = std::string("Error linking shader : ") + infolog;
            throw std::runtime_error(errorLog);
        }
    }

    glUseProgram(program);

    /* Cleanup AFTER linking */
    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(program);
}
