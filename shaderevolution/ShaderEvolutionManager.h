#ifndef SHADEREVOLUTIONMANAGER_H
#define SHADEREVOLUTIONMANAGER_H

#include "mainwindow.h"
#include "AstNodes.h"
#include <random>
#include "support/scenegraph/ShaderEvolutionTestingScene.h"


class MainWindow;

class ShaderEvolutionManager
{
public:
    void init(MainWindow * window);
    MainWindow * m_window;

    std::unique_ptr<GenotypeNode> generateTree(int chanceOfOperator);
    std::minstd_rand rng;
    std::uniform_int_distribution<> changeDist;

    QString m_shaderScenePath;
    void renderTestingScene();
    void mutate(ShaderEvolutionTestingScene * scene);

};

// The global ShaderEvolutionManager object, initialized in
extern ShaderEvolutionManager SEManager;

#endif // SHADEREVOLUTION_H
