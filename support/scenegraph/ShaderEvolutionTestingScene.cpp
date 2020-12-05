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

#include <chrono>
using namespace std::chrono;
using namespace CS123::GL;

#include "shaderevolution/ShaderConstructor.h"
#include "shaderevolution/ShaderEvolutionManager.h"
#include <iostream>
#include "shaderevolution/MutationFactory.h"

int ShaderEvolutionTestingScene::numberOfTestShaders = 6;

ShaderEvolutionTestingScene::ShaderEvolutionTestingScene():
    LODdivisor(-1), //-1 = uninitialized, anything else is initialized (since a scene can have 0 primitives)
    startTime(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count())
{
    initializeGenotypes();
    shapeBank.resize(6);
    defineShapeBank();
}

ShaderEvolutionTestingScene::~ShaderEvolutionTestingScene()
{
}


void ShaderEvolutionTestingScene::initializeGenotypes() {
    genotype_bank.clear();
    for (int i = 0; i < ShaderEvolutionTestingScene::numberOfTestShaders; i ++){
        genotype_bank.push_back(std::make_unique<ShaderGenotype>(SEManager.generateTree()));
    }
    constructShaders();
}

void ShaderEvolutionTestingScene::constructShaders() {
    shader_bank.clear();

    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/shaders/shaderevolutionshader.vert");
    for (int i = 0; i < ShaderEvolutionTestingScene::numberOfTestShaders; i ++){
        std::string src = genotype_bank[i]->root->stringify();
        std::string fragmentSource = ShaderConstructor::genShader(src);
        shader_bank.push_back(std::make_unique<CS123Shader>(vertexSource, fragmentSource));
    }
}

void ShaderEvolutionTestingScene::mutateGenotypes(){
    for (int i = 0; i < ShaderEvolutionTestingScene::numberOfTestShaders; i ++){
        mutate(genotype_bank[i]->root.get(), nullptr, genotype_bank[i]->currentGeneration);
        genotype_bank[i]->currentGeneration ++;
    }
    constructShaders();
}

void ShaderEvolutionTestingScene::render(SupportCanvas3D *context) {
    setLOD();
    glClearColor(0.2, 0.2, 0.2, 0.3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int size = primitives.size();
    for (int i = 0; i < size; i++){
        CS123ScenePrimitiveBundle bundle = primitives[i];
        CS123SceneMaterial mat = bundle.primitive.material;
        mat.cDiffuse *= globalData.kd;
        mat.cAmbient *= globalData.ka;
        mat.shininess *= globalData.ks;
        mat.cTransparent *= globalData.kt;

        drawPrimitiveWithShader(i, bundle.model, mat, (shapeBank[(int) bundle.primitive.type]).get(), context);
    }
    context->update();
}

void ShaderEvolutionTestingScene::drawPrimitiveWithShader (int shapeIndex, glm::mat4x4 modelMat, CS123SceneMaterial mat, Shape *shape, SupportCanvas3D *c){
    current_shader = shader_bank[shapeIndex].get();

    current_shader->bind();
    setShaderSceneUniforms(c);
    setLights();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    current_shader->setUniform("m", modelMat);
    current_shader->setUniform("time", calculateTime());
    current_shader->applyMaterial(mat);
    shape->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    current_shader->unbind();
}

void ShaderEvolutionTestingScene::setShaderSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    current_shader->setUniform("useLighting", settings.useLighting);
    current_shader->setUniform("p" , camera->getProjectionMatrix());
    current_shader->setUniform("v", camera->getViewMatrix());
}

void ShaderEvolutionTestingScene::setLights()
{
    int size = lightingInformation.size();
    for (int i = 0; i < size; i++){
        current_shader->setLight(lightingInformation[i]);
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
    shapeBank[5] = std::make_unique<Sphere>(p1, p2); //Spheres will substitite for meshes
}

//[-1 1]
float ShaderEvolutionTestingScene::calculateTime(){
    long cur_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    float difference = cur_time - startTime;
    const float pi = M_PI;
    const float frequency = 0.1; // Frequency in Hz
    return sinf(2 * pi * frequency * 0.001 * difference);
}

std::string ShaderEvolutionTestingScene::getShaderSource(int index, bool showAnnotations){
    return genotype_bank[index]->root->stringify(showAnnotations);
}


