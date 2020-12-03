#include "ShaderEvolutionManager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include "NodeDispenser.h"

ShaderEvolutionManager SEManager;

void ShaderEvolutionManager::init(MainWindow * window)
{
    m_window = window;
    maxProbability = 100;
    changeDist = std::uniform_int_distribution<>(1, maxProbability);
}


//ChanceOfOperator [0, 100]
//This will make recursive calls that slowly reduce chanceOfOperator so that the
//basecase of leaf nodes is guaranteed to be met eventually
std::unique_ptr<GenotypeNode> ShaderEvolutionManager::generateTree(int chanceOfOperator){
    //Make choice
    int choice = changeDist(rng);
    std::unique_ptr<GenotypeNode> nodePointer;

    //Get node
    if (choice <= chanceOfOperator) nodePointer = NodeDispenser::getOperationNode();
    else nodePointer = NodeDispenser::getLeafNode();

    //Set up node
    for (int i = 0; i < nodePointer->numberOfChildrenNeeded; i++){
        nodePointer->children.push_back(generateTree(chanceOfOperator - 10));
    }
    return nodePointer;
}

std::unique_ptr<GenotypeNode> ShaderEvolutionManager::generateTree(){
    return generateTree(maxProbability);
}

void ShaderEvolutionManager::renderTestingScene(){
    m_window->fileOpen(":/xmlScenes/xmlScenes/shaderTestingScene.xml");
}


void ShaderEvolutionManager::mutate(ShaderEvolutionTestingScene * scene){
    if (scene != nullptr){
        scene->initializeShaders();
    }
}

