

#ifndef _MoveMaterial_
#define _MoveMaterial_

#include "MaterialGL.h"

class MoveMaterial : public MaterialGL {
public:
    MoveMaterial(std::string name = "", glm::vec3 finalPosition = glm::vec3(0.0f), glm::vec3 positionDepart = glm::vec3(0.0f), float coef = 0.0f);

    ~MoveMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface(){};

protected:
    glm::vec3 finalPosition, positionDepart, pointCourbe, lastPosition;
    std::chrono::steady_clock::time_point startTime;
};

#endif