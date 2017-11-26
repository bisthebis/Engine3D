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
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


class VertexBuffer
{
public:
    VertexBuffer(); //Create an empty, disabled buffer
    VertexBuffer(unsigned int id);
    VertexBuffer(const VertexBuffer&) = delete; //Non-copyable, but movable
    VertexBuffer(VertexBuffer && rhs);
    VertexBuffer& operator=(const VertexBuffer &) = delete;
    VertexBuffer& operator=(VertexBuffer && rhs);
    ~VertexBuffer();
    unsigned int id() const;
private:
    unsigned int _id;
    bool enabled = true;
};

/**
 * @brief create a VBO of type ARRAY_BUFFER
 * @param data : pointer to the raw data
 * @param size
 * @return a VBO
 * @pre size >= size of data
 */
VertexBuffer createArrayBuffer(float* data, unsigned int size);

#endif // VERTEXBUFFER_H
