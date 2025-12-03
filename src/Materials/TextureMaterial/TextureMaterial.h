

#ifndef _TextureMaterial_
#define _TextureMaterial_

#include "MaterialGL.h"
#include <Texture2D.h>

class TextureMaterial : public MaterialGL {
public:
    TextureMaterial(std::string name = "");

    ~TextureMaterial();

    virtual void render(Node *o);

    virtual void animate(Node *o, const float elapsedTime);

    virtual void displayInterface(){};

    // TP4
    void setPhong(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shiny);
    void setDiffuseTexture(Texture2D *tex);
    void setNormalMap(Texture2D *tex);

protected:
    GLProgram *vp;
    GLProgram *fp;

    GLuint l_View, l_Proj, l_Model, l_Temps,
        l_posLum, l_color, l_posCam, 
        l_texture, l_texture2, l_textureN,
        l_ka, l_kd, l_ks, l_shiny; // location of uniforms

    Texture2D *textureDiff, *textureNorm;

    glm::vec3 u_ka, u_kd, u_ks;
    float u_shiny;

    float time = 0.0f;
};

#endif