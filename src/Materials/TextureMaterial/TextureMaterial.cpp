
#include "TextureMaterial.h"
#include "Node.h"
#include <glfw3.h>
#include <glm/gtc/type_ptr.hpp>

TextureMaterial::TextureMaterial(std::string name) : MaterialGL(name), name(name) {

    vp = new GLProgram(MaterialPath + "TextureMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "TextureMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");

    l_kd = glGetUniformLocation(fp->getId(), "kd");
    l_ka = glGetUniformLocation(fp->getId(), "ka");
    l_ks = glGetUniformLocation(fp->getId(), "ks");
    l_s = glGetUniformLocation(fp->getId(), "s");

    l_posLum = glGetUniformLocation(vp->getId(), "posLum");
    l_posCam = glGetUniformLocation(vp->getId(), "posCam");
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    glBindTextureUnit(0, textureDiffuse->getId());
    glBindTextureUnit(2, textureNormale->getId());

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void TextureMaterial::animate(Node *o, const float elapsedTime) {
    Camera *camera = scene->camera();

    // MVC
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 projMatrix = camera->getProjectionMatrix();
    glm::mat4 modelMatrix = o->frame()->getModelMatrix();

    glProgramUniformMatrix4fv(vp->getId(), l_View, 1, false, glm::value_ptr(viewMatrix));
    glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, false, glm::value_ptr(projMatrix));
    glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, false, glm::value_ptr(modelMatrix));

    // Phong
    glProgramUniform1f(fp->getId(), l_kd, kd);
    glProgramUniform1f(fp->getId(), l_ka, ka);
    glProgramUniform1f(fp->getId(), l_ks, ks);
    glProgramUniform1i(fp->getId(), l_s, s);

    // Position de la lumière
    glm::vec3 pLum = glm::vec3(0.0, 0.0, 0.0);

    Node *L = scene->getNode("L");
    pLum = L->frame()->convertPtTo(pLum, o->frame());

    glProgramUniform3f(vp->getId(), l_posLum, pLum.x, pLum.y, pLum.z);

    // Position de la caméra
    glm::vec3 pCam = glm::vec3(0.0, 0.0, 0.0);
    pCam = camera->frame()->convertPtTo(pCam, o->frame());

    glProgramUniform3f(vp->getId(), l_posCam, pCam.x, pCam.y, pCam.z);
}

void TextureMaterial::setDiffuseTexture(Texture2D *texture) {
    this->textureDiffuse = texture;
}

void TextureMaterial::setNormalMap(Texture2D *texture) {
    this->textureNormale = texture;
}

void TextureMaterial::setPhong(float kd, float ka, float ks, int s) {
    this->kd = kd;
    this->ka = ka;
    this->ks = ks;
    this->s = s;
}