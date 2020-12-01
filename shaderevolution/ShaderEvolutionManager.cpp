#include "ShaderEvolutionManager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>


ShaderEvolutionManager::ShaderEvolutionManager(MainWindow * window):
    m_window(window)
{

}

void ShaderEvolutionManager::mutate(){
    std::cout << "Yay, this did a thing" << std::endl;
}

void ShaderEvolutionManager::renderTestingScene(){
    m_window->fileOpen(":/xmlScenes/xmlScenes/shaderTestingScene.xml");
}
