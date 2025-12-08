#pragma once
#include "EffectGL.h"


class DepthOfField : public EffectGL {
public:
    DepthOfField(std::string name);
    ~DepthOfField();

    virtual void apply(FrameBufferObject *src, FrameBufferObject *target);

    virtual void animate(const float elapsedTime);

    virtual void displayInterface() {};

protected:
    GLProgram *vp;
    GLProgram *fp;
};