

#ifndef _MoveMaterial_
#define _MoveMaterial_

#include "MaterialGL.h"

class RotateMaterial : public MaterialGL {
public:
    RotateMaterial(std::string name = "", glm::vec3 finalPosition = glm::vec3(0.0f), glm::vec3 positionDepart = glm::vec3(0.0f), float coef = 0.0f);

    ~RotateMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface(){};

protected:
    glm::vec3 finalPosition, positionDepart, lastPosition, controlPoint;
    std::chrono::steady_clock::time_point startTime;

    float orbitRadius = 1.0f, orbitSpeed = 1.0f;
};

#endif