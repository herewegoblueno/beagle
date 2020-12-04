#include "LSystem.h"
#include <iostream>

LSystem::LSystem()
{

}

// set up L system mappings
LSystem::LSystem(std::map<std::string, std::string> & mappings, std::string start, float angle) {
    m_mappings = mappings;
    m_current = start;
    m_turtle = std::make_unique<Turtle>();
    m_length = 1.f;
    m_angle = angle;

}

// generate an L system string based off number of times to replace
std::string LSystem::generate(int replacements) {
    for(int i = 0; i < replacements; i++) {
        m_length *= 0.5f;
        replace();
    }
    std::cout << m_current << std::endl;

    return m_current;
}

// given the current string, iterate through and draw with the turtle
void LSystem::draw(void) {
    // std::cout << "we finna draw!" << std::endl;
    int currentLen = m_current.size();
    for(int i = 0; i < currentLen; i++) {
        switch(m_current[i]){
        case 'F': {
            m_turtle->forward(m_length);
            break;
        }
        case '+': {
            // turn left
            m_turtle->turn(m_angle);
            break;
        }
        case '-': {
            // turn right
            m_turtle->turn(-m_angle);
            break;
        }
        case '\\': {
            // roll left
            m_turtle->roll(m_angle);
            break;
        }
        case '/': {
            // roll right
            m_turtle->roll(-m_angle);
            break;
        }
        case '^': {
            // pitch up
            m_turtle->pitch(m_angle);
            break;
        }
        case '&': {
            // pitch down
            m_turtle->pitch(-m_angle);
            break;
        }
        case '[': {
            // push turtle position
            m_turtle->push();
            break;
        }
        case ']': {
            // push turtle position
            m_turtle->pop();
            break;
        }
        default: {
            // do nothing
        }
        }
    }
}

void LSystem::replace() {
    std::string replaced;
    int currentLen = m_current.size();
    for(int i = 0; i < currentLen; i++) {
        // check if there is a mapping from current character in string to another string
        if(m_mappings.find(m_current.substr(i, 1)) != m_mappings.end()) {
            // if mapping from current character found, append mapped value to new string
            replaced.append(m_mappings[m_current.substr(i, 1)]);
        } else {
            // else, add current character to string
            replaced.append(m_current.substr(i, 1));
        }
    }
    // set current to updated string
    m_current = replaced;

}

std::vector<glm::vec3> LSystem::getStartingPoints() {
    return m_turtle->getStartingCoords();
}

std::vector<glm::vec3> LSystem::getEndingPoints() {
    return m_turtle->getEndingCoords();
}
