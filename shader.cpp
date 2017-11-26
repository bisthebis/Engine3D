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

    if (!file.good())
        throw std::runtime_error(std::string("Could not open file : ") + path);
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

std::unique_ptr<Shader> makeShaderFromFile(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    return makeShaderFromSource(vertexCode, fragmentCode);
}

std::unique_ptr<Shader> makeShaderFromSource(const std::string &vertexSource, const std::string &fragmentSource) {
    return std::make_unique<Shader>(vertexSource, fragmentSource);
}

Shader::Shader(const std::string &vertex, const std::string &frag)
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, frag);

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


unsigned int compileShader(GLenum type, const std::string &source) {
    unsigned int result = glCreateShader(type);
    const GLchar *source_data = source.data();
    glShaderSource(result, 1, &source_data, nullptr);
    glCompileShader(result);

    {
        int success;
        char infolog[512];
        glGetShaderiv(result, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(result, 512, nullptr, infolog);
            std::string errorLog = std::string("Error compiling fragment shader : ") + infolog;
            throw std::runtime_error(errorLog);
        }
    }

    return result;
}
