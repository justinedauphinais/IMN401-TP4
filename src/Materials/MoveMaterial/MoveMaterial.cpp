
#include "MoveMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

MoveMaterial::MoveMaterial(std::string name, glm::vec3 finalPosition, glm::vec3 positionDepart, float coef) : MaterialGL(name), finalPosition(finalPosition), positionDepart(positionDepart), lastPosition(positionDepart) {
    pointCourbe = (finalPosition + positionDepart) / 2.0f;
    pointCourbe.y += coef;
}

MoveMaterial::~MoveMaterial() {}

void MoveMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void MoveMaterial::animate(Node *o, const float elapsedTime) {
    auto currentTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration<float>(currentTime - startTime);
    float time = duration.count();

    float speed = 1.0f;
    time *= speed;

    float t = (sin(time) + 1.0f) / 2.0f;
    glm::vec3 move =
        (1.0f - t) * (1.0f - t) * positionDepart +
        2.0f * (1.0f - t) * t * pointCourbe +
        t * t * finalPosition;
    o->frame()->translate(move - lastPosition);
    lastPosition = move;
}