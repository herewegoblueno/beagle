#include "LSystemVisualizer.h"
#include "glm/gtx/transform.hpp"


LSystemVisualizer::LSystemVisualizer()
{
    // test map for trees
    std::map<std::string, std::string> alphabet;
    alphabet.insert(std::pair<std::string, std::string>("F", "FF+[+F-F-F]-[-F+F+F]"));
    // make L System
    m_LSystem = std::make_unique<LSystem>(alphabet, "F", M_PI/6.f);
    // get coords
    m_startingPoints = m_LSystem->getStartingPoints();
    m_endingPoints = m_LSystem->getEndingPoints();
}

int LSystemVisualizer::getNumCyls() {
    return m_startingPoints.size();
}

glm::mat4x4 LSystemVisualizer::getTransformationMatrix(int index) {
    glm::vec3 start = m_startingPoints.at(index);
    glm::vec3 end = m_endingPoints.at(index);
    // position to translate to
    glm::vec3 pos = 0.5f * (start + end);
    // scaling - y direction, by length of vector
    glm::vec3 scale;
    scale.y = glm::length(start - end);
    scale.x = 0.05;
    scale.z = 0.05;
    // rotate to the direction vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::vec3(0, 1, 0), end - start));
    glm::vec3 yaxis = glm::normalize(glm::cross(end - start, xaxis));

    glm::mat4x4 rotation = glm::mat4x4(xaxis.x, yaxis.x, (end - start).x, 0,
                                       xaxis.y, yaxis.y, (end - start).y, 0,
                                       xaxis.z, yaxis.z, (end - start).z, 0,
                                       0, 0, 0, 1);

    return glm::translate(pos)*rotation*glm::scale(scale);



}
