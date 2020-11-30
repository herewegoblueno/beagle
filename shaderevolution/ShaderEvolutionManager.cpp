#include "ShaderEvolutionManager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>


ShaderEvolutionManager::ShaderEvolutionManager(MainWindow * window):
    m_window(window)
{

}


QString ShaderEvolutionManager::getShaderScenePath(){
    if (m_shaderScenePath.isNull()){
        QMessageBox::information((QWidget *)m_window, "Help us out", "Look for the shaderTestScene.xml file");
        m_shaderScenePath = QFileDialog::getOpenFileName((QWidget *)m_window, QString(), "/course/cs123/data/");
    }
    return m_shaderScenePath;
}

void ShaderEvolutionManager::mutate(){
    std::cout << "Yay, this did a thing" << std::endl;
}

void ShaderEvolutionManager::renderTestingScene(){
    m_window->fileOpen(getShaderScenePath());
}
