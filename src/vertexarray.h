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
#ifndef VERTAXARRAY_H
#define VERTAXARRAY_H

#include "vertexbuffer.h"
#include <vector>

/**
 * @brief The VertexArray class holds a Vertex Array Object (OpenGL) and can take ownership of its related VBOs.
 *
 */
class VertexArray
{
public:
    /**
     * @brief Creates an empty VAO
     */

    VertexArray();

    ~VertexArray();

    /**
     * @brief Deletes the previous VAO (if any) and the related VBOs and creates a new one.
     */

    void initEmpty();

    /**
     * @brief Bind the current VAO. If empty, it's equivalent to unbinding.
     */

    void bind();

    /**
     * @brief Unbind the current VAO. Equivalent to glBindVertexArray(0);
     */

    inline void unbind();

    /**
     * @brief Takes a VertexBuffer object and add it to the list of managed VBOs.
     * @param vbo : rhs VBO to take ownership of.
     */

    void takeVBO(VertexBuffer&& vbo);

    /**
     * @brief Checks whether there is a valid VAO inside.
     * @return true if there is a VAO, false otherwise
     */

    bool empty() const {return !enabled;}

private:
    std::vector<VertexBuffer> vbos;
    unsigned int vao;
    bool enabled = true;

    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&& rhs);
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& rhs);

};

#endif // VERTAXARRAY_H
