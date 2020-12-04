#include "LSystem.h"

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
    return m_current;
}

// given the current string, iterate through and draw with the turtle
void LSystem::draw(void) {
    int currentLen = m_current.size();
    for(int i = 0; i < currentLen; i++) {
        switch(m_current[i]){
        case 'L': {
            m_turtle->forward(m_length);
        }
        case '+': {
            // turn left
            m_turtle->turn(m_angle);
        }
        case '-': {
            // turn right
            m_turtle->turn(-m_angle);
        }
        case '\\': {
            // roll left
            m_turtle->roll(m_angle);
        }
        case '/': {
            // roll right
            m_turtle->roll(-m_angle);
        }
        case '^': {
            // pitch up
            m_turtle->pitch(m_angle);
        }
        case '&': {
            // pitch down
            m_turtle->pitch(-m_angle);
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
        if(m_mappings.find(m_current.substr(i, i+1)) != m_mappings.end()) {
            // if mapping from current character found, append mapped value to new string
            replaced.append(m_mappings[m_current.substr(i, i+1)]);
        } else {
            // else, add current character to string
            replaced.append(m_current.substr(i, i+1));
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
