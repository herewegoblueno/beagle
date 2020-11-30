#include "ShaderEvolutionTestingScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "support/camera/Camera.h"

#include "support/Settings.h"
#include "support/scenegraph/SupportCanvas3D.h"
#include "support/lib/ResourceLoader.h"
#include "support/gl/shaders/CS123Shader.h"

#include "support/shapes/Cube.h"
#include "support/shapes/Cone.h"
#include "support/shapes/Sphere.h"
#include "support/shapes/Cylinder.h"
#include "support/shapes/Torus.h"

using namespace CS123::GL;


ShaderEvolutionTestingScene::ShaderEvolutionTestingScene()
{
    loadPhongShader();
    shapeBank.resize(6);
    LODdivisor = -1; //-1 = uninitialized, anything else is initialized (since a scene can have 0 primitives)
    defineShapeBank();
}

ShaderEvolutionTestingScene::~ShaderEvolutionTestingScene()
{
}

void ShaderEvolutionTestingScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void ShaderEvolutionTestingScene::render(SupportCanvas3D *context) {
    setLOD();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Phong pass
    m_phongShader->bind();
    setPhongSceneUniforms(context);
    setLights();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGeometry();
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

}

void ShaderEvolutionTestingScene::setPhongSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void ShaderEvolutionTestingScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
}

void ShaderEvolutionTestingScene::setLights()
{
    int size = lightingInformation.size();
    for (int i = 0; i < size; i++){
        m_phongShader->setLight(lightingInformation[i]);
    }
}

void ShaderEvolutionTestingScene::renderGeometry() {
    int size = primitives.size();
    for (int i = 0; i < size; i++){
        CS123ScenePrimitiveBundle bundle = primitives[i];
        CS123SceneMaterial mat = bundle.primitive.material;
        mat.cDiffuse *= globalData.kd;
        mat.cAmbient *= globalData.ka;
        mat.shininess *= globalData.ks;
        mat.cTransparent *= globalData.kt;

        m_phongShader->setUniform("m", bundle.model);
        m_phongShader->applyMaterial(mat);


        (shapeBank[(int) bundle.primitive.type])->draw();
    }
}

void ShaderEvolutionTestingScene::settingsChanged() {
    defineShapeBank();
}

void ShaderEvolutionTestingScene::setLOD() {
    if (primitiveCount == -1) return; //Scene hasn't finished loading yet
    LODdivisor = pow(primitiveCount, 0.5) - 2; //https://www.desmos.com/calculator/jdgphtltcc (my own func)
    if (LODdivisor < 1) LODdivisor = 1;
    if (LODdivisor > 15) LODdivisor = 15;
}

void ShaderEvolutionTestingScene::defineShapeBank(){
    int p1 = std::floor(settings.shapeParameter1 / std::max(1.f, LODdivisor));
    int p2 = std::floor(settings.shapeParameter2 / std::max(1.f, LODdivisor));
    int p3 = std::floor(settings.shapeParameter3 / std::max(1.f, LODdivisor));
    shapeBank[0] = std::make_unique<Cube>(p1);
    shapeBank[1] = std::make_unique<Cone>(p1, p2);
    shapeBank[2] = std::make_unique<Cylinder>(p1, p2);
    shapeBank[3] = std::make_unique<Torus>(p1, p2, p3);
    shapeBank[4] = std::make_unique<Sphere>(p1, p2);
    shapeBank[5] = std::make_unique<Sphere>(p1, p2); //Speres will substitite for meshes for now
}

