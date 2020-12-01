#ifndef SHADEREVOLUTIONMANAGER_H
#define SHADEREVOLUTIONMANAGER_H

#include "mainwindow.h"

class MainWindow;

class ShaderEvolutionManager
{
public:
    ShaderEvolutionManager(MainWindow * window);
    MainWindow * m_window;

    QString m_shaderScenePath;
    void renderTestingScene();
    void mutate();

};

#endif // SHADEREVOLUTION_H
