
#include "BaseMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

BaseMaterial::BaseMaterial(std::string name) : MaterialGL(name) {

    vp = new GLProgram(MaterialPath + "BaseMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "BaseMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");
}

BaseMaterial::~BaseMaterial() {}

void BaseMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void BaseMaterial::animate(Node *o, const float elapsedTime) {
    Camera *camera = scene->camera();

    glm::mat4 projectionMatrix = camera->getProjectionMatrix();
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 modelMatrix = o->frame()->getModelMatrix();

    glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
