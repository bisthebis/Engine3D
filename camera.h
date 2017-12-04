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
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>


/**
 * @brief Class holding a camera in 3D world (with a position and a direction)
 * @invariant getDirection().length() == 1
 * @invariant getView() == glm::lookAt(pos, dir, {0, 1, 0})
 * @invariant Angles and direction match.
 * @invariant Phi is in range [-pi/2, pi/2]
 * @invariant Theta is in range [-pi, pi]
 *
 */
class Camera
{
public:
    Camera();

    const glm::mat4& getView() const;
    glm::vec3 getPos() const;
    glm::vec3 getDirection() const;

    void setPosition(glm::vec3 newPos); //Doesn't change direction (=> target changes)
    void lookAt(glm::vec3 target);

    void rotateTheta(float rad); //négative -> on the left
    void rotatePhi(float rad); // Négative -> Lower

private:
    glm::vec3 pos;
    glm::vec3 dir;

    //Radians !
    float theta; //Theta is angle between x and z, starting from x;
    float phi; //Angle between x and y, starting from x;

    glm::mat4 cache;
    void computeMatrix();
    void computeDirFromAngles();
    void computeAnglesFromDir();

};

#endif // CAMERA_H
