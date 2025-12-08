#include "DepthOfField.h"
#include <glm/gtc/type_ptr.hpp>

DepthOfField::DepthOfField(std::string name) : EffectGL(name) {
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(EffectPath + "DepthOfField/DepthOfField-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->link();
    m_ProgramPipeline->printInfoLog();
}

DepthOfField::~DepthOfField() {}

void DepthOfField::apply(FrameBufferObject *src, FrameBufferObject *target) {
    glBindTextureUnit(0, src->getColorTexture()->getId());

    if (target)
        target->enable();

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    m_ProgramPipeline->bind();
    drawQuad();
    m_ProgramPipeline->release();
    if (target)
        target->disable();
}

void DepthOfField::animate(const float elapsedTime) {}