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
#include "camera.h"
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

Camera::Camera() : pos(1,1,1)
{
    lookAt(glm::vec3{0,0,0});
}

glm::vec3 Camera::getPos() const {return pos;}
glm::vec3 Camera::getDirection() const {return dir;}
const glm::mat4& Camera::getView() const {return cache;}

void Camera::computeMatrix() {
    cache = glm::lookAt(pos, dir, {0, 1, 0});
}

void Camera::lookAt(glm::vec3 target) {
    if (target == pos)
        throw std::runtime_error("Camera tries to look at itself");

    dir = glm::normalize(target - pos);
    computeMatrix();
    computeAnglesFromDir();
}

void Camera::rotateY(float rad) {
    theta += rad;

    //Invariant check
    if (theta > M_PI)
        theta -= 2.f * M_PI;
    else  if (theta < -M_PI)
        theta += 2.f * M_PI;

    computeDirFromAngles();
    computeMatrix();
}

void Camera::setPosition(glm::vec3 newPos) {
    pos = newPos;
    computeMatrix();
    computeAnglesFromDir();
}

void Camera::computeDirFromAngles() {
    dir.x = cos (theta) * cos (phi);
    dir.y = sin (phi);
    dir.z = sin (theta) * cos (phi);
    dir = glm::normalize(dir); //Just in case;
}

void Camera::computeAnglesFromDir() {
    //CHECK INVARIANT : Length of Dir is 1
    float length_2_delta = glm::dot(dir, dir) - 1;
    length_2_delta = length_2_delta > 0 ? length_2_delta : -length_2_delta;
    assert (length_2_delta < 0.01);


    phi = asin(dir.y);
    theta = acos(dir.x/sqrt(1 - dir.y*dir.y));
}
