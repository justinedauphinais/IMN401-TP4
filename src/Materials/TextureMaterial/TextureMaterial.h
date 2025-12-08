

#ifndef _TextureMaterial_
#define _TextureMaterial_

#include "MaterialGL.h"
#include "Texture2D.h"

class TextureMaterial : public MaterialGL {
public:
    TextureMaterial(std::string name = "");

    void setDiffuseTexture(Texture2D *texture);
    void setNormalMap(Texture2D *texture);
    void setPhong(float kd, float ka, float ks, int s);
    void setFlagReverseTexture(bool v) { flagReverseTexture = v; }
    void setCoefDist(float c) { coefDist = c; }
    void setFlagDeform(bool d) { flagDeform = d; }

    ~TextureMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface() {};

protected:
    std::string name;

    GLProgram *vp;
    GLProgram *fp;

    Texture2D *texture, *textureN;

    float kd, ka, ks, coefDist;
    int s;
    glm::vec3 C;
    bool flagReverseTexture;
    bool flagDeform;

    GLuint l_View, l_Proj, l_Model, l_kd, l_ka, l_ks, l_s, l_C, l_posLum, l_posCam, l_flagTexture, l_time, l_distCoef, l_flagDeform; // location of uniforms
};

#endif