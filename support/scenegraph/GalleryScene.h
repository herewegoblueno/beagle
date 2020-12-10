#ifndef GALLERYSCENE_H
#define GALLERYSCENE_H

#include "OpenGLScene.h"

#include <memory>
#include <vector>
#include "support/shapes/Shape.h"
#include "lsystems/LSystemVisualizer.h"
#include "LSystemTreeScene.h"

// basically the L System tree scene but copied


namespace CS123 { namespace GL {

    class Shader;
    class CS123Shader;
    class Texture2D;
}}



class GalleryScene : public OpenGLScene {
public:
    GalleryScene();
    virtual ~GalleryScene();
    virtual void render(SupportCanvas3D *context) override;
    virtual void settingsChanged() override;

    // Use this method to set an internal selection, based on the (x, y) position of the mouse
    // pointer.  This will be used during the "modeler" lab, so don't worry about it for now.
    void setSelection(int x, int y);
private:

    void loadPhongShader();
    void loadWireframeShader();
    void loadNormalsShader();
    void loadNormalsArrowShader();

    void setPhongSceneUniforms(SupportCanvas3D *context);
    void setMatrixUniforms(CS123::GL::Shader *shader, SupportCanvas3D *context);
    void setLights();
    void renderGeometry(RENDERING_PASS pass);
    void defineShapeBank();
    void setLOD();
    void makeLSystemVisualizer(int index);

    void makePotPosns();
    void setUpLights();
    void drawTheScene();
    void drawGround();
    void drawPots();
    void drawBG();

    std::vector<std::unique_ptr<Shape>> shapeBank;
    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::Shader> m_wireframeShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsShader;
    std::unique_ptr<CS123::GL::Shader> m_normalsArrowShader;
    std::unique_ptr<LSystemVisualizer> m_lSystemViz;

    std::vector<glm::vec3> m_potPosns;

    float LODdivisor;

    // could be useful for determining number of shapes related to trees?
    int numTreePrims;
};



#endif // GALLERYSCENE_H
