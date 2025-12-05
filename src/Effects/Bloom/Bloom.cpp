#include "Bloom.h"
#include <glm/gtc/type_ptr.hpp>

Bloom::Bloom(std::string name) : EffectGL(name) {

    // Load shaders
    vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
    fpExtract = new GLProgram(EffectPath + "Bloom/BloomExtract-FS.glsl", GL_FRAGMENT_SHADER);
    fpCombine = new GLProgram(EffectPath + "Bloom/BloomCombine-FS.glsl", GL_FRAGMENT_SHADER);

    // Pipeline initial setup: vertex + extract FS
    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fpExtract, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->link();

    // Uniform locations
    l_texExtract = glGetUniformLocation(fpExtract->getId(), "myFBO");
    l_texScene = glGetUniformLocation(fpCombine->getId(), "originalScene");
    l_texBlur = glGetUniformLocation(fpCombine->getId(), "blurredBright");

    // FBOs
    fbo1 = new FrameBufferObject("BrightPass");
    fbo2 = new FrameBufferObject("BlurPass");

    // Use your blur effect
    flou = new Flou("BloomBlur");
}

Bloom::~Bloom() {}

void Bloom::apply(FrameBufferObject *src, FrameBufferObject *target) {

    // ================================
    // PASS 1 — BRIGHT EXTRACTION
    // ================================
    glProgramUniformHandleui64ARB(fpExtract->getId(), l_texExtract,
                                  src->getColorTexture()->getHandle());

    fbo1->enable();
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    m_ProgramPipeline->useProgramStage(fpExtract, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->bind();
    drawQuad();
    m_ProgramPipeline->release();
    fbo1->disable();

    // ================================
    // PASS 2 — BLUR BRIGHT AREAS
    // ================================
    flou->apply(fbo1, fbo2); // horizontal + vertical blur using your existing class

    // ================================
    // PASS 3 — COMBINE SCENE + BLOOM
    // ================================
    if (target)
        target->enable();

    glClear(GL_COLOR_BUFFER_BIT);

    // Send original scene + blurred bright
    glProgramUniformHandleui64ARB(fpCombine->getId(), l_texScene,
                                  src->getColorTexture()->getHandle());
    glProgramUniformHandleui64ARB(fpCombine->getId(), l_texBlur,
                                  fbo2->getColorTexture()->getHandle());

    m_ProgramPipeline->useProgramStage(fpCombine, GL_FRAGMENT_SHADER_BIT);
    m_ProgramPipeline->bind();
    drawQuad();
    m_ProgramPipeline->release();

    if (target)
        target->disable();
}
