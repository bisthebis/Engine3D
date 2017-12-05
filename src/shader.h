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
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <memory>
#include <glad/glad.h>

/**
 * @brief Class holding an OpenGL Shader (one vertex + one fragment)
 * @invariant : getProgramId() is a valid OpenGL Program
 * @see Related functions : ShaderUtility
 *
 * This class stores an OpenGL Shader Program and manages its lifetime. It is best to use with smart pointers.
 * Use makeShaderFromFile() and makeShaderFromSource() (in ShaderUtility module) to create a simple shader.
 *
 * \code
 * //Typical usage
 * string vertexSource, fragmentSource;
 * // [...]
 * auto shaderFromFile = makeShaderFromFile("myshader.vert", "myshader.frag");
 * auto shaderFromSource = makeShaderFromFile(vertexSource, fragmentSource);
 * //These are of std::unique_ptr<Shader> type.
 * \endcode
 */
class Shader
{
public:
    /**
     * @brief Builds a "classic" shader (one vertex + one fragment) from source strings
     * @param vertex : Source code of the Vertex Shader
     * @param frag : Source code of the Fragment Shader
     */
    Shader(const std::string& vertex, const std::string& frag);
    ~Shader();

    /**
     * @brief getProgramId : Returns the Program ID of the underlying shader. Calling glDeleteProgram on it is undefined behavior
     * @return ProgramID
     */
    unsigned int getProgramId() const {return program;}
private:
    Shader(const Shader&) = delete;
    Shader& operator= (const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader& operator = (Shader&&) = delete; //Use unique ptrs !
    unsigned int program;
};

/** @defgroup ShaderUtility
 * @{ */

/**
 * @brief compileShader : takes an input string and returns an OpenGL Shader part
 * @param type : type of the Shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, ...)
 * @param source : source code
 * @return the id of the shader.
 */

unsigned int compileShader(GLenum type, const std::string& source);

/**
 * @brief readFile : read a file and returns all its content as a std::string
 * @param path : path of the file
 * @return string containing file's content
 * @throw std::runtime_error
 */

std::string readFile(const std::string& path);

/**
 * @brief makeShaderFromFile : creates a Shader from two files (by reading them)
 * @param vertexPath : path of the file containing Vertex Shader source code
 * @param fragmentPath : path of the file containing Fragment Shader source code.
 * @return a unique_ptr containing a Shader
 * @throw std::runtime_error
 */

std::unique_ptr<Shader> makeShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath);

/**
 * @brief makeShaderFromFile : creates a Shader from two files (by reading them)
 * @param vertexPath : Vertex Shader source code
 * @param fragmentPath :Fragment Shader source code.
 * @return a unique_ptr containing a Shader
 * @throw std::runtime_error
 */

std::unique_ptr<Shader> makeShaderFromSource(const std::string& vertexCode, const std::string& fragmentCode);

/** @} */

#endif // SHADER_H
