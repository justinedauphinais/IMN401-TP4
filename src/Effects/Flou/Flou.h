#pragma once

#include "EffectGL.h"

class Flou : public EffectGL {
public:
    Flou(std::string name);

    ~Flou();

    virtual void apply(FrameBufferObject *src, FrameBufferObject *target);

    virtual void animate(const float elapsedTime);

    virtual void displayInterface(){};

protected:
    GLProgram *vp;
    GLProgram *fph;
    GLProgram *fpv;
    GLuint l_TextureH, l_TextureV;

    FrameBufferObject *tmp;
};