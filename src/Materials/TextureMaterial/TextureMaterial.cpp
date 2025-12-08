
#include "TextureMaterial.h"
#include "Node.h"
#include <glfw3.h>
#include <glm/gtc/type_ptr.hpp>

TextureMaterial::TextureMaterial(std::string name) : MaterialGL(name), name(name), kd(0.7), ka(0.4), ks(5.0), s(100), flagReverseTexture(false), coefDist(0.1), flagDeform(false) {

    vp = new GLProgram(MaterialPath + "TextureMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "TextureMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");

    C = glm::vec3(1.0, 1.0, 1.0); // couleur de la lumière

    l_kd = glGetUniformLocation(fp->getId(), "kd");
    l_ka = glGetUniformLocation(fp->getId(), "ka");
    l_ks = glGetUniformLocation(fp->getId(), "ks");
    l_s = glGetUniformLocation(fp->getId(), "s");
    l_C = glGetUniformLocation(fp->getId(), "C");

    l_posLum = glGetUniformLocation(vp->getId(), "posLum");
    l_posCam = glGetUniformLocation(vp->getId(), "posCam");
    l_flagTexture = glGetUniformLocation(vp->getId(), "flagText");

    l_time = glGetUniformLocation(vp->getId(), "time");
    l_distCoef = glGetUniformLocation(vp->getId(), "distCoef");
    l_flagDeform = glGetUniformLocation(vp->getId(), "flagDeform");
}

void TextureMaterial::setDiffuseTexture(Texture2D *texture) {
    this->texture = texture;
}

void TextureMaterial::setNormalMap(Texture2D *texture) {
    this->textureN = texture;
}

void TextureMaterial::setPhong(float kd, float ka, float ks, int s) {
    this->kd = kd;
    this->ka = ka;
    this->ks = ks;
    this->s = s;
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    glBindTextureUnit(0, texture->getId());
    glBindTextureUnit(2, textureN->getId());

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void TextureMaterial::animate(Node *o, const float elapsedTime) {

    // if (o->getName() == "Bunny") {
    //     glm::vec3 objectPos = o->frame()->getModelMatrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);
    //     std::cout << "Bunny position: (" << objectPos.x << ", " << objectPos.y << ", " << objectPos.z << ")" << std::endl;
    // }
    float time = glfwGetTime();
    // std::cout << time; DEBUG
    glProgramUniform1f(vp->getId(), l_time, time);

    glProgramUniform1f(vp->getId(), l_distCoef, coefDist);

    Camera *camera = Scene::getInstance()->camera();
    glProgramUniformMatrix4fv(vp->getId(), l_View, 1, false, glm::value_ptr(camera->getViewMatrix()));
    glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, false, glm::value_ptr(camera->getProjectionMatrix()));
    glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, false, glm::value_ptr(o->frame()->getModelMatrix()));

    glProgramUniform1f(fp->getId(), l_kd, kd);
    glProgramUniform1f(fp->getId(), l_ka, ka);
    glProgramUniform1f(fp->getId(), l_ks, ks);
    glProgramUniform1i(fp->getId(), l_s, s);
    glProgramUniform3f(fp->getId(), l_C, C.r, C.g, C.b);
    glProgramUniform1i(vp->getId(), l_flagTexture, flagReverseTexture ? 1 : 0);

    glm::vec3 pLum = glm::vec3(0.0, 0.0, 0.0);
    Node *L = Scene::getInstance()->getNode("L");
    pLum = L->frame()->convertPtTo(pLum, o->frame());
    glProgramUniform3f(vp->getId(), l_posLum, pLum.x, pLum.y, pLum.z);

    glm::vec3 pCam = glm::vec3(0.0, 0.0, 0.0);
    pCam = camera->frame()->convertPtTo(pCam, o->frame());
    glProgramUniform3f(vp->getId(), l_posCam, pCam.x, pCam.y, pCam.z);

    if (flagDeform) {
        glProgramUniform1i(vp->getId(), l_flagDeform, 1);
    }
}