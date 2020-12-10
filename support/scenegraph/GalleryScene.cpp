#include "GalleryScene.h"

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

#include "glm/gtx/transform.hpp"
#include "time.h"


#include <iostream>
using namespace CS123::GL;


GalleryScene::GalleryScene()
{
    // random numbers based off time
    srand((unsigned)time(NULL));
    loadPhongShader();
    numTreePrims = -1;
    shapeBank.resize(6);
    LODdivisor = -1; //-1 = uninitialized, anything else is initialized (since a scene can have 0 primitives)
    defineShapeBank();

    setUpLights();
    makePotPosns();
    // to do: save the settings before i mess with them
    drawTheScene();
}


GalleryScene::~GalleryScene()
{
}

void::GalleryScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

// version with just phong shader - is this where we add in the shader evolution shaders?
void GalleryScene::render(SupportCanvas3D *context) {
    setLOD();
    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Phong pass
    m_phongShader->bind();
    setPhongSceneUniforms(context);
    setLights();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    renderGeometry(PHONG);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();


}

void GalleryScene::setPhongSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void GalleryScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix());
}

void GalleryScene::setLights()
{
    int size = lightingInformation.size();
    for (int i = 0; i < size; i++){
        m_phongShader->setLight(lightingInformation[i]);
    }
}

void GalleryScene::renderGeometry(RENDERING_PASS pass) {
    int size = primitives.size();
    for (int i = 0; i < size; i++){
        CS123ScenePrimitiveBundle bundle = primitives[i];
        CS123SceneMaterial mat = bundle.primitive.material;
        mat.cDiffuse *= globalData.kd;
        mat.cAmbient *= globalData.ka;
        mat.shininess *= globalData.ks;
        mat.cTransparent *= globalData.kt;

        switch (pass) {
            case PHONG:
                m_phongShader->setUniform("m", bundle.model);
                m_phongShader->applyMaterial(mat);
                break;
            case WIREFRAME:
                m_wireframeShader->setUniform("m", bundle.model);
                break;
            case NORMAL_LINE:
                m_normalsShader->setUniform("m", bundle.model);
                break;
            case NORMAL_ARROW:
                m_normalsArrowShader->setUniform("m", bundle.model);
                break;
        }


        (shapeBank[(int) bundle.primitive.type])->draw();
    }
}

void GalleryScene::drawTheScene() {
    primitives.clear();
    // make a new L System visualizer
    int oldRecurs = settings.numRecursions;
    int oldType = settings.lSystemType;
    bool oldLeaves = settings.hasLeaves;

    int numTrees = m_potPosns.size();
    for(int i = 0; i < numTrees; i++) {
        // randomize settings
        // get recursive depth between 2 and 4
        settings.numRecursions = 2 + rand()%3;
        // randomize type of tree (0-5)
        settings.lSystemType = rand()%6;
        // if seaweed, cap depth at 3 bc it lags (at least on my computer)
        if(settings.lSystemType == 1 && settings.numRecursions > 3) {
            settings.numRecursions = 3;
        }

        m_lSystemViz = std::make_unique<LSystemVisualizer>();
        makeLSystemVisualizer(i);
    }
    numTreePrims = primitives.size();

    drawPots();
    drawGround();
    // draw large shape to use as background
    drawBG();

    settings.numRecursions = oldRecurs;
    settings.lSystemType = oldType;
    settings.hasLeaves = oldLeaves;
}

void GalleryScene::drawGround() {
    // make a large, flat cube
    glm::vec3 pos = glm::vec3(0, -1.25f, 0);
    glm::vec3 scale = glm::vec3(7, 0.04f, 7);

    CS123SceneMaterial material;
    material.clear();
    material.cAmbient.r = 0.13f;
    material.cAmbient.g = 0.1f;
    material.cAmbient.b = 0.05f;
    material.cDiffuse.r = 0.70f;
    material.cDiffuse.g = 0.5f;
    material.cDiffuse.b = 0.2f;

    CS123ScenePrimitive theGround = {PrimitiveType::PRIMITIVE_CUBE, std::string(), material};
    addPrimitive(theGround, glm::translate(pos)*glm::scale(scale));
}

void GalleryScene::drawBG() {
    // make a large, flat cube off in the distance
    glm::vec3 pos = glm::vec3(0, 0, -10);
    glm::vec3 scale = glm::vec3(30, 30, 0.04f);

    // make it sky colored
    CS123SceneMaterial material;
    material.clear();
    material.cAmbient.r = 0.2f;
    material.cAmbient.g = 0.35f;
    material.cAmbient.b = 0.45f;
    material.cDiffuse.r = 0.55f;
    material.cDiffuse.g = 0.6f;
    material.cDiffuse.b = 1.f;

    CS123ScenePrimitive theSky = {PrimitiveType::PRIMITIVE_CUBE, std::string(), material};
    addPrimitive(theSky, glm::translate(pos)*glm::scale(scale));
}

void GalleryScene::settingsChanged() {
    // make a new LSystem with the current settings
    drawTheScene();
    renderGeometry(PHONG);
}

// this could probably be a constant but the syntax is slightly less ugly this way
void::GalleryScene::makePotPosns() {
    m_potPosns.push_back(glm::vec3(2, -1.085, 2));
    m_potPosns.push_back(glm::vec3(1.5f, -1.085, 0));
    m_potPosns.push_back(glm::vec3(0, -1.085, -2));
    m_potPosns.push_back(glm::vec3(-1.5f, -1.085, 0));
    m_potPosns.push_back(glm::vec3(-2, -1.085, 2));

}

// adds all pots to scene
void::GalleryScene::drawPots() {
    int numPots = m_potPosns.size();
    glm::vec3 scale = glm::vec3(0.7f, 0.4f, 0.7f);
    glm::mat4x4 scaleMat = glm::scale(scale);
    CS123SceneMaterial material;
    material.clear();
    material.cAmbient.g = 0.1f;
    material.cAmbient.b = 0.05f;
    material.cDiffuse.g = 0.7f;
    material.cDiffuse.b = 0.5f;

    CS123ScenePrimitive pot = {PrimitiveType::PRIMITIVE_CYLINDER, std::string(), material};

    for(int i = 0; i < numPots; i++) {
        addPrimitive(pot, glm::translate(m_potPosns.at(i))*scaleMat);
    }
}

void GalleryScene::setLOD() {
    if (primitiveCount == -1) return; //Scene hasn't finished loading yet
    LODdivisor = pow(primitiveCount, 0.5) - 2; //https://www.desmos.com/calculator/jdgphtltcc (my own func)
    if (LODdivisor < 1) LODdivisor = 1;
    if (LODdivisor > 15) LODdivisor = 15;
}

void GalleryScene::defineShapeBank(){
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

void GalleryScene::setUpLights() {
    // add some lights to the scene
    // to do: make the lights in a helper
    CS123SceneLightData light = {0, LightType::LIGHT_POINT, glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 1), glm::vec4(0, 1, 3, 0)};
    CS123SceneLightData light2 = {0, LightType::LIGHT_POINT, glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 1), glm::vec4(0, 1, -3, 0)};
    CS123SceneLightData light3 = {0, LightType::LIGHT_POINT, glm::vec4(1, 1, 1, 1), glm::vec3(0, 0, 0.05), glm::vec4(0, 5, 0, 0)};

    CS123SceneGlobalData globalLSys = {0.7f, 0.6f, 0.1f, 1};
    setGlobal(globalLSys);
    lightingInformation.push_back(light);
    lightingInformation.push_back(light2);
    lightingInformation.push_back(light3);

    setLights();
}


void GalleryScene::makeLSystemVisualizer(int index) {

    glm::mat4x4 outerTrans = glm::translate(glm::vec3(m_potPosns.at(index).x, 0, m_potPosns.at(index).z));
    // rotate middle pot 90 degrees so if a 2D tree, faces viewer
    if(index == 2) {
        outerTrans = outerTrans * glm::rotate((float)M_PI/4.f, glm::vec3(0, 1, 0));
    }

   int numCyls = m_lSystemViz->getNumCyls();
    CS123SceneMaterial material;
    material.clear();
    material.cAmbient.r = 0.13f;
    material.cAmbient.g = 0.1f;
    material.cAmbient.b = 0.05f;
    material.cDiffuse.r = 0.70f;
    material.cDiffuse.g = 0.5f;
    material.cDiffuse.b = 0.2f;

    material.cSpecular.r = material.cSpecular.g = material.cSpecular.b = 0.3;
    material.shininess = 12;
    // if seaweed, make material green
    if(settings.lSystemType == 1) {
        material.cAmbient.r = 0.04f;
        material.cAmbient.g = 0.2f;
        material.cAmbient.b = 0.04f;
        material.cDiffuse.r = 0.2f;
        material.cDiffuse.b = 0.4f;
        // also seaweed can't have leaves
        settings.hasLeaves = false;
    } else {
        settings.hasLeaves = true;
    }
    // add all cylinders to scene
    CS123ScenePrimitive cyl = {PrimitiveType::PRIMITIVE_CYLINDER, std::string(), material};
    for(int i = 0; i < numCyls; i++) {
        // make a new scene primitive
        addPrimitive(cyl, outerTrans*m_lSystemViz->getTransformationMatrix(i));

    }

    // if there are leaves, add the leaves to the scene
    if(settings.hasLeaves) {
        CS123SceneMaterial leafMaterial;
        leafMaterial.clear();
        leafMaterial.cAmbient.r = 0.05f;
        leafMaterial.cAmbient.g = 0.5f;
        leafMaterial.cAmbient.b = 0.05f;
        leafMaterial.cDiffuse.r = 0.05f;
        leafMaterial.cDiffuse.g = 0.3f;
        leafMaterial.cDiffuse.b = 0.2f;

        leafMaterial.cSpecular.r = leafMaterial.cSpecular.g = leafMaterial.cSpecular.b = 0.3;
        leafMaterial.shininess = 12;

        CS123ScenePrimitive leafCyl = {PrimitiveType::PRIMITIVE_CYLINDER, std::string(), leafMaterial};
        int numLeaves = m_lSystemViz->getNumLeaves();
        for(int i = 0; i < numLeaves; i++) {
            addPrimitive(leafCyl, outerTrans*m_lSystemViz->getLeafMatrix(i));
        }

    }

    settings.hasLeaves = true;


}
