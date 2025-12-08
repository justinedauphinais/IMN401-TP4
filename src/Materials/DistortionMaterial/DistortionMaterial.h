

#ifndef _DistortionMaterial_
#define _DistortionMaterial_

#include "MaterialGL.h"
#include <Texture2D.h>

class DistortionMaterial : public MaterialGL {
public:
    DistortionMaterial(std::string name = "");

    ~DistortionMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface(){};

    // TP4
    void setPhong(float ka, float kd, float ks, int shiny);
    void setDiffuseTexture(Texture2D *tex);
    void setNormalMap(Texture2D *tex);
    void setFlagReverseTexture(bool v) { flagReverseTexture = v; }
    void setCoefDist(float c) { coefDist = c; }
    void setFlagDeform(bool d) { catDeform = d; }


protected:
    GLProgram *vp;
    GLProgram *fp;

    GLuint l_View, l_Proj, l_Model, l_kd, l_ka, l_ks, l_s, l_C, l_posLum, l_posCam, l_flagTexture, l_time, l_distCoef, l_flagDeform; // location of uniforms

        // location of uniforms

    Texture2D *texture, *textureN;

    float ka, kd, ks, coefDist;
    int s;
    glm::vec3 C;
    bool flagReverseTexture;
    bool catDeform;
    float time = 0.0f;
};

#endif