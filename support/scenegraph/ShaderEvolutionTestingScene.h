#ifndef SHADEREVOLUTIONTESTINGSCENE_H
#define SHADEREVOLUTIONTESTINGSCENE_H


#include "OpenGLScene.h"

#include <memory>
#include <vector>
#include "support/shapes/Shape.h"
#include "shaderevolution/AstNodes.h"


namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class Texture2D;
}}


class ShaderEvolutionTestingScene : public OpenGLScene {
public:
    ShaderEvolutionTestingScene();
    virtual ~ShaderEvolutionTestingScene();

    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;

    void initializeShaders();

private:

    void setShaderSceneUniforms(SupportCanvas3D *context);
    void setLights();
    void defineShapeBank();
    void setLOD();
    void drawPrimitiveWithShader(int shapeIndex, glm::mat4x4 modelMat, CS123SceneMaterial mat, Shape *shape, SupportCanvas3D *c);
    float calculateTime();

    std::vector<std::unique_ptr<Shape>> shapeBank;
    std::vector<std::unique_ptr<CS123::GL::CS123Shader>> shader_bank;
    std::vector<std::unique_ptr<GenotypeNode>> genotype_bank;
    CS123::GL::CS123Shader *current_shader;

    float LODdivisor;
    long startTime;

};


#endif // SHADEREVOLUTIONTESTINGSCENE_H
