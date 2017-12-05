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
#include "vertexbuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer() : enabled(false) {}

VertexBuffer::VertexBuffer(unsigned int id) : _id(id)
{}

VertexBuffer::~VertexBuffer() {
    if (enabled)
        glDeleteBuffers(1, &_id);
}

unsigned int VertexBuffer::id() const {
    return enabled ? _id : 0;
}

VertexBuffer::VertexBuffer(VertexBuffer &&rhs) {
    _id = rhs.id();
    this->enabled = rhs.enabled;
    rhs.enabled = false;
}

VertexBuffer& VertexBuffer::operator =(VertexBuffer&& rhs) {
    _id = rhs.id();
    this->enabled = rhs.enabled;
    rhs.enabled = false;
    return *this;
}

VertexBuffer createArrayBuffer(float *data, unsigned int size) {
    unsigned int id;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    return VertexBuffer(id);
}
