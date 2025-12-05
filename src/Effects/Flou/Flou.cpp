
#include "Flou.h"
#include <glm/gtc/type_ptr.hpp>

Flou::Flou(std::string name) : EffectGL(name) {
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    //fp = new GLProgram(EffectPath + "Flou/Flou-FS.glsl", GL_FRAGMENT_SHADER);
    fph = new GLProgram(EffectPath + "Flou/FlouH-FS.glsl", GL_FRAGMENT_SHADER);
    fpv = new GLProgram(EffectPath + "Flou/FlouV-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fph, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();
    m_ProgramPipeline->printInfoLog();

    l_TextureH = glGetUniformLocation(fph->getId(), "myFBO");
    l_TextureV = glGetUniformLocation(fpv->getId(), "myFBO");

    tmp = new FrameBufferObject();
}

Flou::~Flou() {}

void Flou::apply(FrameBufferObject *src, FrameBufferObject *target) {

    // =========================
    // PASS 1 : Horizontal blur
    // =========================
    glProgramUniformHandleui64ARB(fph->getId(), l_TextureH, src->getColorTexture()->getHandle());
    tmp->enable();

    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    m_ProgramPipeline->useProgramStage(fph, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->bind();
    drawQuad();
    m_ProgramPipeline->release();

    tmp->disable();

    // =========================
    // PASS 2 : Vertical blur
    // =========================
    glProgramUniformHandleui64ARB(fpv->getId(), l_TextureV, tmp->getColorTexture()->getHandle());

    if (target)
        target->enable();

    glClear(GL_COLOR_BUFFER_BIT);

    m_ProgramPipeline->useProgramStage(fpv, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->bind();
    drawQuad();
    m_ProgramPipeline->release();

    if (target)
        target->disable();
}

void Flou::animate(const float elapsedTime) {}
