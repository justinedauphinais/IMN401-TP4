#include "RotateMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

RotateMaterial::RotateMaterial(std::string name, glm::vec3 endPos, glm::vec3 startPos, float heightOffset) : MaterialGL(name), finalPosition(endPos), positionDepart(startPos), lastPosition(startPos) {

    controlPoint = (finalPosition + positionDepart) * 0.5f;

    controlPoint.y += heightOffset;

    startTime = std::chrono::steady_clock::now();
}

RotateMaterial::~RotateMaterial() {}

void RotateMaterial::render(Node *o) {
    m_ProgramPipeline->bind();
    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void RotateMaterial::animate(Node *o, const float elapsedTime) {
    auto now = std::chrono::steady_clock::now();
    float timeSinceStart = std::chrono::duration<float>(now - startTime).count();

    float speed = 1.0f;

    float t = (std::sin(timeSinceStart * speed) + 1.0f) * 0.5f;

    // B(t) = (1 - t)^2 * P0 + 2(1 - t)t * P1 + t^2 * P2
    glm::vec3 bezierPos =
        (1.0f - t) * (1.0f - t) * positionDepart +
        2.0f * (1.0f - t) * t * controlPoint +
        t * t * finalPosition;

    float radius = 0.5f;
    float rotationSpeed = 1.0f;

    glm::vec3 circleOffset;
    circleOffset.x = std::cos(timeSinceStart * rotationSpeed) * radius;
    circleOffset.z = std::sin(timeSinceStart * rotationSpeed) * radius;
    circleOffset.y = 0.0f; // no vertical movement

    glm::vec3 newPos = bezierPos + circleOffset;

    o->frame()->translate(newPos - lastPosition);

    lastPosition = newPos;
}
