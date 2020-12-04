#ifndef LSYSTEMVISUALIZER_H
#define LSYSTEMVISUALIZER_H

#include "LSystem.h"

class LSystemVisualizer
{
public:
    LSystemVisualizer();
    int getNumCyls(void);
    glm::mat4x4 getTransformationMatrix(int index);
private:
    std::unique_ptr<LSystem> m_LSystem;
    std::vector<glm::vec3> m_startingPoints;
    std::vector<glm::vec3> m_endingPoints;
};

#endif // LSYSTEMVISUALIZER_H
