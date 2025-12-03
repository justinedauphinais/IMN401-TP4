
#include "TextureMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

TextureMaterial::TextureMaterial(std::string name) : MaterialGL(name) {

    vp = new GLProgram(MaterialPath + "TextureMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
    fp = new GLProgram(MaterialPath + "TextureMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);

    m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
    m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

    l_View = glGetUniformLocation(vp->getId(), "View");
    l_Proj = glGetUniformLocation(vp->getId(), "Proj");
    l_Model = glGetUniformLocation(vp->getId(), "Model");
    l_Temps = glGetUniformLocation(vp->getId(), "temps");
    l_posLum = glGetUniformLocation(vp->getId(), "posLum");
    l_color = glGetUniformLocation(vp->getId(), "color");
    l_posCam = glGetUniformLocation(vp->getId(), "posCam");

    l_texture = glGetUniformLocation(fp->getId(), "textureDiffuse");
    l_textureN = glGetUniformLocation(fp->getId(), "textureN");

    l_ka = glGetUniformLocation(fp->getId(), "ka");
    l_kd = glGetUniformLocation(fp->getId(), "kd");
    l_ks = glGetUniformLocation(fp->getId(), "ks");
    l_shiny = glGetUniformLocation(fp->getId(), "shiny");
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::render(Node *o) {

    m_ProgramPipeline->bind();

    o->drawGeometry(GL_TRIANGLES);
    m_ProgramPipeline->release();
}

void TextureMaterial::animate(Node *o, const float elapsedTime) {

    /**********************************************
    TP 2 - A completer
    Calculer et Transmettre les matrices Model View et Proj au shaders
    - Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
    - Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv
    ***********************************************/

    if (elapsedTime < 20) time += elapsedTime / 1000;

    glm::mat4 model = o->frame()->getModelMatrix();
    glm::mat4 view = scene->camera()->getViewMatrix();
    glm::mat4 projection = scene->camera()->getProjectionMatrix();

    const int progID = vp->getId();
    if (l_Model >= 0) glProgramUniformMatrix4fv(progID, l_Model, 1, GL_FALSE, glm::value_ptr(model));
    if (l_View >= 0) glProgramUniformMatrix4fv(progID, l_View, 1, GL_FALSE, glm::value_ptr(view));
    if (l_Proj >= 0) glProgramUniformMatrix4fv(progID, l_Proj, 1, GL_FALSE, glm::value_ptr(projection));

    if (l_Temps >= 0) glProgramUniform1f(progID, l_Temps, time);
    if (l_color >= 0) glProgramUniform3f(progID, l_color, 1.0f, 0.0f, 0.0f);

    // Position lumière
    Node *Lumiere = scene->getNode("L");

    glm::vec3 P = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 positionLumiere = Lumiere->frame()->convertPtTo(P, o->frame());

    // Position cam
    Camera *Cam = scene->camera();
    glm::vec3 PCam = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 positionCam = Cam->frame()->convertPtTo(PCam, o->frame());

    if (l_posLum >= 0) glProgramUniform3f(progID, l_posLum, positionLumiere.x, positionLumiere.y, positionLumiere.z);
    if (l_posCam >= 0) glProgramUniform3f(progID, l_posCam, positionCam.x, positionCam.y, positionCam.z);

    if (l_texture >= 0) glProgramUniformHandleui64ARB(fp->getId(), l_texture, textureDiff->getHandle());
    if (l_textureN >= 0) glProgramUniformHandleui64ARB(fp->getId(), l_textureN, textureNorm->getHandle());

    // Phong parameters
    if (l_ka >= 0) glProgramUniform3f(fp->getId(), l_ka, u_ka.x, u_ka.y, u_ka.z);
    if (l_kd >= 0) glProgramUniform3f(fp->getId(), l_kd, u_kd.x, u_kd.y, u_kd.z);
    if (l_ks >= 0) glProgramUniform3f(fp->getId(), l_ks, u_ks.x, u_ks.y, u_ks.z);
    if (l_shiny >= 0) glProgramUniform1f(fp->getId(), l_shiny, u_shiny);
}

void TextureMaterial::setPhong(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shiny) {
    u_ka = ka;
    u_kd = kd;
    u_ks = ks;
    u_shiny = shiny;
}

void TextureMaterial::setDiffuseTexture(Texture2D *tex) {
    textureDiff = tex;
}

void TextureMaterial::setNormalMap(Texture2D *tex) {
    textureNorm = tex;
}
