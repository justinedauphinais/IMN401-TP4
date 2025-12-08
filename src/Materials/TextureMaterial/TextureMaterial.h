

#ifndef _TextureMaterial_
#define _TextureMaterial_

#include "MaterialGL.h"
#include "Texture2D.h"

class TextureMaterial : public MaterialGL {
public:
    TextureMaterial(std::string name = "");

    ~TextureMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface() {};



    void setCatDeform(bool d) { catDeform = d; }

protected:
    std::string name;

    GLProgram *vp;
    GLProgram *fp;

    Texture2D *textureDiffuse, *textureNormale;

    float kd, ka, ks;
    int s;
    glm::vec3 C;

    bool catDeform;

    GLuint l_View, l_Proj, l_Model, l_kd, l_ka, l_ks, l_s, l_C, l_posLum, l_posCam, l_flagTexture, l_time, l_distCoef, l_catDeform; // location of uniforms
};

#endif