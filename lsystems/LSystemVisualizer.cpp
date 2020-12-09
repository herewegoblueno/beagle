#include "LSystemVisualizer.h"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include "support/Settings.h"


LSystemVisualizer::LSystemVisualizer()
{
    // test map for trees
    // std::map<std::string, std::string> alphabet;
    // alphabet.insert(std::pair<std::string, std::string>("F", "FF+[+F-F-F]-[-F+F+F]"));
    // make L System
    // m_LSystem = std::make_unique<LSystem>(alphabet, "F", M_PI/6.f);
    m_LSystem = std::make_unique<LSystem>(LSystemUtils::getMap(settings.lSystemType), LSystemUtils::getStart(settings.lSystemType), LSystemUtils::getAngle(settings.lSystemType));
    m_LSystem->generate(settings.numRecursions);
    m_LSystem->draw();
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
    // std::cout << "index " << index << " start " << start.y << " end " << end.y << std::endl;
    // std::cout << "index " << index << " x start " << start.x << " end " << end.x << std::endl;
    // std::cout << "index " << index << " z start " << start.z << " end " << end.z << std::endl;

    // position to translate to
    glm::vec3 pos = 0.5f * (start + end);
    // scaling - y direction, by length of vector
    glm::vec3 scale;
    scale.y = glm::length(end - start);
    scale.x = 0.025;
    scale.z = 0.025;
    // rotate to the direction vector
    // glm::vec3 xaxis = glm::normalize(glm::cross(glm::vec3(0, 1, 0), end - start));
    // glm::vec3 yaxis = glm::normalize(glm::cross(end - start, xaxis));

    // glm::mat4x4 rotation = glm::mat4x4(xaxis.x, yaxis.x, (end - start).x, 0,
                                    //   xaxis.y, yaxis.y, (end - start).y, 0,
                                     //  xaxis.z, yaxis.z, (end - start).z, 0,
                                     //  0, 0, 0, 1);
    glm::vec3 axis = glm::cross(glm::vec3(0, 1, 0), end - start);
    float sinangle = glm::length(axis)/(glm::length(end - start));
    std::cout << "sin o the angle " << sinangle << std::endl;
    float cosangle = glm::dot(glm::vec3(0, 1, 0), end - start)/(glm::length(end - start));
    axis = glm::normalize(axis);
    std::cout << "arcsin o the angle " << asin(sinangle) << std::endl;
    std::cout << "arccos o the angle " << acos(cosangle) << std::endl;

    // glm::mat4x4 rotation = glm::mat4x4(cosangle + axis.x*axis.x*(1 - cosangle), axis.x*axis.y*(1-cosangle) + axis.z*sinangle, axis.x*axis.z*(1-cosangle) - axis.y*sinangle, 0);
    // return glm::mat4x4(1);
    // return rotation;
    // case where no rotation needed
    if(abs(glm::normalize(end - start).y - 1.f) <= 0.0001) {
        return glm::translate(pos)*glm::scale(scale);
    }
    if(acos(cosangle) > asin(sinangle)) {
        return glm::translate(pos)*glm::rotate((float)acos(cosangle), axis)*glm::scale(scale);
    }
    return glm::translate(pos)*glm::rotate((float)asin(sinangle), axis)*glm::scale(scale);



}
