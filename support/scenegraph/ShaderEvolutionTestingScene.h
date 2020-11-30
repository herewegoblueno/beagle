#ifndef SHADEREVOLUTIONTESTINGSCENE_H
#define SHADEREVOLUTIONTESTINGSCENE_H


#include "OpenGLScene.h"

#include <memory>
#include <vector>
#include "support/shapes/Shape.h"


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

    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);


private:

    void loadPhongShader();

    void setPhongSceneUniforms(SupportCanvas3D *context);
    void setMatrixUniforms(CS123::GL::Shader *shader, SupportCanvas3D *context);
    void setLights();
    void renderGeometry();
    void defineShapeBank();
    void setLOD();

    std::vector<std::unique_ptr<Shape>> shapeBank;
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;

    float LODdivisor;

};


#endif // SHADEREVOLUTIONTESTINGSCENE_H
