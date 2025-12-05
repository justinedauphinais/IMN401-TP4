#pragma once
#include "EffectGL.h"
#include "Effects/Flou/Flou.h"

class Bloom : public EffectGL {
public:
    Bloom(std::string name);
    ~Bloom();

    virtual void apply(FrameBufferObject *src, FrameBufferObject *target);

protected:
    GLProgram *vp;
    GLProgram *fpExtract;
    GLProgram *fpCombine;

    GLuint l_texExtract;
    GLuint l_texScene;
    GLuint l_texBlur;

    FrameBufferObject *fbo1; // bright pass
    FrameBufferObject *fbo2; // blurred bright pass

    Flou *flou; // your blur class
};
